#pragma once

#include "Matrix.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class Board : public Matrix
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

			bool isInBounds(
				int row,
				int col,
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			bool isInBounds(
				const cv::Point& pos,
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			bool fitsAt(
				int row,
				int col,
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			bool fitsAt(
				const cv::Point& pos,
				const TetrominoBase& tetromino,
				uint8_t edges = Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT) const;

			void pasteAt(int row, int col, const TetrominoBase& tetromino);

			void pasteAt(const cv::Point& pos, const TetrominoBase& tetromino);

			void clearRow(int row);

			void clearRows(int rowBegin, int rowEnd);

			void clear();
		};
	}
}