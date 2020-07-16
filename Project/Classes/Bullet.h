/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Headers.h"

//简单子弹
class Bullet : public cocos2d::Sprite {
public:
	static Bullet* create(const char *pszFileName);
	void DoOnCreate(cocos2d::Sprite*, float);
	void DoOnFrame();
	void DoDefaultAction();
	void setVelocit(float);
	void setAngle(float);//接受的单位为角度
	void setRot(float);
	void setRotVelocity(float);
	void setRebound(bool);
	void setShuttle(bool);
	void setDestroyable(bool);
	void setBound(bool);
	void setAim(bool);
	void setNavi(bool);
	void setAcceleration(float);
	void setAccAngle(float);
	void setDmg(float);
	void setvMax(float);
	float getAngle();
	bool getDestoryable();
	void beGraze(Player*);
	float getDmg();
protected:
	//子弹速度决定于分速度，与velocity的值无直接关系
	cocos2d::Vec2 v;//子弹在x轴方向和y轴方向上的分速度
	float velocity = 0;//子弹速度，单位：像素/帧
	float vMax = 9999;//子弹最大速度，单位：像素/帧
	float angle = 0;//子弹角度，以弧度存储
	float rot = 0;//子弹朝向，以弧度存储
	float rotvelocity = 0;//子弹朝向的旋转速度，以角度度存储
	float a = 0;//子弹加速度
	float ar = 0;//子弹加速度的角度，以角度存储
	int timer = 0;//子弹的内置计时器
	float dmg = 1;//子弹伤害
	int temp1 = 0;
	int temp2 = 0;
	bool flag = false;
	bool begraze = false;//是否被擦弹
	bool aim = false;//是否对着自机
	bool navi = true;//是否保持朝向与角度一致
	bool rebound = false;//是否反弹
	bool shuttle = false;//是否穿板
	bool bound = true;//是否出屏消弹
	bool destroyable = true;//是否可被摧毁
};//By LLS

//子弹组尝试

/*子弹组不属于sprite，该处暂时作废
class Bullets :public Bullet {
public:
	static Bullets* create(const char *pszFileName, int num);
	void Bullets::DoOnFrame();
	void Bullets::DoOnCreate();
	int num;//子弹数量
	float velocity_end = 0;//子弹速度，单位：像素/帧
	float angle_spread = 0;//子弹角度，单位：角度
	float interval = 0;//子弹发射间隔，单位：秒
};//By LLS
*/

//自定义子弹的声明请写在此处

class jiaocha :public Bullet {
public:
	static jiaocha* create(const char *pszFileName);
	void DoOnCreate(float, float, int);
	void DoOnFrame(float);
	int temp3 = 0;
};//By LLS

class Follow :public Bullet {
public:
	static Follow* create(const char *pszFileName);
	void DoOnFrame(Player*);
};//By LLS

class Speed :public Bullet {
public:
	static Speed* create(const char *pszFileName);
	void DoOnFrame(Player*);
	float vv;
};//By LLS


/*
class LaserSmall : public Bullet {
public:
	static LaserSmall* create(const char *pszFileName);
	void DoOnCreate(cocos2d::Sprite*, float);
	void DoOnFrame();
	bool destroyable = false;//是否可被摧毁
};
*/
#endif //__BULLET_H__