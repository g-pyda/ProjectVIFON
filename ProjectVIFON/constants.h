#pragma once
#include <vector>
#include <string>

static constexpr unsigned int MAXwidth = 300;
static constexpr unsigned int MAXheight = 300;

static constexpr unsigned int windowWidth = 1024;
static constexpr unsigned int windowHeight = 640;
static constexpr unsigned int defTileSize = 32;

namespace enums {
	static enum fieldOfStudy {
		ComputerScience, Microbiology, Geology, Law, Sociology, Medicine, Architecture
	};
	
	static enum food {
		chicken, beef, oil, seasonings, tofu, cheese, ham, butter, bread, bun,
		tortilla, milk, cream, yoghurt, lettuce, tomato, cucumber, pepper, carrot, onion,
		garlic, broccoli, apple, banana, peach, watermelon, strawberry, blueberry, potato, rice,
		groats, nuddles, vifon, cookies, flour, eggs, sugar, chips, frozen_fries, frozen_pizza,
		popcorn, corn_flakes, water, soda_can, soda_bottle, beer_can, beer_6pack, vodka, whiskey, juice_can,
		juice_bottle, tea, coffee, chocolate_milk
	};

	static std::vector <std::string> str_food {
		"chicken", "beef", "oil", "seasonings", "tofu", "cheese", "ham", "butter", "bread", "bun",
		"tortilla", "milk", "cream", "yoghurt", "lettuce", "tomato", "cucumber", "pepper", "carrot", "onion",
		"garlic", "broccoli", "apple", "banana", "peach", "watermelon", "strawberry", "blueberry", "potato", "rice",
		"groats", "nuddles", "vifon", "cookies", "flour", "eggs", "sugar", "chips", "frozen_fries", "frozen_pizza",
		"popcorn", "corn_flakes", "water", "soda_can", "soda_bottle", "beer_can", "beer_6pack", "vodka", "whiskey", "juice_can",
		"juice_bottle", "tea", "coffee", "chocolate_milk"
	};

	static enum hygeneUtil {
		toothpaste, toothbrush, listerine, shower_gel, shampoo, conditioner, kitchen_clean, bathroom_clean, dish_soap, towel,
		soap, toilet_paper
	};

	static enum hobby {
		guitar, computer, laptop, tv, book, headphones
	};

	static enum accomodation {
		dorm1, dorm2, flat
	};

	static enum movableObject {
		Bed, Desk, Closet, Toilet, Sink, Bath, Fridge, Stove, Counter, Bookshelve, Fern, Sunflower
	};
	
	static enum map {
		start, dorm, outdoor, hipermarket, uni
	};
};

namespace const_config {

	// array of food data configuration
	// [0] - price, [1] - hunger points, [2] - thirst points, [3] - MAXamount
	static const float foodData[][4] = {
		{20, 12, 0, 6}, {30, 12, 0, 6}, {5, 1, 0, 30}, {10, 0, 0, 20}, {10, 5, 0, 5}, {8, 6, 0, 10}, {7, 7, 0, 10}, {4, 1, 0, 30}, {2, 10, 0, 10}, {0.8f, 7, 0, 1},
		{5, 6, 0, 4}, {3, 5, 10, 4}, {4, 5, 0, 2}, {3, 5, 5, 2}, {5, 1, 0, 6}, {0.4f, 2, 0, 2}, {0.4f, 1, 0, 2}, {0.5f, 2, 0, 3}, {0.2f, 2, 0, 1}, {0.2f, 2, 0, 2},
		{1, 0.5f, 0, 10}, {5, 2, 0, 3}, {0.2f, 2, 0, 1}, {0.4f, 4, 0, 1}, {0.3f, 2, 0, 1}, {20, 2, 3, 8}, {25, 2, 0, 10}, {15, 2, 0, 5}, {3, 10, 0, 10}, {4, 9, 0, 10},
		{5, 10, 0, 10}, {5, 8, 0, 10}, {1, 20, 0, 1}, {4, 3, 0, 2}, {3, 6, 0, 10}, {10, 6, 0, 12}, {3, 1, 0, 250}, {6, 2, 0, 2}, {8, 8, 0, 3}, {15, 6, 0, 4},
		{2, 2, 0, 2}, {8, 7, 0, 10}, {1, 0, 10, 4}, {3, 0, 5, 1}, {7, 0, 5, 3}, {3, 0, 8, 1}, {15, 0, 8, 6}, {40, 0, 3, 25}, {60, 0, 3, 20}, {2, 0, 8, 1},
		{6, 0, 8, 4}, {10, 0, 7, 30}, {30, 0, 8, 30}, {5, 0, 9, 1}
	};

	//array of cleaning + hygene data configuration
	// [0] - price, [1] - MAXamount
	static const int cleaningData[][2]{
		{8, 30}, {2, 30}, {15, 40}, {10, 30}, {12, 25}, {15, 20}, {50, 10}, {50, 10}, {7, 50}, {15, 300}, {6, 30}, {5, 120}
	};
}

static bool isPaused = false;
static enums::map whichMap = enums::map::dorm;
