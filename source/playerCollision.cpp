#include "npcCollision.h"

void putLittleStar(RECT *rcHit, player *me)
{
	if (!(me->cond & player_removed) && me->ym < -0x200)
	{
		//PlaySoundObject(3, 1);
		createCaret(me->x, me->y - rcHit->top, 13, 0);
		createCaret(me->x, me->y - rcHit->top, 13, 0);
	}
}

//Judging functions
int playerJudgeBlock(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;

	if (me->y - rcHit->top < (2 * (2 * ty + 1) - 1) << 11
		&& rcHit->bottom + me->y > (2 * (2 * ty - 1) + 1) << 11
		&& me->x - rcHit->left < (2 * tx + 1) << 12
		&& me->x - rcHit->left > tx << 13)
	{
		me->x = ((2 * tx + 1) << 12) + rcHit->left;

		if (me->xm < -0x180)
			me->xm = -0x180;

		if (!isKeyDown(keyLeft) && me->xm < 0)
			me->xm = 0;

		hit |= leftWall;
	}

	if (me->y - rcHit->top < (2 * (2 * ty + 1) - 1) << 11
		&& rcHit->bottom + me->y > (2 * (2 * ty - 1) + 1) << 11
		&& rcHit->right + me->x > (2 * tx - 1) << 12
		&& rcHit->right + me->x < tx << 13)
	{
		me->x = ((2 * tx - 1) << 12) - rcHit->right;

		if (me->xm > 0x180)
			me->xm = 0x180;

		if (!isKeyDown(keyRight) && me->xm > 0)
			me->xm = 0;

		hit |= rightWall;
	}

	if (me->x - rcHit->left < ((2 * tx + 1) << 12) - 0x600
		&& rcHit->right + me->x > ((2 * tx - 1) << 12) + 0x600
		&& me->y - rcHit->top < (2 * ty + 1) << 12
		&& me->y - rcHit->top > ty << 13)
	{
		me->y = ((2 * ty + 1) << 12) + rcHit->top;

		putLittleStar(rcHit, me);

		if (me->ym < 0)
			me->ym = 0;

		hit |= ceiling;
	}

	if (me->x - rcHit->left < ((2 * tx + 1) << 12) - 0x600
		&& rcHit->right + me->x > ((2 * tx - 1) << 12) + 0x600
		&& rcHit->bottom + me->y > (2 * ty - 1) << 12
		&& rcHit->bottom + me->y < ty << 13)
	{
		me->y = ((2 * ty - 1) << 12) - rcHit->bottom;

		//if (me->ym > 1024)
			//PlaySoundObject(23, 1);

		if (me->ym > 0)
			me->ym = 0;

		hit |= ground;
	}

	return hit;
}

//Ceiling slopes
int playerJudgeTriangleA(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;
	
	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y - rcHit->top < (ty << 13) - (-0x2000 * tx + me->x) / 2 + 0x800
		&& me->y + rcHit->bottom > (2 * ty - 1) << 12)
	{
		if (!(me->cond & player_removed) && me->ym < -0x200)
			putLittleStar(rcHit, me);
		if (me->ym < 0)
			me->ym = 0;

		me->y = (ty << 13) - (-0x2000 * tx + me->x) / 2 + 0x800 + rcHit->top;
		
		hit = ceiling;
	}

	return hit;
}

int playerJudgeTriangleB(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;

	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y - rcHit->top < (ty << 13) - (-0x2000 * tx + me->x) / 2 - 0x800
		&& me->y + rcHit->bottom >(2 * ty - 1) << 12)
	{
		if (!(me->cond & player_removed) && me->ym < -0x200)
			putLittleStar(rcHit, me);
		if (me->ym < 0)
			me->ym = 0;

		me->y = (ty << 13) - (-0x2000 * tx + me->x) / 2 - 0x800 + rcHit->top;

		hit = ceiling;
	}

	return hit;
}

int playerJudgeTriangleC(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;

	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y - rcHit->top < (ty << 13) + (-0x2000 * tx + me->x) / 2 - 0x800
		&& me->y + rcHit->bottom >(2 * ty - 1) << 12)
	{
		if (!(me->cond & player_removed) && me->ym < -0x200)
			putLittleStar(rcHit, me);
		if (me->ym < 0)
			me->ym = 0;

		me->y = (ty << 13) + (-0x2000 * tx + me->x) / 2 - 0x800 + rcHit->top;

		hit = ceiling;
	}

	return hit;
}

