#pragma once

#include "core.h"
#include "DisplayBase.h"
#include "ColoredChar.h"

#include <boost/multi_array.hpp>	// Fix this, break down into only what we need

namespace tetris
{
	namespace core
	{
		class CORE_API ColoredConsoleDisplay : public DisplayBase
		{
		public:
			
			virtual void rasterize(const Game& game) override;

			virtual void show() override;

			virtual std::string name() override;

		protected:
			// Sets all views (sub-arrays) (i.e. m_heldPiece, m_nextPiece, m_board) to be sub arrays
			// of m_fullImage. It adjusts its size to the size of the board determined by the call to
			// .setBoardSize()
			void resetImages(const Game & game);

			void drawMainBoarder();

			void drawHeldPieceBox(const Game& game);

			void drawBoardBox(const Game& game);

			void drawScoreBox(const Game& game);

			void drawNextPieceBox(const Game& game);

			void drawTetromino(cv::Mat& m_img, const TetrominoBase& piece, bool isGhost = false);

		protected:

			boost::multi_array<ColoredChar, 2> m_fullImage;

			// --- Views (of m_fullImage) ---

			// Box showing the held piece
			// Submatrix of m_fullImage
			boost::multi_array<ColoredChar, 2>  m_heldPieceBox;

			// Box showing all the placed pieces and the falling piece
			// Submatrix of m_fullImage
			boost::multi_array<ColoredChar, 2>  m_boardBox;

			// Box showing score
			// Submatrix of m_fullImage
			boost::multi_array<ColoredChar, 2>  m_scoreBox;

			// Box showing the next piece generated
			// Submatrix of m_fullImage
			boost::multi_array<ColoredChar, 2>  m_nextPieceBox;
		};
	}
}
