// Text based game where user tries to escape from house by finding the key

#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <cstdlib>
#include <ctime>

class container {
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
		//const static int m_numRooms = 5;
		enum class roomNumbers {bedroom, livingRoom, hallway, kitchen, diningRoom, total};
		const std::string m_roomNames[(int)roomNumbers::total] = {"BEDROOM","LIVING ROOM", "HALLWAY", "KITCHEN", "DINING ROOM"};
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
		room rooms[(int)roomNumbers::total];
		bool locked;	
	public:
		house() {
			for(int i = 0; i < (int)roomNumbers::total; i++) {
				rooms[i].setRoomName(m_roomNames[i]);
			}	
			locked = true;
		}
		int getNumRooms() {
			return (int)roomNumbers::total;
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
			for(int i = 0; i < (int)roomNumbers::total; i++) {
				std::cout << rooms[i].getRoomName() << " " << std::flush;
			}
			std::cout << std::endl;
		}
		std::string getCurrentRoomName(int currentRoom) {
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
					for(int i = 0; i < m_numLRoomExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_livingRoomExits[i]].getRoomName() << std::endl;
					}
					break;
				case (int)roomNumbers::hallway :
					for(int i = 0; i < m_numHallwayExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_hallwayExits[i]].getRoomName() << std::endl;
					}
					break;
				case (int)roomNumbers::kitchen :
					for(int i = 0; i < m_numKitchenExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_kitchenExits[i]].getRoomName() << std::endl;
					}
					break;
				case (int)roomNumbers::diningRoom :
					for(int i = 0; i < m_numDRoomExits; i++) {
						std::cout << i + 1 << ". " << rooms[m_diningRoomExits[i]].getRoomName() << std::endl;
					}
					break;
			}
		}	

		int getActualMove(int currentRoom, int newRoom) {
			switch(currentRoom) {
				case (int)roomNumbers::bedroom :
					newRoom = m_bedroomExits[newRoom-1];
					return newRoom;
				case (int)roomNumbers::livingRoom :
					newRoom = m_livingRoomExits[newRoom-1];
					return newRoom;
				case (int)roomNumbers::hallway :
					newRoom = m_hallwayExits[newRoom - 1];
					return newRoom;
				case (int)roomNumbers::kitchen :
					newRoom = m_kitchenExits[newRoom - 1];
					return newRoom;
				case (int)roomNumbers::diningRoom :
					newRoom = m_diningRoomExits[newRoom - 1];
					return newRoom;
			}
		}	
		int getExitRoom() {
			return (int)roomNumbers::hallway;
		}
		bool getState() {
			return locked;
		}
		void setState() {
			locked = false;
		}
};

class inventory {
	private:
		//const static int m_numItems = 1;
		enum class itemNumbers { key, charm, total };
		const std::string itemNames[(int)itemNumbers::total] = {"KEY", "SILVER CHARM" };
		int itemLocation[(int)itemNumbers::total];
		int itemCounts[(int)itemNumbers::total];
		bool itemFound[(int)itemNumbers::total]; // Indicates whether items have been found or not
	public:
		inventory(house &house) {
			srand(time(NULL));
			int numRooms = house.getNumRooms();
			for(int i = 0; i < (int)itemNumbers::total; i++) {
				itemCounts[i] = 0;
				itemLocation[i] = rand() % (numRooms);
				itemFound[i] = false;
			}
		}

		int getTotalItems() {
			return (int)itemNumbers::total;
		}

		std::string getItemName(int i) {
			return itemNames[i];
		}

		int getItemLoc(int i) {
			return itemLocation[i];
		}

		bool checkItemFound(int i) {
		       return itemFound[i];
		}	       

		bool checkCharm() {
			return itemFound[(int)itemNumbers::charm];
		}

		bool checkKey() {
			return itemFound[(int)itemNumbers::key];
		}

		void setItemFound(int i) {
			itemFound[i] = true;
		}

		void incrementItem(int i) {
			itemCounts[i]++;
		}
};

class player {
	private: 
		int currentRoom;
		int fear;
		int turn;
	public:
		player() : currentRoom(0), fear(0), turn(0) {} // Set start room to bedroom
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

		int getTurn() {
			return turn;
		}

		void incrementTurn() {
			++turn;
		}

