#include "TestMoveSequence.h"

#include <Tetris/core/Board.h>

#include <iostream>

using namespace tetris::core;
using namespace tetris::ai;
using namespace std;

namespace tetris
{
	namespace driver
	{
		void testSolutionSequencePrint()
		{
			SolutionSequence seq;
			Board board;

			seq.moveDown();

			seq.moveLeft();

			seq.moveRight();

			seq.moveSpin(board);

			seq.move(Move::DOWN, board);

			seq.move(Move::LEFT, board);

			seq.move(Move::RIGHT, board);

			seq.move(Move::SPIN, board);

			seq.print(cout);

		}
	}
}
