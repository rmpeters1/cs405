// game.cpp
// Rose Peters
// Created: 16-01-2022
// Source file for game class
#include "game.hpp"

pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::getInput() {
	pair<pair<size_t, size_t>, pair<size_t, size_t>> CompMove;
	if (_player == 1) {
		setBoard(1);
		for (auto row = 0; row < _size; row++) {
			for (auto col = 0; col < _size; col++) {
				cout << "trmp" << _tempValues[row][col];
			}
		}
		CompMove = minimax(_depth);
		setBoard(2);
	}
	vector<pair<int, pair<pair<size_t, size_t>, pair<size_t, size_t>>>> moveSelection;
	int moveNumber = 1;
	int moveSize = 2;
	int chosenMove = 0;
	int computerMove = 1;
	for (auto& m : _moves) {
		for (auto& pmoves : m) {
			moveSelection.push_back(std::make_pair(moveNumber, std::make_pair(pmoves.first, pmoves.second)));
			cout << "Move " << moveNumber << ": " << " (" << pmoves.first.first << ", " << pmoves.first.second;
			cout << ") to (" << pmoves.second.first << ", " << pmoves.second.second << ")" << endl;
			if (pmoves.first == CompMove.first && pmoves.second == CompMove.second) {
				computerMove = moveNumber;
			}
			moveNumber++;
		}

	}
	while (true) {
		if (gameIsOver()) {
			break;
		}
		if (_player == 0) {
			cout << "Choose a move: ";
			cin >> chosenMove;

		}
		if (_player == 1) {
			cout << "Opponent is playing their turn..." << endl;
		}
		for (auto& ms : moveSelection) {
			if (_player == 1) {
				if (computerMove == ms.first) {
					return std::make_pair(ms.second.first, ms.second.second);
				}
			}
			if (_player == 0) {
				if (chosenMove == ms.first) {
					return std::make_pair(ms.second.first, ms.second.second);
				}
			}
		}
	}
	return std::make_pair(std::make_pair(0, 0), std::make_pair(0, 0));
}

void Game::switchDirection() {
	if (_player == 1) {
		if (_movementDirection == 1) {
			_movementDirection *= -1;
		}
	} if (_player == 0) {
		if (_movementDirection == -1) {
			_movementDirection *= -1;
		}
	}
}

int Game::switchKingDirection(size_t row, size_t col, char upOrDown) const {
	if (_player == 1) {
		if (board[row][col] == _playerKingLetter && upOrDown == 'U') {
			return -1;
		}
		return 1;
	}
	else if (_player == 0) {
		if (board[row][col] == _playerKingLetter && upOrDown == 'D') {
			return -1;
		}
		return 1;
	}
}

void Game::setPlayer(std::size_t player) {
	_player = player;
}

void Game::setPlayerLetter() {
	if (_player == 0) {
		_playerLetter = 'b';
		_playerKingLetter = 'B';
	}
	if (_player == 1) {
		_playerLetter = 'r';
		_playerKingLetter = 'R';
	}
}

pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>> Game::pieceJump() {
	char command = ' ';
	pair<pair<size_t, size_t>, pair<size_t, size_t>> CompMove;
	if (!_jumps.empty()) {
		CompMove = minimax(_depth);
	}
	vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<int, pair<size_t, size_t>>>> jumpSelection;
	int moveNumber = 1;
	int computerMove = 1;
	int chosenMove = 0;
	if (_jumped) {
		for (auto& m2 : _jumps) {
			for (auto& pjumps2 : m2) {
				if (_temp == pjumps2.first.first) {
					jumpSelection.push_back(std::make_pair(std::make_pair(pjumps2.first.first, pjumps2.first.second),
						std::make_pair(moveNumber, pjumps2.second)));
					cout << "Second jump: move " << moveNumber << ": (" << pjumps2.first.first.first << ", " << pjumps2.first.first.second;
					cout << ") to (" << pjumps2.first.second.first << ", " << pjumps2.first.second.second << ")" << endl;
					if (pjumps2.first.first == CompMove.first && pjumps2.first.second == CompMove.second) {
						computerMove = moveNumber;
					}
					moveNumber++;
				}
			}
		}
		while (true) {
			if (_player == 0) {
				cout << "Choose a move: ";
				cin >> chosenMove;

			}

			if (_player == 1) {
				cout << "Opponent is playing their turn..." << endl;
			}
			for (auto& js : jumpSelection) {
				if (_player == 1) {
					if (computerMove == js.second.first) {
						_jumped = true;
						_temp = js.first.second;
						return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);

					}
				}
				if (_player == 0) {
					if (chosenMove == js.second.first) {
						_jumped = true;
						_temp = js.first.second;
						return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);

					}
				}
			}
		}
	}
	else if (_hasJump) {
		for (auto& m : _jumps) {
			for (auto& pjumps : m) {
				jumpSelection.push_back(std::make_pair(std::make_pair(pjumps.first.first, pjumps.first.second),
					std::make_pair(moveNumber, pjumps.second)));
				cout << "Move " << moveNumber << ": (" << pjumps.first.first.first << ", " << pjumps.first.first.second;
				cout << ") to (" << pjumps.first.second.first << ", " << pjumps.first.second.second << ")" << endl;
				if (pjumps.first.first == CompMove.first && pjumps.first.second == CompMove.second) {
					computerMove = moveNumber;
				}
				moveNumber++;
			}
		}

		while (!_jumped) {
			if (_player == 0) {
				if (_jumped) {
					break;
				}
				cout << "Choose a move: ";
				cin >> chosenMove;

			}
			if (_player == 1) {
				if (_jumped) {
					break;
				}
				cout << "Opponent is playing their turn..." << endl;
			}
			for (auto& js : jumpSelection) {
				if (_player == 1) {
					if (computerMove == js.second.first) {
						_jumped = true;
						_temp = js.first.second;
						return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);

					}
				}
				if (_player == 0) {
					if (chosenMove == js.second.first) {
						_jumped = true;
						_temp = js.first.second;
						return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);

					}
				}
			}
		}
	}
}

void Game::moveJump(pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>> p1, bool showBoard) {
	_boardValues[p1.first.second.first][p1.first.second.second] = _boardValues[p1.first.first.first][p1.first.first.second];
	_boardValues[p1.first.first.first][p1.first.first.second] = 3;
	_boardValues[p1.second.first][p1.second.second] = 3;

	board[p1.first.second.first][p1.first.second.second] = getLetter(p1.first.first.first, p1.first.first.second);
	board[p1.second.first][p1.second.second] = ' ';
	board[p1.first.first.first][p1.first.first.second] = 'X';
	if (showBoard) {
		printBoard();
	}
	board[p1.first.first.first][p1.first.first.second] = ' ';
}

void Game::movePiece(pair<size_t, size_t> p1, pair<size_t, size_t> p2, bool showBoard) {
	_boardValues[p2.first][p2.second] = _boardValues[p1.first][p1.second];
	_boardValues[p1.first][p1.second] = 3;

	board[p2.first][p2.second] = getLetter(p1.first, p1.second);
	board[p1.first][p1.second] = 'X';
	if (showBoard) {
		printBoard();
	}
	board[p1.first][p1.second] = ' ';
}

