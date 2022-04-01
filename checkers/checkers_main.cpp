#include "game.hpp"

int main() {
	size_t player = 0;
	pair<pair<size_t, size_t>, pair<size_t, size_t>> input;
	pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>> jumpInput;
	Game g;
	g.printBoard();
	g.switchDirection();
	g.setPlayerLetter();
	g.generateMoves();
	input = g.getInput();
	g.movePiece(input.first, input.second, true);
	g.resetMoves();
	g.resetJumped();
	while (!g.gameIsOver()) {
		if (g.gameIsOver()) {
			break;
		}

		player = 1 - player;
		g.setPlayer(player);
		g.switchDirection();
		g.setPlayerLetter();
		g.generateMoves();
		if (g.getHasJump()) {
			while (!g.gameIsOver()) {
				jumpInput = g.pieceJump();
				g.moveJump(jumpInput, true);
				g.resetMoves();
				g.generateMoves();
				if (!g.getHasJump()) {
					break;
				}
			}
		}
		else if (!g.getJumped()) {
			input = g.getInput();
			g.movePiece(input.first, input.second, true);
		}
		g.checkForKing();
		g.winConditions();
		g.resetJumped();
		g.resetMoves();

	}
}