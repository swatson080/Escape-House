// Text based game where user tries to escape from house by finding the key

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <ctime>

class container {
};

class items {
};

class player {
	private: 
		int currentRoom;
	public:
		player() : currentRoom(0) {}
		int getCurrentRoom() {
			return currentRoom;
		}
		void setCurrentRoom(int newRoom) {
			currentRoom = newRoom;
		}
};

class room {
	private:
		std::string m_roomName;
	public:
		// Constructors are below, but currently not using them
		/*
		room() {
			m_roomName = "Unknown name";
		}
		room(std::string name) : m_roomName(name) {}
		*/
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
		enum class roomNumbers {bedroom, bathroom, kitchen, livingRoom};
		const std::string m_roomNames[m_numRooms] = {"Bedroom","Bathroom","Kitchen","Living Room"};
		const static int m_numBedroomExits = 2; // Number of available moves from the bedroom
		const static int m_numBathroomExits = 1; // Number of available moves from the bathroom
		const static int m_numKitchenExits = 2; // Number of available moves from the kitchen
		const static int m_numLRoomExits = 1; // Number of available moves from the living room

		const int m_bedroomExits[m_numBedroomExits] = { (int)roomNumbers::bathroom, (int)roomNumbers::kitchen }; 
		const int m_bathroomExits[m_numBathroomExits] = { (int)roomNumbers::bedroom };
		const int m_kitchenExits[m_numKitchenExits] = { (int)roomNumbers::bedroom, (int)roomNumbers::livingRoom };
		const int m_livingRoomExits[m_numLRoomExits] = { (int)roomNumbers::kitchen };
		room rooms[m_numRooms];
		bool locked;	
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
		void printCurrentRoom(int currentRoom) {
			std::cout << "You are in the " << rooms[currentRoom].getRoomName() << "." << std::endl;
		}
		
		void printAvailableRooms(int currentRoom) {
			// This function should print which rooms are currently available for the player to move to
			// Needs another function that just returns which rooms are available, based on which room the player is currently in
			switch(currentRoom) {
				case (int)roomNumbers::bedroom : 
					for(int i = 0; i < m_numBedroomExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_bedroomExits[i]].getRoomName() << std::endl;
					}
					break;
				case (int)roomNumbers::bathroom :
					for(int i = 0; i < m_numBathroomExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_bathroomExits[i]].getRoomName() << std::endl;
					}
					break;
			}
			std::cout << ">" << std::flush;
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
/*
	house testHouse;
	std::cout << "House has been created with " << testHouse.getNumRooms() << " rooms. Right now it is " << std::flush;
	if(testHouse.getState()) {
		std::cout << " locked." << std::endl;
	}
	else {
		std::cout << " unlocked." << std::endl;
	}	
	testHouse.printRoomNames();
	testHouse.printCurrentRoom();
	*/
	house house;
	player player;
	house.printCurrentRoom(player.getCurrentRoom());
	std::cout << "Which room do you want to move to?" << std::endl;
	house.printAvailableRooms(player.getCurrentRoom());
	player.setCurrentRoom(getIntInput(">"));
	house.printCurrentRoom(player.getCurrentRoom());
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

