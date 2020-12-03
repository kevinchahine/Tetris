#pragma once

#include "core.h"

#include <iostream>

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
			static const char PENDING = '?';	// Still needs more time to decide
			static const char EXIT = 'x';		// Exit game

			Move() = default;
			Move(char ch);
			Move(const Move&) = default;
			Move(Move&&) noexcept = default;
			virtual ~Move() noexcept = default;
			Move& operator=(char ch);
			Move& operator=(const Move&) = default;
			Move& operator=(Move&&) noexcept = default;

			bool operator==(char move) const;

			friend std::ostream& operator<<(std::ostream& os, const Move& move) {
				switch (move.move)
				{
				case Move::SPIN:    os << "SPIN";       break;
				case Move::DOWN:    os << "DOWN";       break;
				case Move::LEFT:    os << "LEFT";       break;
				case Move::RIGHT:   os << "RIGHT";      break;
				case Move::NONE:    os << "NONE";       break;
				case Move::SWAP:	os << "SWAP";		break;
				case Move::PENDING: os << "NOT READY";  break;
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
