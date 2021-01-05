#pragma once
#include "core.h"

#include "TetrominoBase.h"
#include "Board.h"

namespace tetris
{
	namespace core
	{
		// Generates all valid moves from the current state excluding swap
		// Stores them in a tetris::core::Move
		// C is to be a container class that that stores tetris::core::Move and has a push_back function
		// ex: std::vector<tetris::core::Move>
		template<typename C>
		void generateMoves(
			C& dstContainer,				// destination
			const Board& board,				
			const TetrominoBase& falling, 
			bool leaveOutSwap = true);

		// ---------------------------------- Definitions ---------------------------

		template<typename C>
		void generateMoves(C& dstContainer, const Board& board, const TetrominoBase& fallingPiece, bool leaveOutSwap)
		{
			using namespace std;

			bool overlaps;
			TetrominoBase falling;

			// --- DOWN ---
			falling = fallingPiece;
			falling.moveDown();
			overlaps = board.overlaps(falling, Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.push_back(Move::DOWN);
			}

			// --- LEFT ---
			falling = fallingPiece;
			falling.moveLeft();
			overlaps = board.overlaps(falling,  Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.push_back(Move::LEFT);
			}

			// --- RIGHT ---
			falling = fallingPiece;
			falling.moveRight();
			overlaps = board.overlaps(falling, Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.push_back(Move::RIGHT);
			}

			// --- SPIN ---
			falling = fallingPiece;
			falling.spin();

			while (board.isInBounds(falling, Board::LEFT) == false) {
				falling.moveRight();
			}

			while (board.isInBounds(falling, Board::RIGHT) == false) {
				falling.moveLeft();
			}
			overlaps = board.overlaps(falling, Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.push_back(Move::SPIN);
			}

			// --- SWAP ---
			if (leaveOutSwap == false) {
				// swap is always valid move but sometimes we don't want to use it
				falling = fallingPiece;
				dstContainer.push_back(Move::SWAP);
			}
		}
	}
}