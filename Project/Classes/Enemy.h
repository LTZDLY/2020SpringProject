/*
	����һ����ʱ�쳣��ª�Ĺ�����
	�Զ�����˼̳���Enemy
	ע������DoOnCreated DoOnFrame
	pwq from ddlǰ��pfr
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
	virtual void DoOnCreated();//����˲��ִ�ж���
	virtual void DoOnFrame();//ÿ��һ��ʱ������ƶ�
protected:
	float healthPoint = 0;//����ֵ
};

class myEnemy : public Enemy
{
public:
	static myEnemy* create(const char* pszFileName);
	virtual void DoOnCreated();
	virtual void DoOnFrame();
};
#endif
