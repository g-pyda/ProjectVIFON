#include "Player.h"

Player::Player() {
	std::cout << "New player created" << std::endl;
}

Player::Player(std::string nickname, enums::fieldOfStudy studies, int money, int needs[8], int d_till_fee, 
	enums::accomodation accom_type, std::vector <Food> owned_food, std::string TEXadress, sf::Vector2f coordinates) {
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

	//avatar
	if (!this->texture.loadFromFile(TEXadress))
		std::cout << "Avatar didn't load" << std::endl;
	this->avatar.setTexture(texture);
	this->avatar.setPosition(coordinates.x, coordinates.y);
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

	// avatar to display
	this->texture = another.texture;
	this->avatar.setPosition(another.avatar.getPosition());
	this->avatar.setTexture(texture);
}

sf::Sprite* Player::getAvatarPtr() {
	return &(this->avatar);
}

void Player::move(sf::Vector2f offset) {
	this->avatar.move(offset);
}

void Player::use(enums::movableObject object) {
	switch (object) {
	case enums::movableObject::Bed:
		std::cout << "Bed approached - sleep, nap, lay down" << std::endl;
		break;
	case enums::movableObject::Desk:
		std::cout << "Desk approached - sit, learn, play on the computer(optional)" << std::endl;
		break;
	case enums::movableObject::Closet:
		std::cout << "Closet approached - change clothes, take dirty clothes" << std::endl;
		break;
	case enums::movableObject::Toilet:
		std::cout << "Toilet approached - pee, poop, scroll through the internet" << std::endl;
		break;
	case enums::movableObject::Sink:
		std::cout << "Sink approached - wash hands, wash face, brush the teeth, flex in front of the mirror" << std::endl;
		break;
	case enums::movableObject::Bath:
		std::cout << "Bath approached - take a long bath, take a fast shower" << std::endl;
		break;
	case enums::movableObject::Fridge:
		std::cout << "Fridge approached - open, eat something random" << std::endl;
		break;
	case enums::movableObject::Stove:
		std::cout << "Stove approached - cook, cook something random, bake, make a hot drink" << std::endl;
		break;
	case enums::movableObject::Counter:
		std::cout << "Counter approached - open, eat something random" << std::endl;
		break;
	case enums::movableObject::Bookshelve:
		std::cout << "Bookshelve approached - read, read something random" << std::endl;
		break;
	case enums::movableObject::Fern:
		std::cout << "Fern approached - look at" << std::endl;
		break;
	case enums::movableObject::Sunflower:
		std::cout << "Sunflower approached - look at" << std::endl;
		break;
	case enums::movableObject::none:
	default:
		break;
	}
}

void Player::eat(int hunger, int thirst, int energy) {
	this->NDhunger += hunger;
	this->NDthirst += thirst;
	this->NDenergy += energy;
}

void Player::evaluateEvery2min() {
	this->NDhunger -= 5;
	if (this->NDhunger < 30)
		this->NDphysicalHlth -= 1;
	else if (this->NDhunger < 10)
		this->NDphysicalHlth -= 3;

	this->NDthirst -= 5;
	if (this->NDthirst < 30)
		this->NDphysicalHlth -= 2;
	else if (this->NDthirst < 10)
		this->NDphysicalHlth -= 4;

	this->NDtoilet -= 5;
	if (this->NDhunger <= 0) {
		this->NDtoilet = 100;
		this->NDhygene = 0;
	}

	this->NDhygene -= 5;
	if (this->NDhygene < 30)
		this->NDphysicalHlth -= 1;
	else if (this->NDhygene < 10)
		this->NDphysicalHlth -= 3;

	this->NDenergy -= 5;
	if (this->NDenergy < 15)
		this->NDphysicalHlth -= 1;
	else if (this->NDhygene <= 0)
		this->NDphysicalHlth -= 15;

	this->NDentertainment -= 5;
	if (this->NDentertainment < 30)
		this->NDmentalHlth -= 1;
	else if (this->NDentertainment < 10)
		this->NDmentalHlth -= 3;
}