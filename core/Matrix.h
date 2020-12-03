#pragma once

#include <iostream>

#pragma warning( push, 3 )
#include <opencv2/core/mat.hpp>
#pragma warning( pop )

namespace tetris
{
	namespace core
	{
		class Matrix : public cv::Mat
		{
		public:
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

			// Coordinates are not in terms of traditional opencv x,y coordinates
			uint8_t& at(int row, int col);

			// Coordinates are not in terms of traditional opencv x,y coordinates
			const uint8_t& at(int row, int col) const;

			void print(std::ostream& os = std::cout) const;

			bool isInBounds(int row, int col) const;
		};
	}
}