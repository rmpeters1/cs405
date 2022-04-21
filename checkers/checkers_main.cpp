#include "game.hpp"

int main() {
	int player = 0;
	pair<pair<int, int>, pair<int, int>> input;
	pair<pair<int, int>, pair<int, int>> jumpInput;
	Game g;
	g.setGameType(1);
	g.setAutoplay(false);

	g.printBoard();
	g.switchDirection();
	g.setPlayerLetter();
	g.generateMoves();
	input = g.getInput();
	g.movePiece(input.first, input.second, false, true);
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
		if (g.gameIsOver()) {
			break;
		}
		if (g.getHasJump()) {
			while (!g.gameIsOver()) {
				jumpInput = g.pieceJump();
				g.movePiece(jumpInput.first,jumpInput.second, true, true);
				g.resetMoves();
				g.generateMoves();
				if (!g.getHasJump()) {
					break;
				}
			}
		}
		else if (!g.getJumped()) {
			input = g.getInput();
			g.movePiece(input.first, input.second, false, true);
		}
		g.checkForKing();
		g.winConditions();
		g.resetJumped();

		g.resetMoves();

	}
}