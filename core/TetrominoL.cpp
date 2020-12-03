#include "pch.h"
#include "TetrominoL.h"

namespace tetris
{
	namespace core
	{
		TetrominoL::TetrominoL() :
			TetrominoBase(3, 3)
		{
			at(0, 2) = L;
			at(1, 0) = L;
			at(1, 1) = L;
			at(1, 2) = L;
		}
	}
}