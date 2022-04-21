// game.hpp
// Rose Peters
// Created: 12-01-2022
// Header for Game class


#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<utility>
using std::pair;
#include <vector>
using std::vector;
#include<string>
using std::string;
#include <ostream>
#include <sstream>
using std::ostringstream;
#include <cmath>
#include <random>
using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;
#include <chrono>


// class Game
// Manages players and board for checkers game.
class Game {
public:
	Game() = default;
	~Game() = default;



	// getInput
	// Return pairs of coordinates, start and end position
	pair<pair<int, int>, pair<int, int>> getInput();

	// generateMoves
	// Store all possible checker piece moves
	int generateMoves();


	// resetMoves
	// Clear out list of generated moves
	void resetMoves();

	// movePiece
	// Move piece based on input
	void movePiece(pair<int, int> p1, pair<int, int> p2, bool jump, bool showBoard);

	// pieceJump
	// prompt to jump if a jump is possible
	pair<pair<int, int>, pair<int, int>> pieceJump();

	// getHasJump
	// Return value of given bool
	bool getHasJump();

	// getJumped
	// Return the value of given bool
	bool getJumped();

	// resetJumped
	// if turn is over, reset jump value
	void resetJumped();

	// minimax
	// Determine best move based on scoring system
	pair<pair<int, int>, pair<int, int>> minimax(int depth);
	pair<pair<int, int>, pair<int, int>> minMove(int depth, int alpha, int beta);
	pair<pair<int, int>, pair<int, int>> maxMove(int depth, int alpha, int beta);
	pair<pair<int, int>, pair<int, int>> evalGameState(int minmax);

	// monteCarlo
	// Determine best move based on time limit
	pair<pair<int, int>, pair<int, int>> monteCarlo(std::chrono::steady_clock::time_point time);
	pair<pair<int, int>, pair<int, int>> MCTSUpper(std::chrono::steady_clock::time_point time, int upper, int lower);
	pair<pair<int, int>, pair<int, int>> MCTSLower(std::chrono::steady_clock::time_point time, int upper, int lower);



	int valueOfMoves(pair<pair<int, int>, pair<int, int>> move);

	// switchDirection
	// Set direction of movement based on player
	void switchDirection();

	// switchKingDirection
	// Return value for direction based on whether a king piece is selected
	int switchKingDirection(int row, int col, char upOrDown) const;

	// winConditions
	// set conditions for the game to end
	void winConditions();

	// setPlayer
	// Set player number (1 or 2)
	void setPlayer(int player);

	// setGameType
	// Set the game type for AI and human players
	void setGameType(int gametype);

	//setPlayerLetter 
	// set what letter the current player is
	void setPlayerLetter();

	// setAutoplay
	// Set autoplay boolean
	void setAutoplay(bool autoplay);

	// switchToKing
	// Mark piece as king
	void switchToKing(int row, int col);

	// checkForKing
	// check if a piece qualifies as king piece
	// if so, make call to switchToKing() function
	void checkForKing();

	// printLetter
	// Return player or king letter based on piece information 
	char getLetter(int row, int col) const;

	// printBoard
	// print board based on piece information
	ostringstream printBoard() const;

	// gameIsOver
	// Return whether or not game is over
	bool gameIsOver() const;

	// size
	// Return size of the board
	int size() const;

	// setSize
	void setSize(int size);

	// setBoard
	// set temporary board or main board to the other based on given input
	void setBoard(int switchNumber);

private:
	// player is who will start first. (1 - Computer / 0 - Human)
	int _player = 0;
	int _movementDirection = 1;
	pair<int, int> _temp;
	char _playerLetter = ' ';
	char _playerKingLetter = ' ';
	bool _hasJump = false;
	bool _jumped = false;
	bool _gameOver = false;
	bool _autoplay;

	// size of board
	int _size = 8;
	int _depth = 1;
	
	// 1: Random moves, 2: minimax, 3: montecarlo
	int _gameType;

	vector<vector<pair<pair<int, int>, pair<int, int>>>> _tempMoveSet;
	vector<vector<pair<pair<int, int>, pair<int, int>>>> _moves;
	vector<vector<pair<pair<int, int>, pair<int, int>>>> _jumps;

	char board[8][8] =
	{
		{' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r'},
		{'r', ' ', 'r', ' ', 'r', ' ', 'r', ' '},
		{' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r'},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
		{' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
		{'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
	};

	// need to manually set this and the board size to change the board.
	/*char board[10][10] =
	{
		{' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r'},
		{'r', ' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r', ' '},
		{' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r'},
		{'r', ' ', 'r', ' ', 'r', ' ', 'r', ' ', 'r', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
		{' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
		{'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
		{' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b'},
		{'b', ' ', 'b', ' ', 'b', ' ', 'b', ' ', 'b', ' '},
	};*/

	// used for minimax / montecarlo
	int _boardValues[8][8] = {
		3,1,3,1,3,1,3,1,
		1,3,1,3,1,3,1,3,
		3,1,3,1,3,1,3,1,
		3,3,3,3,3,3,3,3,
		3,3,3,3,3,3,3,3,
		0,3,0,3,0,3,0,3,
		3,0,3,0,3,0,3,0,
		0,3,0,3,0,3,0,3
	};

	// save copy of boards during minimax / montecarlo 
	char _tempBoard[8][8] = { ' ' };
	int _tempValues[8][8] = { 0 };

};
