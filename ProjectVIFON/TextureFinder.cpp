#include "TextureFinder.h"

int defNrOfTiles(enums::movableObject objToCheck) {
	switch (objToCheck) {
	case enums::Bed:
	case enums::Closet:
	case enums::Bath:
	case enums::Bookshelve:
		return 2;
	case enums::Desk:
	case enums::Toilet:
	case enums::Sink:
	case enums::Fridge:
	case enums::Stove:
	case enums::Counter:
	case enums::Fern:
	case enums::Sunflower:
		return 1;
	default:
		return 0;
	}
}

