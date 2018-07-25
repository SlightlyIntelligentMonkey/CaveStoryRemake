#include "caret.h"
//yeah i like carrots

std::vector<caret> carets(0);

CARETSTAT caretStats[] = {
	{ 0x0,		0x0 },
	{ 0x800,	0x800 },
	{ 0x1000,	0x1000 },
	{ 0x1000,	0x1000 },
	{ 0x1000,	0x1000 },
	{ 0x800,	0x800 },
	{ 0x1000,	0x1000 },
	{ 0x800,	0x800 },
	{ 0x1000,	0x1000 },
	{ 0x1000,	0x1000 },
	{ 0x3800,	0x1000 },
	{ 0x800,	0x800 },
	{ 0x2000,	0x2000 },
	{ 0x800,	0x800 },
	{ 0x2800,	0x2800 },
	{ 0x800,	0x800 },
	{ 0x2800,	0x800 },
	{ 0x6800,	0x800 },
};

void updateCarets()
{
	if (carets.size())
	{
		//Remove dead carets
		for (size_t i = 0; i < carets.size(); i++) {
			if (!(carets[i].cond & 0x80))
			{
				carets.erase(carets.begin() + i);
				i--;
			}
		}

		//Update
		for (unsigned int i = 0; i < carets.size(); i++)
			carets[i].update();
	}
}

void drawCarets()
{
	if (carets.size())
	{
		for (unsigned int i = 0; i < carets.size(); i++)
		{
			if (carets[i].cond & 0x80)
				carets[i].draw();
		}
	}
}

//Action code
void caretAct000(caret *CARET) //Inexistente
{
	CARET->cond = 0;
}

void caretAct001(caret *CARET) //Pulsing Disc Particles
{
	RECT rcRight[4];
	RECT rcLeft[4];
	
	//A bunch of framerects
	rcLeft[0] = { 0, 64, 8, 72 };
	rcLeft[1] = { 8, 64, 16, 72 };
	rcLeft[2] = { 16, 64, 24, 72 };
	rcLeft[3] = { 24, 64, 32, 72 };
	
	rcRight[0] = { 64, 24, 72, 32 };
	rcRight[1] = { 72, 24, 80, 32 };
	rcRight[2] = { 80, 24, 88, 32 };
	rcRight[3] = { 88, 24, 96, 32 };
	
	//Movement
	if (!CARET->action)
	{
		CARET->action = 1;

		CARET->xsp = random(-0x400, 0x400);
		CARET->ysp = random(-0x400, 0);
	}
	
	CARET->ysp += 0x40;
	
	CARET->x += CARET->xsp;
	CARET->y += CARET->ysp;

	//Animate
	if (++CARET->animationWait > 5)
	{
		CARET->animationWait = 0;
		if (++CARET->animation > 3) { CARET->cond = 0; }
	}

	//Set framerect
	if (CARET->direction)
		CARET->frameRect = rcRight[CARET->animation];
	else
		CARET->frameRect = rcLeft[CARET->animation];
	
	return;
}

void caretAct002(caret *CARET) //Rising Disc / Exploding Diamond
{
	RECT rcRight[4];
	RECT rcLeft[4];
	RECT rcUp[3];

	//A bunch of framerects
	rcLeft[0] = { 0, 32, 16, 48 };
	rcLeft[1] = { 16, 32, 32, 48 };
	rcLeft[2] = { 32, 32, 48, 48 };
	rcLeft[3] = { 48, 32, 64, 48 };

	rcRight[0] = { 176, 0, 192, 16 };
	rcRight[1] = { 192, 0, 208, 16 };
	rcRight[2] = { 208, 0, 224, 16 };
	rcRight[3] = { 224, 0, 240, 16 };

	rcUp[0] = { 0, 32, 16, 48 };
	rcUp[1] = { 32, 32, 48, 48 };
	rcUp[2] = { 16, 32, 32, 48 };

	//Act
	switch (CARET->direction)
	{
	case 0:
		CARET->ysp -= 16;
		CARET->y += CARET->ysp;

		//Animate
		if (++CARET->animationWait > 5)
		{
			CARET->animationWait = 0;
			++CARET->animation;
		}

		if (CARET->animation > 3)
			CARET->cond = 0;

		CARET->frameRect = rcLeft[CARET->animation];
		break;

	case 1:
		//Animate ??
		CARET->frameRect = rcUp[++CARET->animationWait / 2 % 3];

		if (CARET->animationWait > 24)
			CARET->cond = 0;
		break;

	case 2:
		//Animate
		if (++CARET->animationWait > 2)
		{
			CARET->animationWait = 0;
			++CARET->animation;
		}

		if (CARET->animation > 3)
			CARET->cond = 0;

		CARET->frameRect = rcRight[CARET->animation];
		break;
	}
}

