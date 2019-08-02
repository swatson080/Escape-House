// Text based game where user tries to escape from house by finding the key

#include <iostream>
#include <string>
#include <sstream>
#include <climits>

class room {
	private:
		std::string m_roomName;
	public:
		room() {
			m_roomName = "Unknown name";
		}
		room(std::string name) : m_roomName(name) {}
		void setRoomName(std::string name) {
			m_roomName = name;
		}
		std::string getRoomName() {
			return m_roomName;
		}
};

class house {
	private:
		const static int m_numRooms = 4;
		const std::string m_roomNames[m_numRooms] = {"Bedroom","Bathroom","Kitchen","Living Room"};
		bool locked;	
		room rooms[m_numRooms];
	public:
		house() {
			for(int i = 0; i < m_numRooms; i++) {
				rooms[i].setRoomName(m_roomNames[i]);
			}	
			locked = true;
		}
		int getNumRooms() {
			return m_numRooms;
		}
		void printRoomNames() {
			for(int i = 0; i < m_numRooms; i++) {
				std::cout << rooms[i].getRoomName() << " " << std::flush;
			}
			std::cout << std::endl;
		}
		bool getState() {
			return locked;
		}
};

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
// Create a test house object
	house testHouse;
	std::cout << "House has been created with " << testHouse.getNumRooms() << " rooms. Right now it is " << std::flush;
	if(testHouse.getState()) {
		std::cout << " locked." << std::endl;
	}
	else {
		std::cout << " unlocked." << std::endl;
	}	
	testHouse.printRoomNames();
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

