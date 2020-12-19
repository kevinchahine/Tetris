#include "pch.h"
#include "HeuristicHelpers.h"

#include <Tetris/core/TetrominoBase.h>

#include <iostream>

using namespace std;
using namespace tetris::core;


namespace tetris
{
	namespace ai
	{
		int countHoles(const core::Board& board)
		{
			int nHoles = 0;

			// --- Count the number of holes in board ---
			// A hole is an empty cell that has an occupied cell somewhere above it.
			for (int col = 0; col < board.cols; col++) {
				// --- 1.) Going from top to bottom, find the first occupied cell in this column --- 
				int rowOfTopCell = 0;
				while (rowOfTopCell < board.rows) {
					if (board.at(rowOfTopCell, col) != TetrominoBase::EMPTY) {
						break;
					}

					rowOfTopCell++;
				}

				// *** Now rowOfTopCell is the row index of the highest occupied cell in this column ***

				// 2.) --- Now, simply count how empty cells (holes) under this cell ---
				for (; rowOfTopCell < board.rows; rowOfTopCell++) {
					if (board.at(rowOfTopCell, col) == TetrominoBase::EMPTY) {
						nHoles++; // Found another hole
					}
				}
			}

			return nHoles;
		}

		int countSittingCells(const core::Board& board)
		{
			int nSitting = 0;

			// --- Count the number of holes in board ---
			// A hole is an empty cell that has an occupied cell somewhere above it.
			for (int col = 0; col < board.cols; col++) {
				int nHolesInCol = 0;

				// --- 1.) Going from bottom to top, find the first occupied cell in this column --- 
				for (int row = board.rows - 1; row >= 0; row--) {
					// Is this cell a empty?
					if (board.at(row, col) == TetrominoBase::EMPTY) {
						// Yes it is empty. Count it as a hole.
						nHolesInCol++;
					}
					else {
						// Its occupied. This means it is sitting on <nHolesInCol> holes
						// nHolesInCol may a be zero.
						nSitting += nHolesInCol;
					}
				}
			}

			return nSitting;
		}

		int maxHeight(const core::Board& board)
		{
			int max = 0;

			return max;
		}
	}
}