#include "Inventory.h"

Inventory::Inventory(string name):m_name(name)
{
}

Inventory::~Inventory()
{
}

void Inventory::SetParent(Inventory * _parent)
{
}

Inventory * Inventory::GetParent()
{
	return nullptr;
}

string Inventory::GetName()
{
	return m_name;
}

int Inventory::GetLevel()
{
	return 0;
}

Item::Item(string name):Inventory(name)
{
}

Item::~Item()
{
}

void Item::View()
{
}

Bag::Bag(string name):Inventory(name)
{
}

Bag::~Bag()
{
	for (vector<Inventory*>::iterator  i = m_InventoryList.begin(); i != m_InventoryList.end(); i++)
	{
		delete (*i);
	}
	vector<Inventory*>().swap(m_InventoryList);
}

void Bag::View()
{
	cout << GetName() + " Bag" << endl;
	cout << "----------------------------------" << endl;
	vector<Inventory*>::iterator begin = m_InventoryList.begin();
	vector<Inventory*>::iterator end = m_InventoryList.end();
	int count = 1;
	while (begin != end)
	{
		cout << to_string(count) + ". ";
		(*begin)->View();
		begin++;
		count++;
	}

	cout << "----------------------------------" << endl;

}

void Bag::AddInventory(Inventory * inventory)
{
	inventory->SetParent(this);	
	m_InventoryList.push_back(inventory);
}

Inventory * Bag::FindInventory(string name)
{
	for (vector<Inventory*>::iterator i = m_InventoryList.begin(); i != m_InventoryList.end(); i++)
	{
		if ((*i)->GetName() == name)
		{
			return (*i);
		}
	}

	return NULL;
}

Inventory * Bag::FindInventory(int index)
{
	return  FindInventory(m_InventoryList[index]->GetName());
}

void Bag::RemoveInventory(Inventory * inventory)
{
	vector<Inventory*>::iterator remove = find(m_InventoryList.begin(), m_InventoryList.end(), inventory);

	if (remove != m_InventoryList.end())
	{
		m_InventoryList.erase(remove);
	}
}
