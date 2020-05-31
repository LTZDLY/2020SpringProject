/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "Bullet.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void HelloWorld::addbullet(float dt) {


	// 2.获取触摸点的坐标，并计算这个点相对于_player的偏移量。
	Vec2 touchLocation = Vec2(100,100);
	Vec2 offset = touchLocation - this->getPosition();
	// 如果offset的x值是负值，这表明玩家正试图朝后射击。在本游戏中这是不允许的。
	// 3.在玩家所在的位置创建一个飞镖，将其添加到场景中。
	auto projectile = Sprite::create("grain.png");
	projectile->setPosition(this->getPosition());
	auto physicsBody = PhysicsBody::createBox(projectile->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	projectile->setPhysicsBody(physicsBody);
	projectile->setTag(0);
	this->addChild(projectile);

	// 4.将偏移量转化为单位向量，即长度为1的向量。
	offset.normalize();
	// 将其乘以1000，你就获得了一个指向用户触屏方向的长度为1000的向量。为什么是1000呢？因为长度应当足以超过当前分辨率下屏幕的边界。
	auto shootAmount = offset * 1000;
	// 将此向量添加到飞镖的位置上去，这样你就有了一个目标位置。
	auto realDest = shootAmount + projectile->getPosition();

	// 5.创建一个动作，将飞镖在2秒内移动到目标位置，然后将它从场景中移除。
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));

}

