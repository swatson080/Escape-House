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


class room {
	private:
		std::string m_roomName;
	public:
		void setRoomName(std::string name) {
			m_roomName = name;
		}
		std::string getRoomName() {
			return m_roomName;
		}
};

class house {
	private:
		const static int m_numRooms = 5;
		enum class roomNumbers {bedroom, livingRoom, hallway, kitchen, diningRoom};
		const std::string m_roomNames[m_numRooms] = {"Bedroom","Living Room", "Hallway", "Kitchen", "Dining Room"};
		const static int m_numBedroomExits = 2; // Number of available moves from the bedroom
		const static int m_numLRoomExits = 2; // Number of available moves from the living room
		const static int m_numHallwayExits = 2; // Number of available moves from the hallway
		const static int m_numKitchenExits = 3; // Number of available moves from the kitchen 
		const static int m_numDRoomExits = 1; // Number of available moves from the dining room

		const int m_bedroomExits[m_numBedroomExits] = { (int)roomNumbers::livingRoom, (int)roomNumbers::kitchen }; 
		const int m_livingRoomExits[m_numLRoomExits] = { (int)roomNumbers::bedroom, (int)roomNumbers::hallway };
		const int m_hallwayExits[m_numHallwayExits] = { (int)roomNumbers::livingRoom, (int)roomNumbers::kitchen };
		const int m_kitchenExits[m_numKitchenExits] = { (int)roomNumbers::bedroom, (int)roomNumbers::hallway, (int)roomNumbers::diningRoom };
		const int m_diningRoomExits[m_numDRoomExits] = { (int)roomNumbers::kitchen };
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
		int getNumRoomExits(int currentRoom) {
			switch(currentRoom) {
				case (int)roomNumbers::bedroom :
					return m_numBedroomExits;
				case (int)roomNumbers::livingRoom :
					return m_numLRoomExits;
				case (int)roomNumbers::hallway:
					return m_numHallwayExits;
				case (int)roomNumbers::kitchen:
					return m_numKitchenExits;
				case (int)roomNumbers::diningRoom:
					return m_numDRoomExits;
			}
		}
		void printRoomNames() {
			for(int i = 0; i < m_numRooms; i++) {
				std::cout << rooms[i].getRoomName() << " " << std::flush;
			}
			std::cout << std::endl;
		}
		std::string printCurrentRoom(int currentRoom) {
			return rooms[currentRoom].getRoomName();
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
				case (int)roomNumbers::livingRoom :
					break;
				case (int)roomNumbers::hallway :
					break;
				case (int)roomNumbers::kitchen :
					break;
				case (int)roomNumbers::diningRoom :
					break;
			}
			std::cout << ">" << std::flush;
		}	

		bool getState() {
			return locked;
		}
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
		void updateRoom(house &house) {
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

};

// FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////////////////////////////////////
int menuChoice();
int gameLoopMenuChoice(player player, house house);
int getIntInput(std::string message); 
std::string getStringInput();
void play();

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

int gameLoopMenuChoice(player player, house house) {
	std::string menuMessage = 
		"\nWhat do you want to do?\n1. Move to another room\n2.Search " + house.printCurrentRoom(player.getCurrentRoom()) + "\n>";
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

void play() {
// Create a test house object
/*
	house testHouse;
	player testPlayer;
	std::cout << "House has been created with " << testHouse.getNumRooms() << " rooms. Right now it is " << std::flush;
	if(testHouse.getState()) {
		std::cout << " locked." << std::endl;
	}
	else {
		std::cout << " unlocked." << std::endl;
	}	
	testHouse.printRoomNames();
	std::cout << "You are in the " << testHouse.printCurrentRoom(testPlayer.getCurrentRoom()) << "." << std::endl;
	*/
	house house;
	player player;
	house.printCurrentRoom(player.getCurrentRoom());
	switch(gameLoopMenuChoice(player,house)) {
		case 1:
			std::cout << "Okay, switching rooms..." << std::endl;
			break;
		case 2:
			std::cout << "Okay, searching room..." << std::endl;
			break;		
	}
	house.printAvailableRooms(player.getCurrentRoom());
	player.updateRoom(house);
	house.printCurrentRoom(player.getCurrentRoom());
}

