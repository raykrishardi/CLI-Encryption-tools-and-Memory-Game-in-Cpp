#include <iostream>
#include <string>
#include "assignment1.h"

using namespace std;

void menu(){
	string sAppCode;
	bool validAppCode = false;
	
	//perform validation on application code input (input must be either 1 or 2 only)
	while (!validAppCode){
		cout << "Application:" << endl;
		cout << "1. Codebreaker" << endl;
		cout << "2. Memory Challenge" << endl;
		cout << "Select application: ";
		getline(cin, sAppCode);

		//application code 1 indicates codebreaker game
		if (sAppCode == "1"){
			system("cls");
			codebreaker();
			validAppCode = true;
		}
		//application code 2 indicates memory challenge game
		else if (sAppCode == "2"){
			system("cls");
			memoryChallengeMenu();
			validAppCode = true;
		}
		else {
			cout << "Invalid application code! Try again...";
			system("timeout 3");
			system("cls");
		}
	}
	system("pause");
}