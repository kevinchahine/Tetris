#include "pch.h"
#include "ColoredConsoleDisplay.h"

#include <iostream>
#include <array>

#include <iocolor/iocolor.h>

using namespace std;

namespace tetris
{
	namespace core
	{
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
			// --- Calculate size of image ---
			const size_t N_ROWS = game.board().rows + 3;
			const size_t N_COLS = game.board().cols + 16;

			// --- Full Image ---
			using array_type = boost::multi_array<int, 3>;

			array_type::extent_gen extents;

			m_fullImage.resize(extents[N_ROWS][N_COLS]);	

			for (size_t row = 0; row < N_ROWS; row++) {
				for (size_t col = 0; col < N_COLS; col++) {
					m_fullImage[row][col] = ColoredChar(' ', iocolor::WHITE, iocolor::BLACK);
				}
			}

			// --- HeldPieceBox ---

			// --- BoardBox ---
			
			// --- ScoreBox ---
			
			// --- NextPieceBox ---

		}

		void ColoredConsoleDisplay::drawMainBoarder()
		{
			auto shape = m_fullImage.shape();
			const size_t N_ROWS = shape[0];
			const size_t N_COLS = shape[1];

			// --- TOP + BOTTOM ---
			for (int col = 0; col < N_COLS; col++) {
				m_fullImage[0][col] = ColoredChar('-', iocolor::BLUE);
				m_fullImage[N_ROWS - 1][col] = ColoredChar('-', iocolor::BLUE);
			}

			// --- LEFT + RIGHT ---
			for (int row = 0; row < N_ROWS; row++) {
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
