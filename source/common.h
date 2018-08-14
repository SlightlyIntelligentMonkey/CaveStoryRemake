#pragma once
//This includes everything that everything needs.
#include <SDL.h>
#include <SDL_image.h>

#define LONG int32_t
#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t
#define UINT uint32_t

typedef struct {
 LONG left, top, right, bottom;
} RECT;

typedef struct {
 LONG x, y;
} POINT;

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <vector>

//Enums
enum Collisions
{
	leftWall = 0b0001, //Touching a left wall
	ceiling = 0b0010, //Touching a ceiling
	rightWall = 0b0100, //Touching a right wall
	ground = 0b1000, //Touching the ground
	slopeRight = 0x10, //On a slope that goes up to the right (used to keep Quote on the slope)
	slopeLeft = 0x20, //On a slope that goes up to the left (used to keep Quote on the slope)
	water = 0x100, //In water
	spike = 0x400, //In spike tile
	bloodWater = 0x800, //Set by water spikes, if wasn't in water, water particles will be blood (used in Last Cave)
	windLeft = 0x1000, //In wind going to the left
	windUp = 0x2000, //In wind going up
	windRight = 0x4000, //In wind going to the right
	windDown = 0x8000, //In wind going down
	slopeE = 0x10000, //A slope flag used to keep Quote on the slope
	slopeF = 0x20000, //A slope flag used to keep Quote on the slope
	slopeG = 0x40000, //A slope flag used to keep Quote on the slope
	slopeH = 0x80000, //A slope flag used to keep Quote on the slope
};

enum NPC_flags {
	npc_solidsoft = 0b0001, //Pushes quote out
	npc_ignore44 = 0b0010, //Ignores tile 44 (No NPC)
	npc_invulnerable = 0b0100, //Can't get hit
	npc_ignoresolid = 0b1000, //Doesn't collide with anything
	npc_bouncy = 0x10, //Quote bounces on the top
	npc_shootable = 0x20, //Can be shot
	npc_solidhard = 0x40, //Essentially acts as level tiles
	npc_reartop = 0x80, //Rear and top don't hurt
	npc_eventtouch = 0x100, //Run event when touched
	npc_eventdie = 0x200, //Run event when killed
	npc_appearset = 0x800, //Only appear when flag is set
	npc_altdir = 0x1000, //Spawn facing to the right (or however the npc interprets the direction as)
	npc_interact = 0x2000, //Run event when interacted with
	npc_hideset = 0x4000, //Hide when flag is set
	npc_showdamage = 0x8000, //Show #Damage taken
};

enum NPC_cond {
	npccond_alive = 0x80, //Determines if an npc is alive
};

enum player_flag {
	player_interact = 0b0001, //Inspecting
	player_removed = 0b0010, //Removed
	player_walk = 0b0100, //Walking (used for animation)
	player_noFriction = 0x20, //Disables friction
	player_visible = 0x80, //Quote is visible
};

enum equipItems {
	equip_booster08 = 0x01,
	equip_mapSystem = 0x02,
	equip_turboCharge = 0x04,
	equip_armsBarrier = 0x08,
	equip_airTank = 0x10,
	equip_booster20 = 0x20,
	equip_mimigaMask = 0x40,
	equip_whimsicalStar = 0x80,
	equip_nikumaruCounter = 0x100,
};

//Struct
struct VIEW {
	int x;
	int y;
	int *lookX;
	int *lookY;
	int speed;

	int quake;
	int quake2;
};

//Macro
#define TILE2COORD(x) x << 13

//Drawing related variables
extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern SDL_Rect DrawRect;
extern SDL_Rect ImageRect;

extern VIEW viewport;

extern SDL_Texture* sprites[40];

//Event variable
extern SDL_Event events;

//Some game variables
extern int framerate;
extern unsigned int framerateTicks;

extern VIEW viewport;

extern int mode;

extern bool exitGame;

extern int gameFlags;

//Functions
void doError();
void doCustomError(const char *msg);

//Modules
#include "math.h"
#include "filesystem.h"
#include "render.h"
#include "flags.h"
#include "script.h"
#include "input.h"
#include "sound.h"

//Classes
#include "player.h"
#include "npc.h"
#include "bullet.h"
#include "caret.h"
#include "valueview.h"

//States
#include "game.h"
