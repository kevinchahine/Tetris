#include "pch.h"
#include "TetrominoBase.h"
#include "Board.h"

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
		TetrominoBase::TetrominoBase() :
			Matrix{ cv::Mat::zeros(cv::Size(4, 4), CV_8UC1) }
		{
		}

		TetrominoBase::TetrominoBase(int nRows, int nCols) :
			Matrix{ cv::Mat::zeros(cv::Size{nCols, nRows}, CV_8UC1) }
		{
		}

		void TetrominoBase::spin()
		{
			cv::rotate(*this, *this, cv::ROTATE_90_COUNTERCLOCKWISE);
		}

		void TetrominoBase::spin(const Board& board)
		{
			spin();

			while (board.isInBounds(*this, Board::LEFT) == false) {
				moveRight();
			}

			while (board.isInBounds(*this, Board::RIGHT) == false) {
				moveLeft();
			}
		}

		void TetrominoBase::unSpin()
		{
			cv::rotate(*this, *this, cv::ROTATE_90_CLOCKWISE);
		}

		void TetrominoBase::moveDown()
		{
			m_position.y++;
		}

		void TetrominoBase::moveLeft()
		{
			m_position.x--;
		}

		void TetrominoBase::moveRight()
		{
			m_position.x++;
		}

		void TetrominoBase::moveUp()
		{
			m_position.y--;
		}

		void TetrominoBase::show(const std::string& windowName) const
		{
			cv::Size cellSize = cv::Size{ 40, 40 };

			cv::Mat img = cv::Mat::zeros(cellSize * 4, CV_8UC3);
			
			for (int r = 0; r < cols; r++) {
				for (int c = 0; c < rows; c++) {
					if (at(r, c) != TetrominoBase::EMPTY) {
						cv::Scalar color = shades[at(r, c)];

						cv::rectangle(
							img,
							cv::Rect{ cv::Point{ c * cellSize.width, r * cellSize.height }, cellSize },
							color);
					}
				}
			}

			cv::imshow(windowName, img);
		}

	}
}