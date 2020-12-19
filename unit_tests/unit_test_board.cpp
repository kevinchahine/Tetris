#include "pch.h"
#include "CppUnitTest.h"

#include <Tetris/core/Game.h>
#include <Tetris/core/Tetrominos.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace tetris::core;

namespace tetris
{
	namespace unit_tests
	{
		TEST_CLASS(UnitTestBoard)
		{
		public:

			TEST_METHOD(overlaps)
			{
				Game game;
				
				TetrominoBase piece = TetrominoO();
				piece.position() = cv::Point(4, 4);

				Assert::IsFalse(game.board().overlaps(piece));

				game.board().pasteAt(piece);

				Assert::IsTrue(game.board().overlaps(piece));

				piece.position() = cv::Point(-1, 4);

				Assert::IsTrue(game.board().overlaps(piece));

				Assert::IsFalse(game.board().overlaps(piece, Board::TOP | Board::RIGHT | Board::BOTTOM));

			}
		};
	}
}
