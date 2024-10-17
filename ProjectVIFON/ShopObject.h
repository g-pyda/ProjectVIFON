#pragma once
#include <iostream>

class Player;

class ShopObject {
protected:
	std::string str_name;
	int price;
	int MAXamount;
	int LEFTamount;
public:
	//default constructor or dependand on the config data
	ShopObject();
	ShopObject(std::string name, int LEFTamount);
	int getPrice() const;
	int getMAXamount() const;
	int getLEFTamount() const;
	void sell(Player* player);
	void buy(Player* player);
};

