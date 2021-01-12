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
		class AI_API DfsSolver2 : public DfsSolver
		{
		public:

			DfsSolver2() = default;
			DfsSolver2(const DfsSolver2&) = default;
			DfsSolver2(DfsSolver2&&) noexcept = default;
			virtual ~DfsSolver2() noexcept = default;
			DfsSolver2 & operator=(const DfsSolver2 &) = default;
			DfsSolver2 & operator=(DfsSolver2 &&) noexcept = default;

			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

			virtual std::string name() override;

		protected:
			SolutionSequence solve(const core::Game & game);
		};
	}
}

