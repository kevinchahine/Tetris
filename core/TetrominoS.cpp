#include "pch.h"
#include "TetrominoS.h"

namespace tetris
{
	namespace core
	{
		TetrominoS::TetrominoS() :
			TetrominoBase(3, 3)
		{
			at(0, 1) = S;
			at(0, 2) = S;
			at(1, 0) = S;
			at(1, 1) = S;
		}
	}
}