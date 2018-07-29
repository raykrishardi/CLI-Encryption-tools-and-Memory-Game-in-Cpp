#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// ----------------------------------------------------------------
//							global variable
// ----------------------------------------------------------------

//stores message to be coded/decoded
string message; 
//stores number of message to be coded/decoded
int numberOfMessage; 


// ----------------------------------------------------------------
//						functions for validation
// ----------------------------------------------------------------

//checks whether the message contains any numerical digit
//returns true if it contains numerical digit
bool isNumeric(string message){
	bool isNumeric = false;

	for (int i = 0; i < message.length(); i++){
		if (isdigit(message[i])){
			isNumeric = true;
			break;
		}
	}


	return isNumeric;
}

//checks whether the number of message contains any character that is not numerical digit
//returns true if it contains any character that is not numerical digit
bool isLetter(string sNumberOfMessage){
	bool isLetter = false;

	for (int i = 0; i < sNumberOfMessage.length(); i++){
		if (!isdigit(sNumberOfMessage[i])){
			isLetter = true;
			break;
		}
	}

	return isLetter;
}

//checks whether the codeword is in all lower case alphabet letter
//returns false if it is not in all lower case
bool isAllLowerCaseAlphabet(string codeword){
	bool isAllLowerCase = true;

	for (int i = 0; i < 4; i++){
		if (!(codeword[i] >= 97 && codeword[i] <= 122)){
			isAllLowerCase = false;
			break;
		}
	}

	return isAllLowerCase;
}

//checks whether the message contains any upper case alphabet letter
//returns true if it contains upper case
bool isUpperCaseAlphabet(string message){
	bool isUpperCase = false;

	for (int i = 0; i < message.length(); i++){
		if (message[i] >= 65 && message[i] <= 90){
			isUpperCase = true;
			break;
		}
	}

	return isUpperCase;
}


// ----------------------------------------------------------------
//						utilities functions
// ----------------------------------------------------------------

//prompts for appropriate message based on the option 
//performs validation on the message
void promptMessage(int option){
	bool messageValid = false;

	while (!messageValid){
		if (option == 0) //used to prompt message to be stored in the file
			cout << "\nWhat message do you want to store? ";
		else if (option == 1) //used to prompt message to be coded
			cout << "\nWhat message do you want to code? ";
		else if (option == 2) //used to prompt message to be decoded
			cout << "\nWhat message do you want to decode? ";
		getline(cin, message);

		//message cannot contain any number or upper case letter and the first character must be a lower case letter
		if (!isNumeric(message) && !isUpperCaseAlphabet(message) && message[0] >= 97 && message[0] <= 122)
			messageValid = true;
		else 
			cout << "Invalid message! Try again...";
	}
}

//prompts the number of messages to be stored in the file (max 10) and the content of the message
//finally save these messages to the "messages.txt" file
void promptAndSaveMessage(){
	const int MAX_NUMBER_OF_MESSAGE = 10;
	string sNumberOfMessage;
	bool validNumberOfMessage = false;

	ofstream outMessageFile;

	//perform validation on the number of messages
	while (!validNumberOfMessage){
		cout << "How many messages do you want to save into the file (max 10)? ";
		getline(cin, sNumberOfMessage);

		numberOfMessage = atoi(sNumberOfMessage.c_str());

		//number of messages must be in the range of 1 to 10 and contain numerical digit only
		if (numberOfMessage > 0 && numberOfMessage <= MAX_NUMBER_OF_MESSAGE && !isLetter(sNumberOfMessage))
			validNumberOfMessage = true;
		else
			cout << "Invalid number of message! Try again..." << endl;
	}

	//delete existing messages from the messages.txt file
	outMessageFile.open("messages.txt", ios::trunc);
	outMessageFile.close();

	//add new messages to the messages.txt file
	for (int i = 1; i <= numberOfMessage; i++){
		promptMessage(0); //ask for message to be stored in the file
		//open the file and append the message into the file
		outMessageFile.open("messages.txt", ios::app);
		outMessageFile << message << endl;
		//close the file so that next message will be appended to the file
		outMessageFile.close();
	}

}


// ----------------------------------------------------------------
//							codebreaker
// ----------------------------------------------------------------

