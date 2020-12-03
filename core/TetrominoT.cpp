#include "pch.h"
#include "TetrominoT.h"

namespace tetris
{
	namespace core
	{
		TetrominoT::TetrominoT() :
			TetrominoBase(3, 3)
		{
			at(0, 1) = T;
			at(1, 0) = T;
			at(1, 1) = T;
			at(1, 2) = T;
		}
	}
}