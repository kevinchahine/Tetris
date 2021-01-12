#include "pch.h"
#include "DfsSolver.h"

#include "SolutionSequence.h"
#include "FrontierStack.h"

#include <Tetris/core/MoveStatePair.h>
#include <Tetris/core/MoveGenerator.h>

#include <algorithm>
#include <iterator>
#include <queue>
#include <stack>
#include <set>
#include <limits>

using namespace tetris::core;
using namespace std;

namespace tetris
{
	namespace ai
	{
		void DfsSolver::reset()
		{
			m_moveSequence.clear();
		}

		core::Move DfsSolver::getInput(const Game & game)
		{
			if (m_moveSequence.empty()) {
				
				m_moveSequence = solve(game).sequence();

				if (m_moveSequence.empty()) {
					throw std::exception("No solution was found\n");
				}
			}
			else {
			}

			Move selection = m_moveSequence.front();

			m_moveSequence.pop_front();

			return selection;
		}

		std::unique_ptr<ControllerBase> DfsSolver::clone()
		{
			return make_unique<DfsSolver>(*this);
		}

		std::string DfsSolver::name()
		{
			return "DFS1";
		}

		SolutionSequence DfsSolver::solve(const Game & game)
		{
			// Contains states that we want to try next.
			// Make sure that states added to frontier are not found in explored
			// to prevent infinite loops
			FrontierStack<SolutionSequence> frontier;

			// Explored list containing hash values of states that we have analyzed
			// *** "states" should move from the frontier, get analyzed and pushed to explored
			set<size_t> explored;

			SolutionSequence bestSol;							// Best solution found so far
			float bestHeur = numeric_limits<float>::lowest();	// Heuristic of the best solution

			// 1.) Generate starting moves and push them into the frontier
			branchValidMoves(frontier, explored, game.board(), game.fallingPiece());

			// 2.) --- Keep repeating as long has there are moves to try in the frontier ---
			while (!frontier.empty())
			{
				// 2-1.) --- Grab the next state from the frontier ---
				// --- Don't forget to pop it off when we're done with it ---
				SolutionSequence seq = move(frontier.top());
				frontier.pop();

				// 2-1.) --- Put sequence in explored list ---
				// so that we don't analyze it again 
				explored.insert(hash<SolutionSequence>{}(seq));

				// 2-2.) --- Is this a goal state? ---
				// It is a goal state if the falling piece is laying on something
				if (game.board().isLaying(seq.falling())) {
					float heur = calcHeuristic(game.board(), seq.falling());

					if (heur > bestHeur) {
						bestHeur = heur; 
						bestSol = seq;
					}
				}

				// 2-3.) See if there are any moves we can do from here
				branchValidMoves(frontier, explored, game.board(), seq);
			}
			
			// 3.) --- Final down move to place piece ---
			bestSol.placePiece();		

			return bestSol;
		}

		void DfsSolver::branchValidMoves(
			FrontierStack<SolutionSequence>& frontier, 
			const std::set<size_t>& explored, 
			const core::Board& board,
			const SolutionSequence& baseSequence) const
		{
			vector<Move> validMoves;
			generateMoves(validMoves, board, baseSequence.falling());

			// Copy moves in reverse order
			for (auto it = validMoves.rbegin(); it != validMoves.rend(); it++)
			{
				Move m = *it;

				// Make a copy of the sequence
				SolutionSequence seqCopy = baseSequence;	

				// Apply move to sequence
				seqCopy.move(m, board);

				// Calc hash of new sequence
				size_t hashValue = hash<SolutionSequence>{}(seqCopy);

				// Only add new sequence if this state has not already been analyzed
				if (explored.count(hashValue) == 0) {
					frontier.push(move(seqCopy));	// move sequence to frontier
				}
			}
		}
	}
}