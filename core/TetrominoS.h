#pragma once
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class TetrominoS :
			public TetrominoBase
		{
		public:
			TetrominoS();
			TetrominoS(const TetrominoS&) = default;
			TetrominoS(TetrominoS&&) noexcept = default;
			virtual ~TetrominoS() noexcept = default;
			TetrominoS& operator=(const TetrominoS&) = default;
			TetrominoS& operator=(TetrominoS&&) noexcept = default;
		};
	}
}
