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
			const core::Game& game = *m_gamePtr;

			// Next moves to try
			stack<core::MoveStatePair> frontier;

			// Keeps track of moves that got us to the current state
			queue<core::TetrominoBase> moves;

			// Contains hash values of states we have already analysed
			// To prevent infinite loops and improve efficiency
			set<int> explored;

			// Generate starting moves
			vector<core::MoveStatePair> validMoves;
			game.generateMoves(validMoves);

			// Keep repeating as long has there are moves to try in the frontier
			while (frontier.empty() == false)
			{
				tetris::core::MoveStatePair node = move(frontier.top());
				frontier.pop();


			}

			return core::Move::DOWN;	// change this please
		}

	}
}