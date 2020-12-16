#pragma once

#include "core.h"
#include "Matrix.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API Board : public Matrix
		{
		public:
			static const uint8_t TOP = 0b0000'0001;
			static const uint8_t BOTTOM = 0b0000'0010;
			static const uint8_t LEFT = 0b0000'0100;
			static const uint8_t RIGHT = 0b0000'1000;

		public:
			Board();
			Board(int nRows, int nCols);
			Board(const Board&) = default;
			Board(Board&&) noexcept = default;
			virtual ~Board() noexcept = default;
			Board& operator=(const Board&) = default;
			Board& operator=(Board&&) noexcept = default;

			// Determines if tetromino is out of bounds at the specified boundaries
			// Default is all boundaries.
			// Does not consider occpancy of board cells
			bool isInBounds(
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			// Determines if tetromino overlaps an occupied cell on the board.
			// Considers boundary of board. 
			// Returns false if any part of tetromino is out of bounds
			// Returns true if all tetromino cells are not out of bounds and do not overlap occupied cells
			// on the board.
			bool overlaps(
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			// Copies cells in tetromino onto the board.
			// Does not clear full rows.
			// Call Board::clearRows() after calling this method.
			void pasteAt(const TetrominoBase& tetromino);

			// Removes the cells from the board that are behind tetromino.
			// Does the opposite of pasteAt()
			// Can be used to undo moves 
			void removeFrom(const TetrominoBase& tetromino);

			// Removes all cells at the specified row regardless of whether they 
			// it is a full row or not.
			// Cells above this row will slide down.
			void clearRow(int row);
			
			// Not implemented
			void clearRows(int rowBegin, int rowEnd);

			// Removes all cells on the board
			void clear();
		};
	}
}