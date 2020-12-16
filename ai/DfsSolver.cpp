#include "pch.h"
#include "DfsSolver.h"

#include <Tetris/core/MoveStatePair.h>

#include <queue>
#include <stack>
#include <set>

using namespace std;

namespace tetris
{
	namespace ai
	{
		void DfsSolver::reset()
		{

		}

		core::Move DfsSolver::getInput()
		{
			return solve();
		}

		core::Move DfsSolver::solve()
		{
			const core::Game& game = this->game();

			// Next moves to try
			vector<core::MoveStatePair> frontier;

			// Keeps track of moves that got us to the current state
			///queue<core::TetrominoBase> moves;

			// Contains hash values of states we have already analysed
			// To prevent infinite loops and improve efficiency
			set<size_t> explored;

			// Generate starting moves and push them into the frontier
			game.generateMoves(frontier);

			// Keep repeating as long has there are moves to try in the frontier
			while (!frontier.empty())
			{
				cout << '.';
				// 2.) --- Grab the next state from the stack ---
				// --- Don't forget to pop it off when we're done with it ---
				tetris::core::MoveStatePair node = move(frontier.back());
				frontier.pop_back();

				// 3.) --- Find out if we have already analyzed it yet ---
				// Start by calculating the hash of the current state
				size_t hash_value = std::hash<tetris::core::MoveStatePair>{}(node);
				// Have we analyzed this state yet?
				if (explored.count(hash_value) == 0) {
					// We haven't analyzed this state yet. Lets do so now.


				}
			}
			
			if (m_callback != nullptr) {
				m_callback(core::Move::DOWN);
			}

			return core::Move::DOWN;	// change this please
		}

	}
}