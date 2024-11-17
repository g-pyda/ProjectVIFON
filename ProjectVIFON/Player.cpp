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