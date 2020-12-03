#pragma once

#include <stdint.h>

#include "Matrix.h"

namespace tetris
{

	namespace core
	{	
		// 4x4 cv::Mat 
		// element values:
		//	0 - empty cell
		//	x - shape identifier as a uint8_t (x is non zero)
		class TetrominoBase : public Matrix
		{
		public:
			TetrominoBase();
			TetrominoBase(int nRows, int nCols);
			TetrominoBase(const TetrominoBase&) = default;
			TetrominoBase(TetrominoBase&&) noexcept = default;
			virtual ~TetrominoBase() noexcept = default;
			TetrominoBase& operator=(const TetrominoBase&) = default;
			TetrominoBase& operator=(TetrominoBase&&) noexcept = default;

			void spin();

			void unSpin();

		};
	}
}