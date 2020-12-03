#include "pch.h"
#include "TetrominoJ.h"

namespace tetris
{
	namespace core
	{
		TetrominoJ::TetrominoJ() :
			TetrominoBase(3, 3)
		{
			at(0, 0) = J;
			at(1, 0) = J;
			at(1, 1) = J;
			at(1, 2) = J;
		}
	}
}