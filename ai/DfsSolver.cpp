#include "pch.h"
#include "DfsSolver.h"

#include <Tetris/core/MoveGenerator.h>
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

			// Keeps track of 
			queue<core::TetrominoBase> moves;

			// Contains hash values of states we have already analysed
			// To prevent infinite loops and improve efficiency
			set<int> explored;

			// Generate starting moves
			vector<core::Move> validMoves = tetris::core::MoveGenerator::generate(game, true);

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