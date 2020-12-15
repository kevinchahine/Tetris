#include "pch.h"
#include "MoveGenerator.h"

using namespace std;

namespace tetris
{
	namespace core
	{
		vector<Move> MoveGenerator::generate(const Game& game, bool leaveOutSwap)
		{
			vector<Move> validMoves;
			validMoves.reserve(5);

			if (game.isSafe(Move::DOWN)) { validMoves.push_back(Move::DOWN); }
			if (game.isSafe(Move::LEFT)) { validMoves.push_back(Move::LEFT); }
			if (game.isSafe(Move::SPIN)) { validMoves.push_back(Move::SPIN); }
			if (game.isSafe(Move::RIGHT)) { validMoves.push_back(Move::RIGHT); }

			// Swap is always valid, but sometimes we don't care for it
			if (leaveOutSwap == false) {	validMoves.push_back(Move::SWAP); }

			return validMoves;
		}
	}
}