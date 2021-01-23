#include "pch.h"
#include "ColoredConsoleDisplay.h"

#include <iostream>
#include <array>

#include <iocolor/iocolor.h>

using namespace std;

using range = boost::multi_array_types::index_range;

namespace tetris
{
	namespace core
	{
		ColoredConsoleDisplay::ColoredConsoleDisplay()
		{
			m_heldPieceView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[range(0, 0)][range(0, 0)]]);

			m_boardView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[range(0, 0)][range(0, 0)]]);

			m_scoreView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[range(0, 0)][range(0, 0)]]);
			
			m_nextPieceView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[range(0, 0)][range(0, 0)]]);
		}

		void ColoredConsoleDisplay::rasterize(const Game & game)
		{
			resetImages(game);

			drawMainBoarder();

			drawHeldPieceBox(game);

			drawBoardBox(game);

			drawScoreBox(game);

			drawNextPieceBox(game);

			//void drawTetromino(m_img, const TetrominoBase& piece, bool isGhost = false);
			
		}

		void ColoredConsoleDisplay::show()
		{
			auto shape = m_fullImage.shape();
			
			const size_t N_ROWS = shape[0];
			const size_t N_COLS = shape[1];
			
			cout << iocolor::push();
			
			for (size_t row = 0; row < N_ROWS; row++) {
			
				cout << iocolor::push();
			
				for (size_t col = 0; col < N_COLS; col++) {
					cout << m_fullImage[row][col];
				}
			
				cout << iocolor::pop() << '\n';
			}
			
			cout << iocolor::pop() << '\n';
		}

		std::string ColoredConsoleDisplay::name()
		{
			return "Colored Console";
		}

		void ColoredConsoleDisplay::resetImages(const Game & game)
		{
			/* General Layout:
				+------------------------------+
				| +----+ +-------------+ +----+|
				| |@@  | |             | | #  ||
				| | @@ | |             | | ###||
				| +----+ |             | +----+|
				| +----+ |             |       |
				| |S:40| |             |       |
				| |T:10| |        @    |       |
				| +----+ |       @@@   |       |
				|        |             |       |
				|        |             |       |
				|        |             |       |
				|        |             |       |
				|        |      #      |       |
				|        |     ##$$ %  |       |
				|        |  @@@@#$$%%% |       |
				|        +-------------+       |
				+------------------------------+
			*/
			
			// --- Calculate size of image ---
			const size_t N_ROWS = max(game.board().rows + 3, 8);
			const size_t N_COLS = max(game.board().cols + 16, 20);

			// --- Full Image ---
			
			array_type::extent_gen extents;
			
			m_fullImage.resize(extents[N_ROWS][N_COLS]);	
			cout << "We now have " << m_fullImage.shape()[0] << " rows \n"
				<< "\t and " << m_fullImage.shape()[1] << " cols.\n";

			for (size_t row = 0; row < N_ROWS; row++) {
				for (size_t col = 0; col < N_COLS; col++) {
					m_fullImage[row][col] = ColoredChar(' ', iocolor::WHITE, iocolor::BLACK);
				}
			}
			
			array_type::index_gen indicies;
			
			// --- HeldPieceBox ---
			range rowRange1 = range(1, 7);
			range colRange1 = range(1, 7);
			m_heldPieceView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[rowRange1][colRange1]]);
			
			// --- BoardBox ---
			range rowRange2 = range(1, 1 + m_boardSize.width);
			range colRange2 = range(7, 7 + m_boardSize.height);
			m_boardView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[rowRange2][colRange2]]);
			
			// --- ScoreBox ---
			range rowRange3 = range(rowRange1.finish(), rowRange1.finish() + 7);
			range colRange3 = range(1, 7);
			m_boardView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[rowRange3][colRange3]]);
			
			// --- NextPieceBox ---
			range rowRange4 = range(1, 7);
			range colRange4 = range(colRange2.finish(), colRange2.finish() + 7);
			m_scoreView = make_unique<array_type::array_view<2>::type>(
				m_fullImage[boost::indices[rowRange4][colRange4]]);
		}

		void ColoredConsoleDisplay::drawMainBoarder()
		{
			auto shape = m_fullImage.shape();
			const size_t N_ROWS = shape[0];
			const size_t N_COLS = shape[1];
			
			// --- TOP + BOTTOM ---
			for (size_t col = 0; col < N_COLS; col++) {
				m_fullImage[0][col] = ColoredChar('-', iocolor::BLUE);
				m_fullImage[N_ROWS - 1][col] = ColoredChar('-', iocolor::BLUE);
			}
			
			// --- LEFT + RIGHT ---
			for (size_t row = 0; row < N_ROWS; row++) {
				m_fullImage[row][0] = ColoredChar('|', iocolor::BLUE);
				m_fullImage[row][N_COLS - 1] = ColoredChar('|', iocolor::BLUE);
			}
			
			// --- Corners ---
			m_fullImage[0][0] = ColoredChar('+', iocolor::BLUE);
			m_fullImage[N_ROWS - 1][0] = ColoredChar('+', iocolor::BLUE);
			m_fullImage[0][N_COLS - 1] = ColoredChar('+', iocolor::BLUE);
			m_fullImage[N_ROWS - 1][N_COLS - 1] = ColoredChar('+', iocolor::BLUE);
			
		}

		void ColoredConsoleDisplay::drawHeldPieceBox(const Game & game)
		{
		}
		
		void ColoredConsoleDisplay::drawBoardBox(const Game & game)
		{
		}
		
		void ColoredConsoleDisplay::drawScoreBox(const Game & game)
		{
		}
		
		void ColoredConsoleDisplay::drawNextPieceBox(const Game & game)
		{
		}
		
		void ColoredConsoleDisplay::drawTetromino(cv::Mat & m_img, const TetrominoBase & piece, bool isGhost)
		{
		}
	}
}
