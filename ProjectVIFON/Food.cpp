#include "Food.h"
#include "ShopObject.h"

int Food::getHungerPTS() const {
	return hungerPTS;
}
int Food::getThirstPTS() const {
	return thirstPTS;
}
int Food::getDaysTillExp() const {
	return daysTillExp;
}

Food::Food(std::string str_name, enums::food name, int LEFTamount, int daysTillExp) {
	this->name = name;
	this->str_name = str_name;
	this->price = const_config::foodData[name][0];
	this->MAXamount = const_config::foodData[name][3];
	this->LEFTamount = LEFTamount;
	this->hungerPTS = const_config::foodData[name][1];
	this->thirstPTS = const_config::foodData[name][2];
	this->daysTillExp = daysTillExp;
}