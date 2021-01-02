#pragma once

#include "core.h"

#include <iostream>
#include <exception>

#pragma warning (disable: 4275)		// remove dll-export warning for objects in stl

namespace tetris
{
	namespace core
	{
		class CORE_API Move
		{
		public:
			static const char SPIN = 'w';
			static const char DOWN = 's';
			static const char LEFT = 'a';
			static const char RIGHT = 'd';
			static const char NONE = ' ';
			static const char SWAP = 'q';
			static const char PENDING = '?';	// Still needs more time to decide (Not used)
			static const char EXIT = 'x';		// Exit game (Not really a move, used for convenience)

		public:
			// Exception class representing an invalid, or illegal move move
			class CORE_API BadMove : public std::exception
			{
			public:
				BadMove() : std::exception("Bad Move") {}
			};

			Move() = default;
			Move(char ch);
			Move(const Move&) = default;
			Move(Move&&) noexcept = default;
			virtual ~Move() noexcept = default;
			Move& operator=(char ch);
			Move& operator=(const Move&) = default;
			Move& operator=(Move&&) noexcept = default;

			bool operator==(char move) const { return this->move == move; }
			bool operator!=(char move) const { return this->move != move; }

			bool operator==(const Move& move) const { return this->move == move.move; }
			bool operator!=(const Move& move) const { return this->move != move.move; }

			friend std::ostream& operator<<(std::ostream& os, const Move& move) {
				switch (move.move)
				{
				case Move::SPIN:    os << "SPIN";       break;
				case Move::DOWN:    os << "DOWN";       break;
				case Move::LEFT:    os << "LEFT";       break;
				case Move::RIGHT:   os << "RIGHT";      break;
				case Move::NONE:    os << "NONE";       break;
				case Move::SWAP:	os << "SWAP";		break;
				case Move::PENDING: os << "PENDING";	break;
				case Move::EXIT:	os << "EXIT GAME";  break;
				default:
					std::cout << "Error: " << __FUNCTION__ << " line " << __LINE__
						<< ": " << move.move << " is an undefined move value\n";
				}

				return os;
			}

			bool setMove(char move);

			char getMove() const;

		private:
			char move = NONE;
		};
	}
}
