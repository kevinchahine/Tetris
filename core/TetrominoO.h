#pragma once

#include "core.h"
#include "TetrominoBase.h"

namespace tetris
{
	namespace core
	{
		class CORE_API TetrominoO :
			public TetrominoBase
		{
		public:
			TetrominoO();
			TetrominoO(const TetrominoO&) = default;
			TetrominoO(TetrominoO&&) noexcept = default;
			virtual ~TetrominoO() noexcept = default;
			TetrominoO& operator=(const TetrominoO&) = default;
			TetrominoO& operator=(TetrominoO&&) noexcept = default;
		};
	}
}

