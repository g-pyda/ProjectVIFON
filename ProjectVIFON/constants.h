#pragma once
static constexpr unsigned int MAXwidth = 300;
static constexpr unsigned int MAXheight = 300;

static constexpr unsigned int windowWidth = 32*32;
static constexpr unsigned int windowHeight = 20*32;
static constexpr unsigned int defTileSize = 32;

static enum movableObject {
	Bed, Desk, Closet, Toilet, Sink, Bath, Fridge, Stove, Counter, Bookshelve, Fern, Sunflower
};

static enum map {
	start, dorm, outdoor, hipermarket, uni
};

static bool isPaused = false;
static map whichMap = dorm;
