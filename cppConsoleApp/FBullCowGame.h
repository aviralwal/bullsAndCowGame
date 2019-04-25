#pragma once
#include <string>
#include <iostream>

using FString = std::string;
using int32 = int;

enum EGuessStatus {
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame {
public:
	FBullCowGame();
	void reset();
	int32 getMaxTries() const;
	int32 getCurrentTry() const;
	bool isGameWon() const;
	EGuessStatus checkGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString); // counts bulls and cow and increases try no, assuming correct guess
	int32 getHiddenWordLength() const;

private:
	int32 myMaxTries = 5;
	int32 myCurrentTry = 1;
	FString myHiddenWord; 
	bool isWon = false;
	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
};