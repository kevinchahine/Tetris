#include "pch.h"
#include "GraphicalDisplay.h"

#include <iostream>

#pragma warning ( push, 3 )
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		const cv::Scalar RED{ 0, 0, 255 };
		const cv::Scalar PURPLE{ 255, 0, 255 };
		const cv::Scalar BLUE{ 255, 0, 0 };
		const cv::Scalar CYAN{ 255, 255, 128 };
		const cv::Scalar GREEN{ 0, 255, 0 };
		const cv::Scalar YELLOW{ 0, 255, 255 };
		const cv::Scalar ORANGE{ 64, 128, 255 };
		const cv::Scalar GRAY{ 128, 128, 128 };
		const cv::Scalar WHITE{ 255, 255, 255 };
		const cv::Scalar BLACK{ 0, 0, 0 };

		const cv::Scalar shades[] = {
			BLACK,
			CYAN,
			RED,
			PURPLE,
			BLUE,
			GREEN,
			YELLOW,
			ORANGE,
			GRAY,
			WHITE
		};

		void GraphicalDisplay::rasterize(const Game& game)
		{
			// Calculate dimensions of image
			const cv::Size IMG_SIZE{ game.board().cols * cellSize.width, game.board().rows * cellSize.height };

			// Resize image if needed
			if (m_image.size() != IMG_SIZE || m_image.type() != CV_8UC3) {
				m_image = cv::Mat::zeros(IMG_SIZE, CV_8UC3);
			}

			// Black out image
			cv::rectangle(m_image, cv::Rect{ cv::Point{0, 0}, m_image.size() }, BLACK, -1);

			// Draw placed pieces
			const Board& board = game.board();

			for (int r = 0; r < board.rows; r++) {
				for (int c = 0; c < board.cols; c++) {
					cv::Scalar color = shades[board.at(r, c)];

					cv::rectangle(m_image, cv::Rect{ cv::Point{ c * cellSize.width, r * cellSize.height}, cellSize }, color, -1);

					//cv::rectangle(m_image, cv::Rect{ cv::Point{ c * cellSize, r * cellSize}, cv::Size{ cellSize, cellSize } }, BLACK, 1);
				}
			}

			// Draw falling piece
			const TetrominoBase& falling = game.fallingPiece();
			const cv::Point& pos = game.fallingPiecePos();

			for (int r = 0; r < falling.cols; r++) {
				for (int c = 0; c < falling.rows; c++) {
					if (falling.at(r, c) != TetrominoBase::EMPTY) {
						int rowCoord = pos.y + r;
						int colCoord = pos.x + c;
						if (rowCoord >= 0 &&
							rowCoord < board.rows &&
							colCoord >= 0 &&
							colCoord < board.cols)
						{
							cv::Scalar color = shades[falling.at(r, c)];

							cv::rectangle(m_image, cv::Rect{ cv::Point{ colCoord * cellSize.width, rowCoord * cellSize.height }, cellSize }, color, -1);
						}
					}
				}
			}
		}

		void GraphicalDisplay::show()
		{
			cv::imshow("TETRIS", m_image);
			cv::waitKey(1);
		}
	}
}
