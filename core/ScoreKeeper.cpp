#include "pch.h"
#include "ScoreKeeper.h"

namespace tetris
{
	namespace core
	{
		std::ostream& operator<<(std::ostream& os, const ScoreKeeper& scoreKeeper)
		{
			os << iocolor::setfg(iocolor::YELLOW) << scoreKeeper.score << " points "
				<< iocolor::setfg(iocolor::GREEN) << scoreKeeper.turnNumber << " turns";

			return os;
		}

		void ScoreKeeper::add(int points)
		{
			score += points;
		}
	}
}
