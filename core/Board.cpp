#include "pch.h"
#include "Board.h"

#include <iostream>

#pragma warning (push, 3)
#include <opencv2/imgproc.hpp>
#pragma warning ( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		Board::Board() :
			Matrix{ cv::Mat::zeros(cv::Size{ 10, 20 }, CV_8UC1) }
		{
		}

		Board::Board(int nRows, int nCols) :
			Matrix{ cv::Mat::zeros(cv::Size{ nCols, nRows }, CV_8UC1) }
		{
		}

		bool Board::isInBounds(int row, int col, const TetrominoBase& tetromino, uint8_t edges) const
		{
			const bool top = edges & TOP;
			const bool bottom = edges & BOTTOM;
			const bool left = edges & LEFT;
			const bool right = edges & RIGHT;

			for (int r = 0; r < tetromino.size().height; r++) {
				for (int c = 0; c < tetromino.size().width; c++) {
					// Does this cell contain something?
					if (tetromino.at(r, c) != TetrominoBase::EMPTY) {
						// Yes it contains part of the tetromino
						int rowOnBoard = row + r;
						int colOnBoard = col + c;

						// Is cell inside the board (or is it out of bounds)?
						if ((top && rowOnBoard < 0) ||				// Is cell above top boarder?
							(bottom && rowOnBoard >= this->rows) ||	// Is cell below bottom boarder?
							(left && colOnBoard < 0) ||				// Is cell left of left boarder?
							(right && colOnBoard >= this->cols))	// Is cell right of right boarder?
						{
							// Cell contains something and is outside the board.
							return false;
						}
					}
				}
			}

			// All cells are inbounds
			return true;
		}

		bool Board::isInBounds(const cv::Point& pos, const TetrominoBase& tetromino, uint8_t edges) const
		{
			return isInBounds(pos.y, pos.x, tetromino, edges);
		}

		bool Board::fitsAt(int row, int col, const TetrominoBase& tetromino, uint8_t edges) const
		{
			const bool top = edges & TOP;
			const bool bottom = edges & BOTTOM;
			const bool left = edges & LEFT;
			const bool right = edges & RIGHT;

			for (int r = 0; r < tetromino.size().height; r++) {
				for (int c = 0; c < tetromino.size().width; c++) {
					if (tetromino.at(r, c) != TetrominoBase::EMPTY) {
						int rowOnBoard = row + r;
						int colOnBoard = col + c;

						// Is cell inside the board (or is it out of bounds)?
						if ((top && rowOnBoard >= 0) &&				// Is cell below top boarder?
							(bottom && rowOnBoard < this->rows) &&	// Is cell above bottom boarder?
							(left && colOnBoard >= 0) &&			// Is cell right of left boarder?
							(right && colOnBoard < this->cols))		// Is cell left of right boarder?)
						{
							// Cell is inside the board. But does it overlap a cell thats 
							// already on the board.

							// Is board cell empty or does it have something in it?
							if (this->at(rowOnBoard, colOnBoard) != TetrominoBase::EMPTY) {
								// Cell is not empty.
								return false;	// There is an overlap, therefore tetromino does not fit where it is.
							}
						}
						else {
							return false;	// Cell is out of bounds and in that case also doesn't fit where it is.
						}
					}
				}
			}

			// Tetromino does not have any cells that are out of bounds or overlap any pieces
			// that are already on the board.
			return true;	// So it fits
		}

		bool Board::fitsAt(const cv::Point& pos, const TetrominoBase& tetromino, uint8_t edges) const
		{
			return fitsAt(pos.y, pos.x, tetromino, edges);
		}

		void Board::pasteAt(int row, int col, const TetrominoBase& tetromino)
		{
			for (int r = 0; r < tetromino.size().height; r++) {
				for (int c = 0; c < tetromino.size().width; c++) {
					if (tetromino.at(r, c) != TetrominoBase::EMPTY) {
						int rowCoord = row + r;
						int colCoord = col + c;
						if (rowCoord >= 0 &&
							rowCoord < this->rows &&
							colCoord >= 0 &&
							colCoord < this->cols)
						{
							this->at(rowCoord, colCoord) = tetromino.at(r, c);
						}
					}
				}
			}
		}

		void Board::pasteAt(const cv::Point& pos, const TetrominoBase& tetromino)
		{
			pasteAt(pos.y, pos.x, tetromino);
		}

		void Board::clearRow(int row)
		{
			// Get region of cells above the row we are to remove
			const auto SRC_ROI = cv::Rect(0, 0, this->cols, row);

			cv::Mat temp = (*this)(SRC_ROI).clone();

			// Get region of cells of row we are to remove
			const auto DST_ROI = cv::Rect(0, 1, this->cols, row);

			// Copy top cells to the ones below
			temp.copyTo((*this)(DST_ROI));

			// Clear top row
			for (int c = 0; c < this->cols; c++) {
				this->at(0, c) = TetrominoBase::EMPTY;
			}
		}

		void Board::clear()
		{
			cv::rectangle((*this), cv::Rect{ cv::Point{0, 0}, this->size() }, Matrix::EMPTY, -1);
		}
	}
}