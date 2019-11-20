#include <iostream>
#include <string>
#include <locale>

// I'm really moving out of my comfort zone here and using something I call my kryptonite, enums!
enum choice{ROCK = 1, PAPER, SCISSORS, QUIT, ERROR};
enum matchResult{WIN = 1, LOSS, DRAW};
bool gameRunning = 1;

choice GetSelection(std::string _inputString);
matchResult CheckForWin(choice _playerInput, choice _computerChoice);
std::string GetChoice(choice _choice);

int main() {
	choice playerInput;
	
	int playerScore = 0;
	int computerScore = 0;
	int totalScore = 3;

	std::string strplayerInput;


	std::cout << "\nWelcome to Rock, Paper, Scissors! Challenge yourself against a computer to win and become the king of RnG!\n\nTo start, press enter. To quit, type 'Quit'";
	std::cin.get();

	while(gameRunning) {
		std::cout << "\n*******************";

		if (playerScore >= totalScore) {
			std::cout << "\nCongratulations! You won!\n";
			gameRunning = false;
			break;
		}
		else if (computerScore >= totalScore) {
			std::cout << "\nGame over, you've lost!\n";
			gameRunning = false;
			break;
		}

		std::cout << "\nEnter your selection (Rock, Paper, Scissors): ";
		std::cin >> strplayerInput;
		
		playerInput = GetSelection(strplayerInput);
		
		if (playerInput == ERROR) {
			std::cout << "\nInvalid input, please enter either 'Rock', 'Paper' or 'Scissors'\n";
			continue;
		}
		
		if (playerInput == QUIT) {
			std::cout << "\nExiting...";
			gameRunning = false;
			break;
		}
		
		choice computerChoice = (choice)(std::rand() % 3 + 1); // This complicated line basically generates a random int from 1 to 3 using the stdlib and turns it to an enum choice.


		std::cout << "You chose: " << GetChoice(playerInput) << "\nThe computer chose: " << GetChoice(computerChoice) << std::endl;

		int matchResult = CheckForWin(playerInput, computerChoice);

		switch (matchResult) {
			case WIN:
				std::cout << "\nCongratulations, you win this round!\n";
				playerScore++;
				break;
			case LOSS:
				std::cout << "\nFailure, you lost that round!\n";
				computerScore++;
				break;
			case DRAW:
				std::cout << "\nDraw! No one gets a score.\n";
				break;
			default:
				std::cout << "\nError, unknown match result! Skipping round...\n";
				break;
		}

		std::cout << "\nPlayer's score is: " << playerScore << " The player needs " << totalScore - playerScore << " points to win.";
		std::cout << "\nComputer's score is: " << computerScore << " The computer needs " << totalScore - computerScore << " points to win.";

	}
	std::cin.ignore();
	std::cin.get();
	return 0;
}

choice GetSelection(std::string _inputString) {
	std::locale loc;
	for (std::string::size_type i = 0; i < _inputString.length(); ++i)	_inputString[i] = std::tolower(_inputString[i], loc);

	if (_inputString == "rock")	return ROCK;
	else if (_inputString == "paper")	return PAPER;
	else if (_inputString == "scissors")	return SCISSORS;
	else if (_inputString == "quit")	return QUIT;
	else return ERROR;
}

matchResult CheckForWin(choice _playerInput, choice _computerChoice) {
	// Draw!
	if (_computerChoice == _playerInput)	return DRAW;
	
	//Check for Player win status, because we already termined a draw, it's either a win or lose.
	if ((_playerInput == ROCK && _computerChoice == SCISSORS) || (_playerInput == PAPER && _computerChoice == ROCK) || (_playerInput == SCISSORS && _computerChoice == PAPER))	return WIN;
	else return LOSS; // All possible win conditions exhausted, call loss.
}

std::string GetChoice(choice _choice) {
	switch (_choice) {
	case ROCK:
		return "Rock";
		break;
	case PAPER:
		return "Paper";
		break;
	case SCISSORS:
		return "Scissors";
		break;
	default:
		return "ERROR: INVALID CHOICE";
	}
}