int Game::generateMoves() {
	// vector of two pairs : start coord and jump coord
	// and pair of enemy piece's coord
	vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>>> jumps;
	vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>> temp;
	for (auto row = 0; row < _size; row++) {
		for (auto col = 0; col < _size; col++) {
			if (board[row][col] == getLetter(row, col)) {
				// left move
				if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col - 1]
					!= getLetter(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col - 1) &&
					col - 1 >= 0) {

					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col - 1] == ' ') {
						if ((1 * _movementDirection * switchKingDirection(row, col, 'D')) == -1 &&
							row - (1 * _movementDirection * switchKingDirection(row, col, 'D')) <= 7) {
							temp.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col - 1)));
						}

						else if ((1 * _movementDirection * switchKingDirection(row, col, 'D')) == 1 &&
							row - (1 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							temp.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col - 1)));
						}
					}

					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col - 1] != ' ' &&
						board[row - (2 * _movementDirection * switchKingDirection(row, col, 'D'))][col - 2] == ' ' &&
						col - 2 >= 0) {
						if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == -2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) <= 7) {
							jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col - 2)),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col - 1)));
						}

						else if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == 2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col - 2)),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col - 1)));
						}

					}
				}
				// right move
				if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col + 1]
					!= getLetter(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col + 1) &&
					col + 1 <= 7) {

					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col + 1] == ' ') {
						if ((1 * _movementDirection * switchKingDirection(row, col, 'D')) == -1 &&
							row - (1 * _movementDirection * switchKingDirection(row, col, 'D')) <= 7) {
							temp.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col + 1)));
						}

						else if ((1 * _movementDirection * switchKingDirection(row, col, 'D')) == 1 &&
							row - (1 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							temp.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col + 1)));
						}
					}
					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'D'))][col + 1] != ' ' &&
						board[row - (2 * _movementDirection * switchKingDirection(row, col, 'D'))][col + 2] == ' ' &&
						col + 2 <= 7) {
						if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == -2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) <= 7) {
							jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col + 2)),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col + 1)));
						}

						else if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == 2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col + 2)),
								std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'D')), col + 1)));
						}
					}
				}

				// double check specifically for king's "up" moves
				if (board[row][col] == _playerKingLetter) {
					// left move
					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col - 1]
						!= getLetter(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col - 1) &&
						col - 1 >= 0) {
						if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col - 1] == ' ') {
							if ((1 * _movementDirection * switchKingDirection(row, col, 'U')) == -1 &&
								row - (1 * _movementDirection * switchKingDirection(row, col, 'U')) <= 7) {
								temp.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col - 1)));
							}

							else if ((1 * _movementDirection * switchKingDirection(row, col, 'U')) == 1 &&
								row - (1 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								temp.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col - 1)));
							}
						}
						if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col - 1] != ' ' &&
							board[row - (2 * _movementDirection * switchKingDirection(row, col, 'U'))][col - 2] == ' ' &&
							col - 2 >= 0) {
							if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == -2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) <= 7) {
								jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col - 2)),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col - 1)));
							}

							else if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == 2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col - 2)),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col - 1)));
							}
						}
					}
					// right move
					if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col + 1]
						!= getLetter(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col + 1) &&
						col + 1 <= 7) {
						if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col + 1] == ' ') {
							if ((1 * _movementDirection * switchKingDirection(row, col, 'U')) == -1 &&
								row - (1 * _movementDirection * switchKingDirection(row, col, 'U')) <= 7) {
								temp.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col + 1)));
							}

							else if ((1 * _movementDirection * switchKingDirection(row, col, 'U')) == 1 &&
								row - (1 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								temp.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col + 1)));
							}
						}
						if (board[row - (1 * _movementDirection * switchKingDirection(row, col, 'U'))][col + 1] != ' ' &&
							board[row - (2 * _movementDirection * switchKingDirection(row, col, 'U'))][col + 2] == ' ' &&
							col + 2 <= 7) {
							if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == -2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) <= 7) {
								jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col + 2)),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col + 1)));
							}

							else if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == 2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								jumps.push_back(std::make_pair(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col + 2)),
									std::make_pair(row - (1 * _movementDirection * switchKingDirection(row, col, 'U')), col + 1)));
							}
						}
					}
				}
			}
			if (!jumps.empty()) {
				_jumps.push_back(jumps);
				_hasJump = true;
			}
			if (!temp.empty()) {
				_moves.push_back(temp);
			}
			temp.clear();
			jumps.clear();
		}
	}
	if (_jumps.empty()) {
		_hasJump = false;
	}
	if (_moves.empty() && _jumps.empty()) {
		_gameOver = true;
		cout << _playerLetter << " lost!";
	}
	return 0;
}


pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::minimax(int depth) {
	return maxMove(0, 0);
}

pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::maxMove(int alpha, int beta) {
	char temp[8][8] = { ' ' };
	int tempValues[8][8];
	size_t player = _player;
	/*if (gameIsOver() || _depth == 0) {
		return evalGameState(alpha);
	}*/
	if (_depth > 0) {
		_depth -= 1;
		pair<pair<size_t, size_t>, pair<size_t, size_t>> bestMove;
		pair<pair<size_t, size_t>, pair<size_t, size_t>> move;
		vector<vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>>> tempMoves;
		vector<vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>>>> tempJumps;

		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempJumps.push_back(jumps); }
			for (auto& m : tempJumps) {
				for (auto& maxmoves : m) {

					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							temp[row][col] = board[row][col];
							tempValues[row][col] = _boardValues[row][col];
						}
					}
					if (_player != 1) {
						player = 1;
						setPlayer(player);
						switchDirection();
						setPlayerLetter();
					}
					moveJump(maxmoves, true);
					player = 1 - player;
					setPlayer(player);
					switchDirection();
					setPlayerLetter();
					resetMoves();
					move = minMove(alpha, beta);
					if (valueOfMoves(move) > valueOfMoves(bestMove)) {
						bestMove = move;
						beta = valueOfMoves(move);
					}
					if (beta < alpha) {
						for (auto row = 0; row < _size; row++) {
							for (auto col = 0; col < _size; col++) {
								board[row][col] = temp[row][col];
								_boardValues[row][col] = tempValues[row][col];
							}
						}
						return bestMove;
					}
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							board[row][col] = temp[row][col];
							_boardValues[row][col] = tempValues[row][col];
						}
					}
				}
			}
		}
		else {
			for (auto moves : _moves) { tempMoves.push_back(moves); }
			for (auto& m : tempMoves) {
				for (auto& maxmoves : m) {
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							temp[row][col] = board[row][col];
							tempValues[row][col] = _boardValues[row][col];
						}
					}
					if (_player != 1) {
						player = 1;
						setPlayer(player);
						switchDirection();
						setPlayerLetter();
					}
					movePiece(maxmoves.first, maxmoves.second, true);
					player = 1 - player;
					setPlayer(player);
					switchDirection();
					setPlayerLetter();
					resetMoves();
					move = minMove(alpha, beta);
					if (valueOfMoves(move) > valueOfMoves(bestMove)) {
						bestMove = move;
						alpha = valueOfMoves(move);
					}
					if (beta > alpha) {
						for (auto row = 0; row < _size; row++) {
							for (auto col = 0; col < _size; col++) {
								board[row][col] = temp[row][col];
								_boardValues[row][col] = tempValues[row][col];
							}
						}
						return bestMove;
					}
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							board[row][col] = temp[row][col];
							_boardValues[row][col] = tempValues[row][col];
						}
					}
				}
			}
		}
		return bestMove;
	}
}
pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::minMove(int alpha, int beta) {
	char temp[8][8];
	int tempValues[8][8];
	size_t player = _player;
	/*if (gameIsOver() || _depth == 0) {
	* improve searching with heuristic
		return evalGameState(beta);
	}*/
	if (_depth >= 0) {
		pair<pair<size_t, size_t>, pair<size_t, size_t>> bestMove;
		pair<pair<size_t, size_t>, pair<size_t, size_t>> move;
		vector<vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>>>> tempJumps;
		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempJumps.push_back(jumps); }
			for (auto& m : tempJumps) {
				for (auto& minmoves : m) {

					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							temp[row][col] = board[row][col];
							tempValues[row][col] = _boardValues[row][col];

						}
					}
					if (_boardValues[minmoves.first.first.first][minmoves.first.first.second] != _player) {
						player = _boardValues[minmoves.first.first.first][minmoves.first.first.second];
						setPlayer(player);
						switchDirection();
						setPlayerLetter();
					}
					moveJump(minmoves, true);
					player = 1 - player;
					setPlayer(player);
					switchDirection();
					setPlayerLetter();
					resetMoves();
					move = maxMove(alpha, beta);
					if (valueOfMoves(move) > valueOfMoves(bestMove)) {
						bestMove = move;
						beta = valueOfMoves(move);
					}
					if (beta < alpha) {
						for (auto row = 0; row < _size; row++) {
							for (auto col = 0; col < _size; col++) {
								board[row][col] = temp[row][col];
								_boardValues[row][col] = tempValues[row][col];
							}
						}
						return bestMove;
					}
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							board[row][col] = temp[row][col];
							_boardValues[row][col] = tempValues[row][col];
						}
					}
				}
			}
		}
		else {
			vector<vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>>> tempMoves = _moves;
			for (auto& m : tempMoves) {
				for (auto& minmoves : m) {
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							temp[row][col] = board[row][col];
							tempValues[row][col] = _boardValues[row][col];
						}
					}
					if (_boardValues[minmoves.first.first][minmoves.first.second] != _player) {
						player = _boardValues[minmoves.first.first][minmoves.first.second];
						setPlayer(player);
						switchDirection();
						setPlayerLetter();
					}
					movePiece(minmoves.first, minmoves.second, true);
					player = 1 - player;
					setPlayer(player);
					switchDirection();
					setPlayerLetter();
					resetMoves();
					move = maxMove(alpha, beta);
					if (valueOfMoves(move) > valueOfMoves(bestMove)) {
						bestMove = move;
						beta = valueOfMoves(move);
					}
					if (beta < alpha) {
						for (auto row = 0; row < _size; row++) {
							for (auto col = 0; col < _size; col++) {
								board[row][col] = temp[row][col];
								_boardValues[row][col] = tempValues[row][col];
							}
						}
						return bestMove;
					}
					for (auto row = 0; row < _size; row++) {
						for (auto col = 0; col < _size; col++) {
							board[row][col] = temp[row][col];
							_boardValues[row][col] = tempValues[row][col];
						}
					}
				}
			}
		}
		return bestMove;
	}
}

