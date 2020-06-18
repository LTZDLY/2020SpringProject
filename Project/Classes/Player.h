/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自PCommonShot类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define GROUP_PLAYER_BULLET 32
#define GROUP_PLAYER_PDD 1024
#define GROUP_PLAYER 64
#define GROUP_ITEM 128

#include "cocos2d.h"
#include "Bullet.h"

struct PlayerInfo
{
	friend class Player;
public:
	cocos2d::Vec2 dir;
	bool shift = false;
	bool shoot = false;
	int keyboardnum = 0;
private:
	float _v = 0;
	int _bombs = 0;
	int _players = 0;
	int _powers = 0;
	int _timer = 0;
	int _angle = 0;
	int _bullet_cd = 0;
};

struct Hitbox {
	cocos2d::Sprite* pdd1 = cocos2d::Sprite::create("pdd.png");
	cocos2d::Sprite* pdd2 = cocos2d::Sprite::create("pdd.png");
	float rot1 = 0;
	float rot2 = 0;
	float alpha = 0;
};

class Player : public cocos2d::Sprite {
public:
	friend class PCommonShot;
	static Player* create(const char *pszFileName);
	Hitbox pdd;
	void DoOnCreate();
	void DoOnFrame();
	void DoDefaultAction();
	void Atk(cocos2d::Scene*);
	void beHit(Bullet*);
	PlayerInfo info;
};

class PCommonShot : public cocos2d::Sprite {
public:
	static PCommonShot* create(const char *pszFileName);
	void PCommonShot::DoOnCreate();
	void PCommonShot::DoOnFrame();
	void PCommonShot::DoDefaultAction();
	void PCommonShot::setVelocit(float);
	void PCommonShot::setAngle(float);
	void PCommonShot::setDmg(float);
	void PCommonShot::Hit(cocos2d::Sprite*);
private:
	int _angle = 0;
	int _interval = 10;
	int _timer = 0;
	float _velocity = 0;
	float _dmg = 0;//子弹伤害
};


#endif //__PLAYER_H__