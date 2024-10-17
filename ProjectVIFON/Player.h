#pragma once

#include <iostream>
#include <vector>
#include "constants.h"
#include "Food.h"

class Player {
private:
	// overal info
	std::string nickname;
	enums::fieldOfStudy field;
	int money;

	// needs status
	int NDphysicalHlth;
	int NDmentalHlth;
	int NDhunger;
	int NDthirst;
	int NDtoilet;
	int NDhygene;
	int NDenergy;
	int NDentertainment;

	//accommodation status
	int daysTillFee;
	int accommodationType;

	//owned objects
	std::vector <Food> ownedFood = {};
public:
	Player();
	Player(std::string nickname, enums::fieldOfStudy studies, int money, int needs[8],
		int d_till_fee, enums::accomodation accom_type, std::vector <Food> owned_food);
	void operator=(const Player& another);
};

