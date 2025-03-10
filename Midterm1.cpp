#include "Midterm1.h"

using namespace std;

int rollDice()
{
	return 1 + (rand() % 6);
}

bool isValidNumber(const std::string& str) {
	for (char c : str) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

enum GameState {
	BIDDING_PHASE,
	CHALLENGE_PHASE,
	ROUND_END,
	GAME_OVER
};

enum Decision {
	CHALLENGE,
	ACCEPT,
	BID
};

int main()
{
	srand(time(0));

	Player Plr;
	Plr.name = "Your";
	Player Computer1;
	Computer1.name = "Computer 1";
	Player Computer2;
	Computer2.name = "Computer 2";
	cout << "Welcome to Liar's Dice. In this game, the objective is to be the last player with dice remaining." << endl;
	cout << "There are three players." << endl;
	cout << "Please enter your name." << endl;
	cin >> Plr.name;
	bool game = true;
	while (game)
	{
		bool challenged = false;
		bool betting = true;
		bool accepted = false;
		int finalFace = 0;
		int finalCount = 0;
		Player* challenger = &Plr;
		Player* better = &Plr;
		Player* acceptor = &Plr;
		while (betting)
		{
			Plr.rollDices();
			cout << "You roll." << endl;
			Computer1.rollDices();
			cout << "Computer 1 rolls." << endl;
			Computer2.rollDices();
			cout << "Computer 2 rolls." << endl;

			cout << "All players have rolled." << endl;
			cout << "Your dice are: ";
			Plr.showRoll();

			int face = 0;
			int count = 0;

			while (face == 0)
			{
				string userFace = "";
				cout << "It is your turn to bid. What face would you like to bid on? (1, 2, 3, 4, 5, 6)" << endl;
				cin >> userFace;

				if (isValidNumber(userFace) == false)
				{
					cout << "Invalid number." << endl;
					continue;
				}

				face = stoi(userFace);

				if (face > 6 || face < 1)
				{
					cout << "Invalid number." << endl;
					face = 0;
					continue;
				}
			}

			while (count == 0)
			{
				string userCount = "";
				cout << "How many of this face do you bet is on the table between all players? " << endl;
				cin >> userCount;

				if (isValidNumber(userCount) == false)
				{
					cout << "Invalid number." << endl;
					continue;
				}

				count = stoi(userCount);
			}

			cout << "You bet there are " << count << " " << face << "s." << endl;

			bool aiBid = false;
			Player* currentPlr = &Plr;
			Player* prevPlr = &Plr;

			for (int i = 0; i < 2; i++)
			{
				if (i == 2)
				{
					currentPlr = &Computer2;
				}
				else
				{
					currentPlr = &Computer1;
				}

				if (aiBid)
				{
					continue;
				}

				int decision = 1 + (rand() % 4);

				enum Decision plrDecision;

				int aicount = currentPlr->countFace(face);

				int ainumber = rand() % 1001;

				if (aicount == count)
				{
					if (ainumber < 250)
					{
						plrDecision = BID;
					}
					else if (ainumber < 500)
					{
						plrDecision = CHALLENGE;
					}
					else
					{
						plrDecision = ACCEPT;
					}
				}
				else
				{
					if (ainumber < 250)
					{
						plrDecision = ACCEPT;
					}
					else if (ainumber < 500)
					{
						plrDecision = BID;
					}
					else
					{
						plrDecision = CHALLENGE;
					}
				}
				switch (plrDecision)
				{
				case ACCEPT:
					cout << "Computer " << i << " has accepted the bid. All players will reveal their dice." << endl;
					accepted = true;
					betting = false;
					finalFace = face;
					finalCount = count;
					acceptor = currentPlr;
					break;
				case CHALLENGE:
					cout << "Computer " << i << " has challenged the bid. All players will reveal their dice." << endl;
					challenged = true;
					betting = false;
					finalFace = face;
					finalCount = count;
					challenger = currentPlr;
					break;
				case BID:
					cout << "Computer " << i << " has decided to up the bid." << endl;
					aiBid = true;
					better = currentPlr;
					break;
				}
				if (!aiBid)
				{
					break;
				}
				prevPlr = currentPlr;
			}
		}

		int total = 0;
		int plrCount = Plr.countFace(finalFace);
		cout << "You reveal your dice. You have " << plrCount << " " << finalFace << "s." << endl;
		total += plrCount;
		int cp1Count = Computer1.countFace(finalFace);
		cout << "Computer 1 reveals its dice. They have " << cp1Count << " " << finalFace << "s. " << endl;
		total += cp1Count;
		int cp2Count = Computer2.countFace(finalFace);
		cout << "Computer 2 reveals its dice. They have " << cp2Count << " " << finalFace << "s. " << endl;
		total += cp2Count;

		cout << "There are " << total << " " << finalFace << "s on the table." << endl;

		if (total == finalCount)
		{
			cout << better->name << "'s bet is correct." << endl;
			if (accepted)
			{
				cout << better->name << " loses 1 dice." << endl;
				better->diceCount -= 1;
			}
			else if (challenged)
			{
				cout << challenger->name << " loses 1 dice." << endl;
				challenger->diceCount -= 1;
			}
		}
		else
		{
			cout << better->name << "'s bet is incorrect." << endl;
			if (accepted)
			{
				cout << acceptor->name << " loses 1 dice." << endl;
				acceptor->diceCount -= 1;
			}
			else if (challenged)
			{
				cout << better->name << " loses 1 dice." << endl;
				better->diceCount -= 1;
			}
		}
	}

	return 0;
}
