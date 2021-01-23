#pragma once

#include "ai.h"

#include "AiController.h"
#include "FrontierStack.h"
#include "SolutionSequence.h"

namespace tetris
{
	namespace ai
	{
		class AI_API DfsSolver : public AiController
		{
		public:

			DfsSolver() = default;
			DfsSolver(const DfsSolver&) = default;
			DfsSolver(DfsSolver&&) noexcept = default;
			virtual ~DfsSolver() noexcept = default;
			DfsSolver & operator=(const DfsSolver &) = default;
			DfsSolver & operator=(DfsSolver &&) noexcept = default;

			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

			virtual std::string name() override;

		protected:
			void branchValidMoves(
				FrontierStack<SolutionSequence>& frontier, 
				const std::set<size_t>& explored,
				const core::Board& board, 
				const SolutionSequence& baseSequence) const;

			SolutionSequence solve(const core::Game & game);
		};
	}
}

