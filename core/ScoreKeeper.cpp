#include "pch.h"
#include "ScoreKeeper.h"

#include <iocolor/iocolor.h>

using namespace std;

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

		void ScoreKeeper::nLinesCleared(int nLinesCleared)
		{
			switch (nLinesCleared)
			{
			case 0:					break;
			case 1: score += 40	 ;	break;
			case 2:	score += 100 ;	break;
			case 3:	score += 300 ;	break;
			case 4:	score += 1200;	break;
			default:	cout << "You can't possibly clear " << nLinesCleared << " lines in a single turn.\n"; break;
			}
		}
	}
}
