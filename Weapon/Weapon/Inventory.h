#pragma once
#include "Macro.h"

class Inventory
{
public:
	Inventory(string name);
	virtual ~Inventory();
	virtual void View() = 0;
	virtual void AddInventory(Inventory* inventory) = 0;
	virtual void RemoveInventory(Inventory* inventory) = 0;
	void SetParent(Inventory* _parent);
	Inventory* GetParent();
	string GetName();
	int GetLevel();
private:
	Inventory* parent;
	const string m_name;
};

class Item : public Inventory
{
public:
	Item(string name);
	~Item();
	virtual void View();
	void AddInventory(Inventory* inventory) {}
	void RemoveInventory(Inventory* inventory) {}
};

class Bag : public Inventory
{
public:
	Bag(string name);
	~Bag();
	void View() override;
	void AddInventory(Inventory* inventory) override;
	Inventory* FindInventory(string name);
	Inventory* FindInventory(int index);
	void RemoveInventory(Inventory* inventory) override;
	int GetSize() { return m_InventoryList.size(); }
private:
	vector<Inventory*> m_InventoryList;
};


