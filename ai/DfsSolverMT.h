#pragma once

#include "ai.h"

#include "DfsSolver.h"
#include "FrontierStack.h"
#include "SolutionSequence.h"

namespace tetris
{
	namespace ai
	{
		class AI_API DfsSolverMT : public DfsSolver
		{
		public:

			DfsSolverMT() = default;
			DfsSolverMT(const DfsSolverMT&) = default;
			DfsSolverMT(DfsSolverMT&&) noexcept = default;
			virtual ~DfsSolverMT() noexcept = default;
			DfsSolverMT & operator=(const DfsSolverMT &) = default;
			DfsSolverMT & operator=(DfsSolverMT &&) noexcept = default;

			virtual void reset() override;

			virtual core::Move getInput(const core::Game & game) override;

			virtual std::unique_ptr<ControllerBase> clone() override;

			virtual std::string name() override;

		protected:

			// Mainly sets up frontier and creates threads that
			// run solveImpl
			SolutionSequence solve(const core::Game & game);

			// To be run of on a thread
			SolutionSequence solveImpl(const core::Game & game);

		private:	// ---------------- Shared by threads ---------------------
			
			// Contains states that we want to try next.
			// Make sure that states added to frontier are not found in explored list
			// to prevent infinite loops
			FrontierStack<SolutionSequence> frontier;

			// Explored list containing hash values of states that we have analyzed
			// *** "states" should move from the frontier, get analyzed and then
			// its hash value pushed to explored
			set<size_t> explored;

			// Best solution found so far
			SolutionSequence bestSol;
			// Heuristic of the best solution
			float bestHeur;


		};
	}
}
