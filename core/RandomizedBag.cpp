#include "pch.h"

#include <array>
#include <algorithm>    // for std::shuffle

#include "RandomizedBag.h"

#include "Tetrominos.hpp"

using namespace std;

namespace tetris
{
	namespace core
	{
		const TetrominoBase& RandomizedBag::nextTetromino()
		{
			if (this->empty()) {
				fillAndShuffle();
			}

			auto index = indicies.back();
			indicies.pop_back();

			// An array of tetrominos
			const static TetrominoBase tetrominos[7] = {
				TetrominoI(),
				TetrominoO(),
				TetrominoT(),
				TetrominoL(),
				TetrominoJ(),
				TetrominoS(),
				TetrominoZ()
			};

			return tetrominos[index];
		}

		void RandomizedBag::fillAndShuffle()
		{
			// Initialize with 1, 2, 3, ..., 6
			indicies.resize(7);

			for (int i = 0; i < indicies.size(); i++) {
				indicies.at(i) = i;
			}

			// Shuffle
			random_shuffle(indicies.data(), indicies.data() + indicies.size());
		}

		void RandomizedBag::clear()
		{
			indicies.clear();
		}

		bool RandomizedBag::empty()
		{
			return indicies.empty();
		}

		void RandomizedBag::pop()
		{
			indicies.pop_back();
		}
	}
}