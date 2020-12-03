#pragma once

#include "core.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API TetrominoZ :
			public TetrominoBase
		{
		public:
			TetrominoZ();
			TetrominoZ(const TetrominoZ&) = default;
			TetrominoZ(TetrominoZ&&) noexcept = default;
			virtual ~TetrominoZ() noexcept = default;
			TetrominoZ& operator=(const TetrominoZ&) = default;
			TetrominoZ& operator=(TetrominoZ&&) noexcept = default;
		};
	}
}