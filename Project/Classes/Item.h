/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

#define GROUP_ITEM 128
#define GROUP_DOOR 8

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

private:
};
#endif //__ITEM_H__