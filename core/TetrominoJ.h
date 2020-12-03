#pragma once
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class TetrominoJ :
			public TetrominoBase
		{
		public:
			TetrominoJ();
			TetrominoJ(const TetrominoJ&) = default;
			TetrominoJ(TetrominoJ&&) noexcept = default;
			virtual ~TetrominoJ() noexcept = default;
			TetrominoJ& operator=(const TetrominoJ&) = default;
			TetrominoJ& operator=(TetrominoJ&&) noexcept = default;
		};
	}
}