//codebreaker application
void codebreaker(){
	bool validFileOption = false;
	string fileOption;

	int option;
	bool optionValid = false;
	string sOption;

	int messageNumber = 0;

	string codeword;
	bool codewordValid = false;

	int codewordNumberPre = 0;
	int codewordNumberFinal = 0;
	int tempNum = 0;

	ifstream inMessageFile;


	//main display menu
	cout << "Code/Decode Service\n\n";
	//performs validation on file and code/decode option
	while (!optionValid){
		//validation on file option
		while (!validFileOption){
			cout << "Do you want to use a file(y/n)? ";
			getline(cin, fileOption);

			if (fileOption == "y"){
				promptAndSaveMessage(); //prompt and save message to the messages.txt file
				validFileOption = true;
			}
			else if (fileOption == "n")
				validFileOption = true;
			else
				cout << "Invalid option! Try again..." << endl;
		}


		cout << "What would you like to do? Code (1) or Decode (2): ";
		getline(cin, sOption);

		//validation on code/decode option
		option = atoi(sOption.c_str());

		switch (option){
		case 1:
			if (fileOption == "n")
				promptMessage(option); //prompt for message only
			optionValid = true;
			break;
		case 2:
			if (fileOption == "n")
				promptMessage(option); //prompt for message only
			optionValid = true;
			break;
		default:
			cout << "Invalid option! Try again..." << endl;
		}
	}


	//prompt and validate code word
	while (!codewordValid){
		cout << "What is the code word (lowercase word 4 characters long): ";
		getline(cin, codeword);

		//code word must be 4 characters long and in all lower case alphabet letter
		if (codeword.length() == 4 && isAllLowerCaseAlphabet(codeword))
			codewordValid = true;
		else
			cout << "Invalid code word! Try again..." << endl;
	}

	// --------------------------
	//	calculate codeword number
	// --------------------------
	for (int i = 0; i < codeword.length(); i++) {
		codewordNumberPre += (codeword[i] - 96);
	}

	tempNum = codewordNumberPre;

	while (tempNum > 9) {
		codewordNumberFinal += tempNum % 10;
		tempNum = tempNum / 10;
	}

	codewordNumberFinal += tempNum;

	if (codewordNumberFinal > 9) {
		codewordNumberFinal = codewordNumberFinal / 10 + codewordNumberFinal % 10;
	}

	cout << "\n[Word Number Calculation... your codeword number is " << codewordNumberFinal << "]\n\n";




	// ----------------
	//  code process
	// ----------------
	if (option == 1){

		//if the user wants to use the file option
		if (fileOption == "y"){
			//read the content of messages.txt file
			inMessageFile.open("messages.txt");

			//process each message in the messages.txt file
			for (int messageFileLine = 1; messageFileLine <= numberOfMessage; messageFileLine++){
				getline(inMessageFile, message);
				//code each message in the messages.txt file
				for (int i = 0; i < message.length(); i++){
					if (message[i] >= 97 && message[i] <= 122){
						messageNumber = message[i] - 96 + codewordNumberFinal;
						//make sure that the message is between a-z
						if (messageNumber > 26){
							message[i] = messageNumber + 96 - 26;
						}
						else {
							message[i] = messageNumber + 96;
						}
					}
				}
				//display the coded messages
				cout << "Your coded message is " << message << "\n";
			}
			cout << endl;
		}
		//if the user does not want to use the file option
		else{
			//code the message
			for (int i = 0; i < message.length(); i++){
				if (message[i] >= 97 && message[i] <= 122){
					messageNumber = message[i] - 96 + codewordNumberFinal;
					//make sure that the message is between a-z
					if (messageNumber > 26){
						message[i] = messageNumber + 96 - 26;
					}
					else {
						message[i] = messageNumber + 96;
					}
				}
			}
			//display the coded message
			cout << "Your coded message is " << message << "\n\n";
		}

	}
	// ----------------
	//  decode process
	// ----------------
	else if (option == 2){

		//if the user wants to use the file option
		if (fileOption == "y"){
			//read the content of messages.txt file
			inMessageFile.open("messages.txt");

			//process each message in the messages.txt file
			for (int messageFileLine = 1; messageFileLine <= numberOfMessage; messageFileLine++){
				getline(inMessageFile, message);
				//decode each message in the messages.txt file
				for (int i = 0; i < message.length(); i++){
					if (message[i] >= 97 && message[i] <= 122){
						messageNumber = message[i] - 96 - codewordNumberFinal;
						//make sure that the message is between a-z
						if (messageNumber <= 0){
							message[i] = messageNumber + 96 + 26;
						}
						else {
							message[i] = messageNumber + 96;
						}
					}
				}
				//display the decoded messages
				cout << "Your decoded message is " << message << "\n";
			}
			cout << endl;
		}
		//if the user does not want to use the file option
		else{
			//decode the message
			for (int i = 0; i < message.length(); i++){
				if (message[i] >= 97 && message[i] <= 122){
					messageNumber = message[i] - 96 - codewordNumberFinal;
					//make sure that the message is between a-z
					if (messageNumber <= 0){
						message[i] = messageNumber + 96 + 26;
					}
					else {
						message[i] = messageNumber + 96;
					}
				}
			}
			//display the decoded message
			cout << "Your decoded message is " << message << "\n\n";
		}
	}
}