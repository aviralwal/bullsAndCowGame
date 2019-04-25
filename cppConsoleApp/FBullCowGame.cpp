#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() {
	reset();
}

void FBullCowGame::reset() {
	myCurrentTry = 1;
	const FString HIDDEN_WORD = "plant";
	myHiddenWord = HIDDEN_WORD;
	isWon = false;
	return;
}
 
int32 FBullCowGame::getMaxTries() const
{
	TMap<int32, int32> wordLengthToMaxTriesMap{ {3,3},{4,4},{5,5} };
	return wordLengthToMaxTriesMap[myHiddenWord.length()];
}

int32 FBullCowGame::getCurrentTry() const
{
	return myCurrentTry;
}

bool FBullCowGame::isGameWon() const
{
	return isWon;
}

bool FBullCowGame::isIsogram(FString word) const {
	if (word.length() <= 1) {
		return true;
	}
	TMap<char, bool> letterSeen;
	for (auto letter : word){
		if (letterSeen[letter] == true)
			return false;
		letterSeen[letter] = true;
	}
	return true;
}

bool FBullCowGame::isLowerCase(FString word) const
{
	for (auto letter : word) {
		if (!islower(letter)) {
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::checkGuessValidity(FString guess) const
{
	if (guess.length() != getHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else if (!isLowerCase(guess)) { 
		return EGuessStatus::Not_Lowercase;
	}
	else if (!isIsogram(guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else {
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	myCurrentTry++;
	FBullCowCount FBullCowCountObj;
	int32 hiddenWordLength = myHiddenWord.length();
	for (int32 allLetters = 0; allLetters < hiddenWordLength; allLetters++){
		for (int32 insideLetter = 0; insideLetter < hiddenWordLength; insideLetter++){
			if (guess[allLetters] == myHiddenWord[allLetters] && allLetters == insideLetter) {

				FBullCowCountObj.Bulls++;
			}
			else if ((allLetters != insideLetter) && (myHiddenWord[allLetters] == guess[insideLetter])) {
				FBullCowCountObj.Cows++;
			}
		}
	}
	if (FBullCowCountObj.Bulls == hiddenWordLength)
		isWon = true;
	return FBullCowCountObj;
}

int32 FBullCowGame::getHiddenWordLength() const
{
	return myHiddenWord.length();
}
 