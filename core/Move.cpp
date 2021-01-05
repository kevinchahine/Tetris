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

		bool Move::setMove(char move)
		{
			move = tolower(move);

			if (move == Move::SPIN ||      
				move == Move::DOWN || 		
				move == Move::LEFT || 		
				move == Move::RIGHT || 	
				move == Move::NONE || 		
				move == Move::SWAP || 		
				move == Move::PLACE || 	
				move == Move::PENDING || 	
				move == Move::EXIT) 
			{
				this->move = move;

				return true;
			}
			else 
			{
				return false;
			}
		}

		char Move::getMove() const
		{
			return move;
		}
	}
}