#include <Piece.h>
#include <string>
#include <vector>
#include <regex>
#include <Vector.h>
#include <parser.h>
#include <Universe.h>

Vector parseChessPosition(const std::string& pos) {
    // Remove specified symbols
    std::string cleanPos;
    for (char c : pos) {
        if (std::isalnum(c) || c == '=') {
            cleanPos += c;
        }
    }

    // Remove promotion symbols (e.g., '=Q', '=q')
    size_t equalPos = cleanPos.find('=');
    if (equalPos != std::string::npos) {
        cleanPos = cleanPos.substr(0, equalPos);
    }

    if (cleanPos.length() < 2) {
        throw std::runtime_error("Invalid position format: " + pos);
    }

    char file = cleanPos[cleanPos.length() - 2];
    char rank = cleanPos[cleanPos.length() - 1];

    int x = std::tolower(file) - 'a';
    int y = 8 - (rank - '0');

    return Vector{x, y};
}

PieceType determinePieceType(const std::string& move) {
    if (move.empty()) return PieceType::NotFound;

    size_t pos = 0;
    // Skip any leading parentheses or other non-letter characters
    while (pos < move.length() && !std::isalpha(move[pos])) {
        pos++;
    }

    if (pos >= move.length()) return PieceType::NotFound;

    char firstChar = move[pos];

    switch (firstChar) {
    case 'K':
        return PieceType::King;
    case 'Q':
        return PieceType::Queen;
    case 'R':
        return PieceType::Rook;
    case 'B':
        return PieceType::Bishop;
    case 'N':
        return PieceType::Knight;
    default:
        // If it's a lowercase letter between 'a' and 'h', it's a pawn move
            if (firstChar >= 'a' && firstChar <= 'h') {
                // You may need additional logic to determine BeforePawn or AfterPawn
                return PieceType::AllPawn;
            } else {
                return PieceType::NotFound;
            }
    }
}


std::vector<std::string> splitMove(const std::string& move, const std::string& delimiter) {
    size_t delimiterPos = move.find(delimiter);
    return {move.substr(0, delimiterPos), move.substr(delimiterPos + delimiter.length())};
}

Vector parseZW(const std::string& zwPart, ColorType currentPlayer) {
    // zwPart format: (wTz) or (-1T3)
    int w = 0, zNum = 0;
    size_t TPos = zwPart.find('T');
    if (TPos != std::string::npos) {
        w = std::stoi(zwPart.substr(1, TPos - 1));
        zNum = std::stoi(zwPart.substr(TPos + 1, zwPart.find(')') - TPos - 1));
        int z = 2 * zNum - (currentPlayer == ColorType::White ? 1 : 0);
        return Vector{0, 0, z, w};
    } else {
        throw std::runtime_error("Invalid ZW format: " + zwPart);
    }
}

Vector parsePositionWithZW(const std::string& posPart, ColorType currentPlayer, int round) {
    int x = 0, y = 0, z = 0, w = 0;
    size_t parenPos = posPart.find('(');
    if (parenPos != std::string::npos) {
        // Parse ZW
        size_t closeParen = posPart.find(')', parenPos);
        if (closeParen == std::string::npos) {
            throw std::runtime_error("Unmatched parenthesis in position: " + posPart);
        }
        Vector zw = parseZW(posPart.substr(parenPos, closeParen - parenPos + 1), currentPlayer);
        z = zw[2];
        w = zw[3];
        // Parse position
        std::string position = posPart.substr(closeParen + 1);
        if (position.empty()) {
            // Handle cases where no position is specified after the parentheses
            // For starting positions, you may need to infer the position from context
            // For this example, we'll throw an error
            throw std::runtime_error("Position missing after ZW notation in move: " + posPart);
        }
        Vector xy = parseChessPosition(position);
        x = xy[0];
        y = xy[1];
    } else {
        // No ZW specified, use default values
        z = 2 * round - (currentPlayer == ColorType::White ? 1 : 0);
        w = 0;
        if (posPart.empty()) {
            throw std::runtime_error("Position missing in move: " + posPart);
        }
        Vector xy = parseChessPosition(posPart);
        x = xy[0];
        y = xy[1];
    }
    return Vector{x, y, z, w};
}


