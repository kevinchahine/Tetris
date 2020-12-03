#include "pch.h"
#include "Game.h"

#include "Tetrominos.hpp"

using namespace std;

namespace tetris
{
	namespace core
	{
		void Game::awake()
		{
			m_board.clear();

			m_heldPiece = bag.nextTetromino();

			loadNextPiece();
		}

		bool Game::isInBounds(const Move& move, uint8_t edges) const
		{
			cv::Point nextPos = m_fallingPiecePos;

			TetrominoBase falling = m_fallingPiece;

			switch (move.getMove())
			{
			case Move::SPIN:
				falling.spin();

				while (m_board.isInBounds(nextPos, falling, Board::LEFT) == false) {
					nextPos.x++;
				}

				while (m_board.isInBounds(nextPos, falling, Board::RIGHT) == false) {
					nextPos.x--;
				}
				break;
			case Move::DOWN:    nextPos.y++;	break;
			case Move::LEFT:    nextPos.x--;	break;
			case Move::RIGHT:   nextPos.x++;	break;
			case Move::NONE:    nextPos.y++;	break;	// same as DOWN
			default:			nextPos.y++;	break;	// same as DOWN
			}

			return m_board.isInBounds(nextPos, falling, edges);
		}

		void Game::applyMove(const Move& move)
		{
			TetrominoBase falling = m_fallingPiece;

			cv::Point nextPos = m_fallingPiecePos;

			switch (move.getMove())
			{
			case Move::SPIN:
				falling.spin();

				while (m_board.isInBounds(nextPos, falling, Board::LEFT) == false) {
					nextPos.x++;
				}

				while (m_board.isInBounds(nextPos, falling, Board::RIGHT) == false) {
					nextPos.x--;
				}
				break;
			case Move::DOWN:    nextPos.y++;	break;
			case Move::LEFT:    nextPos.x--;	break;
			case Move::RIGHT:   nextPos.x++;	break;
			case Move::NONE:    nextPos.y++;	break;	// same as DOWN
			case Move::SWAP:
				swap(m_heldPiece, m_fallingPiece);

				m_fallingPiecePos = cv::Point{ 4, -1 };

				while (m_board.isInBounds(m_fallingPiecePos, falling, Board::TOP) == false) {
					m_fallingPiecePos.y++;

					return;
				}
			default:			nextPos.y++;	break;	// same as DOWN
			}

			// Did piece reach the bottom or overlap another piece
			if (m_board.fitsAt(nextPos, falling)) {
				m_fallingPiece = falling;

				m_fallingPiecePos = nextPos;
			}
		}

		bool Game::applyMoveIfInBounds(const Move& move)
		{
			if (move == Move::SWAP || isInBounds(move, Board::BOTTOM | Board::LEFT | Board::RIGHT)) {
				applyMove(move);

				return true;
			}
			else {
				return false;
			}
		}

		void Game::loadNextPiece()
		{
			m_fallingPiece = bag.nextTetromino();

			m_fallingPiecePos = cv::Point{ 4, -1 };

			while (m_board.isInBounds(m_fallingPiecePos, m_fallingPiece, Board::TOP) == false) {
				m_fallingPiecePos.y++;
			}
		}

		void Game::swapPieces()
		{
			swap(m_heldPiece, m_fallingPiece);

			m_fallingPiecePos = cv::Point{ 4, -1 };

			while (m_board.isInBounds(m_fallingPiecePos, m_fallingPiece, Board::TOP) == false) {
				m_fallingPiecePos.y++;
			}
		}

		bool Game::isGameOver() const
		{
			for (int c = 0; c < m_board.cols; c++) {
				// Is a piece placed on the top row
				if (m_board.at(0, c) != TetrominoBase::EMPTY) {
					return true;	// Game over
				}
			}

			return false; // Still alive 
		}

		void Game::clearFullRows()
		{
			for (int r = 0; r < m_board.rows; r++) {

				bool containsEmptyCell = false;

				for (int c = 0; c < m_board.cols; c++) {
					if (m_board.at(r, c) == Matrix::EMPTY) {
						containsEmptyCell = true;
						break;
					}
				}

				if (containsEmptyCell == false) {
					m_board.clearRow(r);
				}
			}
		}

		bool Game::pieceCanMoveDown() const
		{
			auto fallingPos = m_fallingPiecePos;

			fallingPos.y++;

			for (int r = 0; r < m_fallingPiece.rows; r++) {
				for (int c = 0; c < m_fallingPiece.cols; c++) {
					if (m_fallingPiece.at(r, c) != Matrix::EMPTY) {
						int rowInBoard = fallingPos.y + r;
						int colInBoard = fallingPos.x + c;

						if (rowInBoard >= 0) {
							if (rowInBoard < m_board.rows) {
								if (m_board.at(rowInBoard, colInBoard) != Matrix::EMPTY) {
									return false;
								}
							}
							else {
								return false;
							}
						}
					}
				}
			}

			return true;
		}

		void Game::placePiece()
		{
			m_board.pasteAt(m_fallingPiecePos, m_fallingPiece);
		}
	}
}