#include "pch.h"
#include "Move.h"

namespace tetris
{
	namespace core
	{
		Move::Move(char ch) :
			move(ch)
		{
		}

		Move& Move::operator=(char ch)
		{
			this->move = ch;

			return *this;
		}

		bool Move::operator==(char move) const
		{
			return this->move == move;
		}

		bool Move::setMove(char move)
		{
			switch (move)
			{
			case Move::SPIN:    this->move = move;  return true;
			case Move::DOWN:    this->move = move;  return true;
			case Move::LEFT:    this->move = move;  return true;
			case Move::RIGHT:   this->move = move;  return true;
			case Move::NONE:    this->move = move;  return true;
			case Move::SWAP:	this->move = move;	return true;
			case Move::PENDING: this->move = move;  return true;
			case Move::EXIT:	this->move = move;  return true;
			default:                                return false;
			}
		}

		char Move::getMove() const
		{
			return move;
		}
	}
}