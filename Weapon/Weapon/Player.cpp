#include "Player.h"

Player::Player(): bag(new Bag("Main"))
{
	bag->AddInventory(new Bag("Bow"));
	bag->AddInventory(new Bag("Gun"));
	bag->AddInventory(new Bag("Sword"));
	bag->AddInventory(new Bag("Hammer"));
	bag->AddInventory(new Bag("Dagger"));
	bag->AddInventory(new Bag("Wand"));
}

Player::~Player()
{
	delete bag;
}

void Player::DisplayAll()
{
	int input;

	while (1)
	{
		system("cls");
		cout << "¢¿ ¢À S H O P ¢À ¢¿" << endl;
		cout << "1.Dagger" << endl;
		cout << "2.Gun" << endl;
		cout << "3.Sword" << endl;
		cout << "4.Wand" << endl;
		cout << "5.Bow" << endl;
		cout << "6.Hammer" << endl;
		cout << "7. Á¾·á" << endl;
		cin >> input;

		if (input < 7)
		{
			switch (input)
			{
			case 1:
			OpenBag("Dagger");
				break;
			case 2:
			OpenBag("Gun");
				break;
			case 3:
			OpenBag("Sword");
				break;
			case 4:
			OpenBag("Wand");
				break;
			case 5:
			OpenBag("Bow");
				break;
			case 6:
			OpenBag("Hammer");
				break;
			default:
				break;
			}
		}
		else
		{
			return;
		}
	}
}

void Player::OpenBag(string name)
{
	system("cls");
	bag->FindInventory(name)->View();
	system("pause");
}
