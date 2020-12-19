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
				
				// Place piece in middle
				piece.position() = cv::Point(4, 4);

				Assert::IsFalse(game.board().overlaps(piece));			// should not overlap

				// Put something in the way
				game.board().pasteAt(piece);							

				Assert::IsTrue(game.board().overlaps(piece));			// should overlap

				// Remove piece
				game.board().removeFrom(piece);

				// Move to LEFT edge
				piece.position() = cv::Point(-1, 4);

				Assert::IsTrue(game.board().overlaps(piece));			// Overlap
				
																		// No Overlap
				Assert::IsFalse(game.board().overlaps(piece, Board::TOP | Board::RIGHT | Board::BOTTOM));

				// Move to CENTER
				piece.position() = cv::Point(4, 4);						// No Overlap
				Assert::IsFalse(game.board().overlaps(piece, Board::TOP | Board::RIGHT | Board::BOTTOM));

				// Move to RIGHT edge
				piece.position() = cv::Point(game.board().cols, 4);

				Assert::IsTrue(game.board().overlaps(piece, Board::ALL_EDGES));	// Overlap

																		// No Overlap
				Assert::IsFalse(game.board().overlaps(piece, Board::TOP | Board::LEFT | Board::BOTTOM));

			}
		};
	}
}
