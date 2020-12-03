#include "pch.h"
#include "Matrix.h"

#include <iomanip>

#pragma warning ( push, 3 )
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		Matrix::Matrix(const cv::Mat& mat) :
			cv::Mat{ mat }
		{
		}

		Matrix::Matrix(cv::Mat&& mat) :
			cv::Mat{ std::move(mat) }
		{
		}

		Matrix::Matrix(const Matrix& mat) :
			cv::Mat{ mat.clone() }
		{
		}

		Matrix& Matrix::operator=(const Matrix& mat)
		{
			static_cast<cv::Mat&>(*this) = mat.clone();

			return *this;
		}

		uint8_t& Matrix::at(int row, int col)
		{
			return this->cv::Mat::at<uint8_t>(row, col);
		}

		const uint8_t& Matrix::at(int row, int col) const
		{
			return this->cv::Mat::at<uint8_t>(row, col);
		}

		void Matrix::print(std::ostream& os) const
		{
			for (int r = 0; r < this->rows; r++) {
				for (int c = 0; c < this->cols; c++) {
					os << static_cast<int>(this->at(r, c));
				}
				os << '\n';
			}
			os << '\n';
		}

		bool Matrix::isInBounds(int row, int col) const
		{
			return
				row >= 0 &&
				row < this->rows&&
				col >= 0 &&
				col < this->cols;
		}
	}
}