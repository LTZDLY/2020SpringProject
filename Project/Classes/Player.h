/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

struct Hitbox {
	cocos2d::Sprite* pdd1 = cocos2d::Sprite::create("pdd.png");
	cocos2d::Sprite* pdd2 = cocos2d::Sprite::create("pdd.png");
	float rot1 = 0;
	float rot2 = 0;
	float alpha = 255;
};

class Player : public cocos2d::Sprite {
public:
	static Player* create(const char *pszFileName);
	Hitbox pdd;
	void DoOnFrame();
	void DoDefaultAction();
	bool shift = false;
	int keyboardnum = 0;
	float v_ = 0;
private:

};




#endif //__PLAYER_H__