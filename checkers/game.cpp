// game.cpp
// Rose Peters
// Created: 16-01-2022
// Source file for game class
#include "game.hpp"

pair<pair<int, int>, pair<int, int>> Game::getInput() {

	pair<pair<int, int>, pair<int, int>> CompMove;
	vector<pair<int, pair<pair<int, int>, pair<int, int>>>> moveSelection;
	random_device rd;
	mt19937 gen(rd());
	int moveNumber = 1;
	int moveSize = 2;
	int chosenMove = 0;
	int computerMove = 1;
	if ((_player == 1 || _autoplay) && _gameType == 2) {
		setBoard(1);
		CompMove = minimax(_depth);
		setBoard(2);
	}
	else if ((_player == 1 || _autoplay) && _gameType == 3) {
		setBoard(1);
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		CompMove = monteCarlo(begin);
		setBoard(2);
	}

	for (auto& m : _moves) {
		for (auto& pmoves : m) {
			moveSelection.push_back(std::make_pair(moveNumber, std::make_pair(pmoves.first, pmoves.second)));
			cout << "Move " << moveNumber << ": " << " (" << pmoves.first.first << ", " << pmoves.first.second;
			cout << ") to (" << pmoves.second.first << ", " << pmoves.second.second << ")" << endl;
			if (_gameType == 2) {
				if (pmoves.first == CompMove.first && pmoves.second == CompMove.second) {
					computerMove = moveNumber;
				}
			}
			moveNumber++;
		}

	}
	if ((_player == 1 || _autoplay) && _gameType == 1) {
		int fixedNumber = moveNumber;
		if (fixedNumber > 1) {
			fixedNumber -= 1;
		}
		uniform_int_distribution<int> distrib(1, fixedNumber);
		computerMove = distrib(gen);
	}
	while (true) {
		if (gameIsOver()) {
			break;
		}
		if (_player == 0 && !_autoplay) {
			cout << "Choose a move: ";
			cin >> chosenMove;

		}
		if (_player == 1 || _autoplay) {
			cout << "Opponent / player " << _playerLetter << " is playing their turn..." << endl;
		}
		for (auto& ms : moveSelection) {
			if (_player == 1 || _autoplay) {
				if (computerMove == ms.first) {
					return std::make_pair(ms.second.first, ms.second.second);
				}
			}
			if (_player == 0 && !_autoplay) {
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

int Game::switchKingDirection(int row, int col, char upOrDown) const {
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

void Game::setPlayer(int player) {
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

pair<pair<int, int>, pair<int, int>> Game::pieceJump() {
	char command = ' ';
	pair<pair<int, int>, pair<int, int>> CompMove;
	vector<pair<int, pair<pair<int, int>, pair<int, int>>>> jumpSelection;
	int moveNumber = 1;
	int computerMove = 1;
	int chosenMove = 0;
	random_device rd;
	mt19937 gen(rd());

	if (!_jumps.empty()) {
		if (_gameType == 2) {
			CompMove = minimax(_depth);
		}
	}

	if (_jumped) {
		_jumped = false;
		for (auto& m2 : _jumps) {
			for (auto& pjumps2 : m2) {
				if (_temp == pjumps2.first) {
					jumpSelection.push_back(std::make_pair(moveNumber, std::make_pair(pjumps2.first, pjumps2.second)));
					cout << "Second jump: move " << moveNumber << ": (" << pjumps2.first.first << ", " << pjumps2.first.second;
					cout << ") to (" << pjumps2.second.first << ", " << pjumps2.second.second << ")" << endl;
					if (_gameType == 2) {
						if (pjumps2.first == CompMove.first && pjumps2.second == CompMove.second) {
							computerMove = moveNumber;
						}
					}
					moveNumber++;
				}
			}
		}
		if ((_player == 1 || _autoplay) && _gameType == 1) {
			int fixedNumber = moveNumber;
			if (fixedNumber > 1) {
				fixedNumber -= 1;
			}
			uniform_int_distribution<int> distrib(1, fixedNumber);
			computerMove = distrib(gen);
		}

		if (_player == 0 && !_autoplay) {
			cout << "Choose a move: ";
			cin >> chosenMove;

		}

		if (_player == 1 || _autoplay) {
			cout << "Opponent / player " << _playerLetter << " is playing their turn..." << endl;
		}
		for (auto& js : jumpSelection) {
			if (_player == 1 || _autoplay) {
				if (computerMove == js.first) {
					_jumped = true;
					_temp = js.second.second;
					return std::make_pair(js.second.first, js.second.second);

				}
			}
			if (_player == 0 && !_autoplay) {
				if (chosenMove == js.first) {
					_jumped = true;
					_temp = js.second.second;
					return std::make_pair(js.second.first, js.second.second);

				}
			}
		}

	}
	else if (_hasJump) {
		for (auto& m : _jumps) {
			for (auto& pjumps : m) {
				jumpSelection.push_back(std::make_pair(moveNumber, pjumps));
				cout << "Move " << moveNumber << ": (" << pjumps.first.first << ", " << pjumps.first.second;
				cout << ") to (" << pjumps.second.first << ", " << pjumps.second.second << ")" << endl;
				if (_gameType == 2) {
					if (pjumps.first == CompMove.first && pjumps.second == CompMove.second) {
						computerMove = moveNumber;
					}
				}
				moveNumber++;
			}
		}
		if ((_player == 1 || _autoplay) && _gameType == 1) {
			int fixedNumber = moveNumber;
			if (fixedNumber > 1) {
				fixedNumber -= 1;
			}
			uniform_int_distribution<int> distrib(1, fixedNumber);
			computerMove = distrib(gen);
		}
		while (!_jumped) {
			if (_player == 0 && !_autoplay) {
				if (_jumped) {
					break;
				}
				cout << "Choose a move: ";
				cin >> chosenMove;

			}
			if (_player == 1 || _autoplay) {
				if (_jumped) {
					break;
				}
				cout << "Opponent / player " << _playerLetter << " is playing their turn..." << endl;
			}
			for (auto& js : jumpSelection) {
				if (_player == 1 || _autoplay) {
					if (computerMove == js.first) {
						_jumped = true;
						_temp = js.second.second;
						return std::make_pair(js.second.first, js.second.second);

					}
				}
				if (_player == 0 && !_autoplay) {
					if (chosenMove == js.first) {
						_jumped = true;
						_temp = js.second.second;
						return std::make_pair(js.second.first, js.second.second);

					}
				}
			}
		}
	}
}

void Game::movePiece(pair<int, int> p1, pair<int, int> p2, bool jump, bool showBoard) {
	if (jump) {
		int first = 1;
		if (p2.first - p1.first < 0) {
			first = -1;
		}
		int second = 1;
		if (p2.second - p1.second < 0) {
			second = -1;
		}
		pair<int, int> middleSquare = std::make_pair(p1.first + (1 * first), p1.second + (1 * second));
		_boardValues[p2.first][p2.second] = _boardValues[p1.first][p1.second];
		_boardValues[middleSquare.first][middleSquare.second] = 3;
		_boardValues[p1.first][p1.second] = 3;

		board[p2.first][p2.second] = getLetter(p1.first, p1.second);
		board[middleSquare.first][middleSquare.second] = ' ';
		board[p1.first][p1.second] = 'X';
		if (showBoard) {
			printBoard();
		}
		board[p1.first][p1.second] = ' ';
		_jumped = true;
	}
	if (!jump) {
		_boardValues[p2.first][p2.second] = _boardValues[p1.first][p1.second];
		_boardValues[p1.first][p1.second] = 3;

		board[p2.first][p2.second] = getLetter(p1.first, p1.second);
		board[p1.first][p1.second] = 'X';
		if (showBoard) {
			printBoard();
		}
		board[p1.first][p1.second] = ' ';
	}
}

int Game::generateMoves() {
	// vector of two pairs : start coord and jump coord
	// and pair of enemy piece's coord
	vector<pair<pair<int, int>, pair<int, int>>> jumps;
	vector<pair<pair<int, int>, pair<int, int>>> temp;
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
							jumps.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col - 2)));
						}

						else if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == 2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							jumps.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col - 2)));
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
							jumps.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col + 2)));
						}

						else if ((2 * _movementDirection * switchKingDirection(row, col, 'D')) == 2 &&
							row - (2 * _movementDirection * switchKingDirection(row, col, 'D')) >= 0) {
							jumps.push_back(std::make_pair(std::make_pair(row, col),
								std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'D')), col + 2)));
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
								jumps.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col - 2)));
							}

							else if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == 2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								jumps.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col - 2)));
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
								jumps.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col + 2)));
							}

							else if ((2 * _movementDirection * switchKingDirection(row, col, 'U')) == 2 &&
								row - (2 * _movementDirection * switchKingDirection(row, col, 'U')) >= 0) {
								jumps.push_back(std::make_pair(std::make_pair(row, col),
									std::make_pair(row - (2 * _movementDirection * switchKingDirection(row, col, 'U')), col + 2)));
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
		cout << "Out of moves. " << _playerLetter << " lost!";
	}
	return 0;
}


