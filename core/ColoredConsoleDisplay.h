#pragma once

#include "core.h"
#include "DisplayBase.h"
#include "ColoredChar.h"

#include <boost/multi_array.hpp>	// Fix this, break down into only what we need

#include <memory>

namespace tetris
{
	namespace core
	{
		class CORE_API ColoredConsoleDisplay : public DisplayBase
		{
		public:
			ColoredConsoleDisplay();
			ColoredConsoleDisplay(const ColoredConsoleDisplay &) = default;
			ColoredConsoleDisplay(ColoredConsoleDisplay &&) noexcept = default;
			virtual ~ColoredConsoleDisplay() noexcept = default;
			ColoredConsoleDisplay & operator=(const ColoredConsoleDisplay &) = default;
			ColoredConsoleDisplay & operator=(ColoredConsoleDisplay &&) noexcept = default;

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

			using array_type = boost::multi_array<ColoredChar, 2>;
			using view_type = array_type::array_view<2>::type;

			array_type m_fullImage;

			// --- Views (of m_fullImage) ---

			// Box showing the held piece
			// Submatrix of m_fullImage
			std::unique_ptr<view_type> m_heldPieceView;

			// Box showing all the placed pieces and the falling piece
			// Submatrix of m_fullImage
			std::unique_ptr<view_type> m_boardView;

			// Box showing score
			// Submatrix of m_fullImage
			std::unique_ptr<view_type> m_scoreView;

			// Box showing the next piece generated
			// Submatrix of m_fullImage
			std::unique_ptr<view_type> m_nextPieceView;
		};
	}
}
