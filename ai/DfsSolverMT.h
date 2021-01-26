#pragma once

#include "ai.h"

#include "DfsSolver.h"
#include "FrontierStack.h"
#include "SolutionSequence.h"

#include <thread>
#include <mutex>

using namespace std;

namespace tetris
{
	namespace ai
	{
		class AI_API DfsSolverMT : public DfsSolver
		{
		public:

			DfsSolverMT() = default;
			DfsSolverMT(const DfsSolverMT& rhs);
			DfsSolverMT(DfsSolverMT&& rhs) noexcept;
			virtual ~DfsSolverMT() noexcept = default;
			DfsSolverMT & operator=(const DfsSolverMT &);
			DfsSolverMT & operator=(DfsSolverMT &&) noexcept;

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
			mutable std::mutex frontierMutex;

			// Explored list containing hash values of states that we have analyzed
			// *** "states" should move from the frontier, get analyzed and then
			// its hash value pushed to explored
			set<size_t> explored;
			mutable std::mutex exploredMutex;

			// Best solution found so far
			SolutionSequence bestSol;
			mutable std::mutex bestSolMutex;	// protects both bestSol and bestHeur

			// Heuristic of the best solution
			float bestHeur;
		};
	}
}