pair<pair<int, int>, pair<int, int>> Game::minimax(int depth) {
	return maxMove(depth, -10, 10);
}

pair<pair<int, int>, pair<int, int>> Game::maxMove(int depth, int alpha, int beta) {
	char temp[8][8] = { ' ' };
	int tempValues[8][8];
	int player = _player;
	/*if (gameIsOver() || _depth == 0) {
		return evalGameState(alpha);
	}*/
	if (depth > 0) {
		pair<pair<int, int>, pair<int, int>> bestMove;
		pair<pair<int, int>, pair<int, int>> move;
		vector<vector<pair<pair<int, int>, pair<int, int>>>> tempMoves;

		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempMoves.push_back(jumps); }

		}
		else {
			for (auto moves : _moves) { tempMoves.push_back(moves); }
		}
		bestMove = tempMoves[0][0];

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
				movePiece(maxmoves.first, maxmoves.second, _hasJump, false);
				player = 1 - player;
				setPlayer(player);
				switchDirection();
				setPlayerLetter();
				resetMoves();
				move = minMove(depth - 1, alpha, beta);
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
		return bestMove;

	}
}

pair<pair<int, int>, pair<int, int>> Game::minMove(int depth, int alpha, int beta) {
	char temp[8][8];
	int tempValues[8][8];
	int player = _player;
	/*if (gameIsOver() || _depth == 0) {
	* improve searching with heuristic
		return evalGameState(beta);
	}*/
	if (depth >= 0) {
		pair<pair<int, int>, pair<int, int>> bestMove;
		pair<pair<int, int>, pair<int, int>> move;
		vector<vector<pair<pair<int, int>, pair<int, int>>>> tempMoves;

		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempMoves.push_back(jumps); }

		}
		else {
			for (auto moves : _moves) { tempMoves.push_back(moves); }
		}
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
				movePiece(minmoves.first, minmoves.second, getHasJump(), false);
				player = 1 - player;
				setPlayer(player);
				switchDirection();
				setPlayerLetter();
				resetMoves();
				move = maxMove(depth - 1, alpha, beta);
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
		return bestMove;
	}
}

