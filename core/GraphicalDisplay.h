#pragma once

#include <iostream>

#include "core.h"
#include "DisplayBase.h"

#pragma warning ( push, 3 )
#include <opencv2/core/mat.hpp>
#pragma warning ( pop )

#pragma warning (disable: 4251)

namespace tetris
{
	namespace core
	{
		class CORE_API GraphicalDisplay : public DisplayBase
		{
		public:
			virtual void rasterize(const Game& game) override;

			virtual void show() override;

			cv::Size& cellSize() { return m_cellSize; }
			const cv::Size & cellSize() const { return m_cellSize; }

		protected:
			// Sets all cv::Mat fields (i.e. m_heldPiece, m_nextPiece, m_board) to be sub matricies
			// of m_fullImage. It adjusts its size to the size of the board determined by the call to
			// .setBoardSize()
			void resetSubImages();

			void drawHeldPieceBox(const Game& game);

			void drawBoardBox(const Game& game);

			void drawScoreBox(const Game& game);

			void drawNextPieceBox(const Game& game);

			void drawTetromino(cv::Mat& m_img, const TetrominoBase& piece, bool isGhost = false);

		protected:
			
			// Size of cell in pixels (length and width)
			cv::Size m_cellSize = cv::Size{ 30, 30 };

			// Stores full image that everythings gets copied to 
			// This is what gets shown when calling .show()
			cv::Mat m_fullImage;

			// Box showing the held piece
			// Submatrix of m_fullImage
			cv::Mat m_heldPieceBox;

			// Box showing all the placed pieces and the falling piece
			// Submatrix of m_fullImage
			cv::Mat m_boardBox;

			// Box showing score
			// Submatrix of m_fullImage
			cv::Mat m_scoreBox;

			// Box showing the next piece generated
			// Submatrix of m_fullImage
			cv::Mat m_nextPieceBox;
		};
	}
}