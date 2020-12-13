#include "pch.h"
#include "GraphicalDisplay.h"

#include <iostream>

#pragma warning ( push, 3 )
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#pragma warning ( pop )

using namespace std;

namespace tetris
{
	namespace core
	{
		void GraphicalDisplay::rasterize(const Game& game)
		{
			// Check to see if the size of the game board has changed (or hasn't been set yet)
			if (m_boardSize != game.board().size()) {
				m_boardSize = game.board().size();
				resetSubImages();
			}

			// Draw all the boxes

			drawHeldPieceBox(game);

			drawBoardBox(game);

			drawScoreBox(game);

			drawNextPieceBox(game);
		}

		void GraphicalDisplay::show()
		{
			cv::imshow("TETRIS", m_fullImage);
			cv::waitKey(1);
		}

		void GraphicalDisplay::resetSubImages()
		{
			/* General Layout:
			* +------------------------------+
			* | +----+ +-------------+ +----+|
			* | |@@  | |             | | #  ||
			* | | @@ | |             | | ###||
			* | +----+ |             | +----+|
			* | +----+ |             |       |
			* | |S:40| |             |       |
			* | |T:10| |        @    |       |
			* | +----+ |       @@@   |       |
			* |        |             |       |
			* |        |             |       |
			* |        |             |       |
			* |        |             |       |
			* |        |      #      |       |
			* |        |     ##$$ %  |       |
			* |        |  @@@@#$$%%% |       |
			* |        +-------------+       |
			* +------------------------------+
			*/
			
			cv::Size pieceBoxSize = m_cellSize * 4;
			
			cv::Size boardBoxSize = cv::Size{ 
				m_cellSize.width * m_boardSize.width, 
				m_cellSize.height * m_boardSize.height };

			cv::Size fullImageSize = cv::Size{
				pieceBoxSize.width * 2 + boardBoxSize.width,
				boardBoxSize.height };

			// --- Resize full image (that contains everthing) ---
			m_fullImage = cv::Mat::zeros(fullImageSize, CV_8UC3) + GRAY;

			// --- Held Piece (On the left) ---
			cv::Point heldPiecePos = cv::Point{ 0, 0 };
			m_heldPieceBox = m_fullImage(cv::Rect{ heldPiecePos, pieceBoxSize });

			// --- Board (In the middle) ---
			cv::Point boardPos = cv::Point{ pieceBoxSize.width, 0 };
			m_boardBox = m_fullImage(cv::Rect{ boardPos, boardBoxSize });

			// --- Score (On the left) ---
			cv::Point scorePos = cv::Point{ 0, heldPiecePos.y + m_heldPieceBox.cols };
			m_scoreBox = m_fullImage(cv::Rect{ scorePos, pieceBoxSize });

			// --- Next Piece (On the right) ---
			cv::Point nextPiecePos = cv::Point{ pieceBoxSize.width + boardBoxSize.width, 0 };
			m_nextPieceBox = m_fullImage(cv::Rect{ nextPiecePos, pieceBoxSize });
		}

		void GraphicalDisplay::drawHeldPieceBox(const Game& game)
		{
			// Black out board section
			cv::rectangle(m_heldPieceBox, cv::Rect{ cv::Point{0, 0}, m_heldPieceBox.size() }, BLACK, -1);

			// Alias some objects 
			const Board& board = game.board();
			const TetrominoBase& piece = game.heldPiece();
			
			// Draw held piece
			drawTetromino(m_heldPieceBox, piece);

			cv::putText(m_heldPieceBox, "Held", cv::Point{ 0, m_heldPieceBox.cols * 7 / 8 }, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{ 255, 255, 255 }, 1, cv::LINE_AA, false);
		}

		void GraphicalDisplay::drawBoardBox(const Game& game)
		{
			// Black out board section
			cv::rectangle(m_boardBox, cv::Rect{ cv::Point{0, 0}, m_boardBox.size() }, BLACK, -1);

			// Draw placed pieces
			const Board& board = game.board();

			for (int r = 0; r < board.rows; r++) {
				for (int c = 0; c < board.cols; c++) {
					cv::Scalar color = shades[board.at(r, c)];

					cv::rectangle(m_boardBox, cv::Rect{ cv::Point{ c * m_cellSize.width, r * m_cellSize.height}, m_cellSize }, color, -1);
					//cv::rectangle(m_board, cv::Rect{ cv::Point{ c * cellSize, r * cellSize}, cv::Size{ cellSize, cellSize } }, BLACK, 1);
				}
			}

			// Draw falling piece
			const TetrominoBase& falling = game.fallingPiece();
			const cv::Point& pos = game.fallingPiece().position();

			drawTetromino(m_boardBox, falling);

			// Draw falling piece ghost
			TetrominoBase ghost = falling;

			while (board.overlaps(ghost) == false) {
				ghost.moveDown();
			}
			ghost.moveUp();
			
			drawTetromino(m_boardBox, ghost, true);
		}

		void GraphicalDisplay::drawScoreBox(const Game& game)
		{
			// Black out score box
			cv::rectangle(m_scoreBox, cv::Rect{ cv::Point{0, 0}, m_scoreBox.size() }, BLACK, -1);

			// Alias some objects
			const Board& board = game.board();
			const ScoreKeeper& score = game.scoreKeeper();

			// Draw score
			string scoreText = "Score: " + to_string(score.getScore());
			cv::putText(m_scoreBox, scoreText, cv::Point{ 0, m_scoreBox.cols / 2 }, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{ 255, 255, 255 }, 1, cv::LINE_AA, false);

			// Draw turn number
			string turnNumberText = "Turn: " + to_string(score.getTurnNumber());
			cv::putText(m_scoreBox, turnNumberText, cv::Point{ 0, m_scoreBox.cols * 3 / 4 }, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{ 255, 255, 255 }, 1, cv::LINE_AA, false);
		}

		void GraphicalDisplay::drawNextPieceBox(const Game& game)
		{
			// Black out board section
			cv::rectangle(m_nextPieceBox, cv::Rect{ cv::Point{0, 0}, m_nextPieceBox.size() }, BLACK, -1);

			// Alias some objects 
			const Board& board = game.board();
			const TetrominoBase& piece = game.nextPiece();

			cv::putText(m_nextPieceBox, "Next", cv::Point{ 0, m_nextPieceBox.cols * 7 / 8 }, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar{ 255, 255, 255 }, 1, cv::LINE_AA, false);

			// Draw held piece
			drawTetromino(m_nextPieceBox, piece);
		}

		void GraphicalDisplay::drawTetromino(cv::Mat& m_img, const TetrominoBase& piece, bool isGhost)
		{
			cv::Point pos = piece.position();

			for (int r = 0; r < piece.cols; r++) {
				for (int c = 0; c < piece.rows; c++) {
					if (piece.at(r, c) != TetrominoBase::EMPTY) {
						int rowCoord = pos.y + r;
						int colCoord = pos.x + c;
						if (rowCoord >= 0 &&
							rowCoord < m_img.rows &&
							colCoord >= 0 &&
							colCoord < m_img.cols)
						{
							cv::Scalar color = shades[piece.at(r, c)];

							cv::rectangle(
								m_img, 
								cv::Rect{ cv::Point{ colCoord * m_cellSize.width, rowCoord * m_cellSize.height }, m_cellSize }, 
								color, 
								(isGhost ? 2 : -1));
						}
					}
				}
			}
		}

	} // end of namespace tetris
} // end of namespace core
