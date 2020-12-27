#pragma once

#include "ai.h"
#include <Tetris/ai/AiController.h>

namespace tetris
{
	namespace ai
	{
		class AI_API RandomSolver : public ai::AiController
		{
		public:
			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

		protected:

		};
	}
}

