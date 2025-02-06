#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "Food.h"
#include "WorldObject.h"

class Player {
private:
	// -------------------- SAVE-READ DATA ---------------------------- // 
	
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

	//manipulation over player needs
	void eat(int hunger, int thirst, int energy);

public:
	//constructors
	Player();
	Player(std::string nickname, enums::fieldOfStudy studies, int money, int needs[8], int d_till_fee, 
		enums::accomodation accom_type, std::vector <Food> owned_food, std::string TEXadress, sf::Vector2f coordinates);
	//overloaded assignment operator
	void operator=(const Player& another);
	//method to give pointer to player's avatar used in accessing outside the SaveData class
	sf::Sprite* getAvatarPtr();
	//method to show the players stats
	std::array<int, 8> getNeeds() const;

	//method to move the player's sprite
	void move(sf::Vector2f offset);
	//method to see function of movable object
	//---show options of usage when Player is close enough
	//---usage is specified by the object type
	void use(enums::movableObject object);

	//method evaluating the life cycle of the player - eating, sleeping etc.
	void evaluateEvery2min();

	// ---------------------- GAMEPLAY USE ONLY ------------------------------- //
	float vel = 0;

	// method to give pointer to the players velocity
	float* getVelocityPtr();

	
};

