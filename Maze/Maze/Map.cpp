#include "Map.h"

Map::Map()
{
	ifstream load;
	int num;
	load.open("Stage0.txt");

	while (!load.eof())
	{
		load >> num;
		m_Map.push_back(num);
	}

	load.close();
}

void Map::Show()
{
	for (vector<int>::size_type i = 0; i < m_Map.size(); i++)
	{
		if (i % WIDTH == 0 && i != 0)
		{
			cout << endl;
		}

		if (m_Map[i] == EMPTY)
		{
			cout << "  ";
		}
		else if (m_Map[i] == WALL)
		{
			cout << "¡á";
		}
		else if (m_Map[i] == PLAYER)
		{
			cout << "¢¼";
		}
		else if (m_Map[i] == GATE)
		{
			cout << "¢È";
		}

	}
}