#include "Inventory.h"

Inventory::Inventory(string name)
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
	return string();
}

int Inventory::GetLevel()
{
	return 0;
}

int Inventory::GetSize()
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
	m_InventoryList.clear();
}

void Bag::View()
{
}

void Bag::AddInventory(Inventory * inventory)
{
}

void Bag::RemoveInventory(Inventory * inventory)
{
}
