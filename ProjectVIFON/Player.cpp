#include "Player.h"

Player::Player() {
	std::cout << "New player created" << std::endl;
}

Player::Player(std::string nickname, enums::fieldOfStudy studies, int money, int needs[8],
	int d_till_fee, enums::accomodation accom_type, std::vector <Food> owned_food) {
	// overal info
	this->nickname = nickname;
	this->field = studies;
	this->money = money;

	// needs status
	this->NDphysicalHlth = needs[0];
	this->NDmentalHlth = needs[1];
	this->NDhunger = needs[2];
	this->NDthirst = needs[3];
	this->NDtoilet = needs[4];
	this->NDhygene = needs[5];
	this->NDenergy = needs[6];
	this->NDentertainment = needs[7];

	//accommodation status
	this->daysTillFee = d_till_fee;
	this->accommodationType = accom_type;

	//owned objects
	this->ownedFood = owned_food;
}

void Player::operator=(const Player& another) {
	// overal info
	this->nickname = another.nickname;
	this->field = another.field;
	this->money = another.money;

	// needs status
	this->NDphysicalHlth = another.NDphysicalHlth;
	this->NDmentalHlth = another.NDmentalHlth;
	this->NDhunger = another.NDhunger;
	this->NDthirst = another.NDthirst;
	this->NDtoilet = another.NDtoilet;
	this->NDhygene = another.NDhygene;
	this->NDenergy = another.NDenergy;
	this->NDentertainment = another.NDentertainment;

	//accommodation status
	this->daysTillFee = another.daysTillFee;
	this->accommodationType = another.accommodationType;

	//owned objects
	this->ownedFood = another.ownedFood;
}