void HelloWorld::addMonster(float dt) {
	// Add monster

	auto winSize = Director::getInstance()->getVisibleSize();

	auto _enemy = Sprite::create("Monster.png");
	_enemy->setPosition(Vec2(winSize.width * 0.8, winSize.height * 0.5));
	this->addChild(_enemy);

	auto physicsBody = PhysicsBody::createBox(_enemy->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_enemy->setPhysicsBody(physicsBody);
	
	/*
	//测试使用callfunc执行发弹动作，成功
	//测试task套循环，成功
	float r = acos(-1)/4;
	this->temp2 = 5 * acos(-1) / 180;
	this->temp3 = 0.133 * acos(-1) / 180;
	this->temp4 = 0;
	auto shootStar2 = CallFunc::create([=]() {
		auto shootStar = CallFunc::create([=]() {
			auto a = _enemy->getPosition();
			a.x += 20 * (float)cos(this->temp * r);
			a.y += 20 * (float)sin(this->temp * r);
			auto x = cos((acos(-1)));
			Vec2 b = { a.x + 400 * (float)cos(this->temp * r),a.y + 400 * (float)sin(this->temp * r) };
			auto bullet = Sprite::create("grain.png");
			bullet->setPosition(a);
			this->addChild(bullet);
			bullet->setRotation(-1 * this->temp * r * 180 / acos(-1));
			auto projectileMove = MoveTo::create(5, b);
			auto projectileRemove = RemoveSelf::create();
			bullet->runAction(Sequence::create(projectileMove, projectileRemove, nullptr));
			this->temp++;
		});
		this->temp = this->temp4;
		this->temp2 -= this->temp3;
		this->temp4 -= this->temp2;
		auto delay_no = cocos2d::DelayTime::create(0.00000001);
		_enemy->runAction(Repeat::create(static_cast<Sequence *>(Sequence::create(shootStar, delay_no, nullptr)), 8));
	});
	auto delay_no = cocos2d::DelayTime::create(0.00000000001);
	auto delay = cocos2d::DelayTime::create(0.05);
	_enemy->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(shootStar2, delay, nullptr))));
	//以上为第一次试验代码，请勿作为将来写代码的参考
	*/

	/*
	//测试简单子弹和高光效果，成功
	auto shootStar = CallFunc::create([=]() {
		Bullet *dankumu = Bullet::create("bigball_dark.png");
		dankumu->setPosition(_enemy->getPosition());
		dankumu->setAngle(120);
		dankumu->setVelocit(5);
		dankumu->setRotVelocity(10);
		dankumu->setAcceleration(0.1);
		dankumu->setAccAngle(-90);
		dankumu->DoOnFrame();
		this->addChild(dankumu);
		BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
		dankumu->setBlendFunc(cbl);
	});
	auto delay = cocos2d::DelayTime::create(0.5);
	_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));
	//简单子弹的调用如上所示
	*/

	/*
	//测试lstg中的task嵌套效果，未完成
	//测试自定义子弹和task套循环，成功
	auto shootStar2 = CallFunc::create([=]() {
		auto shootStar = CallFunc::create([=]() {
			jiaocha* dankumu = jiaocha::create("grain.png");
			dankumu->setPosition(_enemy->getPosition());
			dankumu->DoOnCreate(4, temp, temp2);
			dankumu->DoOnFrame();
			this->addChild(dankumu);
			temp2++;
			temp += 360.0 / 100.0;
		});
		auto delay_no = cocos2d::DelayTime::create(0.000000001);
		auto kaihua = Repeat::create(static_cast<Sequence *>(Sequence::create(shootStar, delay_no, nullptr)), 100);
		_enemy->runAction(kaihua);
	});
	auto delay = cocos2d::DelayTime::create(2);
	_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar2, delay, nullptr))));
	//自定义子弹的调用如上所示
	*/

	/*

	生成小怪
	小怪执行动作序列（生成弹幕）

	*/


}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	// My code here

	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// set Background with grey colour
	auto background = DrawNode::create();
	background->drawSolidRect(origin, winSize, cocos2d::Color4F(0.6, 0.6, 0.6, 1.0));
	this->addChild(background); 
	
	_player = Sprite::create("player.png");
	_player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5)); 
	this->addChild(_player);

	// 初始化了随机数生成器。如果不执行这一步，每次运行程序都会产生一样的随机数。
	srand((unsigned)time(nullptr));
	//生成一个怪物
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::addMonster), 0);
	/*
	_enemy = Sprite::create("Monster.png");
	_enemy->setPosition(Vec2(winSize.width * 0.8, winSize.height * 0.5));
	auto physicsBody = PhysicsBody::createBox(_enemy->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_enemy->setPhysicsBody(physicsBody);
	this->addChild(_enemy);
	*/

	//this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::addMonster), 0);
	auto eventListener = EventListenerTouchOneByOne::create();
	// 定义回调函数onTouchBegan():手指第一次碰到屏幕时被调用。
	eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	// 使用EventDispatcher来处理各种各样的事件，如触摸和其他键盘事件。
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
	// 1 - Just an example for how to get the player object
	// 说明一下作为第二个参数传递给addEventListenerWithSceneGraphPriority(eventListener, _player)的_player对象被访问的方式。
	// auto node = unused_event->getcurrentTarget();

	// 2.获取触摸点的坐标，并计算这个点相对于_player的偏移量。
	Vec2 touchLocation = touch->getLocation();
	Vec2 offset = touchLocation - _player->getPosition();
	// 如果offset的x值是负值，这表明玩家正试图朝后射击。在本游戏中这是不允许的。
	if (offset.x < 0) {
		return true;
	}

	// 3.在玩家所在的位置创建一个飞镖，将其添加到场景中。
	auto projectile = Sprite::create("Projectile.png");
	projectile->setPosition(_player->getPosition());
	auto physicsBody = PhysicsBody::createBox(projectile->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	projectile->setPhysicsBody(physicsBody);
	projectile->setTag(10);
	this->addChild(projectile);

	// 4.将偏移量转化为单位向量，即长度为1的向量。
	offset.normalize();
	// 将其乘以1000，你就获得了一个指向用户触屏方向的长度为1000的向量。为什么是1000呢？因为长度应当足以超过当前分辨率下屏幕的边界。
	auto shootAmount = offset * 1000;
	// 将此向量添加到飞镖的位置上去，这样你就有了一个目标位置。
	auto realDest = shootAmount + projectile->getPosition();

	// 5.创建一个动作，将飞镖在2秒内移动到目标位置，然后将它从场景中移除。
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));

	return true;
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == 10)
		{
			nodeB->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == 10)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
	}

	return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

/*
void MyEnemy::DoOnFrame() {
	auto from = this->getPosition();
	auto to = from;
	float minDuration = -4.0;
	float maxDuration = 4.0;
	int rangeDuration = (int)maxDuration - (int)minDuration;
	srand((unsigned)time(nullptr));
	float random = (rand() % rangeDuration) + minDuration;
	to.x += random;
	srand((unsigned)time(nullptr));
	random = (rand() % rangeDuration) + minDuration;
	to.y += random;
	auto move = cocos2d::MoveTo::create(2, to);
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(RepeatForever::create(static_cast<Sequence *>(Sequence::create(move, delay, nullptr))));
}

class Enemy :public cocos2d::Sprite {
	static Enemy* create(const char *pszFileName);
};
Enemy* Enemy::create(const char *filename)
{
	Enemy *sprite = new Enemy();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}
//样例代码，并未测试过有效性
*/