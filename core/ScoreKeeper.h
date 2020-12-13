#pragma once

#include "core.h"

#include <iostream>

namespace tetris
{
	namespace core
	{
		class CORE_API ScoreKeeper
		{
		public:
			// Sets how many lines were cleared in a single drop.
			// Accumulates points based on this number of lines cleared.
			//	1 (single) 	40
			//	2 (double)	100
			//	3 (triple)	300
			//	4 (tetris)	1200
			void nLinesCleared(int nLinesCleared);
			
			void incrementTurnCount() { turnNumber++; }

			void reset() { score = 0; turnNumber = 0; }

			friend std::ostream& operator<<(std::ostream& os, const ScoreKeeper& scoreKeeper);

			int getScore() const { return score; }

			int getTurnNumber() const { return turnNumber; }

		private:
			int score = 0;

			int turnNumber = 0;
		};
	}
}