std::vector<Vector> processMove(const std::string& move, int round, ColorType currentPlayer, std::shared_ptr<Universe> universe) {
    int startZ, startW, endZ, endW;
    Vector startPos, endPos;
    std::string trimmedMove = move;

    // Trim leading and trailing whitespace
    trimmedMove.erase(0, trimmedMove.find_first_not_of(" \t\r\n"));
    trimmedMove.erase(trimmedMove.find_last_not_of(" \t\r\n") + 1);

    // Remove any '~' and text after it (e.g., 'a3~ (>L-1)')
    size_t tildePos = trimmedMove.find('~');
    if (tildePos != std::string::npos) {
        trimmedMove = trimmedMove.substr(0, tildePos);
    }

    size_t arrowPos = trimmedMove.find('>');
    if (arrowPos == std::string::npos) {
        // Normal chess notation

        // Check if there is a preceding parenthesis
        size_t parenPos = trimmedMove.find('(');
        if (parenPos == std::string::npos) {
            // No parenthesis
            startW = endW = 0;
            startZ = endZ = 2 * round - (currentPlayer == ColorType::White ? 1 : 0);
        } else {
            // Parenthesis present
            size_t parenEnd = trimmedMove.find(')', parenPos);
            if (parenEnd == std::string::npos) {
                throw std::runtime_error("Unmatched parenthesis in move: " + move);
            }
            Vector zw = parseZW(trimmedMove.substr(parenPos, parenEnd - parenPos + 1), currentPlayer);
            startW = endW = zw[3];
            startZ = endZ = zw[2];
            // Remove the parenthesis from the move notation
            trimmedMove.erase(parenPos, parenEnd - parenPos + 1);
        }

        // Parse the move to extract the destination position and the piece type
        PieceType pieceType = determinePieceType(trimmedMove);
        Vector endXY = parseChessPosition(trimmedMove);

        endPos = {endXY[0], endXY[1], endZ, endW};

        startPos = universe
            ->getTimeline(startW)
            ->getBoardState(startZ)
            ->getStartWithTypeColorDest(pieceType, currentPlayer, endPos);
    } else {
        // Handle '>' or '>>' notation
        std::string delimiter = (trimmedMove.find(">>") != std::string::npos) ? ">>" : ">";
        auto parts = splitMove(trimmedMove, delimiter);
        std::string startPart = parts[0];
        std::string endPart = parts[1];

        startPos = parsePositionWithZW(startPart, currentPlayer, round);
        endPos = parsePositionWithZW(endPart, currentPlayer, round);
    }

    return { startPos, endPos };
}

bool isAnnotation(const std::string& move) {
    // If the move starts with '~' or does not contain any alphabetic characters
    // (excluding 'T' for time), it's likely an annotation
    std::string strippedMove;
    for (char c : move) {
        if (std::isalpha(c) && c != 'T') {
            strippedMove += c;
        }
    }
    return strippedMove.empty();
}

std::vector<std::string> splitMoves(const std::string& moveStr) {
    std::vector<std::string> moves;
    std::string currentMove;
    int parenDepth = 0;

    for (size_t i = 0; i < moveStr.size(); ++i) {
        char c = moveStr[i];

        if (c == '(') {
            parenDepth++;
            currentMove += c;
        } else if (c == ')') {
            parenDepth--;
            currentMove += c;
        } else if (std::isspace(c) && parenDepth == 0) {
            if (!currentMove.empty()) {
                // Only add the move if it's not an annotation
                if (!isAnnotation(currentMove)) {
                    moves.push_back(currentMove);
                }
                currentMove.clear();
            }
            // skip whitespace
        } else {
            currentMove += c;
        }
    }

    if (!currentMove.empty()) {
        // Only add the move if it's not an annotation
        if (!isAnnotation(currentMove)) {
            moves.push_back(currentMove);
        }
    }

    return moves;
}
