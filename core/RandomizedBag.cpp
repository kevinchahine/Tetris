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
		// Global for now. Should be static members of class RandomizedBag 
		std::default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

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

		void RandomizedBag::resetRandomSeed(int seed)
		{
			randomEngine.seed(seed);
		}

		void RandomizedBag::fillAndShuffle()
		{
			// Initialize with 0, 1, 2, 3, ..., 6
			indicies.resize(7);

			for (int i = 0; i < indicies.size(); i++) {
				indicies.at(i) = i;
			}

			// Shuffle 
			shuffle(indicies.data(), indicies.data() + indicies.size(), randomEngine);
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