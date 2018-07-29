#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "assignment1.h"

using namespace std;

// -----------------------------------------------------------------------
//							global variable/constant
// -----------------------------------------------------------------------

//constant that determines the number of row and column in "board" array 
const int BOARD_ROW = 7, BOARD_COL = 7;
//constant that determines the number of row and column in "characters" array 
const int CHARACTERS_ROW = 7, CHARACTERS_COL = 7;

//array that represents the game board
char board[BOARD_ROW][BOARD_COL] = {
	{ ' ', '0', '1', '2', '3', '4', '5' },
	{ '0', '-', '-', '-', '-', '-', '-' },
	{ '1', '-', '-', '-', '-', '-', '-' },
	{ '2', '-', '-', '-', '-', '-', '-' },
	{ '3', '-', '-', '-', '-', '-', '-' },
	{ '4', '-', '-', '-', '-', '-', '-' },
	{ '5', '-', '-', '-', '-', '-', '-' }
};

//array that represents characters inside the board
char characters[CHARACTERS_ROW][CHARACTERS_COL] = {
	{ ' ', '0', '1', '2', '3', '4', '5' },
	{ '0', 'a', 'a', 'b', 'b', 'c', 'c' },
	{ '1', 'd', 'd', 'e', 'e', 'f', 'f' },
	{ '2', 'g', 'g', 'h', 'h', 'i', 'i' },
	{ '3', 'j', 'j', 'k', 'k', 'l', 'l' },
	{ '4', 'm', 'm', 'n', 'n', 'o', 'o' },
	{ '5', 'p', 'p', 'q', 'q', 'r', 'r' }
};

//variable that stores the player name
string player1Name;
string player2Name;

//variable that stores the player score
int player1Score = 0;
int player2Score = 0;

//variable that keeps track of the number of pair characters
int pairCounter = 0; 

//variable that determines whether the user decided to play in single player mode or not
string singlePlayerMode;

//variable that determines the save game state
//initialised to "n" to prevent user from continuing on previous saved game state that does not exist
//i.e. selecting the continue game the first time user launched the application
string saveGameState = "n"; 

//variable that determines the current player (player1/player2)
int playerNumber;

//variable that determines whether test mode is activated or not
string testMode;

//vector that keeps track of the leaderboard
vector<int> leaderboard;


// ----------------------------------------------------------------
//						function for validation
// ----------------------------------------------------------------


//checks whether the player name is valid or not (must consist of either upper/lower case alphabet letter)
//returns false if it is not either combination of upper/lower case alphabet letter
bool isName(string playerName){
	bool isName = true;
	char chr;

	for (int i = 0; i < playerName.length(); i++){
		chr = playerName[i];
		if (!(chr >= 65 && chr <= 90 || chr >= 97 && chr <= 122)){
			isName = false;
			break;
		}
	}

	return isName;
}


// ----------------------------------------------------------------
//						utilities functions
// ----------------------------------------------------------------


//prompts player name
//performs validation on the name
void promptPlayerName(){
	bool validPlayer1Name = false;
	bool validPlayer2Name = false;


	while (!validPlayer1Name){
		cout << "What is your name Player One? ";
		getline(cin, player1Name);

		//checks whether name consist of either upper/lower case alphabet letter and the length is greater than 0
		if (isName(player1Name) && player1Name.length() > 0)
			validPlayer1Name = true;
		else
			cout << "Invalid name! Try again..." << endl;
	}

	//if single player mode is on then assign "computer" as player2 name
	if (singlePlayerMode == "y")
		player2Name = "computer";
	else{
		//if single player mode is off then prompts for player2 name and perform validation
		while (!validPlayer2Name){
			cout << "What is your name Player Two? ";
			getline(cin, player2Name);

			//checks whether name consist of either upper/lower case alphabet letter and the length is greater than 0
			if (isName(player2Name) && player2Name.length() > 0)
				validPlayer2Name = true;
			else
				cout << "Invalid name! Try again..." << endl;
		}
	}
}

