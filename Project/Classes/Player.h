/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自PCommonShot类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Bullet;
class Enemy;
struct PlayerInfo
{
	friend class Player;
public:
	cocos2d::Vec2 dir;
	bool shift = false;
	bool shoot = false;
	bool _collect = true;
	int keyboardnum = 0;
private:
	float _hp = 10;
	float _v = 0;
	int _bombs = 0;
	int _bombs_cd = 0;
	int _powers = 100;
	int _timer = 0;
	int _angle = 0;
	int _bullet_cd = 0;
	int _invincibled = 0;
	int _invincibled_cd = 0;
	int _hit_cd = 0;
	bool _hit_flag = false;
	LONG64 _score = 0;
	LONG32 _score_get_max = 10000;
	LONG32 _graze = 0;
	int _graze_temp = 10;
};

struct Hitbox {
	cocos2d::Sprite* pdd1 = cocos2d::Sprite::create("pdd.png");
	cocos2d::Sprite* pdd2 = cocos2d::Sprite::create("pdd.png");
	float rot1 = 0;
	float rot2 = 0;
	float alpha = 0;
};

class Player : public cocos2d::Sprite {
	friend class Item;
public:
	friend class PCommonShot;
	static Player* create(const char *pszFileName);
	PlayerInfo info;
	Hitbox pdd;
	void DoOnCreate();
	void DoOnFrame();
	void DoDefaultAction();
	void Atk();
	void beHit(Bullet*);
	void beHit(Enemy*);
	void setInvincibled(int);
	void powerAdd(int);
	void powerDrop(int);
	void scoreAdd(LONG32);
	void grazeAdd(int);
	void setHitCd(int);
	LONG32 getScoreGetMax();
	LONG64 getScore();
	LONG32 getGraze();
	int getPower();
	float getHp();
	int getBombs();
	void setBomb();
private:
};

class PCommonShot : public cocos2d::Sprite {
public:
	static PCommonShot* create(const char *pszFileName);
	void PCommonShot::DoOnCreate(float);
	void PCommonShot::DoOnFrame();
	void PCommonShot::DoDefaultAction();
	void PCommonShot::setVelocit(float);
	void PCommonShot::setAngle(float);
	void PCommonShot::setDmg(float);
	float PCommonShot::getDmg();
	void PCommonShot::Hit(Player*, Enemy*);
protected:
	float _angle = 0;
	int _interval = 10;
	int _timer = 0;
	float _velocity = 0;
	float _dmg = 1;//子弹伤害
};

class PBomb : public PCommonShot {
public:
	static PBomb* create();
	void PBomb::DoDefaultAction();
	float vv;
	float ang;
};

#endif //__PLAYER_H__