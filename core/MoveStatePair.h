#pragma once

#include "core.h"

#include "TetrominoBase.h"
#include "Move.h"

namespace tetris
{
	namespace core
	{
		class CORE_API MoveStatePair
		{
		public:
			core::Move move;

			// Destination of falling piece after making move
			core::TetrominoBase state;

		};
	}
}