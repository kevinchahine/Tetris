#pragma once

#include "ai.h"
#include "DfsSolver.h"

namespace tetris
{
	namespace ai
	{
		// A more advanced Depth-first search solver that analyzes the best
		//	end states of:
		//		- falling piece
		//		- held piece
		//		- next piece
		class AI_API DfsSolver3 : public DfsSolver
		{
		public:

			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

		protected:
			SolutionSequence solve(const core::Game & game);
		};
	}
}
