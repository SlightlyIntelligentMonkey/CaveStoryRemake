#pragma once

#include "npc.h"

struct SDL_Texture;

struct STAGE_TABLE
{
	char tileset[0x20];
	char filename[0x20];
	uint32_t backgroundScroll;
	char background[0x20];
	char npc1[0x20];
	char npc2[0x20];
	uint8_t boss;
	char name[0x23];
};

struct MAPNAME
{
	int flag;
	int wait;
	char name[32];
};

extern MAPNAME mapName;

extern STAGE_TABLE *stageTable;

extern int levelWidth;
extern int levelHeight;

extern int currentLevel;

extern uint8_t *levelMap;
extern uint8_t *levelTileAttributes;

extern SDL_Texture *levelTileset;

extern uint8_t backgroundScroll;
extern SDL_Texture *levelBackground;

uint8_t getTileAttribute(int x, int y) attrPure;

void deleteTile(int x, int y);
void shiftTile(int x, int y);
bool changeTile(int x, int y, uint8_t tile);

void loadStageTable();

void loadLevel(int levelIndex);
<<<<<<< HEAD
void drawLevel(bool foreground);
=======
void drawLevel(bool foreground);

// Note : 1 tile is 0x2000 units

template<typename T> constexpr inline int32_t tilesToUnits(T x)
{
    return x * 0x2000;
}

template<typename T> constexpr inline int32_t unitsToTiles(T x)
{
	return x / 0x2000;
}
>>>>>>> upstream/master
