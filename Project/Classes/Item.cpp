/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include "Item.h"

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
	physicsbody->setContactTestBitmask(1);
	physicsbody->setCollisionBitmask(1);
	physicsbody->setCategoryBitmask(1);
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
