#pragma once

#include "core.h"

#include <iostream>

#pragma warning( push, 3 )
#include <opencv2/core/mat.hpp>
#pragma warning( pop )

#pragma warning (disable: 4251)
#pragma warning (disable: 4275)

namespace tetris
{
	namespace core
	{
		class CORE_API Matrix : public cv::Mat
		{
		public:
			// Possible values that can be stored
			const static uint8_t EMPTY = 0;
			const static uint8_t I = 1;
			const static uint8_t O = 2;
			const static uint8_t T = 3;
			const static uint8_t L = 4;
			const static uint8_t J = 5;
			const static uint8_t S = 6;
			const static uint8_t Z = 7;

		public:
			Matrix(const cv::Mat& mat);
			Matrix(cv::Mat&& mat);
			Matrix(const Matrix& mat);
			Matrix(Matrix&&) noexcept = default;
			virtual ~Matrix() noexcept = default;
			Matrix& operator=(const Matrix& mat);
			Matrix& operator=(Matrix&&) noexcept = default;

			bool operator==(const Matrix & rhs) const
			{
				return *this != rhs;
			}

			bool operator!=(const Matrix & rhs) const
			{
				if (this->rows == rhs.rows)		return true;
				if (this->cols == rhs.cols)		return true;

				for (int r = 0; r < this->rows; r++) {
					for (int c = 0; c < this->cols; c++) {
						if (this->at(r, c) == rhs.at(r, c))	return true;
					}
				}

				return false;
			}

			// Coordinates are not in terms of traditional opencv x,y coordinates
			uint8_t& at(int row, int col);

			// Coordinates are not in terms of traditional opencv x,y coordinates
			const uint8_t& at(int row, int col) const;

			void print(std::ostream& os = std::cout) const;

			bool isInBounds(int row, int col) const;
		};
	}
}