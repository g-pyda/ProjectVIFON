#pragma once
#include "ShopObject.h"
#include "constants.h"

class Food : protected ShopObject {
private:
	enums::food name;
	int hungerPTS;
	int thirstPTS;
	int daysTillExp;
public:
	//default constructor dependand on the config data
	Food(std::string str_name, enums::food name, int LEFTamount, int daysTillExp);
	// eating or drinking
	void use();
	int getHungerPTS() const;
	int getThirstPTS() const;
	int getDaysTillExp() const;
	
};

