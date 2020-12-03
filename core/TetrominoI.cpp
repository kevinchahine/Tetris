#include "pch.h"
#include "TetrominoI.h"

namespace tetris
{
	namespace core
	{
		TetrominoI::TetrominoI() :
			TetrominoBase(4, 4)
		{
			at(1, 0) = I;
			at(1, 1) = I;
			at(1, 2) = I;
			at(1, 3) = I;
		}
	}
}