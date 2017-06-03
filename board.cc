#include "board.h"
#include "cmove.h"
#include <string>

std::string Board::getStringRep() {
  std::string stringRep;
  U64 base = 1;

  for(U64 i=0;i<64;i++) {
    U64 square = base<<i;
    bool squareOccupied = (square & OCCUPIED) != 0;

    if (i % 8 == 0) {
      stringRep.insert(0, "\n");
    }

    if (squareOccupied) {
      if (square & WHITE_PAWNS) stringRep.insert(0, " P ");
      else if (square & BLACK_PAWNS) stringRep.insert(0, " p ");

      else if (square & WHITE_ROOKS) stringRep.insert(0, " R ");
      else if (square & BLACK_ROOKS) stringRep.insert(0, " r ");

      else if (square & WHITE_KNIGHTS) stringRep.insert(0, " N ");
      else if (square & BLACK_KNIGHTS) stringRep.insert(0, " n ");

      else if (square & WHITE_BISHOPS) stringRep.insert(0, " B ");
      else if (square & BLACK_BISHOPS) stringRep.insert(0, " b ");

      else if (square & WHITE_QUEENS) stringRep.insert(0, " Q ");
      else if (square & BLACK_QUEENS) stringRep.insert(0, " q ");

      else if (square & WHITE_KING) stringRep.insert(0, " K ");
      else if (square & BLACK_KING) stringRep.insert(0, " k ");
    } else {
      stringRep.insert(0, " . ");
    }
  }

  return stringRep;
}

U64 Board::getOccupied() {
  return getWhitePieces() | getBlackPieces();
}

U64 Board::getWhitePieces() {
  return WHITE_PAWNS | \
  WHITE_ROOKS | \
  WHITE_KNIGHTS | \
  WHITE_BISHOPS | \
  WHITE_QUEENS | \
  WHITE_KING;
}

U64 Board::getBlackPieces() {
  return BLACK_PAWNS | \
  BLACK_ROOKS | \
  BLACK_KNIGHTS | \
  BLACK_BISHOPS | \
  BLACK_QUEENS | \
  BLACK_KING;
}

void Board::setToStartPos() {
  _whiteToMove = true;

  WHITE_PAWNS = 65280ull;
  BLACK_PAWNS = 71776119061217280ull;

  WHITE_ROOKS = 129ull;
  BLACK_ROOKS = 9295429630892703744ull;

  WHITE_KNIGHTS = 66ull;
  BLACK_KNIGHTS = 4755801206503243776ull;

  WHITE_BISHOPS = 36ull;
  BLACK_BISHOPS = 2594073385365405696ull;

  WHITE_QUEENS = 16ull;
  BLACK_QUEENS = 1152921504606846976ull;

  WHITE_KING = 8ull;
  BLACK_KING = 576460752303423488ull;

  WHITE_PIECES = getWhitePieces();
  BLACK_PIECES = getBlackPieces();
  OCCUPIED = getOccupied();
  NOT_OCCUPIED = ~OCCUPIED;
}

MoveList Board::getWhitePawnMoves() {
  MoveList potentialMoves;

  // Move all pawns up 1
  U64 movedPawns1 = WHITE_PAWNS << 8;
  for(U64 i=0;i<64;i++) {
    U64 square = static_cast<U64>(1) << i;

    // If this is a square in front of a pawn and is not occupied
    if ((movedPawns1 & square) && (square & NOT_OCCUPIED)) {
      // Add to MoveList
      potentialMoves.push_back(CMove(i-8, i));
    }
  }

  // Move pawns on rank 2 up 2
  U64 movedPawns2 = (WHITE_PAWNS & RANK_2) << 16;
  for(U64 i=0;i<64;i++) {
    U64 square = static_cast<U64>(1) << i;

    // If this is a square in front of a pawn and is not occupied
    if ((movedPawns2 & square) && (square & NOT_OCCUPIED)) {
      // Add to MoveList
      potentialMoves.push_back(CMove(i-16, i));
    }
  }

  return potentialMoves;
}

MoveList Board::getBlackPawnMoves() {
  MoveList potentialMoves;

  // Move all pawns up 1
  U64 movedPawns1 = BLACK_PAWNS >> 8;
  for(U64 i=0;i<64;i++) {
    U64 square = static_cast<U64>(1) << i;

    // If this is a square in front of a pawn and is not occupied
    if ((movedPawns1 & square) && (square & NOT_OCCUPIED)) {
      // Add to MoveList
      potentialMoves.push_back(CMove(i+8, i));
    }
  }

  // Move pawns on rank 7 up 2
  U64 movedPawns2 = (BLACK_PAWNS & RANK_7) >> 16;
  for(U64 i=0;i<64;i++) {
    U64 square = static_cast<U64>(1) << i;

    // If this is a square in front of a pawn and is not occupied
    if ((movedPawns2 & square) && (square & NOT_OCCUPIED)) {
      // Add to MoveList
      potentialMoves.push_back(CMove(i+16, i));
    }
  }

  return potentialMoves;
}
