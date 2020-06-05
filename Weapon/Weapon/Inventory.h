#pragma once
#include "Macro.h"

class Inventory
{
public:
	Inventory(string name);
	virtual ~Inventory();
	virtual void View() = 0;
	virtual void AddInventory(Inventory* inventory) = 0;
	virtual Inventory* FindInventory(string name) = 0;
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
	Inventory* FindInventory(string name) { return NULL; }
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
	void RemoveInventory(Inventory* inventory) override;
private:
	vector<Inventory*> m_InventoryList;
};


