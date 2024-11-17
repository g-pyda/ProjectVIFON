#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Food.h"
#include "WorldObject.h"

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

	// avatar to display
	sf::Sprite avatar;
	sf::Texture texture;

	// accommodation status
	int daysTillFee;
	int accommodationType;

	// owned objects
	std::vector <Food> ownedFood = {};
public:
	//constructors
	Player();
	Player(std::string nickname, enums::fieldOfStudy studies, int money, int needs[8], int d_till_fee, 
		enums::accomodation accom_type, std::vector <Food> owned_food, std::string TEXadress, sf::Vector2f coordinates);
	//overloaded assignment operator
	void operator=(const Player& another);
	//method to give pointer to player's avatar used in accessing outside the SaveData class
	sf::Sprite* getAvatarPtr();

	//method to move the player's sprite
	void move(sf::Vector2f offset);
	//method to see function of movable object
	//---show options of usage when Player is close enough
	//---usage is specified by the object type
	void use(enums::movableObject object);
	
};

