#pragma once

#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class TetrominoI :
			public TetrominoBase
		{
		public:
			TetrominoI();
			TetrominoI(const TetrominoI&) = default;
			TetrominoI(TetrominoI&&) noexcept = default;
			virtual ~TetrominoI() noexcept = default;
			TetrominoI& operator=(const TetrominoI&) = default;
			TetrominoI& operator=(TetrominoI&&) noexcept = default;
		};
	}
}