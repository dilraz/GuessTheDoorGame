#pragma once
#include "Door.h"
#include "Random.h"
#include "Player.h"

class GameManager
{
private:
	Door* doors; //dynamically allocated array of doors
	int totalDoors; //how many doors in the game?
	int numofPlayers;
	int openedDoors; //how many doors opened?
	string* playerNames;
	Player* player;

	bool isGameOver;
public:
	GameManager(int totalDoorsToGenerate)
	{
		totalDoors = totalDoorsToGenerate;
		openedDoors = 0;

		setDoors(totalDoors);
	}

	~GameManager()
	{
		delete[] doors;
	}

	void PrintAllDoors()
	{
		cout << "\n*** DOORS ***\n";
		for (int i = 0; i < totalDoors; i++)
		{
			doors[i].Print();
		}
	}
	void setDoors(int totalDoorsToGenerate)
	{
		doors = new Door[totalDoorsToGenerate]; //allocate memory 
		for (int i = 0; i < totalDoorsToGenerate; i++)
		{
			DOOR_TYPE dt = (DOOR_TYPE)GEP::RandomRange(0, 1);
			int randVal = 0;
			if (dt == 0)
				randVal = GEP::RandomRange(20, 60);
			else
				randVal = GEP::RandomRange(10, 30);

			doors[i].InitializeDoor(dt, randVal);
		}
	}

	int getOpenedDoorsCount() { return openedDoors; }
	int getTotalDoorsCount() { return totalDoors; }
	int getRemainingDoorsCount() { return totalDoors - openedDoors; }


	//doorNum ranges from 1 to MAX DOORS
	Door OpenDoor(int doorNum)
	{
		//doorNum-1 because the doorNum starts from 1

		doors[doorNum - 1].SetToOpen();
		return doors[doorNum - 1];

	}

	int Start()
	{
		
		
		
			string input;
			cout << "*** The Hidden Door Game | Multi Player  ***\n";
			cout << "\n1. Start New Game\n" << "2. Instructions\n" << "3. Quit\n" << endl;
			cin >> input;
			
				if (input == "1")
				{

					system("CLS");
					PrintAllDoors();

					//	cout << " The goal of this game is to open doors one by one to reveal what's behind it. \n";
					cout << "Enter the number of players: ";
					cin >> numofPlayers;
					player = new Player[numofPlayers];

					playerNames = new string[numofPlayers];
					for (int i = 0;i < numofPlayers;i++)
					{
						cout << "Enter your name Player " << i + 1 << ":" << endl;
						cin >> playerNames[i];
						player[i] = Player(playerNames[i]);

					}
					GameLoop();
				}
				else if (input == "2")
				{
					system("CLS");
					cout << "*** Instructions page ***\n" << "\n1. Enter amount of players" << "\n2. Enter your names" << "\n3. Enter your moves and Win!\n" << endl;
					
					PrintAllDoors();

					//	cout << " The goal of this game is to open doors one by one to reveal what's behind it. \n";
					cout << "Enter the number of players: ";
					cin >> numofPlayers;
					player = new Player[numofPlayers];

					playerNames = new string[numofPlayers];
					for (int i = 0;i < numofPlayers;i++)
					{
						cout << "Enter your name Player " << i + 1 << ":" << endl;
						cin >> playerNames[i];
						player[i] = Player(playerNames[i]);

					}
					GameLoop();

				}
				else if (input == "3")
				{
					return 0;
				}
				else if (input == "q")
				{
					return 0;
				}
	


			//create a player object using the player name. 
			//Note that the Player's only constructor requires the player name.

		

	}



	void GameLoop()
	{
		string restart;
		int doorNumToOpen = 0;
		cout << "\n***PLAYERS***" << endl;
		for (int i = 0;i < numofPlayers;i++)
		{

			cout << "Name: " << player[i].getPlayerName() << " | Health: " << player[i].getHealth() << " | Score: " << player[i].getScore() << endl;
		}
		while (!isGameOver)
		{
			for (int i = 0;i < numofPlayers;i++) {
				//print how many doors are left to be opened..
				cout << " Total doors: " << totalDoors << " | Remaining: " << getRemainingDoorsCount() << endl;

				cout << "Enter the door you'd like to open Player (" << i + 1 << ") (1 to " << totalDoors << ")  : " << endl;
				cin >> doorNumToOpen;


				//If doorNumToOpen has already been opened, then user has to re-enter a valid door
				if (doors[doorNumToOpen - 1].IsOpened())
				{
					cout << " That door has already been opened. Choose another door.\n";
					continue;
				}
				else 
				{
					openedDoors += 1;
				}

				//open door
				doors[doorNumToOpen - 1].SetToOpen();
				//show what was behind the door
				doors[doorNumToOpen - 1].RevealDoor();

				//update player's variables

				if (doors[doorNumToOpen - 1].GetDoorType() == SCORE)
					player[i].AddToScore(doors[doorNumToOpen - 1].GetDoorValue());
				else if (doors[doorNumToOpen - 1].GetDoorType() == ENEMY)
					player[i].ReduceHealth(doors[doorNumToOpen - 1].GetDoorValue());

				//print updated player variables
				//print the updated score & the updated health
				player[i].PrintPlayerProperties();

				//check for game end conditions

				if (checkWin()==true)
				{
					i = numofPlayers - 1;
				}
				//
			}



		}
		cout << "Do you want to restart the game YES(y) or NO(n) ?\n" << endl;
		cin >> restart;

		if (restart == "y" || restart == "Y")
		{
			openedDoors = 0;
			for (int i = 0;i < numofPlayers;i++)
			{
				player[i].Reset();
			}
			setDoors(totalDoors);
			PrintAllDoors();
			isGameOver = false;
			GameLoop();
			restart = "";
		}
		else if (restart == "n" || restart == "N")
		{
			isGameOver = true;
			restart = "";
		}

		if (isGameOver)
		{
			shutDown();
		}
	}


	bool checkWin()
	{
		if (openedDoors == totalDoors)
		{

			isGameOver = true;
			//check for WIN condition
			
			
			int max=0;
			//i.e. whether all doors have been opened 

			for (int x=0; x < numofPlayers; x++)   // <-- semicolon?
			{
					if (player[x].getScore() > max)
					{
						max = player[x].getScore();
					}
					
				}

			

			if (max != 0) {
				cout << "\n***WINNER***" << endl;
				for (int x = 0; x < numofPlayers; x++)    // <-- semicolon?
				{
					if (player[x].getScore() == max) {

						cout << "Game Over. "
							<< player[x].getPlayerName()
							<< " wins the game.\n"
							<< "Final Score: "
							<< player[x].getScore() << endl;
					}

				}
			}
			else {
				cout << "\n***GAME TIED***" << endl;
			}
			cout << "\n***SCOREBOARD***" << endl;
			for (int i = 0;i < numofPlayers;i++)
			{

				cout << "Name: " << player[i].getPlayerName() << " | Health: " << player[i].getHealth() << " | Score: " << player[i].getScore() << endl;
			}



			return true;
		}
	}
		
	


	void shutDown()
	{
		this->~GameManager();
	}



};
