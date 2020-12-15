#pragma once

#include "core.h"
#include "Move.h"
#include "Game.h"

#include <vector>

namespace tetris
{
	namespace core
	{
		class CORE_API MoveGenerator
		{
		public:
			static std::vector<Move> generate(const Game& game, bool leaveOutSwap = false);

			// C is to be a container class that has a push_back function
			template<typename C>
			static void generate(C& dstContainer, const Game& game, bool leaveOutSwap = false);
		};

		template<typename C>
		void MoveGenerator::generate(C& dstContainer, const Game& game, bool leaveOutSwap)
		{
			if (game.isSafe(Move::DOWN)) { dstContainer.push_back(Move::DOWN); }
			if (game.isSafe(Move::LEFT)) { dstContainer.push_back(Move::LEFT); }
			if (game.isSafe(Move::SPIN)) { dstContainer.push_back(Move::SPIN); }
			if (game.isSafe(Move::RIGHT)) { dstContainer.push_back(Move::RIGHT); }

			// Swap is always valid, but sometimes we don't care for it
			if (leaveOutSwap == false) { dstContainer.push_back(Move::SWAP); }
		}
	}
}

