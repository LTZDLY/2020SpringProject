/*
	����һ����ʱ�쳣��ª�Ĺ�����
	�Զ�����˼̳���Enemy
	ע������DoOnCreated DoOnFrame
	pwq from ddlǰ��pfr
*/

#include "Enemy.h"

Enemy* Enemy::create(const char* pszFileName)
{
	Enemy* enemyA = new Enemy();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void Enemy::setHP(float hp)
{
	this->healthPoint = hp;
}

float Enemy::getHP(float hp)
{
	return this->healthPoint;
}

void Enemy::DoOnCreated(){ }

void Enemy::DoOnFrame(){ }

myEnemy* myEnemy::create(const char* pszFileName)
{
	myEnemy* enemyA = new myEnemy();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void myEnemy::DoOnCreated()//����˲��ִ�ж���
{
	auto  rotateBy = cocos2d::RotateBy::create(0.5f, 180.0f);
	auto sequence = cocos2d::Sequence::create(rotateBy, rotateBy->clone(), nullptr);
	this->runAction(sequence);
}

void myEnemy::DoOnFrame()//ÿ��һ��ʱ������ƶ�
{
	srand((unsigned)(time(NULL)));
	auto x = cocos2d::random(1.0, 10.0);
	srand((unsigned)(time(NULL)));
	auto y = cocos2d::random(1.0, 10.0);
	auto move1 = cocos2d::MoveBy::create(x/2, cocos2d::Vec2(x, 0));
	auto move2 = cocos2d::MoveBy::create(y/2, cocos2d::Vec2(0, y));
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(move1, move2, delay,nullptr))));
}
