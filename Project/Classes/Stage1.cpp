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

#include "Stage1.h"
#include "Bullet.h"
#include "Player.h"
#include "Item.h"

USING_NS_CC;

PlayerInfo info_temp;


template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }

Scene* Stage::createScene()
{
    return Stage::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StageScene.cpp\n");
}

Scene* StageOP::createScene()
{
	return StageOP::create();
}

Scene* Stage1::createScene()
{
	return Stage1::create();
}

StageOP::StageOP() {

	auto door = Door::create("CloseNormal.png");
	door->setPosition(100, 100);
	door->DoOnCreate(1);
	this->addChild(door,9999);

}
bool Stage::init() {
	if (!Scene::init())
	{
		return false;
	}
	if (!Scene::initWithPhysics())
	{
		return false;
	}
	auto s = Director::getInstance()->getWinSize();
	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// set Background with grey colour

	auto background1 = DrawNode::create();
	background1->drawSolidRect(origin, winSize, cocos2d::Color4F(1.0, 1.0, 1.0, 1.0));
	this->addChild(background1);

	auto background = Sprite::create("ui_bg.png");
	background->setScale(1.425f);
	background->setPosition(Vec2((53.0 + 640.0 / 1.5) / 2.0, 160));
	this->addChild(background, 2000);

	addKeyboardListener();
	addContactListener();

	_player = _player->create("player.png");
	_player->DoOnCreate();
	_player->setPosition(info_temp.dir);
	_player->Atk(this);

	auto playbody = PhysicsBody::createCircle(1.5f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
	playbody->setContactTestBitmask(1);
	playbody->setCollisionBitmask(1);
	playbody->setCategoryBitmask(1);
	playbody->setTag(GROUP_PLAYER);
	playbody->setDynamic(true);
	playbody->setGravityEnable(false);
	_player->setPhysicsBody(playbody);
	_player->info = info_temp;
	_player->DoOnFrame();

	this->addChild(_player, GROUP_PLAYER);

	return true;
}

bool Stage::onTouchBegan(Touch* touch, Event* unused_event) {
	return true;
}

void Stage::addKeyboardListener() {
	auto* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Stage::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Stage::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void Stage::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, Event* event) {
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
void Stage::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, Event* event) {
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
void Stage::addContactListener() {
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Stage::onConcactBegin, this);
	//contactListener->onContactPreSolve = CC_CALLBACK_1(HitBrick::onContactPreSolve, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
bool Stage::onConcactBegin(PhysicsContact & contact) {
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
			static_cast<PCommonShot*>(nodeA)->Hit(static_cast<Sprite*>(nodeB)) :
			static_cast<PCommonShot*>(nodeB)->Hit(static_cast<Sprite*>(nodeA));
		CCLOG("p_b删除，e掉血");
		break;
	case GROUP_PLAYER + GROUP_ENEMY:
		CCLOG("p掉血");
		break;
	case GROUP_PLAYER + GROUP_ITEM:
		CCLOG("item删除");
		break;
	case GROUP_PLAYER + GROUP_DOOR:
		CCLOG("Teleport");
		info_temp = _player->info;
		info_temp.dir = _player->getPosition();
		int temp = -1;
		nodeA->getTag() == GROUP_DOOR ?
			temp = static_cast<Door*>(nodeA)->getNum() :
			temp = static_cast<Door*>(nodeB)->getNum();
		Scene* scene;
		switch (temp)
		{
		case 0:
			scene = StageOP::createScene();
			break;
		case 1:
			scene = Stage1::createScene();
			break;
		default:
			break;
		}
		Director::getInstance()->replaceScene(scene);
		break;
	}
	return true;
}

Stage1::Stage1()
{

	auto door = Door::create("CloseNormal.png");
	door->setPosition(200, 200);
	door->DoOnCreate(0);
	this->addChild(door, 9999);

}
