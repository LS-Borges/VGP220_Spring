#pragma once

#include <iostream>
#include "Item.h"

class Inventory
{
public:
	Inventory() : mMaxSlots(5), mSlotsOccupied(0)
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).

		mInventory = new Item[5];

		std::cout << "Default constructor called!" << std::endl;
	}
	Inventory(uint32_t capacity) : mMaxSlots(capacity), mSlotsOccupied(0)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).

		mInventory = new Item[capacity];

		std::cout << "Non-default constructor called!" << std::endl;
	}
	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.

		CopyElements(other);

		std::cout << "Copy constructor called!" << std::endl;
	}
	Inventory(Inventory&& other)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.

		MoveElements(std::move(other));

		std::cout << "Move constructor called!" << std::endl;
	}
	~Inventory()
	{
		//TODO: Implement a destructor for this class.

		delete[] mInventory;
		mInventory = nullptr;

		std::cout << "Destructor called!" << std::endl;
	}

	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& rhs)
	{
		CopyElements(rhs);

		std::cout << "Copy Assignment Operator Constructor called!" << std::endl;
		
		return *this;
	}

	//TODO: Implement a move assignment operator
	Inventory& operator=(Inventory&& rhs)
	{
		MoveElements(std::move(rhs));

		std::cout << "Move Assignment Operator constructor called!" << std::endl;

		return *this;
	}


	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;

		//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
		//should expand adding 5 more empty slots for the user.

		if (newItem.name == "Expansion" && newItem.type == Charm)
		{
			Expansion(5);
		}

		int indexName = SearchItemByName(newItem.name);
		int indexLessThan50 = SearchItemByNameLessThan50(newItem.name);

		if (isFullForItem(mInventory) == true)
		{
			std::cout << "Inventory full. " << newItem.quantity << " " << newItem.name << " will be descarted." << std::endl;
		}

		else
		{
			if (newItem.name == "Expansion" && newItem.type == Charm)
			{
				
			}

			else if (indexName == -1 && newItem.quantity <= 50)
			{
				mInventory[mSlotsOccupied] = newItem;
				++mSlotsOccupied;

				std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
			}

			else if (indexName == -1 && newItem.quantity > 50)
			{
				int temp = newItem.quantity;
				newItem.quantity = 50;

				mInventory[mSlotsOccupied] = newItem;
				++mSlotsOccupied;

				std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";

				if (isFullForItem(mInventory) == true)
				{
					std::cout << "Inventory full. " << temp - newItem.quantity << " " << newItem.name << " will be descarted." << std::endl;
				}

				else
				{
					newItem.quantity = temp - newItem.quantity;
					mInventory[mSlotsOccupied] = newItem;
					++mSlotsOccupied;

					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
				}
			}

			else if (indexName != -1)
			{
				if (mInventory[indexLessThan50].quantity + newItem.quantity > 50)
				{
					int temp = 50 - mInventory[indexLessThan50].quantity;
					mInventory[indexLessThan50].quantity = 50;

					std::cout << "Adding " << temp << " " << newItem.name << " in inventory." << "\n";

					if (isFullForItem(mInventory) == true)
					{
						std::cout << "Inventory full. " << newItem.quantity - temp << " " << newItem.name << " will be descarted." << std::endl;
					}

					else
					{
						newItem.quantity = newItem.quantity - temp;

						mInventory[mSlotsOccupied] = newItem;
						++mSlotsOccupied;

						std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
					}
				}

				else
				{
					mInventory[indexLessThan50].quantity = mInventory[indexLessThan50].quantity + newItem.quantity;

					std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";
				}
			}
		}
	}

	void Expansion(int additionalCapacity)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots + additionalCapacity];
		mMaxSlots += additionalCapacity;

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}

		delete[] temp;
		temp = nullptr;

		std::cout << "Inventory expanded!" << std::endl;
	}

	void RemoveExpansion(int additionalCapacity)
	{
		Item* temp = mInventory;
		mInventory = new Item[mMaxSlots - additionalCapacity];
		mMaxSlots -= additionalCapacity;

		if (mSlotsOccupied > mMaxSlots)
		{
			mSlotsOccupied = mMaxSlots;
		}

		for (int i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = temp[i];
		}

		delete[] temp;
		temp = nullptr;

		std::cout << "Inventory reduced!" << std::endl;
	}

	void RemoveItem(std::string itemName, int quantity)
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.

		int index = SearchItemByName(itemName);

		if (itemName == "Expansion" && mInventory[index].type == Charm)
		{
			RemoveExpansion(5);
		}

		if (index == -1)
		{
			std::cout << "Item does not exist!" << std::endl;
		}

		else
		{
			if (mInventory[index].quantity - quantity > 0)
			{
				mInventory[index].quantity = mInventory[index].quantity - quantity;
			}

			else
			{
				for (int i = index; i < mSlotsOccupied; ++i)
				{
					int next = i++;

					if (next = mSlotsOccupied)
					{
						mInventory[i].name = "";
						mInventory[i].quantity = 0;
						//mInventory[i].type = "";  I don't know how to make it "0"

						--mSlotsOccupied;
					}

					else
					{
						mInventory[i] = mInventory[next];
					}
				}
			}

			std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";
		}

	}

	Item* UseItem(std::string itemName)
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Potion and Utility.

		int index = SearchItemByName(itemName);

		if (index != -1)
		{
			if (mInventory[index].type == Potion || mInventory[index].type == Utility)
			{
				mInventory[index].quantity = mInventory[index].quantity - 1;

				std::cout << "Using " << itemName << "\n";
			}

			else
			{
				return nullptr;
			}
			
		}

		else
		{
			return nullptr;
		}
	}
private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;

	void CopyElements(const Inventory& other)
	{
		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = new Item[mMaxSlots];

		for (auto i = 0; i < mSlotsOccupied; ++i)
		{
			mInventory[i] = other.mInventory[i];
		}
	}

	void MoveElements(Inventory&& other)
	{
		mSlotsOccupied = other.mSlotsOccupied;
		other.mSlotsOccupied = 0;

		mMaxSlots - other.mMaxSlots;
		other.mMaxSlots = 0;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = other.mInventory;
		other.mInventory = nullptr;
	}

	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};