int playerJudgeTriangleD(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;

	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y - rcHit->top < (ty << 13) + (-0x2000 * tx + me->x) / 2 + 0x800
		&& me->y + rcHit->bottom >(2 * ty - 1) << 12)
	{
		if (!(me->cond & player_removed) && me->ym < -0x200)
			putLittleStar(rcHit, me);
		if (me->ym < 0)
			me->ym = 0;

		me->y = (ty << 13) + (-0x2000 * tx + me->x) / 2 + 0x800 + rcHit->top;

		hit = ceiling;
	}

	return hit;
}

//Floor slopes
int playerJudgeTriangleE(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y + rcHit->bottom > (ty << 13) + (-0x2000 * tx + me->x) / 2 - 0x800
		&& me->y - rcHit->top < (2 * ty + 1) << 12)
	{
		me->y = (ty << 13) + (-0x2000 * tx + me->x) / 2 - 0x800 - rcHit->bottom;

		if (me->ym > 0)
			me->ym = 0;
		
		return (ground | slopeLeft | slopeE);
	}

	return slopeE;
}

int playerJudgeTriangleF(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x < (2 * tx + 1) << 12
		&& me->x >(2 * tx - 1) << 12
		&& me->y + rcHit->bottom > (ty << 13) + (-0x2000 * tx + me->x) / 2 + 0x800
		&& me->y - rcHit->top < (2 * ty + 1) << 12)
	{
		me->y = (ty << 13) + (-0x2000 * tx + me->x) / 2 + 0x800 - rcHit->bottom;

		if (me->ym > 0)
			me->ym = 0;

		return (ground | slopeLeft | slopeF);
	}

	return slopeF;
}

int playerJudgeTriangleG(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y + rcHit->bottom > (ty << 13) - (-0x2000 * tx + me->x) / 2 + 0x800
		&& me->y - rcHit->top < (2 * ty + 1) << 12)
	{
		me->y = (ty << 13) - (-0x2000 * tx + me->x) / 2 + 0x800 - rcHit->bottom;

		if (me->ym > 0)
			me->ym = 0;

		return (ground | slopeRight | slopeG);
	}

	return slopeG;
}

int playerJudgeTriangleH(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x > (2 * tx - 1) << 12
		&& me->x < (2 * tx + 1) << 12
		&& me->y + rcHit->bottom > (ty << 13) - (-0x2000 * tx + me->x) / 2 - 0x800
		&& me->y - rcHit->top < (2 * ty + 1) << 12)
	{
		me->y = (ty << 13) - (-0x2000 * tx + me->x) / 2 - 0x800 - rcHit->bottom;

		if (me->ym > 0)
			me->ym = 0;

		return (ground | slopeRight | slopeH);
	}

	return slopeH;
}

int playerJudgeWater(RECT *rcHit, player *me, int tx, int ty)
{
	int hit = 0;

	if (me->x - rcHit->left < ((2 * tx + 1) << 12) - 0x600
		&& me->x + rcHit->right > ((2 * tx - 1) << 12) + 0x600
		&& me->y - rcHit->top < ((2 * ty + 1) << 12) - 0x600
		&& me->y + rcHit->bottom > ty << 13)
	{
		hit = water;
	}

	return hit;
}

int playerJudgeSpike(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - 0x800 < (4 * tx + 1) << 11
		&& me->x + 0x800 > (4 * tx - 1) << 11
		&& me->y - 0x800 < (ty << 13) + 0x600
		&& me->y + 0x800 > (ty << 13) - 0x600)
	{
		return spike;
	}

	return 0;
}

int playerJudgeWaterSpike(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - 0x800 < (4 * tx + 1) << 11
		&& me->x + 0x800 > (4 * tx - 1) << 11
		&& me->y - 0x800 < (ty << 13) + 0x600
		&& me->y + 0x800 > (ty << 13) - 0x600)
	{
		return (spike | water | bloodWater);
	}

	return 0;
}

//Current
int playerJudgeCurrentLeft(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - rcHit->left < (4 * (2 * tx + 1) - 1) << 10
		&& me->x + rcHit->right > (4 * (2 * tx - 1) + 1) << 10
		&& me->y - rcHit->top < (4 * (2 * ty + 1) - 1) << 10
		&& me->y + rcHit->bottom > (4 * (2 * ty - 1) + 1) << 10)
	{
		return windLeft;
	}

	return 0;
}

int playerJudgeCurrentUp(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - rcHit->left < (4 * (2 * tx + 1) - 1) << 10
		&& me->x + rcHit->right >(4 * (2 * tx - 1) + 1) << 10
		&& me->y - rcHit->top < (4 * (2 * ty + 1) - 1) << 10
		&& me->y + rcHit->bottom >(4 * (2 * ty - 1) + 1) << 10)
	{
		return windUp;
	}

	return 0;
}

