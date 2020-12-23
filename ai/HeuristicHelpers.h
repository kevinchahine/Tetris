#pragma once

#include "ai.h"

#include <iostream>

#include <Tetris/core/Board.h>

namespace tetris
{
	namespace ai
	{
		int AI_API countHoles(const core::Board& board);

		int AI_API countSittingCells(const core::Board& board);

		int AI_API maxHeight(const core::Board& board);

		int AI_API sumOfHeights(const core::Board& board);

		int AI_API calcBumpiness(const core::Board& board);
	}
}