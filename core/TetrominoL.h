#pragma once
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class TetrominoL :
			public TetrominoBase
		{
		public:
			TetrominoL();
			TetrominoL(const TetrominoL&) = default;
			TetrominoL(TetrominoL&&) noexcept = default;
			virtual ~TetrominoL() noexcept = default;
			TetrominoL& operator=(const TetrominoL&) = default;
			TetrominoL& operator=(TetrominoL&&) noexcept = default;
		};
	}
}

