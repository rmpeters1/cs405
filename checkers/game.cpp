// game.cpp
// Rose Peters
// Created: 16-01-2022
// Source file for game class
#include "game.hpp"

pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::getInput() const {
	pair<pair<size_t, size_t>, pair<size_t, size_t>> CompMove = minimax(1);
	vector<pair<int, pair<pair<size_t, size_t>, pair<size_t, size_t>>>> moveSelection;
	int moveNumber = 1;
	int moveSize = 2;
	int chosenMove = 0;
	int computerMove = 0;
	random_device rd;
	mt19937 gen(rd());
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

void Game::movePiece(pair<size_t, size_t> p1, pair<size_t, size_t> p2) {
	board[p2.first][p2.second] = getLetter(p1.first, p1.second);
	board[p1.first][p1.second] = 'X';
	printBoard();
	board[p1.first][p1.second] = ' ';
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
	vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<int, pair<size_t, size_t>>>> jumpSelection;
	int moveNumber = 1;
	int jumpSize = 0;
	int chosenMove = 0;
	random_device rd;
	mt19937 gen(rd());
	if (_jumped) {
		for (auto& m2 : _jumps) {
			for (auto& pjumps2 : m2) {
				if (_temp == pjumps2.first.first) {
					jumpSelection.push_back(std::make_pair(std::make_pair(pjumps2.first.first, pjumps2.first.second),
						std::make_pair(moveNumber, pjumps2.second)));
					cout << "Second jump: move " << moveNumber << ": (" << pjumps2.first.first.first << ", " << pjumps2.first.first.second;
					cout << ") to (" << pjumps2.first.second.first << ", " << pjumps2.first.second.second << ")" << endl;
					moveNumber++;
				}
			}
		}
		while (true) {
			if (_player == 0) {
				cout << "Choose a move: ";
				cin >> chosenMove;

			}
			if (!jumpSelection.empty()) {
				jumpSize = jumpSelection.size();
			}
			uniform_int_distribution<int> distribJump2(0, jumpSize);
			if (_player == 1) {
				cout << "Opponent is playing their turn..." << endl;
				chosenMove = distribJump2(gen);
			}
			for (auto& js : jumpSelection) {
				if (chosenMove == js.second.first) {
					_temp = js.first.second;
					_jumped = true;
					return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);
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
				moveNumber++;
			}
		}
		if (!jumpSelection.empty()) {
			jumpSize = jumpSelection.size();
		}
		uniform_int_distribution<int> distribJump(0, jumpSize);
		while (true) {
			if (_player == 0) {
				cout << "Choose a move: ";
				cin >> chosenMove;

			}
			if (_player == 1) {
				cout << "Opponent is playing their turn..." << endl;
				chosenMove = distribJump(gen);
			}
			for (auto& js : jumpSelection) {
				if (chosenMove == js.second.first) {
					_temp = js.first.second;
					_jumped = true;
					return std::make_pair(std::make_pair(js.first.first, js.first.second), js.second.second);
				}
			}
		}
	}
}

void Game::moveJump(pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>> p1) {
	board[p1.first.second.first][p1.first.second.second] = getLetter(p1.first.first.first, p1.first.first.second);
	board[p1.second.first][p1.second.second] = ' ';
	board[p1.first.first.first][p1.first.first.second] = 'X';
	printBoard();
	board[p1.first.first.first][p1.first.first.second] = ' ';
}


void Game::generateMoves() {
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
}


pair<pair<size_t, size_t>, pair<size_t, size_t>> Game::minimax(size_t depth) const {
	int score = 0;
	int temp1 = 0;
	vector<pair<int, pair<pair<size_t, size_t>, pair<size_t, size_t>>>> temp;
	pair<pair<size_t, size_t>, pair<size_t, size_t>> bestPlay;
	if (_hasJump) {
		for (auto& m : _jumps) {
			for (auto& minmax : m) {
				if (minmax.first.second.first - minmax.first.first.first == 1) {
					if (minmax.first.second.first + 1 == ' ' && minmax.first.second.second + 1 == ' ') {
						if ((minmax.first.second.first + 1 == ' ' && minmax.first.second.second - 1 == ' ') ||
							(minmax.first.second.first + 1 == ' ' && minmax.first.second.second + 1 == ' '))
							score = 2;
						temp.push_back(std::make_pair(score, minmax.first));
					}
				}
				if (minmax.first.second.first - minmax.first.first.first == -1) {
					if (minmax.first.second.first + 1 == ' ' && minmax.first.second.second + 1 == ' ') {
						if ((minmax.first.second.first - 1 == ' ' && minmax.first.second.second - 1 == ' ') ||
							(minmax.first.second.first - 1 == ' ' && minmax.first.second.second + 1 == ' '))
							score = 3;
						temp.push_back(std::make_pair(score, minmax.first));
					}
				}
				else {
					score = 1;
					temp.push_back(std::make_pair(score, minmax.first));
				}
			}
		}
		for (auto t : temp) {
			if (t.first > temp1) {
				temp1 = t.first;
				bestPlay = t.second;
			}
		}
		return bestPlay;
	}
	else {
		for (auto& m : _moves) {
			int test = 0;
			for (auto& minmax : m) {
				if (minmax.second.first - minmax.first.first == 1) {
					if (minmax.second.first + 1 == ' ' && minmax.second.second + 1 == ' ') {
						if ((minmax.second.first + 1 == ' ' && minmax.second.second - 1 == ' ') ||
							(minmax.second.first + 1 == ' ' && minmax.second.second + 1 == ' '))
							score = 2;
						temp.push_back(std::make_pair(score, minmax));
					}
				}
				if (minmax.second.first - minmax.first.first == -1) {
					if (minmax.second.first + 1 == ' ' && minmax.second.second + 1 == ' ') {
						if ((minmax.second.first - 1 == ' ' && minmax.second.second - 1 == ' ') ||
							(minmax.second.first - 1 == ' ' && minmax.second.second + 1 == ' '))
							score = 3;
						temp.push_back(std::make_pair(score, minmax));
					}
				}
				else {
					score = 1;
					temp.push_back(std::make_pair(score, minmax));
				}
			}
		}
		for (auto t : temp) {
			if (t.first > temp1) {
				temp1 = t.first;
				bestPlay = t.second;
			}
		}
		return bestPlay;
	}

	return bestPlay;
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

char Game::getLetter(size_t row, size_t col) {
	if (board[row][col] == _playerLetter) {
		return _playerLetter;
	}
	if (board[row][col] == _playerKingLetter) {
		return _playerKingLetter;
	}
}

void Game::printBoard() {
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
		}
		cout << "|\n  ";
		for (int i = 0; i < _size; i++) {
			cout << "|_____";
		}
		cout << "|\n";
	}
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