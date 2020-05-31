/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include"Bullet.h"

#define PI (acos(-1))

Bullet* Bullet::create(const char *filename)
{
	Bullet *sprite = new Bullet();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void Bullet::DoOnCreate() {}
void Bullet::DoOnFrame()
{
	Bullet::DoDefaultAction();
	/*
	if 出版==ture and 反弹==ture and flag == 0
	反弹;
	flag = 1;
	*/
	/*
	if 出版==ture and 穿板==ture and flag == 0
	穿板;
	flag = 1;
	*/
}
void Bullet::DoDefaultAction() 
{
	if (this->rotvelocity != 0) 
	{
		this->navi = false;
	}
	auto a = cocos2d::CallFunc::create([=]() 
	{
		timer++;
		auto now = this->getPosition();
		auto to = now;
		to.x += this->v.x;
		to.y += this->v.y;
		auto move = cocos2d::MoveTo::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
		if (this->navi == true) 
		{
			auto ang = atan(this->v.y / this->v.x) / acos(-1.0) * 180;
			auto rota = cocos2d::RotateTo::create((0.0), -ang);
			this->runAction(cocos2d::Sequence::create(rota, nullptr));
		}
		else if (this->rotvelocity != 0) 
		{
			this->rot += this->rotvelocity;
			auto ang = this->rot;
			auto rota = cocos2d::RotateTo::create((0.0), -ang);
			this->runAction(cocos2d::Sequence::create(rota, nullptr));
		}
		if (this->a != 0) 
		{
			this->v.x += this->a * cos(this->ar);
			this->v.y += this->a * sin(this->ar);
		}
		/*
		if 出版==ture and 出屏消弹==ture
		removeself
		*/
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(a, delay, nullptr))));
}
void Bullet::setVelocit(float v) 
{
	this->velocity = v;
	this->v.x = v * cos(this->angle);
	this->v.y = v * sin(this->angle);
}
void Bullet::setAngle(float r) 
{
	r = r * PI / 180;
	this->angle = r;
}
void Bullet::setRot(float r) 
{
	r = r * PI / 180;
	this->rot = r;
}
void Bullet::setRotVelocity(float rv) 
{
	this->rotvelocity = rv;
}
void Bullet::setAcceleration(float a) 
{
	this->a = a;
}
void Bullet::setAccAngle(float r) 
{
	r = r * PI / 180;
	this->ar = r;
}

/*简单子弹组
void CreateBullets(const char *pszFileName, cocos2d::Sprite* _enemy, cocos2d::Scene* a, int num, float interval, float velocity_begin, float velocity_end, float angle, float angle_spread, bool aim) {
	//若task嵌套的问题若无法解决，则此功能无法实现。
	static float v = velocity_begin;
	static float r = angle;
	auto delay = cocos2d::DelayTime::create(interval);
	auto shootStar = cocos2d::CallFunc::create([=]() {
		Bullet *dankumu = Bullet::create(pszFileName);
		dankumu->setPosition(_enemy->getPosition());
		dankumu->setAngle(180);
		dankumu->setVelocit(3);
		dankumu->setRotVelocity(20);
		dankumu->DoOnFrame();
		a->addChild(dankumu);
	});
	auto updata = cocos2d::CallFunc::create([=]() {
		v++;
	});
}
*/
/*子弹组不属于sprite，该处暂时作废
Bullets* Bullets::create(const char *filename, int num)
{
	Bullets *sprite = new Bullets();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
*/

//自定义子弹类的实现请写在后面
jiaocha* jiaocha::create(const char *filename)
{
	jiaocha *sprite = new jiaocha();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void jiaocha::DoOnCreate(float v, float r, int a)
{
	this->temp1 = v;
	this->setAngle(r);
	this->setVelocit(v);
	auto task = cocos2d::CallFunc::create([=]() {
		this->temp1 -= this->temp1 / 135;
		this->setVelocit(this->temp1);
	});
	auto task2 = cocos2d::CallFunc::create([=]() {
		this->setAngle(r + 70 * (2 * (a % 2) - 1));
		this->setVelocit(1);
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 60.0));
	auto se = cocos2d::Sequence::create(task, delay, nullptr);
	auto re = cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(se), 90);
	auto se2 = cocos2d::Sequence::create(re, task2, nullptr);
	this->runAction(se2);
}

void jiaocha::DoOnFrame()
{
	this->DoDefaultAction();
}
