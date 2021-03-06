#pragma once

#include <cstdint>
#include <cstddef>

//Sound struct
struct SOUND;

//sample rate
constexpr unsigned int sampleRate = 44100;

enum soundEffects
{
	SFX_YNChangeChoice = 0x1,
	SFX_MessageTyping = 0x2,
	SFX_QuoteBumpHead = 0x3,
	SFX_SwitchWeapon = 0x4,
	SFX_YNPrompt = 0x5,
	SFX_HighPitchCritterHop = 0x6,
	SFX_DoorOpen = 0xB,
	SFX_DestroyBreakableBlock = 0xC,
	SFX_GetEXP = 0xE,
	SFX_QuoteJump = 0xF,
	SFX_QuoteHurt = 0x10,
	SFX_QuoteDie = 0x11,
	SFX_YNConfirm = 0x12,
	SFX_QuoteHeal = 0x14,
	SFX_Bubble = 0x15,
	SFX_ChestOpen = 0x16,
	SFX_HitGround = 0x17,
	SFX_QuoteWalk = 0x18,
	SFX_SillyExplosion = 0x19,
	SFX_LargeObjectHitGround = 0x1A,
	SFX_LevelUp = 0x1B,
	SFX_ShotHitWall = 0x1C,
	SFX_Teleport = 0x1D,
	SFX_CritterHop = 0x1E,
	SFX_ShotHitInvulnerableEntity = 0x1F,
	SFX_PolarStarShootLevel12 = 0x20,
	SFX_FireballShoot = 0x21,
	SFX_FireballBounce = 0x22,
	SFX_LargeExplosion = 0x23,
	SFX_NoAmmo = 0x25,
	SFX_ItemGet = 0x26,
	SFX_EnemyShootProjectile = 0x27,
	SFX_StreamNoiseSSS2 = 0x28,
	SFX_StreamNoiseSSS1 = 0x29,
	SFX_QuoteMissileGet = 0x2A,
	SFX_ComputerScreenOn = 0x2B,
	SFX_MissileImpact = 0x2C,
	SFX_EXPBounce = 0x2D,
	SFX_IronHeadShot = 0x2E,
	SFX_StrangeClick = 0x2F,
	SFX_BubblerShoot = 0x30,
	SFX_PolarStarShootLevel3 = 0x31,
	SFX_EnemySqueal = 0x32,
	SFX_CritterSmallHurt = 0x33,
	SFX_BehemothLargeHurt = 0x34,
	SFX_GaudiDie = 0x35,
	SFX_HeavyPressLargeObjectHurt = 0x36,
	SFX_HighPitchedGaudiDie = 0x37,
	SFX_WaterSplash = 0x38,
	SFX_CurlyObjectHurt = 0x39,
	SFX_HelicopterBladesSPS = 0x3A,
	SFX_SpurChargeLevel1 = 0x3B,
	SFX_SpurChargeLevel2 = 0x3C,
	SFX_SpurChargeLevel3 = 0x3D,
	SFX_SpurShootLevel1 = 0x3E,
	SFX_SpurShootLevel2 = 0x3F,
	SFX_SpurShootLevel3 = 0x40,
	SFX_SpurChargeMAX = 0x41,
	SFX_EnemySmokePoof = 0x46,
	SFX_QuoteSmashIntoGround = 0x47,
	SFX_Explosion = 0x48,
	SFX_BubblerShootLevel3 = 0x64,
	SFX_Lightning = 0x65,
	SFX_SandCroc = 0x66,
	SFX_BallosBallAndCurlyChargingHerGun = 0x67,
	SFX_SecretItemHurt = 0x68,
	SFX_PuppyBark = 0x69,
	SFX_SpinningProjectile = 0x6A,
	SFX_BlockMove = 0x6B,
	SFX_PowerCritterLargeEnemyJump = 0x6C,
	SFX_CritterFly = 0x6D,
	SFX_PowerCritterFlys = 0x6E,
	SFX_Thud = 0x6F,
	SFX_LargeThud = 0x70,
	SFX_Booster = 0x71,
	SFX_CoreHurt = 0x72,
	SFX_CoreThrust = 0x73,
	SFX_CoreCharge = 0x74,
	SFX_NemesisShot = 0x75,
	SFX_BassBass01 = 0x96,
	SFX_SnareSnare01 = 0x97,
	SFX_HiCloseHiClose = 0x98,
	SFX_HiOpenHiOpen = 0x99,
	SFX_TomTom01 = 0x9A,
	SFX_PerPer01 = 0x9B,
	SFX_CrashesTheGame = 0xA0,
	SFX_Silence1 = 0x76,
	SFX_Silence2 = 0x77,
	SFX_Silence3 = 0x78,
	SFX_Silence4 = 0x79,
	SFX_Silence5 = 0x7A,
	SFX_Silence6 = 0x7B,
	SFX_Silence7 = 0x7C,
	SFX_Silence8 = 0x7D,
	SFX_Silence9 = 0x7E,
	SFX_Silence10 = 0x7F,
	SFX_Silence11 = 0x80,
	SFX_Silence12 = 0x81,
	SFX_Silence13 = 0x82,
	SFX_Silence14 = 0x83,
	SFX_Silence15 = 0x84,
	SFX_Silence16 = 0x85,
	SFX_Silence17 = 0x86,
	SFX_Silence18 = 0x87,
	SFX_Silence19 = 0x88,
	SFX_Silence20 = 0x89,
	SFX_Silence21 = 0x8A,
	SFX_Silence22 = 0x8B,
	SFX_Silence23 = 0x8C,
	SFX_Silence24 = 0x8D,
	SFX_Silence25 = 0x8E,
	SFX_Silence26 = 0x8F,
	SFX_Silence27 = 0x90,
	SFX_Silence28 = 0x91,
	SFX_Silence29 = 0x92,
	SFX_Silence30 = 0x93,
	SFX_Silence31 = 0x94,
	SFX_Silence32 = 0x95,
	SFX_Silence33 = 0x9C,
	SFX_Silence34 = 0x9D,
	SFX_Silence35 = 0x9E,
	SFX_Silence36 = 0x9F,
	SFX_Silence37 = 0x42,
	SFX_Silence38 = 0x43,
	SFX_Silence39 = 0x44,
	SFX_Silence40 = 0x45,
	SFX_Silence41 = 0x49,
	SFX_Silence42 = 0x4A,
	SFX_Silence43 = 0x4B,
	SFX_Silence44 = 0x4C,
	SFX_Silence45 = 0x4D,
	SFX_Silence46 = 0x4E,
	SFX_Silence47 = 0x4F,
	SFX_Silence48 = 0x50,
	SFX_Silence49 = 0x51,
	SFX_Silence50 = 0x52,
	SFX_Silence51 = 0x53,
	SFX_Silence52 = 0x54,
	SFX_Silence53 = 0x55,
	SFX_Silence54 = 0x56,
	SFX_Silence55 = 0x57,
	SFX_Silence56 = 0x58,
	SFX_Silence57 = 0x59,
	SFX_Silence58 = 0x5A,
	SFX_Silence59 = 0x5B,
	SFX_Silence60 = 0x5C,
	SFX_Silence61 = 0x5D,
	SFX_Silence62 = 0x5E,
	SFX_Silence63 = 0x5F,
	SFX_Silence64 = 0x60,
	SFX_Silence65 = 0x61,
	SFX_Silence66 = 0x62,
	SFX_Silence67 = 0x63,
	SFX_Silence68 = 0x0,
	SFX_Silence69 = 0xA,
	SFX_Silence70 = 0xD,
	SFX_Silence71 = 0x13,
	SFX_Silence72 = 0x24,
	SFX_Silence73 = 0x7,
	SFX_Silence74 = 0x8,
	SFX_Silence75 = 0x9,
};

SOUND* SoundObject_Create(size_t size, unsigned long freq);
void SoundObject_Destroy(SOUND *sound);
void SoundObject_Lock(SOUND *sound, uint8_t **buffer, size_t *size);
void SoundObject_Unlock(SOUND *sound);
void SoundObject_SetPosition(SOUND *sound, size_t pos);
void SoundObject_SetFrequency(SOUND *sound, unsigned long freq);
void SoundObject_SetVolume(SOUND *sound, long volume);
void SoundObject_SetPan(SOUND *sound, long pan);
void SoundObject_Play(SOUND *sound, bool loops);
void SoundObject_Stop(SOUND *sound);

void initAudio();
void loadSounds();
void freeSounds();

void playSound(size_t sound_no, int soundMode = 1);
