#include "pch.h"
#include "Game.h"
#include "Tetrominos.hpp"

#include <iocolor/iocolor.h>

#include <algorithm>

#include <opencv2/highgui.hpp>

using namespace std;

namespace tetris
{
	namespace core
	{
		void Game::awake()
		{
			m_board.clear();

			m_heldPiece = bag.nextTetromino();

			m_nextPiece = bag.nextTetromino();

			loadNextPiece();
		}

		void Game::update(const tetris::core::Move& move)
		{
			// --- Apply move if it is safe ---
			bool isSafe = this->moveSafe(move);
			///if (this->isSafe(move)) {
			///	this->moveFast(move);
			///}

			cout << "Move is " << (isSafe ? "Safe" : " Unsafe") << '\t';
			cout << "Hash = " << hash<MoveStatePair>{}(MoveStatePair{ move, m_fallingPiece }) << '\t';

			static int layingCount = 0;
			if (this->isLaying()) {
				layingCount++;
				cout << "Laying " << layingCount << "\t";

				if (layingCount >= 2) {
					this->placeFallingPiece();
					this->clearFullRows();
					this->loadNextPiece();
					layingCount = 0;
				}
			}
			else {
				layingCount = 0;
			}

			if (isSafe) {
				m_scoreKeeper.incrementTurnCount();
				if (this->isGameOver()) {
					cout << iocolor::push()
						<< iocolor::setfg(iocolor::RED)
						<< "Game Over!!!\n"
						<< iocolor::pop();
				}
			}

			cout << '\n';
		}

		bool Game::isSafe(const Move& move) const
		{
			if (move != Move::SWAP) {
				// Save the state of the falling piece so that we can restore it later
				TetrominoBase currFallingPiece = m_fallingPiece;

				// Apply the move the falling piece
				const_cast<Game&>(*this).moveFast(move);

				// See if the falling piece is out of bounds or overlapping an occupied cell
				bool overlaps = m_board.overlaps(m_fallingPiece, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);

				// Restore previous state of the falling piece
				const_cast<TetrominoBase&>(m_fallingPiece) = currFallingPiece;

				// As long as the move won't make the falling piece overlap, then the move is a safe move.
				return !overlaps;
			}
			else {
				return true;
			}
		}

		bool Game::isSafe(const TetrominoBase& fallingPiece) const
		{
			return false;
		}

		void Game::moveFast(const Move& move)
		{
			switch (move.getMove())
			{
			case Move::NONE:    m_fallingPiece.moveDown();	break;	// same as DOWN
			case Move::DOWN:    m_fallingPiece.moveDown();	break;
			case Move::LEFT:    m_fallingPiece.moveLeft();	break;
			case Move::RIGHT:   m_fallingPiece.moveRight();	break;
			case Move::SPIN:
				m_fallingPiece.spin();

				while (m_board.isInBounds(m_fallingPiece, Board::LEFT) == false) {
					m_fallingPiece.moveRight();
				}

				while (m_board.isInBounds(m_fallingPiece, Board::RIGHT) == false) {
					m_fallingPiece.moveLeft();
				}
				break;
			case Move::SWAP:	swapPieces();				break;
			default:			throw Move::BadMove();		break;
			}
		}

		bool Game::moveSafe(const Move& move)
		{
			if (move != Move::SWAP) {
				// Save the state of the falling piece so that we can restore it later
				TetrominoBase currFallingPiece = m_fallingPiece;

				// Apply the move the falling piece
				const_cast<Game&>(*this).moveFast(move);

				// See if the falling piece is out of bounds or overlapping an occupied cell
				bool overlaps = m_board.overlaps(m_fallingPiece, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);

				// Was the move safe?
				if (overlaps == true) {
					// Move was not safe, we need to restore the previous state.
					// Restore previous state of the falling piece
					const_cast<TetrominoBase&>(m_fallingPiece) = currFallingPiece;

					return false;	// Unsafe move
				}
				else {
					return true;	// Safe move
				}
			}
			else {
				moveFast(move);

				return true;		// Swap is always a safe move
			}
		}

		void Game::loadNextPiece()
		{
			m_fallingPiece = m_nextPiece;

			// Place falling piece at very top of board
			m_fallingPiece.position() = cv::Point{ 4, -1 };

			// Move down falling piece until it is completely below top boarder
			while (m_board.isInBounds(m_fallingPiece, Board::TOP) == false) {
				m_fallingPiece.moveDown();
			}

			m_nextPiece = bag.nextTetromino();
		}

		void Game::swapPieces()
		{
			m_heldPiece.print();
			m_fallingPiece.print();

			swap(m_heldPiece, m_fallingPiece);

			// Place falling piece at very top of board
			m_fallingPiece.position() = cv::Point{ 4, -1 };

			// Move down falling piece until it is completely below top boarder
			while (m_board.isInBounds(m_fallingPiece, Board::TOP) == false) {
				m_fallingPiece.moveDown();
			}

			m_heldPiece.position() = cv::Point{ 0, 0 };
		}

		bool Game::isGameOver() const
		{
			bool gameOver = any_of(
				&m_board.at(0, 0),
				&m_board.at(0, 0) + m_board.cols,
				[](uint8_t cell) {return cell != TetrominoBase::EMPTY; }
			);

			return gameOver;
		}

		void Game::clearFullRows()
		{
			int nLinesCleared = 0;

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

					nLinesCleared++;
				}
			}

			// Increment score
			m_scoreKeeper.nLinesCleared(nLinesCleared);
		}

		bool Game::isLaying() const
		{
			// Move falling piece down temporarilly
			const_cast<TetrominoBase&>(m_fallingPiece).moveDown();

			// See if the falling piece overlaps any occupied cells
			bool overlaps = m_board.overlaps(m_fallingPiece);

			// Move falling piece back up to where it was before
			const_cast<TetrominoBase&>(m_fallingPiece).moveUp();

			// If moving down causes no overlaps, then falling piece can
			// move down	
			return overlaps;
		}

		void Game::placeFallingPiece()
		{
			m_board.pasteAt(m_fallingPiece);
		}
	}
}