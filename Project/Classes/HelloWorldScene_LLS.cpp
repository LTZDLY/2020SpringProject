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
#include "Player.h"

USING_NS_CC;

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }

cocos2d::Vector<cocos2d::SpriteFrame*> HelloWorld::getAnimation(const char * format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}

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

	/*
	auto physicsBody = PhysicsBody::createBox(_enemy->getContentSize(), PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	_enemy->setPhysicsBody(physicsBody);
	*/
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

	
	//测试简单子弹和高光效果，成功
	auto shootStar = CallFunc::create([=]() {
		Bullet *dankumu = Bullet::create("grain.png");
		Bullet *dankumu2 = Bullet::create("grain.png");

		auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setContactTestBitmask(0xFFFFFFFF);
		dankumu->setPhysicsBody(physicsBody);
		dankumu->setTag(GROUP_ENEMY_BULLET);
		//屏幕右下角坐标(26.5,0)
		dankumu->setPosition(Vec2(26.5,0));
		dankumu2->setPosition(Vec2(26.5 + 640.0 / 1.5, 480.0 / 1.5));
		dankumu->setAngle(120);
		dankumu->setVelocit(0);
		dankumu->setRot(0);
		//dankumu->setRotVelocity(10);
		dankumu->setAcceleration(0);
		dankumu->setAccAngle(-90);
		dankumu->DoOnFrame();
		dankumu2->DoOnFrame();
		this->addChild(dankumu, GROUP_ENEMY_BULLET);
		this->addChild(dankumu2, GROUP_ENEMY_BULLET);
		BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
		//dankumu->setBlendFunc(cbl);
	});
	auto delay = cocos2d::DelayTime::create(0.3);
	_enemy->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr)), 1));
	//简单子弹的调用如上所示
	

	/*
	//测试lstg中的task嵌套效果，未完成
	//测试自定义子弹和task套循环，成功
	temp = 180;
	temp2 = 0;
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

void HelloWorld::addPlayer(float dt) {
	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	_player = _player->create("player.png");
	_player->DoOnCreate();
	_player->setPosition(Vec2(150,150));
	_player->Atk(this);

	auto playbody = PhysicsBody::createCircle(1.5f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	playbody->setContactTestBitmask(1);
	playbody->setCollisionBitmask(1);
	playbody->setCategoryBitmask(1);
	playbody->setTag(GROUP_PLAYER);
	playbody->setDynamic(true);
	playbody->setGravityEnable(false);
	_player->setPhysicsBody(playbody);

	this->addChild(_player, GROUP_PLAYER);
	_player->DoOnFrame();
}

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

	auto s = Director::getInstance()->getWinSize();
	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// set Background with grey colour

	_labelPosition = Label::createWithTTF("Mouse not supported on this device", "fonts/arial.ttf", 22);
	_labelPosition->setPosition(Vec2(s.width / 2, s.height / 3));
	addChild(_labelPosition,10000);


	auto background1 = DrawNode::create();
	background1->drawSolidRect(origin, winSize, cocos2d::Color4F(0, 0, 0, 1.0));
	this->addChild(background1); 
	
	auto background = Sprite::create("ui_bg.png");
	background->setScale(1.425f);
	background->setPosition(Vec2((53.0 + 640.0 / 1.5) / 2.0, 160));
	this->addChild(background, 2000);

	addKeyboardListener();
	addContactListener();

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::addPlayer), 0);

	// 初始化了随机数生成器。如果不执行这一步，每次运行程序都会产生一样的随机数。
	srand((unsigned)time(nullptr));
	//生成一个怪物

	auto a = SpriteFrameCache::getInstance();
	a->addSpriteFramesWithFile("test.plist");
	//auto frames = getAnimation("enemy-test/%d.png", 12);
	_enemy = Sprite::createWithSpriteFrameName("enemy-test/0.png");

	Vector<SpriteFrame*> mSprite;
	SpriteFrame* frame = nullptr;
	char str[100] = { 0 };
	for (int i = 0; i < 4; i++) {
		sprintf(str, "enemy-test/%d.png", i);
		frame = a->getSpriteFrameByName(str);
		mSprite.pushBack(frame);
	}
	auto aaa = Animation::createWithSpriteFrames(mSprite, 1.0 / 10.0);
	aaa->setLoops(-1);
	aaa->setRestoreOriginalFrame(true);
	auto bbb = Animate::create(aaa);
	_enemy->runAction(bbb);
	

	auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	enemybody->setContactTestBitmask(1);
	enemybody->setCollisionBitmask(1);
	enemybody->setCategoryBitmask(1);
	enemybody->setTag(GROUP_ENEMY);
	enemybody->setDynamic(true);
	enemybody->setGravityEnable(false);
	_enemy->setPhysicsBody(enemybody);

	_enemy->setPosition(Vec2(winSize.width * 0.8, winSize.height * 0.5));
	this->addChild(_enemy, GROUP_ENEMY);
	_enemy->setTag(GROUP_ENEMY);


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
	/*
	//this->scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::addMonster), 0);
	auto eventListener = EventListenerTouchOneByOne::create();
	// 定义回调函数onTouchBegan():手指第一次碰到屏幕时被调用。
	eventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	// 使用EventDispatcher来处理各种各样的事件，如触摸和其他键盘事件。
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
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


void HelloWorld::addKeyboardListener() {
	auto* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, Event* event) {
	std::string str = "MousePosition X:";
	str = str + tostr(_player->getPositionX()) + " Y:" + tostr(_player->getPositionY());
	_labelPosition->setString(str.c_str());
	switch (code) {
	case EventKeyboard::KeyCode::KEY_SHIFT:
		_player->info.shift = true;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		_player->info.shoot = true;
		CCLOG("you press z");
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_player->info.keyboardnum += 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_player->info.keyboardnum += 2;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_player->info.keyboardnum += 4;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_player->info.keyboardnum += 8;
		break;
	}
}

void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case EventKeyboard::KeyCode::KEY_SHIFT:
		_player->info.shift = false;
		break;
	case EventKeyboard::KeyCode::KEY_Z:
		_player->info.shoot = false;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		_player->info.keyboardnum -= 1;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		_player->info.keyboardnum -= 2;
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		_player->info.keyboardnum -= 4;
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		_player->info.keyboardnum -= 8;
		break;
	}
}

void HelloWorld::addContactListener() {
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onConcactBegin, this);
	//contactListener->onContactPreSolve = CC_CALLBACK_1(HitBrick::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool HelloWorld::onConcactBegin(PhysicsContact & contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	if (nodeA->getTag() == nodeB->getTag()) return true;
	std::stringstream ss;
	std::string s;
	switch (nodeA->getTag() + nodeB->getTag())
	{
	case GROUP_PLAYER + GROUP_ENEMY_BULLET:
		nodeA->getTag() == GROUP_PLAYER ?
			static_cast<Player*>(nodeA)->beHit(static_cast<Bullet*>(nodeB)) :
			static_cast<Player*>(nodeB)->beHit(static_cast<Bullet*>(nodeA));
		CCLOG("e_b删除，p掉血");
		break;
	case GROUP_PLAYER_BULLET + GROUP_ENEMY:
		nodeA->getTag() == GROUP_PLAYER_BULLET ? 
			static_cast<PCommonShot*>(nodeA)->Hit(static_cast<Sprite*>(nodeB)): 
			static_cast<PCommonShot*>(nodeB)->Hit(static_cast<Sprite*>(nodeA));
		CCLOG("p_b删除，e掉血");
		break;
	case GROUP_PLAYER + GROUP_ENEMY:
		CCLOG("p掉血");
		break;
	case GROUP_PLAYER + GROUP_ITEM:
		CCLOG("item删除");
		break;
	default:
		break;
	}
	return true;
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