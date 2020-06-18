/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include "Player.h"

#define PI acos(-1)

Player* Player::create(const char *filename)
{
	Player *sprite = new Player();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Player::DoOnCreate() {
	this->setTag(GROUP_PLAYER);
	pdd.pdd1->setPosition(convertToNodeSpace(this->getPosition()));
	pdd.pdd2->setPosition(convertToNodeSpace(this->getPosition()));
	pdd.pdd1->setOpacity(0);
	pdd.pdd2->setOpacity(0);
	this->addChild(pdd.pdd1, GROUP_PLAYER_PDD);
	this->addChild(pdd.pdd2, GROUP_PLAYER_PDD);
};
void Player::DoOnFrame() {

	Player::DoDefaultAction();
}

void Player::DoDefaultAction() {
	auto Move = cocos2d::CallFunc::create([=]()
	{
		auto now = this->getPosition();
		auto to = now;
		if (info.shift == false) {
			if (pdd.alpha > 0) pdd.alpha = 0;
			this->info._v = 6.0;
		}
		else {
			if (pdd.alpha < 255) pdd.alpha += 15;
			this->info._v = 2.5;
		}
		
		this->pdd.rot1 += 5;
		auto ang1 = this->pdd.rot1;
		auto rota1 = cocos2d::RotateTo::create((0.000001), -ang1);
		auto fade = cocos2d::FadeTo::create(0.00001, pdd.alpha);
		this->pdd.pdd1->runAction(cocos2d::Sequence::create(fade->clone(), rota1, nullptr));

		this->pdd.rot2 -= 5;
		auto ang2 = this->pdd.rot2;
		auto rota2 = cocos2d::RotateTo::create((0.000001), -ang2);
		this->pdd.pdd2->runAction(cocos2d::Sequence::create(fade, rota2, nullptr));
		
		switch (info.keyboardnum) {
		case 1:
			to.x -= this->info._v;
			if (info.shift == false) this->info._angle = 180;
			break;
		case 2:
			to.x += this->info._v;
			if (info.shift == false) this->info._angle = 0;
			break;
		case 4:
			to.y += this->info._v;
			if (info.shift == false) this->info._angle = 90;
			break;
		case 8:
			to.y -= this->info._v;
			if (info.shift == false) this->info._angle = 270;
			break;
		case 5:
			to.x -= this->info._v * sqrt(2) / 2.0;
			to.y += this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 135;
			break;
		case 9:
			to.x -= this->info._v * sqrt(2) / 2.0;
			to.y -= this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 225;
			break;
		case 6:
			to.x += this->info._v * sqrt(2) / 2.0;
			to.y += this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 45;
			break;
		case 10:
			to.x += this->info._v * sqrt(2) / 2.0;
			to.y -= this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 315;
			break;
		}
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(Move, delay, nullptr))));
}
void Player::Atk(cocos2d::Scene* scene) {
	auto shoot = cocos2d::CallFunc::create([=]() {
		if (this->info._bullet_cd > 0) {
			this->info._bullet_cd--;
			return;
		}
		if (this->info.shoot == false) return;
		this->info._bullet_cd = 10;
		auto bullet1 = PCommonShot::create("playerbullet.png");
		auto bullet2 = PCommonShot::create("playerbullet.png");
		bullet1->setPosition(this->getPosition());
		bullet2->setPosition(this->getPosition());
		bullet1->setAngle(this->info._angle + 2);
		bullet2->setAngle(this->info._angle - 2);
		bullet1->setVelocit(8);
		bullet2->setVelocit(8);
		auto physicsBody1 = cocos2d::PhysicsBody::createCircle(1.0f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
		physicsBody1->setDynamic(false);
		physicsBody1->setContactTestBitmask(0xFFFFFFFF);
		auto physicsBody2 = cocos2d::PhysicsBody::createCircle(1.0f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
		physicsBody2->setDynamic(false);
		physicsBody2->setContactTestBitmask(0xFFFFFFFF);
		bullet1->setPhysicsBody(physicsBody1);
		bullet2->setPhysicsBody(physicsBody2);
		scene->addChild(bullet1, GROUP_PLAYER_BULLET);
		scene->addChild(bullet2, GROUP_PLAYER_BULLET);
		bullet1->setTag(GROUP_PLAYER_BULLET);
		bullet2->setTag(GROUP_PLAYER_BULLET);
		bullet1->DoOnFrame();
		bullet2->DoOnFrame();
	});
	auto delay_shoot = cocos2d::DelayTime::create(1.0/30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shoot, delay_shoot, nullptr))));
}

void Player::beHit(Bullet * dankumu)
{
	if (dankumu->destroyable == true) {
		auto remove = cocos2d::RemoveSelf::create();
		dankumu->runAction(remove);
	}
	//this->hp -= dankumu->getDmg();
}

PCommonShot* PCommonShot::create(const char *filename)
{
	PCommonShot *sprite = new PCommonShot();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void PCommonShot::DoOnCreate() {}
void PCommonShot::DoOnFrame() {
	this->DoDefaultAction();
}

void PCommonShot::DoDefaultAction() {
	auto Move = cocos2d::CallFunc::create([=]() {
		auto now = this->getPosition();
		auto to = cocos2d::Vec2(0, 0);
		to.x += this->_velocity * cos(this->_angle / 180.0 * PI);
		to.y += this->_velocity * sin(this->_angle / 180.0 * PI);;
		auto move = cocos2d::MoveBy::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(Move, delay, nullptr))));
}

void PCommonShot::setVelocit(float v) {
	this->_velocity = v;
}

void PCommonShot::setAngle(float r) {
	this->_angle = r;
	auto rota = cocos2d::RotateTo::create((0.0), -r);
	this->runAction(cocos2d::Sequence::create(rota, nullptr));
}

void PCommonShot::setDmg(float d) {
	this->_dmg = d;
}

void PCommonShot::Hit(cocos2d::Sprite* enemy)
{
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
	//enemy->beHit(this->_dmg);
}
