#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "game.hpp"

TEST_CASE("") {
	Game g;
	ostringstream output = g.printBoard();
	REQUIRE(output.str() == " r r r rr r r r  r r r r                b b b b  b b b bb b b b ");
}