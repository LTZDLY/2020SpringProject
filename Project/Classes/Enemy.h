/*
	这是一个暂时异常简陋的怪物类
	自定义敌人继承自Enemy
	注意重载DoOnCreated DoOnFrame
	pwq from ddl前的pfr
*/

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
	static Enemy* create(const char* pszFileName);
	void setHP(float hp);
	float getHP(float hp);
	virtual void DoOnCreated();//生成瞬间执行动作
	virtual void DoOnFrame();//每隔一段时间随机移动
protected:
	float healthPoint = 0;//生命值
};

class myEnemy : public Enemy
{
public:
	static myEnemy* create(const char* pszFileName);
	virtual void DoOnCreated();
	virtual void DoOnFrame();
};
#endif
