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

// class Game
// Manages players and board for checkers game.
class Game {
public:
	Game() = default;
	~Game() = default;



	// getInput
	// Return pairs of coordinates, start and end position
	pair<pair<size_t, size_t>, pair<size_t, size_t>> getInput() const;

	// generateMoves
	// Store all possible checker piece moves
	void generateMoves();


	// resetMoves
	// Clear out list of generated moves
	void resetMoves();

	// movePiece
	// Move piece based on input
	void movePiece(pair<size_t, size_t> p1, pair<size_t, size_t> p2);

	// pieceJump
	// prompt to jump if a jump is possible
	pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>> pieceJump();

	//moveJump
	// Piece move function for pieceJump
	void moveJump(pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t,size_t>> p1);

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
	pair<pair<size_t,size_t>, pair<size_t, size_t>> minimax(size_t depth) const;

	// switchDirection
	// Set direction of movement based on player
	void switchDirection();

	// switchKingDirection
	// Return value for direction based on whether a king piece is selected
	int switchKingDirection(size_t row, size_t col, char upOrDown) const;

	// winConditions
	// set conditions for the game to end
	void winConditions();

	// setPlayer
	// Set player number (1 or 2)
	void setPlayer(std::size_t player);

	//setPlayerLetter 
	// set what letter the current player is
	void setPlayerLetter();

	// switchToKing
	// Mark piece as king
	void switchToKing(size_t row, size_t col);

	// checkForKing
	// check if a piece qualifies as king piece
	// if so, make call to switchToKing() function
	void checkForKing();

	// printLetter
	// Return player or king letter based on piece information 
	char getLetter(size_t row, size_t col);

	// printBoard
	// print board based on piece information
	ostringstream printBoard();

	// gameIsOver
	// Return whether or not game is over
	bool gameIsOver() const;

	// size
	// Return size of the board
	size_t size() const;

	// setBoard
	// set temporary board or main board to the other based on given input
	void setBoard(int switchNumber);

private:
	// player is who will start first. (1 - Computer / 0 - Human)
	std::size_t _player = 0;
	int _movementDirection = 1;
	pair<size_t, size_t> _temp;
	char _playerLetter = ' ';
	char _playerKingLetter = ' ';
	bool _hasJump = false;
	bool _jumped = false;
	bool _gameOver = false;
	// size of board
	size_t _size = 8;
	size_t _depth = 1;

	vector<vector<pair<pair<size_t, size_t>, pair<size_t, size_t>>>> _moves;
	vector<vector<pair<pair<pair<size_t, size_t>, pair<size_t, size_t>>, pair<size_t, size_t>>>> _jumps;

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

	char _tempBoard[8][8] = { ' ' };

};
