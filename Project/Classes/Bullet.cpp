/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include"Bullet.h"
#include "AudioEngine.h"

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
void Bullet::DoOnCreate(cocos2d::Sprite* player, float hitbox) {
	if (this->aim == true) {
		auto from = this->getPosition();
		auto to = player->getPosition();
		auto ang = atan((from.x - to.x) / (from.y - to.y));
		if (from.x > to.x)ang += PI / 2;
		else ang = PI / 2 + ang;
		if (from.y > to.y)ang = -ang;
		else ang = PI - ang;
		this->angle += ang;
		this->setAngle(angle / PI * 180);
	}
	auto physicsBody = cocos2d::PhysicsBody::createCircle(hitbox, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x41);
	physicsBody->setCollisionBitmask(0x41);
	physicsBody->setCategoryBitmask(0x08);
	this->setPhysicsBody(physicsBody);
	this->setTag(GROUP_ENEMY_BULLET);
}
void Bullet::DoOnFrame()
{
	Bullet::DoDefaultAction();
	auto a = cocos2d::CallFunc::create([=]() {
		auto now = this->getPosition();
		if (this->rebound == true && flag == false) {
			if (now.x < 50) {
				this->setAngle(180 - this->angle / PI * 180);
				flag = true;
				CCLOG("Rebound");
			}
			else if (now.x > 303){
				this->setAngle(180 - this->angle / PI * 180);
				flag = true;
				CCLOG("Rebound");
			}
			else if (now.y < 13){
				this->setAngle(-this->angle / PI * 180);
				flag = true;
				CCLOG("Rebound");
			}
			else if (now.y > 308) {
				this->setAngle(-this->angle / PI * 180);
				flag = true;
				CCLOG("Rebound");
			}
		}/*
		else if (this->shuttle == true && flag == false) {
			if (now.x < 39) {
				this->setPosition(cocos2d::Vec2(313, now.y));
				flag = true;
				CCLOG("Shuttle");
			}
			else if (now.x > 313) {
				this->setPosition(cocos2d::Vec2(39, now.y));
				flag = true;
				CCLOG("Shuttle");
			}
			else if (now.y < 2) {
				this->setPosition(cocos2d::Vec2(now.x, 318));
				flag = true;
				CCLOG("Shuttle");
			}
			else if (now.y > 318) {
				this->setPosition(cocos2d::Vec2(now.x, 2));
				flag = true;
				CCLOG("Shuttle");
			}
		}*/
	});
	auto delay = cocos2d::DelayTime::create(1.0 / 30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(a, delay, nullptr))));
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
		auto now = this->getPosition();
		auto to = now;
		to.x += this->v.x;
		to.y += this->v.y;
		auto move = cocos2d::MoveTo::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
		if (this->navi == true)
		{
			if (this->v.x != 0 || this->v.y != 0) 
			{
				auto ang = atan(this->v.y / this->v.x) / acos(-1.0) * 180;
				auto rota = cocos2d::RotateTo::create((0.0), -ang);
				this->runAction(cocos2d::Sequence::create(rota, nullptr));
			}
		}
		else if (this->rotvelocity != 0) 
		{
			this->rot += this->rotvelocity;
			auto rota = cocos2d::RotateBy::create((0.0), -this->rotvelocity);
			this->runAction(cocos2d::Sequence::create(rota, nullptr));
		}
		if (this->a != 0) 
		{
			this->v.x += this->a * cos(this->ar);
			this->v.y += this->a * sin(this->ar);
		}
		if (this->bound == true && (now.x < 0 || now.x > 350 || now.y < -30 || now.y > 350)) {
			auto remove = cocos2d::RemoveSelf::create();
			this->runAction(remove);
			CCLOG("destory");
		}
	});
	auto b = cocos2d::CallFunc::create([=]() {
		this->timer++;
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	auto delay_b = cocos2d::DelayTime::create((1.0 / 60.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(a, delay, nullptr))));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(b, delay_b, nullptr))));
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
	auto v = this->velocity;
	this->v.x = v * cos(this->angle);
	this->v.y = v * sin(this->angle);
}
void Bullet::setRot(float r) 
{
	auto rota = cocos2d::RotateTo::create((0.0), -r);
	this->runAction(cocos2d::Sequence::create(rota, nullptr));
	this->rot = r;
}
void Bullet::setRotVelocity(float rv) 
{
	this->rotvelocity = rv;
}
void Bullet::setRebound(bool t) { this->rebound = t; }
void Bullet::setShuttle(bool t) { this->shuttle = t; }
void Bullet::setAim(bool t) { this->aim = t; }
void Bullet::setNavi(bool t) { this->navi = t; }
void Bullet::setAcceleration(float a) 
{
	this->a = a;
}
void Bullet::setAccAngle(float r) 
{
	r = r * PI / 180;
	this->ar = r;
}

void Bullet::setDmg(float d)
{
	this->dmg = d;
}
void Bullet::setDestroyable(bool f) { this->destroyable = f; }
void Bullet::setBound(bool f) { this->bound = f; }
float Bullet::getAngle() { return this->angle; }
bool Bullet::getDestoryable() { return this->destroyable; }
void Bullet::beGraze(Player* player){
	if (this->begraze == true) return;
	cocos2d::AudioEngine::play2d("music/graze.mp3", false, 0.2f);
	player->grazeAdd(1);
	this->begraze = true;
}

float Bullet::getDmg() { return dmg; }

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
	auto repeat = cocos2d::CallFunc::create([=]() {
		auto aa = cocos2d::RemoveSelf::create();
		if (this->timer == 240) this->runAction(aa);
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(repeat, delay, nullptr))));
}
/*
LaserSmall* LaserSmall::create(const char *filename)
{
	LaserSmall *sprite = new LaserSmall();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void LaserSmall::DoOnCreate(){
	auto physicsBody = cocos2d::PhysicsBody::createBox(this->getBoundingBox(), cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x41);
	physicsBody->setCollisionBitmask(0x41);
	physicsBody->setCategoryBitmask(0x08);
	this->setPhysicsBody(physicsBody);
	this->setTag(GROUP_ENEMY_BULLET);
}*/