pair<pair<int, int>, pair<int, int>> Game::monteCarlo(std::chrono::steady_clock::time_point time) {
	return MCTSUpper(time, -10, 10);
}

pair<pair<int, int>, pair<int, int>> Game::MCTSUpper(std::chrono::steady_clock::time_point time, int upper, int lower) {
	char temp[8][8] = { ' ' };
	int tempValues[8][8];
	int player = _player;

	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::microseconds>(endTime - time).count() < 5000000) {
		pair<pair<int, int>, pair<int, int>> bestMove;
		pair<pair<int, int>, pair<int, int>> move;
		vector<vector<pair<pair<int, int>, pair<int, int>>>> tempMoves;

		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempMoves.push_back(jumps); }

		}
		else {
			for (auto moves : _moves) { tempMoves.push_back(moves); }
		}
		bestMove = tempMoves[0][0];

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
				movePiece(maxmoves.first, maxmoves.second, _hasJump, true);
				player = 1 - player;
				setPlayer(player);
				switchDirection();
				setPlayerLetter();
				resetMoves();
				move = MCTSLower(time, upper, lower);
				if (valueOfMoves(move) > valueOfMoves(bestMove)) {
					bestMove = move;
					upper = valueOfMoves(move);
				}
				if (lower > upper) {
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
		return bestMove;

	}
}

