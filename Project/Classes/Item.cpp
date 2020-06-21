/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include "Item.h"

Barriers* Barriers::create(const char *filename)
{
	Barriers *sprite = new Barriers();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Barriers::DoOnCreate(int n) {
	num_B = n;
	this->setTag(GROUP_BARRIERS);
	auto physicsbody = cocos2d::PhysicsBody::createCircle(30.0f, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
	physicsbody->setContactTestBitmask(0x0A);
	physicsbody->setCollisionBitmask(0x9F);
	physicsbody->setCategoryBitmask(0x80);
	physicsbody->setTag(GROUP_BARRIERS);
	physicsbody->setDynamic(false);
	physicsbody->setGravityEnable(false);
	this->setPhysicsBody(physicsbody);
}

Door* Door::create(const char *filename)
{
	Door *sprite = new Door();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Door::DoOnCreate(int n) {
	num = n;
	this->setTag(GROUP_DOOR);
	auto physicsbody = cocos2d::PhysicsBody::createCircle(3.0f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsbody->setContactTestBitmask(0x01);
	physicsbody->setCollisionBitmask(0x01);
	physicsbody->setCategoryBitmask(0x20);
	physicsbody->setTag(GROUP_DOOR);
	physicsbody->setDynamic(true);
	physicsbody->setGravityEnable(false);
	this->setPhysicsBody(physicsbody);
}
void Door::DoOnFrame() {

}
int Door::getNum() { return num; }


Item* Item::create(const char *filename)
{
	Item *sprite = new Item();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Item::DoOnCreate() {
	this->setTag(GROUP_ITEM);
	float r = cocos2d::random(0.0, 2 * acos(-1));
	float v = cocos2d::random(5.0, 10.0);
	float x = v * 5;
	cocos2d::Vec2 to = { x*cos(r),x*sin(r) };
	auto move_ease_in = cocos2d::EaseExponentialOut::create(cocos2d::MoveBy::create(1.5, to));
	this->runAction(move_ease_in);

	auto physicsbody = cocos2d::PhysicsBody::createCircle(5.0f, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
	physicsbody->setContactTestBitmask(0x05);
	physicsbody->setCollisionBitmask(0x95);
	physicsbody->setCategoryBitmask(0x10);
	physicsbody->setTag(GROUP_ITEM);
	physicsbody->setDynamic(true);
	physicsbody->setGravityEnable(false);
	this->setPhysicsBody(physicsbody);

}

void Item::DoOnFrame(Player* player) {
	auto a = cocos2d::CallFunc::create([=] {
		auto from = this->getPosition();
		auto to = player->getPosition();
		auto distance = sqrt(pow((from.x - to.x), 2) + pow((from.y - to.y), 2));
		if (player->info._collect == true && distance < 50) {
			auto sec = to - from;
			sec.normalize();
			sec *= 5;
			auto move = cocos2d::MoveBy::create(1.0 / 30.0, sec);
			this->runAction(move);
		}
	});
	auto delay = cocos2d::DelayTime::create(1.0/30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(a, delay, nullptr))));
}
void Item::DoOnCollect() {}
int Item::getNum() { return _num; }

void Item::setNum(int num) { _num = num; }

P_Point* P_Point::create() {
	const char *filename = "Images/item_01.png";
	P_Point *sprite = new P_Point();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->setNum(GROUP_ITEM_P_POINT);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void P_Point::DoOnCollect(Player* _player) {
	_player->powerAdd(5);
	_player->scoreAdd(10000);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
}

BluePoint* BluePoint::create() {
	const char *filename = "Images/item_02.png";
	BluePoint *sprite = new BluePoint();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->setNum(GROUP_ITEM_BLUE_POINT);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void BluePoint::DoOnCollect(Player* _player) {
	_player->scoreAdd(_player->getScoreGetMax());
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
}

LifePiece* LifePiece::create() {
	const char *filename = "Images/item_05.png";
	LifePiece *sprite = new LifePiece();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->setNum(GROUP_ITEM_LIFE);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void LifePiece::DoOnCollect(Player* _player) {
	_player->addHp(1);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
}

Bomb* Bomb::create() {
	const char *filename = "Images/item_18.png";
	Bomb *sprite = new Bomb();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->setNum(GROUP_ITEM_BOMB);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void Bomb::DoOnCollect(Player* _player) {
	_player->addBomb(1);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
}

GreenPoint* GreenPoint::create() {
	const char *filename = "Images/item_14.png";
	GreenPoint *sprite = new GreenPoint();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		sprite->setNum(GROUP_ITEM_GREENPOINT);
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
void GreenPoint::DoOnCreate() {
	this->setTag(GROUP_ITEM);

	auto physicsbody = cocos2d::PhysicsBody::createCircle(5.0f, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
	physicsbody->setContactTestBitmask(0x05);
	physicsbody->setCollisionBitmask(0x15);
	physicsbody->setCategoryBitmask(0x10);
	physicsbody->setTag(GROUP_ITEM);
	physicsbody->setDynamic(true);
	physicsbody->setGravityEnable(false);
	this->setPhysicsBody(physicsbody);

}
void GreenPoint::DoOnFrame(Player* player) {
	auto a = cocos2d::CallFunc::create([=] {
		auto from = this->getPosition();
		auto to = player->getPosition();
		if (player->info._collect == true) {
			auto sec = to - from;
			sec.normalize();
			sec *= 10;
			auto move = cocos2d::MoveBy::create(1.0 / 30.0, sec);
			this->runAction(move);
		}
	});
	auto delay = cocos2d::DelayTime::create(1.0 / 30.0);
	auto b = cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(a, delay, nullptr)));
	this->runAction(b);
}
void GreenPoint::DoOnCollect(Player* _player) {
	_player->addMaxPoint(10);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
}