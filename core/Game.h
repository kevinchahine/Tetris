#pragma once

#include "Board.h"
#include "Move.h"
#include "RandomizedBag.h"

namespace tetris
{
	namespace core
	{
		class Game
		{
		public:

			void awake();

			bool isInBounds(const Move& move, uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			// Only call this method if move will not cause piece to be out of bounds
			// from the side or top.
			// If piece is out of bounds on the side or top, then piece will be placed
			// where it is.
			void applyMove(const Move& move);

			bool applyMoveIfInBounds(const Move& move);

			void loadNextPiece();

			void swapPieces();

			// Returns true iff a piece has been placed on the top row
			bool isGameOver() const;

			void clearFullRows();

			// Make sure falling piece is inbounds from left to right before calling this method
			// Its ok if piece goes above top row or below bottom row
			bool pieceCanMoveDown() const;

			void placePiece();

			// ------------------------ ACCESSORS ---------------------------------------

			Board& board() { return m_board; }
			const Board& board() const { return m_board; }

			TetrominoBase& fallingPiece() { return m_fallingPiece; }
			const TetrominoBase& fallingPiece() const { return m_fallingPiece; }

			cv::Point& fallingPiecePos() { return m_fallingPiecePos; }
			const cv::Point& fallingPiecePos() const { return m_fallingPiecePos; }

			TetrominoBase& nextPiece() { return m_nextPiece; }
			const TetrominoBase& nextPiece() const { return m_nextPiece; }

			TetrominoBase& heldPiece() { return m_heldPiece; }
			const TetrominoBase& heldPiece() const { return m_heldPiece; }

		protected:
			Board m_board;

			TetrominoBase m_fallingPiece;
			cv::Point m_fallingPiecePos;

			TetrominoBase m_nextPiece;

			TetrominoBase m_heldPiece;

			RandomizedBag bag;
		};
	}
}