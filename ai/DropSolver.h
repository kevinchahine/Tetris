#pragma once

#include "ai.h"
#include <Tetris/ai/AiController.h>

namespace tetris
{
	namespace ai
	{
		/*
		Solves by moving the falling piece left or right to its desired spot then dropping it 
		all the way down. Does use swaps and spins 
		*/
		class AI_API DropSolver : public ai::AiController
		{
		public:
			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

		protected:
			void solve(const core::Game & game);

		};
	}
}
