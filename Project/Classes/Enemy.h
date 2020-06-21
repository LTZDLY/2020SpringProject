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
	virtual void DoOnCreated(int);//生成瞬间执行动作
	virtual void DoOnFrame();//每隔一段时间随机移动
	void beHit(PCommonShot* pb, Player* thePlayer);
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
protected:
};

class littleRed : public Enemy
{
public:
	static littleRed* create(const char* pszFileName);
	virtual void DoOnFrame(Player*);
protected:
};
#endif