pair<pair<int, int>, pair<int, int>> Game::MCTSLower(std::chrono::steady_clock::time_point time, int lower, int upper) {
	char temp[8][8];
	int tempValues[8][8];
	int player = _player;
	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::microseconds>(endTime - time).count() < 5000000) {
		pair<pair<int, int>, pair<int, int>> bestMove;
		pair<pair<int, int>, pair<int, int>> move;
		vector<vector<pair<pair<int, int>, pair<int, int>>>> tempMoves;

		generateMoves();
		if (_hasJump) {
			for (auto jumps : _jumps) { tempMoves.push_back(jumps); }
		}
		else {
			for (auto moves : _moves) { tempMoves.push_back(moves); }
		}
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
				movePiece(minmoves.first, minmoves.second, getHasJump(), false);
				player = 1 - player;
				setPlayer(player);
				switchDirection();
				setPlayerLetter();
				resetMoves();
				move = MCTSUpper(time, upper, lower);
				if (valueOfMoves(move) > valueOfMoves(bestMove)) {
					bestMove = move;
					lower = valueOfMoves(move);
				}
				if (lower < upper) {
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
		return bestMove;
	}
}

int Game::valueOfMoves(pair<pair<int, int>, pair<int, int>> move) {
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

pair<pair<int, int>, pair<int, int>> Game::evalGameState(int minmax) {
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

void Game::setGameType(int gametype) {
	_gameType = gametype;
}

void Game::switchToKing(int row, int col) {
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

char Game::getLetter(int row, int col) const {
	if (board[row][col] == _playerLetter) {
		return _playerLetter;
	}
	if (board[row][col] == _playerKingLetter) {
		return _playerKingLetter;
	}
}

ostringstream Game::printBoard() const {

	/*for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			cout << board[i][j];
		}
	}*/
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

int Game::size() const {
	return _size;
}

bool Game::gameIsOver() const {
	return _gameOver;
}

void Game::setSize(int size) {
	_size = size;
}

void Game::setAutoplay(bool autoplay) {
	_autoplay = autoplay;
}

void Game::winConditions() {
	if (_player == 1) {
		for (auto row = 0; row < _size; row++) {
			for (auto col = 0; col < _size; col++) {
				if (board[0][col] == _playerKingLetter) {
					_gameOver = true;
					break;
				}
			}
		}
		if (_gameOver) cout << "Red wins!" << endl;
	}
	if (_player == 0) {
		for (auto row = 0; row < _size; row++) {
			for (auto col = 0; col < _size; col++) {
				if (board[7][col] == _playerKingLetter) {
					_gameOver = true;
					break;
				}
			}
		}
		if (_gameOver) cout << "Black wins!" << endl;

	}
}

void Game::setBoard(int switchNumber) {
	if (switchNumber == 1) {
		_tempMoveSet = _moves;
	}
	if (switchNumber == 2) {
		_moves = _tempMoveSet;
		_tempMoveSet.clear();
	}

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
	int player = 1;
	setPlayer(player);
}

