#include "ShopObject.h"

#include "Player.h"`

ShopObject::ShopObject() {
	this->str_name = "";
	this->LEFTamount = 0;
	this->MAXamount = 0;
	this->price = 0;
}

ShopObject::ShopObject(std::string name, int LEFTamount) {
	this->str_name = name;
	this->LEFTamount = LEFTamount;
	this->MAXamount = 0;
	this->price = 0;
}

int ShopObject::getPrice() const {
	return price;
}

int ShopObject::getMAXamount() const {
	return MAXamount;
}

int ShopObject::getLEFTamount() const {
	return LEFTamount;
}

void ShopObject::sell(Player* player) {
	
}

void ShopObject::buy(Player* player) {

}