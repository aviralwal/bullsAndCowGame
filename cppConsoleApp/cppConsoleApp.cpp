// cppConsoleApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include "cppConsoleApp.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame; // Created object of the bull cow class

//Creating a function to show intro
void printInfo() {
	
	std::cout << "Welcome to the game." << std::endl << "Can you guess the word of length " << BCGame.getHiddenWordLength() << std::endl;
	return;
}

FText getValidGuess() {
	EGuessStatus status = EGuessStatus::Invalid;
	FText guess = "";
	do {
		std::cout << "Try " << BCGame.getCurrentTry() << " of " << BCGame.getMaxTries() <<" Enter your guess :";
		getline(std::cin, guess);
		status = BCGame.checkGuessValidity(guess);
		switch (status)
		{
		case OK:
			break;
		case Not_Isogram:
			std::cout << "The word is not an isogram";
			break;
		case Wrong_Length:
			std::cout << "The word should be of length " << BCGame.getHiddenWordLength() << std::endl;
			break;
		case Not_Lowercase:
			std::cout << "The word should be all lower case.";
			break;
		default:
			std::cout << "Something unexpected happened";
			break;
		}
		std::cout << std::endl << std::endl ;
	} while (status != EGuessStatus::OK);

	return guess;
}


void playGame()
{
	BCGame.reset();
	int32 maxTries = BCGame.getMaxTries();
	while(!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTries)
	{
		FText guess = getValidGuess();

		
		std::cout << "You guessed " << guess << std::endl;
		FBullCowCount fBullCowCountObj = BCGame.SubmitValidGuess(guess);
		std::cout << "Bulls = " << fBullCowCountObj.Bulls;
		std::cout << ". Cows = " << fBullCowCountObj.Cows << std::endl;
		if (BCGame.isGameWon())
			std::cout << "You guessed Correctly";
		else
			std::cout << "Try Again.";
		std::cout << std::endl;
	}
}

bool askToPlayAgain() {

	std::cout << "Do you want to play again(y/n)? ";
	FText response = "";
	getline(std::cin, response);

	return (response[0] == 'y' || response[0] == 'Y');

}

void printGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << " CONGRATULATIONS! YOU WON. ";
	}
	else {
		std::cout << "BETTER LUCK NEXT TIME.";
	}
	std::cout << std::endl;
}

int main()
{
	bool toPlayAgain = false;
	do {
		printInfo();
		playGame();
		// TODO add a game summary
		printGameSummary();
		toPlayAgain = askToPlayAgain();
	} while (toPlayAgain);

	return 0;
}
