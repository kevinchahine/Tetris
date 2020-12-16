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
			if (m_gamePtr == nullptr) {
				throw std::exception("m_gamePtr was a nullptr");
			}

			const core::Game& game = *m_gamePtr;

			// Next moves to try
			vector<core::MoveStatePair> frontier;

			// Keeps track of moves that got us to the current state
			///queue<core::TetrominoBase> moves;

			// Contains hash values of states we have already analysed
			// To prevent infinite loops and improve efficiency
			set<size_t> explored;

			// Generate starting moves and push them into the frontier
			game.generateMoves(frontier);

			cout << frontier.size() << " moves have been generated\n";
			// Keep repeating as long has there are moves to try in the frontier
			while (!frontier.empty())
			{
				cout << '.';
				// 2.) --- Grab the next state from the stack ---
				// --- Don't forget to pop it off when we're done with it ---
				tetris::core::MoveStatePair & node = frontier.back();

				// 3.) --- Find out if we have already analyzed it yet ---
				// Start by calculating the hash of the current state
				size_t hash_value = std::hash<tetris::core::MoveStatePair>{}(node);
				if (explored.count(hash_value))

				// --- Pop off the back state now that we are done using it ---
				frontier.pop_back();
			}
			
			if (m_callback != nullptr) {
				m_callback(core::Move::DOWN);
			}

			return core::Move::DOWN;	// change this please
		}

	}
}