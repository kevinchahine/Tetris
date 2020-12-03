#pragma once

#include "core.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API TetrominoT :
			public TetrominoBase
		{
		public:
			TetrominoT();
			TetrominoT(const TetrominoT&) = default;
			TetrominoT(TetrominoT&&) noexcept = default;
			virtual ~TetrominoT() noexcept = default;
			TetrominoT& operator=(const TetrominoT&) = default;
			TetrominoT& operator=(TetrominoT&&) noexcept = default;
		};
	}
}

