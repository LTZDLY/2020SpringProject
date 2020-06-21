/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Player.h"

#define GROUP_ITEM 128
#define GROUP_DOOR 8
#define GROUP_ITEM_P_POINT 1
#define GROUP_ITEM_BLUE_POINT 2
#define GROUP_ITEM_BOMB 3
#define GROUP_ITEM_LIFE 4
#define GROUP_ITEM_GREENPOINT 5
#define GROUP_BARRIERS 7

class Barriers : public cocos2d::Sprite {
public:
	static Barriers* create(const char *pszFileName);
	void DoOnCreate(int);
	//void DoOnFrame();
private:
	int num_B;
};

class Door : public cocos2d::Sprite {
public:
	static Door* create(const char *pszFileName);
	void DoOnCreate(int);
	void DoOnFrame();
	int getNum();
private:
	int num = -1;
};

class Item : public cocos2d::Sprite {
public:
	static Item* create(const char *pszFileName);
	virtual void DoOnCreate();
	virtual void DoOnFrame(Player*);
	virtual void DoOnCollect();
	virtual void setNum(int);
	virtual int getNum();
private:
	int _num;
};

class P_Point : public Item {
public:
	static P_Point* create();
	virtual void DoOnCollect(Player*);
};
class BluePoint : public Item {
public:
	static BluePoint* create();
	virtual void DoOnCollect(Player*);
};
class LifePiece: public Item {
public:
	static LifePiece* create();
	virtual void DoOnCollect(Player*);
};
class Bomb : public Item {
public:
	static Bomb* create();
	virtual void DoOnCollect(Player*);
};
class GreenPoint : public Item {
public:
	static GreenPoint* create();
	virtual void DoOnCreate();
	virtual void DoOnFrame(Player*);
	virtual void DoOnCollect(Player*);
};
#endif //__ITEM_H__