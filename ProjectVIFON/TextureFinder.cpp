#include "TextureFinder.h"

int defNrOfTiles(movableObject objToCheck) {
	switch (objToCheck) {
	case Bed:
	case Closet:
	case Bath:
	case Bookshelve:
		return 2;
	case Desk:
	case Toilet:
	case Sink:
	case Fridge:
	case Stove:
	case Counter:
	case Fern:
	case Sunflower:
		return 1;
	default:
		return 0;
	}
}