int playerJudgeCurrentRight(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - rcHit->left < (4 * (2 * tx + 1) - 1) << 10
		&& me->x + rcHit->right >(4 * (2 * tx - 1) + 1) << 10
		&& me->y - rcHit->top < (4 * (2 * ty + 1) - 1) << 10
		&& me->y + rcHit->bottom >(4 * (2 * ty - 1) + 1) << 10)
	{
		return windRight;
	}

	return 0;
}

int playerJudgeCurrentDown(RECT *rcHit, player *me, int tx, int ty)
{
	if (me->x - rcHit->left < (4 * (2 * tx + 1) - 1) << 10
		&& me->x + rcHit->right >(4 * (2 * tx - 1) + 1) << 10
		&& me->y - rcHit->top < (4 * (2 * ty + 1) - 1) << 10
		&& me->y + rcHit->bottom >(4 * (2 * ty - 1) + 1) << 10)
	{
		return windDown;
	}

	return 0;
}

//Main function
void playerHitMap(RECT *rcHit)
{
	player *me = &currentPlayer;

	int fromX = (me->x - rcHit->left + 0x1000) >> 13;
	int fromY = (me->y - rcHit->top + 0x1000) >> 13;
	int toX = (me->x + rcHit->right + 0x1000) >> 13;
	int toY = (me->y + rcHit->bottom + 0x1000) >> 13;

	for (int currentX = fromX; currentX <= toX; currentX++)
	{
		for (int currentY = fromY; currentY <= toY; currentY++)
		{
			switch (getTileAttribute(currentX, currentY))
			{
				//Solid
			case 0x05u: case 0x41u: case 0x43u: case 0x46u:
				me->flag |= playerJudgeBlock(rcHit, me, currentX, currentY);
				break;

				//Spike
			case 0x42u:
				me->flag |= playerJudgeSpike(rcHit, me, currentX, currentY);
				break;

				//Ceiling slopes
			case 0x50u:
				me->flag |= playerJudgeTriangleA(rcHit, me, currentX, currentY);
				break;

			case 0x51u:
				me->flag |= playerJudgeTriangleB(rcHit, me, currentX, currentY);
				break;

			case 0x52u:
				me->flag |= playerJudgeTriangleC(rcHit, me, currentX, currentY);
				break;

			case 0x53u:
				me->flag |= playerJudgeTriangleD(rcHit, me, currentX, currentY);
				break;

				//Floor slopes
			case 0x54u:
				me->flag |= playerJudgeTriangleE(rcHit, me, currentX, currentY);
				break;

			case 0x55u:
				me->flag |= playerJudgeTriangleF(rcHit, me, currentX, currentY);
				break;

			case 0x56u:
				me->flag |= playerJudgeTriangleG(rcHit, me, currentX, currentY);
				break;

			case 0x57u:
				me->flag |= playerJudgeTriangleH(rcHit, me, currentX, currentY);
				break;

				//Water, water solid, and water spike
			case 0x60u:
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x61u:
				me->flag |= playerJudgeBlock(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x62u:
				me->flag |= playerJudgeWaterSpike(rcHit, me, currentX, currentY);
				break;

					//Water slopes
				//Ceiling slopes
			case 0x70u:
				me->flag |= playerJudgeTriangleA(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x71u:
				me->flag |= playerJudgeTriangleB(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x72u:
				me->flag |= playerJudgeTriangleC(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x73u:
				me->flag |= playerJudgeTriangleD(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;
				
				//Floor slopes
			case 0x74u:
				me->flag |= playerJudgeTriangleE(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x75u:
				me->flag |= playerJudgeTriangleF(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x76u:
				me->flag |= playerJudgeTriangleG(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0x77u:
				me->flag |= playerJudgeTriangleH(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

				//Wind
			case 0x80u:
				me->flag |= playerJudgeCurrentLeft(rcHit, me, currentX, currentY);
				break;

			case 0x81u:
				me->flag |= playerJudgeCurrentUp(rcHit, me, currentX, currentY);
				break;

			case 0x82u:
				me->flag |= playerJudgeCurrentRight(rcHit, me, currentX, currentY);
				break;

			case 0x83u:
				me->flag |= playerJudgeCurrentDown(rcHit, me, currentX, currentY);
				break;

				//Water current
			case 0xA0u:
				me->flag |= playerJudgeCurrentLeft(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0xA1u:
				me->flag |= playerJudgeCurrentUp(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0xA2u:
				me->flag |= playerJudgeCurrentRight(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

			case 0xA3u:
				me->flag |= playerJudgeCurrentDown(rcHit, me, currentX, currentY);
				me->flag |= playerJudgeWater(rcHit, me, currentX, currentY);
				break;

				//Default
			default:
				break;
			}
		}
	}
}

//Npc hit functions
int playerHitNpcSoftSolid(RECT *rcHit, player *me, npc *NPC)
{
	int hit = 0;

	if (me->y - rcHit->top < NPC->y + NPC->hit.bottom - 0x600
		&& me->y + rcHit->bottom > NPC->y - NPC->hit.top + 0x600
		&& me->x - rcHit->left < NPC->x + NPC->hit.right
		&& me->x - rcHit->left > NPC->x)
	{
		if (me->xm <= 0x1FF)
			me->xm += 0x200;

		hit = leftWall;
	}

	if (me->y - rcHit->top < NPC->y + NPC->hit.bottom - 0x600
		&& me->y + rcHit->bottom > NPC->y - NPC->hit.top + 0x600
		&& me->x + rcHit->right - 0x200 > NPC->x - NPC->hit.right
		&& me->x + rcHit->right - 0x200 < NPC->x)
	{
		if (me->xm >= -0x1FF)
			me->xm -= 0x200;

		hit |= rightWall;
	}

	if (me->x - rcHit->left < NPC->x + NPC->hit.right - 0x600
		&& me->x + rcHit->right > NPC->x - NPC->hit.right + 0x600
		&& me->y - rcHit->top < NPC->y + NPC->hit.bottom
		&& me->y - rcHit->top > NPC->y)
	{
		if (me->ym < 0)
			me->ym = 0;

		hit |= ceiling;
	}

	if (me->x - rcHit->left < NPC->x + NPC->hit.right - 0x600
		&& me->x + rcHit->right > NPC->x - NPC->hit.right + 0x600
		&& me->y + rcHit->bottom > NPC->y - NPC->hit.top
		&& me->y + rcHit->bottom < NPC->y + 0x600)
	{
		if (NPC->bits & npc_bouncy)
		{
			me->ym = NPC->ym - 0x200;

			hit |= ground;
		}
		else if (!(me->flag & ground) && me->ym > NPC->ym)
		{
			me->y = NPC->y - NPC->hit.top - rcHit->bottom + 0x200;
			me->ym = NPC->ym;

			me->x += NPC->xm;
			hit |= ground;
		}
	}

	return hit;
}

int playerHitNpcHardSolid(RECT *rcHit, player *me, npc *NPC)
{
	long double xDiff = 0.0;
	long double yDiff = 0.0;
	int hit = 0;

	long double fx1 = 0.0;
	long double fx2 = 0.0;
	long double fy1 = 0.0;
	long double fy2 = 0.0;

	if (NPC->x <= me->x)
		xDiff = me->x - NPC->x;
	else
		xDiff = NPC->x - me->x;

	fx1 = xDiff;
	fx2 = NPC->hit.right;

	if (fx1 == 0.0)
		fx1 = 1.0;
	if (fx2 == 0.0)
		fx2 = 1.0;

	if (NPC->y <= me->y)
		yDiff = me->y - NPC->y;
	else
		yDiff = NPC->y - me->y;

	fy1 = yDiff;
	fy2 = NPC->hit.top;

	if (fy1 / fx1 <= fy2 / fx2)
	{
		if (me->y - rcHit->top < NPC->y + NPC->hit.bottom && me->y + rcHit->bottom > NPC->y - NPC->hit.top)
		{
			if (me->x - rcHit->left < NPC->x + NPC->hit.right && me->x - rcHit->left > NPC->x)
			{
				if (me->xm < NPC->xm)
					me->xm = NPC->xm;

				me->x = NPC->hit.right + NPC->x + rcHit->left;

				hit = leftWall;
			}

			if (me->x + rcHit->right > NPC->x - NPC->hit.right && me->x + rcHit->right < NPC->x)
			{
				if (me->xm > NPC->xm)
					me->xm = NPC->xm;

				me->x = NPC->x - NPC->hit.right - rcHit->right;

				hit |= rightWall;
			}
		}
	}
	else if (me->x - rcHit->left < NPC->x + NPC->hit.right && me->x + rcHit->right > NPC->x - NPC->hit.right)
	{
		if (me->y - rcHit->top < NPC->y + NPC->hit.bottom && me->y - rcHit->top > NPC->y)
		{
			if (me->ym >= NPC->ym)
			{
				if (me->ym < 0)
					me->ym = 0;
			}
			else
			{
				me->y = NPC->y + NPC->hit.bottom + rcHit->top + 0x200;

				me->ym = NPC->ym;
			}

			hit = ceiling;
		}

		if (me->y + rcHit->bottom > NPC->y - NPC->hit.top && me->y + rcHit->bottom < NPC->y + 0x600)
		{
			//if (gMC.ysp - npc->ysp > 1024)
			//	PlaySoundObject(23, 1);

			//if (unk_81C8594 == 1)
			//{
			//	y = npc->y - npc->collideRect.top - unk_81C85D0 + 512;
			//	hit |= 8u;
			//}

			if (NPC->bits & npc_bouncy)
			{
				me->ym = NPC->ym - 0x200;

				hit |= ground;
			}
			else if (!(me->flag & ground) && me->ym > NPC->ym)
			{
				me->y = NPC->y - NPC->hit.top - rcHit->bottom + 0x200;

				me->ym = NPC->ym;
				me->x += NPC->xm;

				hit |= ground;
			}
		}
	}
	return hit;
}

int playerHitNpcNonSolid(RECT *rcHit, player *me, npc *NPC)
{
	if (NPC->direct)
	{
		if (me->x + 0x400 > NPC->x - NPC->hit.right
			&& me->x - 0x400 < NPC->x + NPC->hit.left
			&& me->y + 0x400 > NPC->y - NPC->hit.top
			&& me->y - 0x400 < NPC->y + NPC->hit.bottom)
		{
			return 1;
		}
	}

	if (me->x + 0x400 > NPC->x - NPC->hit.left
		&& me->x - 0x400 < NPC->x + NPC->hit.right
		&& me->y + 0x400 > NPC->y - NPC->hit.top
		&& me->y - 0x400 < NPC->y + NPC->hit.bottom)
	{
		return 1;
	}

	return 0;
}

void playerHitNpcs(RECT *rcHit)
{
	int hit = 0;

	player *me = &currentPlayer;

	if ((me->cond & player_visible) && !(me->cond & player_removed))
	{
		for (uint32_t i = 0; i < npcs.size(); ++i)
		{
			if ((npcs[i].cond & npccond_alive))
			{
				if (npcs[i].bits & npc_solidsoft)
				{
					hit = playerHitNpcSoftSolid(rcHit, me, &npcs[i]);

					me->flag |= hit;
				}
				else if (npcs[i].bits & npc_solidhard)
				{
					hit = playerHitNpcHardSolid(rcHit, me, &npcs[i]);

					me->flag |= hit;
				}
				else
				{
					hit = playerHitNpcNonSolid(rcHit, me, &npcs[i]);
				}

				if (hit && npcs[i].code_char == 1)
				{
					//PlaySoundObject(14, 1);
					//AddExpMyChar(gNPC[i].exp);
					npcs[i].cond = 0;
				}
				if (hit && npcs[i].code_char == 86)
				{
					//PlaySoundObject(42, 1);
					//AddBulletMyChar(gNPC[i].code_event, gNPC[i].exp);
					npcs[i].cond = 0;
				}

				if (hit && npcs[i].code_char == 87)
				{
					//PlaySoundObject(20, 1);
					//AddLifeMyChar(gNPC[i].exp);
					npcs[i].cond = 0;
				}

				if (hit && npcs[i].bits & npc_eventtouch)//!(g_GameFlags & 4) && hit && gNPC[i].bits & 0x100)
				{
					//StartTextScript(gNPC[i].code_event);
				}

				if (!(npcs[i].bits & npc_interact))
				{
					if (npcs[i].bits & npc_reartop)
					{
						if (hit & rightWall && npcs[i].xm < 0)
							me->damage(npcs[i].damage);
						if (hit & leftWall && npcs[i].xm > 0)
							me->damage(npcs[i].damage);
						if (hit & ground && npcs[i].ym < 0)
							me->damage(npcs[i].damage);
						if (hit & ceiling && npcs[i].ym > 0)
							me->damage(npcs[i].damage);
					}
					else if (hit && npcs[i].damage)
					{
						me->damage(npcs[i].damage);
					}
				}

				if (hit && me->cond & player_interact && npcs[i].bits & npc_interact)
				{
					runScriptEvent(npcs[i].code_event);
					me->xm = 0;
					me->ques = false;
				}
			}
		}

		if (me->ques)
			createCaret(me->x, me->y, 9, 0);
	}
}
