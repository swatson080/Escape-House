// Text based game where user tries to escape from house by finding the key

#include <iostream>
#include <string>
#include <sstream>
#include <climits>

void play();

int menuChoice();
int getIntInput(std::string message); 
std::string getStringInput();


int main() {

	bool exit = false;

	do {
		switch(menuChoice()) {
			case 1:
				play();
				break;
			case 2:
				exit = true;
				break;
		}
	} while(!exit);


	return 0;

}

void play() {
// Add game loop here
	std::cout << "Playing game..." << std::endl;
}

// Returns users selection 
int menuChoice() {
	std::string menuMessage = "\nMAIN MENU\n1. Start\n2. Quit\n>";
	while(true) {
		int selection = getIntInput(menuMessage);
		if(selection > 0 && selection <= 2) {
			return selection;
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
	}
}

// Gets integer input from user
int getIntInput(std::string message) {
	std::string rawInput;
	while(true) {
		std::cout << message;
		rawInput = getStringInput();
		std::stringstream stream(rawInput);

		int value;
		char temp;
		stream >> value;
		if(stream && !(stream >> temp) && value >= 0 && value <= INT_MAX) {
			return value;
		}
		else {
			std::cout << "Invalid input" << std::endl;
		}
	}
}	

// Gets string input from user
std::string getStringInput() {
	std::string input;
	std::getline(std::cin,input);
	return input;
}