void caretAct003(caret *CARET) //Star
{
	//Animate
	if (CARET->animationWait++ > 2)
	{
		CARET->animationWait = 0;

		if (CARET->animation++ > 3) 
			CARET->cond = 0;
	}
	
	CARET->frameRect = { (CARET->animation << 4), 48, 16 + (CARET->animation << 4), 64 };
}

void caretAct004(caret *CARET) //Fireball impact?
{
	//Set framerects
	RECT rcLeft[9];

	rcLeft[0] = { 64, 32, 80, 48 };
	rcLeft[1] = { 80, 32, 96, 48 };
	rcLeft[2] = { 96, 32, 112, 48 };

	rcLeft[3] = { 64, 48, 80, 64 };
	rcLeft[4] = { 80, 48, 96, 64 };
	rcLeft[5] = { 96, 48, 112, 64 };

	rcLeft[6] = { 64, 64, 80, 80 };
	rcLeft[7] = { 80, 64, 96, 80 };
	rcLeft[8] = { 96, 64, 112, 80 };

	//Animate
	if (++CARET->animationWait > 1)
	{
		CARET->animationWait = 0;
		if (++CARET->animation > 2) { CARET->cond = 0; }
	}

	//framerect
	CARET->frameRect = rcLeft[CARET->animation + CARET->direction * 3];
}

void caretAct005(caret *CARET) //Zzz...
{
	//Set framerects
	RECT rcLeft[7];

	rcLeft[0] = { 32, 64, 40, 72 };
	rcLeft[1] = { 32, 72, 40, 80 };
	rcLeft[2] = { 40, 64, 48, 72 };
	rcLeft[3] = { 40, 72, 48, 80 };
	rcLeft[4] = { 40, 64, 48, 72 };
	rcLeft[5] = { 40, 72, 48, 80 };
	rcLeft[6] = { 40, 64, 48, 72 };

	//Animate
	if (CARET->animationWait++ > 4)
	{
		CARET->animationWait = 0;
		CARET->animation++;
	}

	if (CARET->animation > 6)
		CARET->cond = 0;

	//Move
	CARET->x += 128;
	CARET->y -= 128;

	//framerect
	CARET->frameRect = rcLeft[CARET->animation];
}

void caretAct007(caret *CARET) //Booster particles
{
	//Animate and set framerect
	if (++CARET->animationWait > 1)
	{
		CARET->animationWait = 0;

		if (++CARET->animation > 6)
			CARET->cond = 0;
	}

	CARET->frameRect = { 56 + (CARET->animation << 3), 0, 64 + (CARET->animation << 3), 8 };

	//Move
	switch (CARET->direction)
	{
	case 0:
		CARET->x -= 0x400;
		break;

	case 1:
		CARET->y -= 0x400;
		break;

	case 2:
		CARET->x += 0x400;
		break;

	case 3:
		CARET->y += 0x400;
		break;
	}
}

void caretAct008(caret *CARET) //Drowned Quote
{
	if (CARET->direction)
		CARET->frameRect = { 32, 80, 48, 96 };
	else
		CARET->frameRect = { 16, 80, 32, 96 };
}

void caretAct009(caret *CARET) //Question mark (when down is pressed)
{
	//Move
	if (++CARET->animationWait <= 4)
		CARET->y -= 2048;

	//Deletion
	if (CARET->animationWait >= 32)
		CARET->cond = 0;

	if (CARET->direction)
		CARET->frameRect = { 48, 64, 64, 80 };
	else
		CARET->frameRect = { 0, 80, 16, 96 };
}

void caretAct010(caret *CARET) //Level up and level down
{
	RECT rcRight[2];
	RECT rcLeft[2];

	rcLeft[0] = { 0, 0, 56, 16 };
	rcLeft[1] = { 0, 16, 56, 32 };

	rcRight[0] = { 0, 96, 56, 112 };
	rcRight[1] = { 0, 112, 56, 128 };

	CARET->animationWait++;

	if (CARET->direction)
	{
		if (CARET->animationWait < 20) 
			CARET->y -= 0x200;

		if (CARET->animationWait >= 80)
			CARET->cond = 0;
	}
	else
	{
		if (CARET->animationWait < 20) 
			CARET->y -= 0x400;

		if (CARET->animationWait >= 80)
			CARET->cond = 0;
	}

	if (CARET->direction)
	{
		CARET->frameRect = rcRight[CARET->animationWait / 2 % 2];
	}
	else
	{
		CARET->frameRect = rcLeft[CARET->animationWait / 2 % 2];
	}
}