		int displayMoveChoice(house &house) {
			std::string menuMessage = 
				"Choose an option:\n1. Move to another room\n2.Search " + house.getCurrentRoomName(currentRoom) + "\n";
			if(currentRoom == house.getExitRoom()) {
				menuMessage += "3. Open door to outside\n";
			}
			menuMessage += ">";
			while(true) {
				int selection = getIntInput(menuMessage);
				if(selection > 0 && selection <= 3) {
					return selection;
				}
				else {
					std::cout << "Invalid Input" << std::endl;
				}
			}
		}
		
		void move(house &house, inventory &inventory) {
			switch(displayMoveChoice(house)) {
				case 1:
					updateRoom(house);
					break;
				case 2:
					searchRoom(inventory,house);
					std::cout << "Finished searching " << house.getCurrentRoomName(currentRoom) << std::endl;
					break;		
				case 3:
					if(currentRoom == house.getExitRoom()) {
						leaveHouse( inventory, house );
						break;
					}
					else {
						std::cout << "Invalid input" << std::endl;
						break;
					}
				default:
					std::cout << "Invalid input" << std::endl;
			}
		}

		void setFear(int f) {
			fear = f;
		}

		int getFear() {
			return fear;
		}

		int getCurrentRoom() {
			return currentRoom;
		}
		void setCurrentRoom(int newRoom) {
			currentRoom = newRoom;
		}
		void updateRoom(house &house) {
			std::cout << "Move where?" << std::endl;
			house.printAvailableRooms(currentRoom);
			while(true) {
				int newRoom = getIntInput(">");
				if(newRoom > 0 && newRoom <= house.getNumRoomExits(currentRoom)) {
					newRoom = house.getActualMove(currentRoom, newRoom);
					setCurrentRoom(newRoom);
					return;
				}
				else {
					std::cout << "Bad Room Selection" << std::endl;
				}
			}
		}

		void searchRoom(inventory &inventory, house &house) {
			for(int i = 0; i < inventory.getTotalItems(); i++) {
				if(currentRoom == inventory.getItemLoc(i) && !inventory.checkItemFound(i)) {
					inventory.incrementItem(i);
					inventory.setItemFound(i);
					std::cout << "You found a " << inventory.getItemName(i) << "!" << std::endl;
				}
			}			
		}

		void leaveHouse(inventory &inventory, house &house) {
			if(inventory.checkKey()) {
				house.setState();
				std::cout << "You escaped from the house!" << std::endl;
			}
			else {
				std::cout << "You need the key to escape from the house!" << std::endl;
			}
		}
};

class ghost {
	private:
		int currentRoom;
	public:
		ghost(house &house) {
			int numRooms = house.getNumRooms();
			currentRoom = rand() % numRooms;
		};

		void move(house &house) {
			int numRooms = house.getNumRooms();
			currentRoom = rand() % numRooms;
		}	

		int getCurrentRoom() {
			return currentRoom;
		}
};

// FUNCTION DEFINITIONS ////////////////////////////////////////////////////////////////////////////////////////////////////
int menuChoice();
int getIntInput(std::string message); 
std::string getStringInput();
void printInfo(house &house, player &player);
void play();

int main() {

	bool exit = false;

	do {
		switch(menuChoice()) {
			case 1:
				std::cout << "STARTING GAME\n" << std::endl;
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

void printInfo(house &house, player &player) {
	
	std::cout << "TURN: " << player.getTurn() << " | LOCATION: " << house.getCurrentRoomName(player.getCurrentRoom()) << " | FEAR: " << player.getFear() << std::endl;

}

void play() {
	const int BRAVERY = 6;
	house house;
	player player;
	inventory inventory(house);
	ghost ghost(house);
	
	do {
		player.incrementTurn();
		ghost.move(house);
		if(ghost.getCurrentRoom() == player.getCurrentRoom()) {
			player.setFear(player.getFear() + 1 + (player.getTurn() / 2));
		}
		if(inventory.checkCharm()) {
			player.setFear(player.getFear() / 2);
		}
		printInfo(house,player);
		player.move(house,inventory);
	} while(house.getState() && player.getFear() <= BRAVERY); 

	if(player.getFear() > BRAVERY) {
		std::cout << "You Died of Fright" << std::endl;
	}
}

