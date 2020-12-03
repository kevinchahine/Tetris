#pragma once

#include "core.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API TetrominoI :
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