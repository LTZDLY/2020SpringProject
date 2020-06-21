/*
	这是一个暂时异常简陋的怪物类
	自定义敌人继承自Enemy
	注意重载DoOnCreated DoOnFrame
	pwq from ddl前的pfr
*/

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Headers.h"

struct itemList {
	int pNum = 0;
	int blueNum = 0;
	int bombNum = 0;
	int lifeNum = 0;
};

class Enemy : public cocos2d::Sprite
{
public:
	static Enemy* create(const char* pszFileName);
	void setHP(float hp);
	float getHP(float hp);
	virtual void DoOnCreated(float, float);//生成瞬间执行动作
	virtual void DoOnFrame();//每隔一段时间随机移动
	void beHit(float dmg, Player* thePlayer, int&);
	void DoOnDestroy(Player* thePlayer);
	//template <class T> void Drop(T, Player*);
protected:
	itemList itemsDrop;
	float healthPoint = 0;//生命值
	cocos2d::SpriteFrameCache* sf = cocos2d::SpriteFrameCache::getInstance();
};

class myEnemy : public Enemy
{
public:
	static myEnemy* create(const char* pszFileName);
	virtual void DoOnCreated();
	virtual void DoOnFrame();
};
class chaseEnemy : public Enemy
{
public:
	static chaseEnemy* create();
	virtual void DoOnFrame(Player*);
	float ang = 0;
protected:
};

class littleRed : public Enemy
{
public:
	static littleRed* create();
	virtual void DoOnFrame(Player*, int);
	float a = 0;
protected:
};

class littleGreen : public Enemy
{
public:
	static littleGreen* create();
	virtual void DoOnFrame(Player*, int);
	float a = 0;
protected:
};

class bigBound : public Enemy
{
public:
	static bigBound* create();
	virtual void DoOnFrame(Player*, int);
	float a = 0;
protected:
};

class bigCross : public Enemy
{
public:
	static bigCross* create();
	virtual void DoOnFrame(Player*, int);
	float temp1;
	float temp2;
protected:
};

class midRed : public Enemy
{
public:
	static midRed* create();
	virtual void DoOnFrame(Player*, int);
	float temp1;
protected:
};

class bigBloom : public Enemy
{
public:
	static bigBloom* create();
	virtual void DoOnFrame(Player*, int);
	float temp0;
	float temp1;
	float temp2;
	float temp3;
	float temp4;
	float temp5 = 10;
protected:
};

class Boss1 : public Enemy
{
public:
	static Boss1* create();
	virtual void DoOnFrame(Player*);
	float rr;
	float a;
	float b;
	float r;
	float now_ang;
protected:
};

class Boss2 : public Enemy
{
public:
	static Boss2* create();
	virtual void DoOnFrame(Player*);
	float temp1;
	float temp2;
	float temp3;
protected:
};

class Boss3 : public Enemy
{
public:
	static Boss3* create();
	virtual void DoOnFrame(Player*);
	float temp1;
	float temp2;
	float temp3;
	float temp5;
	int temp4;
protected:
};
#endif