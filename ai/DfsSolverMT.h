#pragma once

#include "ai.h"

#include "DfsSolver.h"
#include "FrontierStack.h"
#include "SolutionSequence.h"

#include <thread>
#include <mutex>
#include <bitset>

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

			// Reimplemented version based on DfsSolver::branchValidMoves
			// to allow for more efficient mutex locking during multithreading
			// Thread safe
			void branchValidMoves(
				const core::Board& board,
				const SolutionSequence& baseSequence);

			// Mainly sets up frontier and creates threads that
			// run solveImpl
			SolutionSequence solve(const core::Game & game);

			// To be run of on a thread
			void solveImpl(const core::Game & game, std::bitset<64>::reference && noMoreWorkBit);

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
			float bestHeur = numeric_limits<float>::lowest();

			// Syncronizes returns of each thread so that no thread returns
			// prematurely. 
			// Since threads will push and pop elements from the frontier, the frontier
			// may become empty then refiled multiple times during the solve method.
			// If one thread sees that the frontier is empty, it doesn't mean another thread
			// one refill it with more states and therefore should wait instead of return.
			// Without this, some threads my return early leaving the others to finish the work.
			// Each thread should assigned a bit in this bitset.
			// Each thread should set its bit to 0 when it sees that frontier is empty
			// Each thread should set its bit to 1 when it sees frontier is not empty
			// Each thread should return when all bits are set to 0
			// Limits thread count to 64 threads (unfortunately). 
			// If we have the luxury of using a CPU with more than 64 threads,
			// we would need to increase the number of bits in bitset.
			std::bitset<64> noMoreWorkFlags;
		};
	}
}
