#include "pch.h"
#include "SolutionSequence.h"

#include <Tetris/core/Board.h>

#include <algorithm>
#include <iterator>

using namespace tetris::core;
using namespace std;

namespace tetris
{
	namespace ai 
	{
		SolutionSequence::SolutionSequence(const TetrominoBase& falling) :
			m_falling(falling) 
		{}

		SolutionSequence::SolutionSequence(TetrominoBase&& falling) :
			m_falling(std::move(falling)) 
		{}

		void SolutionSequence::moveDown()
		{
			m_sequence.push_back(Move::DOWN);

			m_falling.moveDown();
		}

		void SolutionSequence::moveLeft()
		{
			m_sequence.push_back(Move::LEFT);

			m_falling.moveLeft();
		}

		void SolutionSequence::moveRight()
		{
			m_sequence.push_back(Move::RIGHT);

			m_falling.moveRight();
		}

		void SolutionSequence::moveSpin(const core::Board& board)
		{
			m_sequence.push_back(Move::SPIN);

			m_falling.spin(board);
		}

		void SolutionSequence::move(core::Move move, const core::Board& board)
		{
			m_sequence.push_back(move);

			m_falling.move(move, board);
		}
	}
}