void caretAct011(caret *CARET) //Damage effect
{
	//Move
	if (!CARET->action)
	{
		CARET->action = 1;

		int deg = random(0, 255);

		CARET->xsp = 2 * getCos(deg);
		CARET->ysp = 2 * getSin(deg);
	}
	
	CARET->x += CARET->xsp;
	CARET->y += CARET->ysp;

	//Animate
	if (++CARET->animationWait > 2)
	{
		CARET->animationWait = 0;

		if (++CARET->animation > 6)
			CARET->cond = 0;
	}

	CARET->frameRect = { 64 + (CARET->animation << 3), 8, 72 + (CARET->animation << 3), 16 };
}

void caretAct012(caret *CARET) //White "explosion" disc
{
	RECT rcLeft[2];

	rcLeft[0] = { 112, 0, 144, 32 };
	rcLeft[1] = { 144, 0, 176, 32 };
	
	if (++CARET->animationWait > 2)
	{
		CARET->animationWait = 0;

		if (++CARET->animation > 1)
			CARET->cond = 0;
	}

	CARET->frameRect = rcLeft[CARET->animation];
}

void caretAct013(caret *CARET) //Headbump sparks
{
	RECT rcLeft[2];

	rcLeft[0] = { 56, 24, 64, 32 };
	rcLeft[1] = { 0, 0, 0, 0 };
	
	if (!CARET->action)
	{
		CARET->action = 1;
		
		if (CARET->direction)
		{
			if (CARET->direction == 1)
				CARET->ysp = -0x200 * random(1, 3);
		}
		else
		{
			CARET->xsp = random(-0x600, 0x600);
			CARET->ysp = random(-0x200, 0x200);
		}
	}

	if (!CARET->direction)
	{
		CARET->xsp = 4 * CARET->xsp / 5;
		CARET->ysp = 4 * CARET->ysp / 5;
	}

	CARET->x += CARET->xsp;
	CARET->y += CARET->ysp;

	//Destroy
	if (++CARET->animationWait > 20)
		CARET->cond = 0;

	CARET->frameRect = rcLeft[CARET->animationWait / 2 % 2];
}

void caretAct015(caret *CARET) //Small white pop
{
	RECT rcLeft[4];

	rcLeft[0] = { 0, 72, 8, 80 };
	rcLeft[1] = { 8, 72, 16, 80 };
	rcLeft[2] = { 16, 72, 24, 80 };
	rcLeft[3] = { 24, 72, 32, 80 };

	if (++CARET->animationWait > 2)
	{
		CARET->animationWait = 0;

		if (++CARET->animation > 3)
			CARET->cond = 0;
	}

	CARET->frameRect = rcLeft[CARET->animation];
}

void caretAct016(caret *CARET) //EMPTY
{
	RECT rcLeft[2]; // [esp+0h] [ebp-20h]

	rcLeft[0] = { 104, 96, 144, 104 };
	rcLeft[0] = { 104, 104, 144, 112 };

	if (++CARET->animationWait < 10)
		CARET->y -= 1024;

	if (CARET->animationWait >= 40)
		CARET->cond = 0;

	CARET->frameRect = rcLeft[CARET->animationWait / 2 % 2];
}

void caretAct017(caret *CARET) //PUSH JUMP KEY!
{
	if (++CARET->animationWait > 39)
		CARET->animationWait = 0;

	if (CARET->animationWait > 29)
		CARET->frameRect = { 0, 0, 0, 0 };
	else
		CARET->frameRect = { 0, 144, 144, 152 };
}

caretAct caretActs[] = {
	&caretAct000,
	&caretAct001,
	&caretAct002,
	&caretAct003,
	&caretAct004,
	&caretAct005,
		&caretAct004, //unused, apparently uses caret 4
	&caretAct007,
	&caretAct008,
	&caretAct009,
	&caretAct010,
	&caretAct011,
	&caretAct012,
	&caretAct013,
		&caretAct000, //unused
	&caretAct015,
	&caretAct016,
	&caretAct017,
};

//Init
void caret::init(int setX, int setY, int setType, int setDir)
{
	memset(this, 0, sizeof(*this));

	cond = 0x80;
	type = setType;

	x = setX;
	y = setY;

	direction = setDir;

	offset.x = caretStats[type].offsetX;
	offset.y = caretStats[type].offsetY;
}

//Update code
void caret::update()
{
	caretActs[type](this);
}

void caret::draw()
{
	drawTexture(sprites[0x13], &frameRect, (x - offset.x) / 0x200 - viewX / 0x200, (y - offset.y) / 0x200 - viewY / 0x200);
}

//Create code
void createCaret(int setX, int setY, int setType, int setDir)
{
	caret newCaret;
	newCaret.init(setX, setY, setType, setDir);
	carets.push_back(newCaret);
}