//display the board
void displayBoard(char board[BOARD_ROW][BOARD_COL]){
	for (int row = 0; row < BOARD_ROW; row++){
		for (int col = 0; col < BOARD_COL; col++){
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//display characters inside the board
void displayCharacters(char characters[CHARACTERS_ROW][CHARACTERS_COL]){
	for (int row = 0; row < CHARACTERS_ROW; row++){
		for (int col = 0; col < CHARACTERS_COL; col++){
			cout << characters[row][col] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//shuffle the position of each character inside the board so that they are random
void shuffleCharacters(char characters[CHARACTERS_ROW][CHARACTERS_COL]){
	//shuffle for 5000 times
	for (int i = 1; i <= 5000; i++){
		//represent random rows and columns
		int randomNumber1, randomNumber2, randomNumber3, randomNumber4;
		//temporary variable for swapping purpose
		char tmp;

		//the random row/column must be in the range of 1 to 6
		randomNumber1 = 1 + rand() % 6;
		randomNumber2 = 1 + rand() % 6;
		randomNumber3 = 1 + rand() % 6;
		randomNumber4 = 1 + rand() % 6;

		//swap the values
		tmp = characters[randomNumber1][randomNumber2];
		characters[randomNumber1][randomNumber2] = characters[randomNumber3][randomNumber4];
		characters[randomNumber3][randomNumber4] = tmp;
	}
}

//play the game
//get coordinates, perform validation on coordinates, show content from each coordinates, modify the board if two characters are pair, display appropriate messages
//increment player's score and number of pair characters
void playGame(int playerNumber, string playerName, char characters[CHARACTERS_ROW][CHARACTERS_COL], char board[BOARD_ROW][BOARD_COL]){
	//variables that determine the coordinates 
	int userRow1, userCol1; //first coordinates
	int userRow2, userCol2; //second coordinates 

	//variables that check whether the given coordinates are valid or not
	bool validUserRowCol1 = false;
	bool validUserRowCol2 = false;

	//variable that checks whether the computer chose valid coordinates or not
	bool validComputerRowCol = false;

	//if single player mode is on and it is the computer's turn
	if (singlePlayerMode == "y" && playerNumber == 2){

		//keep generating a random coordinates until the first and second coordinates are valid
		while (!validComputerRowCol){
			//random coordinates must be in the range of 1 to 6
			userRow1 = 1 + rand() % 6;
			userCol1 = 1 + rand() % 6;
			userRow2 = 1 + rand() % 6;
			userCol2 = 1 + rand() % 6;

			//first and second coordinates must not be the same and has not been opened '-'
			if (!(userRow1 == userRow2 && userCol1 == userCol2) && board[userRow1 + 1][userCol1 + 1] == '-' && board[userRow2 + 1][userCol2 + 1] == '-')
				validComputerRowCol = true;
		}

		//display the first and second coordinates chosen by the computer
		cout << "computer first guess: " << userRow1 << " " << userCol1 << endl;
		cout << "computer second guess: " << userRow2 << " " << userCol2 << endl;

	}
	//if it is not the computer's turn
	else{
		//keep asking for valid first coordinates if it is not valid
		while (!validUserRowCol1){
			//prompt for first coordinates
			cout << playerName << ". what is your first guess? Enter as two numbers separated by a space: ";
			cin >> userRow1 >> userCol1;
			//first coordinates is valid if it in the range of 0 to 5
			if (userRow1 >= 0 && userRow1 <= 5 && userCol1 >= 0 && userCol1 <= 5)
				validUserRowCol1 = true;
			else
				cout << "Invalid coordinates! Try again..." << endl;
		}
		//keep asking for valid second coordinates if it is not valid
		while (!validUserRowCol2){
			//prompt for second coordinates
			cout << playerName << ". what is your second guess? Enter as two numbers separated by a space: ";
			cin >> userRow2 >> userCol2;
			//second coordinates is valid if it in the range of 0 to 5 
			//in addition, first and second coordinates must not be the same
			if (userRow2 >= 0 && userRow2 <= 5 && userCol2 >= 0 && userCol2 <= 5){
				if (userRow1 == userRow2 && userCol1 == userCol2)
					cout << "Duplicate coordinates! Try again..." << endl;
				else
					validUserRowCol2 = true;
			}
			else
				cout << "Invalid coordinates! Try again..." << endl;
		}
	}


	//checks whether the given coordinates have not been opened '-' or not
	if (board[userRow1 + 1][userCol1 + 1] == '-' && board[userRow2 + 1][userCol2 + 1] == '-'){
		//display the value of characters inside the board for the given coordinates
		cout << "Space " << userRow1 << ", " << userCol1 << " contains " << characters[userRow1 + 1][userCol1 + 1] << endl;
		cout << "Space " << userRow2 << ", " << userCol2 << " contains " << characters[userRow2 + 1][userCol2 + 1] << endl;

		//if both coordinates contain same value then update the board with the pair values
		if (characters[userRow1 + 1][userCol1 + 1] == characters[userRow2 + 1][userCol2 + 1]){
			board[userRow1 + 1][userCol1 + 1] = characters[userRow1 + 1][userCol1 + 1];
			board[userRow2 + 1][userCol2 + 1] = characters[userRow2 + 1][userCol2 + 1];
			//checks which player has guessed correctly and increment their score properly
			if (playerNumber == 1)
				player1Score++;
			else if (playerNumber == 2)
				player2Score++;
			cout << "Well done! You found a pair!" << endl;
			//increment the number of pair found by 1
			pairCounter++;
		}
		//if both coordinates does not contain the same value then display appropriate message
		else{
			cout << "Bad luck. These two don't match." << endl;
		}
	}
	//if the given coordinates has been opened before (not '-') then player forfeit their turn
	else
		cout << "You chose a cell that has already been chosen! You forfeit your turn." << endl;

}

//prompts the user whether to save current game state or not
void promptSaveGameState(){
	bool validGameState = false;

	//remove trailing new line character up to 100 characters from previous cin >>
	cin.ignore(100, '\n');

	//keep prompting the user if the input is not valid (must be either y or n)
	while (!validGameState){
		cout << "Do you wish to save current game state (y/n)? ";
		getline(cin, saveGameState);

		if (saveGameState == "y" || saveGameState == "n")
			validGameState = true;
		else
			cout << "Invalid option! Try again..." << endl;
	}
}

//add current game's leaderboard to the "leaderboard.txt" file
void addLeaderboardToFile(){
	ofstream outLeaderboardFile;

	//add all elements in current leaderboard to the "leaderboard.txt" file
	for (int i = 0; i < leaderboard.size(); i++){
		outLeaderboardFile.open("leaderboard.txt", ios::app);
		outLeaderboardFile << leaderboard[i] << endl;
		outLeaderboardFile.close();
	}
}

//sort and update the "leaderboard.txt" file
void sortAndUpdateLeaderboard(){
	vector<int> sortedLeaderboard;
	ifstream inLeaderboardFile;
	ofstream outLeaderboardFile;
	string line;

	//this will ignore the header text ("Leaderboard Score:")
	inLeaderboardFile.open("leaderboard.txt");
	getline(inLeaderboardFile, line);

	//insert all score from file into the vector
	while (getline(inLeaderboardFile, line)){
		sortedLeaderboard.push_back(atoi(line.c_str()));
	}
	inLeaderboardFile.close();

	//sort all of the score in descending order
	sort(sortedLeaderboard.rbegin(), sortedLeaderboard.rend());
	//remove duplicate values
	sortedLeaderboard.erase(unique(sortedLeaderboard.begin(), sortedLeaderboard.end()), sortedLeaderboard.end());


	//overwrite the existing file with appropriate header text
	outLeaderboardFile.open("leaderboard.txt");
	outLeaderboardFile << "Leaderboard Score:" << endl;
	outLeaderboardFile.close();

	//add all sorted leaderboard score back to the file
	for (int i = 0; i < sortedLeaderboard.size(); i++){
		outLeaderboardFile.open("leaderboard.txt", ios::app);
		outLeaderboardFile << sortedLeaderboard[i] << endl;
		outLeaderboardFile.close();
	}
}

//display the content in "leaderboard.txt" file
void displayLeaderboard(){
	ifstream inLeaderboardFile;
	string line;

	inLeaderboardFile.open("leaderboard.txt");


	while (getline(inLeaderboardFile, line))
		cout << line << endl;
	
}


// ----------------------------------------------------------------
//							memory challenge
// ----------------------------------------------------------------


//memory challenge application
void memoryChallenge(){
	//allow rand() to generate random number
	srand(time(0));

	//if the user decides to start a new game
	if (saveGameState == "n"){

		//replace all of the opened characters in the board with '-'
		for (int row = 1; row < BOARD_ROW; row++){
			for (int col = 1; col < BOARD_COL; col++){
				board[row][col] = '-';
			}
		}

		//player scores are initialised back to 0
		player1Score = 0;
		player2Score = 0;
		//number of pairs found is initialised back to 0
		pairCounter = 0;

		//reshuffle the characters in the board so that it is random again
		shuffleCharacters(characters);

		//randomly decide which player starts first
		playerNumber = 1 + rand() % 2;


		cout << "Memory Challenge!" << "\n\n";


		//keep prompting the user if the input is not valid (must be either y or n)
		bool validSinglePlayerMode = false;
		while (!validSinglePlayerMode){
			cout << "Do you wish to play against computer (y/n)? ";
			getline(cin, singlePlayerMode);

			if (singlePlayerMode == "y" || singlePlayerMode == "n")
				validSinglePlayerMode = true;
			else
				cout << "Invalid option! Try again..." << endl;
		}


		//keep prompting the user if the input is not valid (must be either y or n)
		bool validTestMode = false;
		while (!validTestMode){
			cout << "Do you wish to turn test mode on (y/n)? ";
			getline(cin, testMode);

			if (testMode == "y" || testMode == "n")
				validTestMode = true;
			else
				cout << "Invalid option! Try again..." << endl;
		}

		//prompt for player name again if the user decides to start a new game
		promptPlayerName();
	}


	//keep looping while all characters in the board has not been opened
	while (pairCounter != 18){
		system("cls");

		cout << "Player1: " << player1Name << " Score: " << player1Score << endl;
		cout << "Player2: " << player2Name << " Score: " << player2Score << "\n\n";

		//display the characters inside the board if test mode is on
		if (testMode == "y")
			displayCharacters(characters);
		//display the game board
		displayBoard(board);

		//if it is the first player's turn
		if (playerNumber == 1){
			playGame(playerNumber, player1Name, characters, board);
			promptSaveGameState();
			//move to next player's turn
			playerNumber++;
			system("timeout 5");
			//if the player decided to save current game state then display the main menu
			if (saveGameState == "y"){
				system("cls");
				memoryChallengeMenu();
				break;
			}

		}
		//if it is the second player's turn
		else{
			playGame(playerNumber, player2Name, characters, board);
			//move to next player's turn
			playerNumber--;
			//if the user is playing with a computer, give more timeout time
			if (singlePlayerMode == "y")
				system("timeout 15");
			//if the user is playing with another user
			else{
				promptSaveGameState();
				system("timeout 5");
				//if the player decided to save current game state then display the main menu
				if (saveGameState == "y"){
					system("cls");
					memoryChallengeMenu();
					break;
				}
			}

		}
	}

	//if all characters in the board has been opened
	if (pairCounter == 18){
		//initialise the save game state back to "n"
		saveGameState = "n"; //when the game has finished, player cannot go back to previous game state
		system("cls");
		displayBoard(board);

		//determine the winner of the game
		if (player1Score == player2Score){
			cout << "Draw Game!" << endl;
			cout << "Player1: " << player1Name << " Score: " << player1Score << endl;
			cout << "Player2: " << player2Name << " Score: " << player2Score << endl;
		}
		else if (player1Score > player2Score){
			cout << "Congratulation!" << endl;
			cout << "Player1: " << player1Name << " Score: " << player1Score << " wins the game!" << endl;
		}
		else if (player1Score < player2Score){
			cout << "Congratulation!" << endl;
			cout << "Player2: " << player2Name << " Score: " << player2Score << " wins the game!" << endl;
		}

		//add first player score to the leaderboard
		leaderboard.push_back(player1Score);
		//add second player score to the leaderboard if multiplayer mode is chosen (computer's score is not added to the leaderboard)
		if (singlePlayerMode == "n"){
			//ensure that duplicate score in not added to the leaderboard
			if (player1Score != player2Score)
				leaderboard.push_back(player2Score);
		}
			
		//add current leaderboard score to the "leaderboard.txt" file
		addLeaderboardToFile();
		//clear the content of the vector
		leaderboard.clear(); 
		//sort and update the leaderboard file
		sortAndUpdateLeaderboard();

		system("pause");
		system("cls");

		//display the menu again
		memoryChallengeMenu();
	}
}

//main menu for memory challenge application
void memoryChallengeMenu(){
	string sOption;
	bool validOption = false;

	//keep looping until valid option is given by the user
	while (!validOption){
		cout << "Memory Challenge:" << endl;
		cout << "1. Start Game" << endl;
		cout << "2. Continue Game" << endl;
		cout << "3. Display leaderboard" << endl;
		cout << "Select option: ";
		getline(cin, sOption);

		//if the user decided to start a new game
		if (sOption == "1"){
			system("cls");
			//previous saved game state is not available if player decides to start a new game again
			saveGameState = "n";
			memoryChallenge();
			validOption = true;
		}
		//if the user decided to continue on previously saved game state
		else if (sOption == "2"){
			//display appropriate message if the saved game state does not exist
			if (saveGameState == "n"){
				cout << "No previous game state found! Try again...";
				system("timeout 3");
				system("cls");
			}
			//continue the last saved game state
			else{
				system("cls");
				memoryChallenge();
				validOption = true;
			}
		}
		//display the content of "leaderboard.txt" file and return back to the main menu
		else if (sOption == "3"){
			system("cls");
			displayLeaderboard();
			system("pause");
			system("cls");
			memoryChallengeMenu();
			validOption = true;
		}
		else {
			cout << "Invalid option! Try again...";
			system("timeout 3");
			system("cls");
		}
	}
}