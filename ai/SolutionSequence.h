#pragma once

#include "ai.h"

#include <Tetris/core/Move.h>
#include <Tetris/core/TetrominoBase.h>

#include <memory>
#include <queue>

// --- Forward Declarations ---
class tetris::core::Board;

namespace tetris
{
	namespace ai
	{
		class AI_API SolutionSequence
		{
		public:

			void moveDown();

			void moveLeft();

			void moveRight();

			void moveSpin(const core::Board & board);

			void move(core::Move move, const core::Board& board);

			void print(std::ostream& os = std::cout);

		protected:
			std::deque<core::Move> m_sequence;

			core::TetrominoBase m_falling;
		};
	}
}