int Game::valueOfMoves(pair<pair<size_t, size_t>, pair<size_t, size_t>> move) {
	// can add jump move conditions to this
	int score = 0;
	if (move.second.first - move.first.first == 1) {
		if ((move.second.first + 1 == ' ' && move.second.second - 1 == ' ') ||
			(move.second.first + 1 == ' ' && move.second.second + 1 == ' '))
			score = 1;
		if (getLetter(move.first.first, move.first.second) == 'R' ||
			getLetter(move.first.first, move.first.second) == 'B') {
			score = 2;
		}
	}
	else if (move.second.first - move.first.first == -1) {
		if ((move.second.first - 1 == ' ' && move.second.second - 1 == ' ') ||
			(move.second.first - 1 == ' ' && move.second.second + 1 == ' '))
			score = 1;
		if (getLetter(move.first.first, move.first.second) == 'R' ||
			getLetter(move.first.first, move.first.second) == 'B') {
			score = 2;
		}
	}
	else if (move.second.first - move.first.first == 2) {
		if ((move.second.first + 2 == ' ' && move.second.second - 1 == ' ') ||
			(move.second.first + 2 == ' ' && move.second.second + 1 == ' '))
			score = 1;
		if (getLetter(move.first.first, move.first.second) == 'R' ||
			getLetter(move.first.first, move.first.second) == 'B') {
			score = 2;
		}
	}
	else if (move.second.first - move.first.first == -2) {
		if ((move.second.first - 2 == ' ' && move.second.second - 1 == ' ') ||
			(move.second.first - 2 == ' ' && move.second.second + 1 == ' '))
			score = 1;
		if (getLetter(move.first.first, move.first.second) == 'R' ||
			getLetter(move.first.first, move.first.second) == 'B') {
			score = 2;
		}
	}
	else {
		score = 0;
	}
	return score;
}

pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::evalGameState(int minmax) {
	for (int row = 0; row < _size; row++) {
		for (int col = 0; col < _size; col++) {

		}
	}
	return std::make_pair(std::make_pair(1, 1), std::make_pair(1, 2));
}


void Game::resetMoves() {
	_moves.clear();
	_jumps.clear();
}

bool Game::getHasJump() {
	return _hasJump;
}

bool Game::getJumped() {
	return _jumped;
}

void Game::resetJumped() {
	_jumped = false;
}


void Game::switchToKing(size_t row, size_t col) {
	if (_player == 1) {
		board[row][col] = 'R';
	}
	else if (_player == 0) {
		board[row][col] = 'B';
	}
}

void Game::checkForKing() {
	if (_player == 1) {
		for (auto col = 0; col < _size; col++) {
			if (board[7][col] == _playerLetter) {
				switchToKing(7, col);
				printBoard();
			}
		}
	}
	if (_player == 0) {
		for (auto col = 0; col < _size; col++) {
			if (board[0][col] == _playerLetter) {
				switchToKing(0, col);
				printBoard();
			}
		}
	}
}

char Game::getLetter(size_t row, size_t col) const {
	if (board[row][col] == _playerLetter) {
		return _playerLetter;
	}
	if (board[row][col] == _playerKingLetter) {
		return _playerKingLetter;
	}
}

ostringstream Game::printBoard() const {
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			cout << _boardValues[i][j];
			if (j == 7) { cout << endl; }
		}
	}
	ostringstream output;
	for (int i = 0; i < _size; i++) {
		cout << "=======";
	}
	cout << "\n\n\n";
	for (int i = 0; i < _size; i++) {
		cout << "     " << i;
	}
	cout << "\n  ";
	for (int i = 0; i < _size; i++) {
		cout << "______";
	}
	cout << "_\n";
	for (int row = 0; row < _size; row++) {
		cout << "  ";
		for (int i = 0; i < _size; i++) {
			cout << "|     ";
		}
		cout << "|\n" << row << " ";
		for (int col = 0; col < _size; col++) {
			cout << "|  " << board[row][col] << "  ";
			output << board[row][col];
		}
		cout << "|\n  ";
		for (int i = 0; i < _size; i++) {
			cout << "|_____";
		}
		cout << "|\n";
	}
	return output;
}

size_t Game::size() const {
	return _size;
}

bool Game::gameIsOver() const {
	return _gameOver;
}

void Game::winConditions() {
	if (_player == 1) {
		for (auto row = 0; row < _size; row++) {
			for (auto col = 0; col < _size; col++) {
				if (board[0][col] == _playerKingLetter) {
					_gameOver = true;
					cout << "Red wins!" << endl;
					break;
				}
			}
		}
	}
	if (_player == 0) {
		for (auto row = 0; row < _size; row++) {
			for (auto col = 0; col < _size; col++) {
				if (board[7][col] == _playerKingLetter) {
					_gameOver = true;
					cout << "Black wins!" << endl;
					break;
				}
			}
		}

	}
}

void Game::setBoard(int switchNumber) {
	for (auto row = 0; row < _size; row++) {
		for (auto col = 0; col < _size; col++) {
			if (switchNumber == 1) {
				_tempBoard[row][col] = board[row][col];
				_tempValues[row][col] = _boardValues[row][col];
			}
			if (switchNumber == 2) {
				board[row][col] = _tempBoard[row][col];
				_boardValues[row][col] = _tempValues[row][col];
				_boardValues[row][col] = _tempValues[row][col];

			}
		}
	}
	size_t player = 1;
	setPlayer(player);
}

