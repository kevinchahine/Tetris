#pragma once

#include "core.h"
#include "Board.h"
#include "Move.h"
#include "TetrominoBase.h"
#include "RandomizedBag.h"
#include "ScoreKeeper.h"
#include "MoveStatePair.h"

#include <typeinfo>
#include <iterator>

#pragma warning (disable: 4251)

namespace tetris
{
	namespace core
	{
		class CORE_API Game
		{
		public:

			void awake();

			void update(const tetris::core::Move& move);

			// Determines if a move will keep the falling piece inbounds. 
			// Does not consider other pieces on the board.
			// Can be used to check bounds of any sides of the board.
			// ex:
			//  using namespace tetris::core;
			//	tetris::core::Game g;
			//	tetris::core::Move m;
			//
			//	// Check to see if move will keep falling piece under top boarder and
			//  // between left and right boarders.
			//  // But doesn't consider bottom boarder.
			//	bool isIn = g.isInBounds(m, Board::TOP | Board::LEFT | Board::RIGHT);
			// 
			// WARNING: Only use for regular moves: SPIN, LEFT, RIGHT, DOWN
			//			Do not use for SWAP.
			bool isSafe(const Move& move) const;

			// See comments of overload
			bool isSafe(const TetrominoBase& fallingPiece) const;

			// Moves falling piece even if it ends up off the edge of the board
			// or overlapping an occupied space
			// Only call this method if move will not cause piece to move out of bounds
			void moveFast(const Move& move);

			// See comments of overload
			void moveFast(TetrominoBase&& fallingPiece);

			// Moves falling piece according to move
			// But only if the move will keep the piece inside the board
			// Does not accound for the top boarder
			bool moveSafe(const Move& move);

			// See comments of overload
			void moveSafe(TetrominoBase&& fallingPiece);

			// Generates all valid moves from the current state excluding swap
			// Stores them in a MoveStatePair so that both the move and the destination state can be saved
			// The state is represented by the falling tetromino piece only.
			// C is to be a container class that that stores MoveStatePairs and has a push_back function
			// ex: std::vector<tetris::core::MoveStatePair>
			template<typename C>
			void generateMoves(C & dstContainer, bool leaveOutSwap = false) const;

			void loadNextPiece();

			// Swaps the fallingpiece with the held piece
			// Places piece at the top 
			void swapPieces();

			// Returns true iff a piece has been placed on the top row
			bool isGameOver() const;

			// Clears all full rows
			// And keeps score
			void clearFullRows();

			// Determines if the piece can move down without overlaping any occupied
			// cells or falling below the bottom boarder
			// Make sure falling piece is inbounds from left to right before calling this method
			// Its ok if piece goes above top row or below bottom row
			bool isLaying() const;

			// Places the falling piece where it is on the board.
			// After calling this method, next falling piece needs to 
			// be recreated by calling .loadNextPiece()
			void placeFallingPiece();

			// ------------------------ ACCESSORS ---------------------------------------

			Board& board() { return m_board; }
			const Board& board() const { return m_board; }

			TetrominoBase& fallingPiece() { return m_fallingPiece; }
			const TetrominoBase& fallingPiece() const { return m_fallingPiece; }

			TetrominoBase& nextPiece() { return m_nextPiece; }
			const TetrominoBase& nextPiece() const { return m_nextPiece; }

			TetrominoBase& heldPiece() { return m_heldPiece; }
			const TetrominoBase& heldPiece() const { return m_heldPiece; }

			ScoreKeeper& scoreKeeper() { return m_scoreKeeper; }
			const ScoreKeeper& scoreKeeper() const { return m_scoreKeeper; }

		protected:
			Board m_board;

			TetrominoBase m_fallingPiece;

			TetrominoBase m_nextPiece;

			TetrominoBase m_heldPiece;

			RandomizedBag bag;

			ScoreKeeper m_scoreKeeper;
		};

		// ------------------------ Template Definitions ----------------------------
		template<typename C>
		void Game::generateMoves(C & dstContainer, bool leaveOutSwap) const
		{
			using namespace std;
			
			bool overlaps;
			TetrominoBase falling;
			
			// --- DOWN ---
			falling = m_fallingPiece;
			falling.moveDown();
			overlaps = m_board.overlaps(falling, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.emplace_back(MoveStatePair(Move::DOWN, falling));
			}
			
			// --- LEFT ---
			falling = m_fallingPiece;
			falling.moveLeft();
			overlaps = m_board.overlaps(falling, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.emplace_back(MoveStatePair(Move::LEFT, falling));
			}
			
			// --- RIGHT ---
			falling = m_fallingPiece;
			falling.moveRight();
			overlaps = m_board.overlaps(falling, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.emplace_back(MoveStatePair(Move::RIGHT, falling));
			}
			
			// --- SPIN ---
			falling = m_fallingPiece;
			falling.spin();
			
			while (m_board.isInBounds(falling, Board::LEFT) == false) {
				falling.moveRight();
			}
			
			while (m_board.isInBounds(falling, Board::RIGHT) == false) {
				falling.moveLeft();
			}
			overlaps = m_board.overlaps(falling, Board::TOP | Board::BOTTOM | Board::LEFT | Board::RIGHT);
			if (!overlaps) {
				dstContainer.emplace_back(MoveStatePair(Move::SPIN, falling));
			}
			
			// --- SWAP ---
			if (leaveOutSwap == true) {
				// swap is always valid move
				falling = m_fallingPiece;
				dstContainer.emplace_back(MoveStatePair(Move::SWAP, falling));
			}
		}
	}
}