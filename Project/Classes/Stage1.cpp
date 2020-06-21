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
#include "Enemy.h"
#include "AudioEngine.h"
#include "Pause.h"
#include <iomanip>
USING_NS_CC;

PlayerInfo info_temp;


template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }
std::string tostr_power(float t) { std::ostringstream os; os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << t; return os.str(); }

std::vector<int> Stage::aa = { 0,0,0,0,0,0,0 };

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
	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);


	auto door = Door::create("CloseNormal.png");
	door->setPosition(100, 100);
	door->DoOnCreate(1);
	this->addChild(door,9999);

}

Stage1::Stage1()
{
	
	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);


	auto door = Door::create("CloseNormal.png");
	door->setPosition(200, 200);
	door->DoOnCreate(0);
	this->addChild(door, 9999);

	if (aa[1] == true) return;

	int enemyType = random(7, 7);
	int num;
	if (enemyType >= 8)num = 1;
	else if (enemyType >= 5)num = random(1, 2);
	else num = random(1, 4);
	static float temp;
	temp = 160 - 25 * (num - 1);
	auto create = CallFunc::create([=]() {
		auto _enemy1 = chaseEnemy::create();
		auto _enemy2 = littleRed::create();
		auto _enemy3 = littleGreen::create();
		auto _enemy5 = bigBound::create();
		auto _enemy8 = bigCross::create();
		switch (enemyType) {
		case 1:
			_enemy1->setPosition(Vec2(176.5, temp));
			_enemy1->DoOnCreated(5, 5);
			_enemy1->DoOnFrame(_player);
			this->addChild(_enemy1, GROUP_ENEMY);
			break;
		case 2:
			_enemy2->setPosition(Vec2(176.5, temp));
			_enemy2->DoOnCreated(5, 5);
			_enemy2->DoOnFrame(_player, 15);
			this->addChild(_enemy2, GROUP_ENEMY);
			break;
		case 3:
			_enemy3->setPosition(Vec2(176.5, temp));
			_enemy3->DoOnCreated(5, 5);
			_enemy3->DoOnFrame(_player, 5);
			this->addChild(_enemy3, GROUP_ENEMY);
			break;
		case 5:
			_enemy5->setPosition(Vec2(176.5, temp));
			_enemy5->DoOnCreated(10, 7);
			_enemy5->DoOnFrame(_player, 20);
			this->addChild(_enemy5, GROUP_ENEMY);
			break;
		case 8:
			_enemy8->setPosition(Vec2(176.5, temp));
			_enemy8->DoOnCreated(10, 7);
			_enemy8->DoOnFrame(_player, 30);
			this->addChild(_enemy8, GROUP_ENEMY);
			break;
		}
		temp += 50;
	});
	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));
	/*
	static float a = 0;
	auto kaihua = CallFunc::create([=]() {
		a = cocos2d::random(0.0, 360.0);
		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("ellipse.png");
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(Vec2(0, 0));
			dankumu->setVelocit(0);
			dankumu->setRot(a);
			dankumu->setRotVelocity(37);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->setDestroyable(false);
			dankumu->setBound(false);
			dankumu->DoOnCreate(_player, 30.0);
			dankumu->DoOnFrame();
			_enemy->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto actionBy = SkewBy::create(0.01, 1.5f, -80.0f);
			dankumu->runAction(actionBy);
			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->DoOnFrame(_player);
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);

			a += 360.0 / 3.0;

		});
		auto delay = cocos2d::DelayTime::create(0.00001);
		_enemy->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr)), 3));
	});
	auto delay = cocos2d::DelayTime::create(3);
	_enemy->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(kaihua, delay, nullptr)), 1));
	*/

	

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
	//左下(26.5, 0)，右上(26.5 + 640 / 1.5, 320)453.166666667

	addKeyboardListener();
	addContactListener();

	std::string str = "Score:  ";
	str += tostr(_player->getScore());
	_labelScore = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelScore->setPosition(380, 290);
	addChild(_labelScore, 2001);

	str = "Hp:  ";
	str += tostr(_player->getHp());
	_labelHp = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelHp->setPosition(380, 190);
	addChild(_labelHp, 2001);

	str = "Bomb:  ";
	str += tostr(_player->getBombs());
	_labelBomb = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelBomb->setPosition(380, 170);
	addChild(_labelBomb, 2001);

	str = "Power:  ";
	str += tostr_power(_player->getPower() / 100.0) + " / 4.00";
	_labelPower = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelPower->setPosition(380, 150);
	addChild(_labelPower, 2001);

	str = "MaxPoint:  ";
	str += tostr(_player->getScoreGetMax());
	_labelScoreGetMax = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelScoreGetMax->setPosition(380, 130);
	addChild(_labelScoreGetMax, 2001);

	str = "Graze:  ";
	str += tostr(_player->getGraze());
	_labelGraze = Label::createWithTTF(str.c_str(), "fonts/arial.ttf", 14);
	_labelGraze->setPosition(380, 110);
	addChild(_labelGraze, 2001);

	this->schedule(CC_SCHEDULE_SELECTOR(Stage::refresh), 1.0 / 30.0);

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
	case EventKeyboard::KeyCode::KEY_X:
		_player->setBomb();
		CCLOG("you press x");
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
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		auto scene = Pause::createScene();
		Director::getInstance()->pushScene(scene);
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
	std::stringstream ss;
	std::string s;
	int temp = -1;
	bool flag = true;
	switch (nodeA->getTag() + nodeB->getTag()) {
	case GROUP_PLAYER + GROUP_ENEMY_BULLET:
		nodeA->getTag() == GROUP_PLAYER ?
			static_cast<Player*>(nodeA)->beHit(static_cast<Bullet*>(nodeB)) :
			static_cast<Player*>(nodeB)->beHit(static_cast<Bullet*>(nodeA));
		CCLOG("e_b删除，p掉血");
		break;
	case GROUP_PLAYER_BULLET + GROUP_ENEMY:
		nodeA->getTag() == GROUP_PLAYER_BULLET ?
			static_cast<PCommonShot*>(nodeA)->Hit(_player, static_cast<Enemy*>(nodeB)) :
			static_cast<PCommonShot*>(nodeB)->Hit(_player, static_cast<Enemy*>(nodeA));
		CCLOG("p_b删除，e掉血");
		break;
	case GROUP_PLAYER_BOMB + GROUP_ENEMY:
		nodeA->getTag() == GROUP_PLAYER_BOMB ?
			static_cast<PBomb*>(nodeA)->Hit(_player, static_cast<Enemy*>(nodeB)) :
			static_cast<PBomb*>(nodeB)->Hit(_player, static_cast<Enemy*>(nodeA));
		CCLOG("p_b删除，e掉血");
		break;/*
	case GROUP_PLAYER_BOMB + GROUP_ENEMY_BULLET:
		nodeA->getTag() == GROUP_PLAYER_BOMB ?
			static_cast<PBomb*>(nodeA)->Hit(_player, static_cast<Bullet*>(nodeB)) :
			static_cast<PBomb*>(nodeB)->Hit(_player, static_cast<Bullet*>(nodeA));
		CCLOG("p_b删除，e掉血");
		break;*/
	case GROUP_PLAYER + GROUP_ENEMY:
		CCLOG("p掉血");
		nodeA->getTag() == GROUP_PLAYER ?
			static_cast<Player*>(nodeA)->beHit(static_cast<Enemy*>(nodeB)) :
			static_cast<Player*>(nodeB)->beHit(static_cast<Enemy*>(nodeA));
		break;
	case GROUP_PLAYER_GRAZE + GROUP_ENEMY_BULLET:
		CCLOG("graze");
		nodeA->getTag() == GROUP_ENEMY_BULLET ?
			static_cast<Bullet*>(nodeA)->beGraze(_player) :
			static_cast<Bullet*>(nodeB)->beGraze(_player);
			
		break;
	case GROUP_PLAYER + GROUP_ITEM:
		nodeA->getTag() == GROUP_PLAYER ?
			flag = static_cast<Player*>(nodeA)->info._collect :
			flag = static_cast<Player*>(nodeB)->info._collect;
		if (flag == false) return false;
		nodeA->getTag() == GROUP_ITEM ?
			temp = static_cast<Item*>(nodeA)->getNum() :
			temp = static_cast<Item*>(nodeB)->getNum();
		switch (temp) {
		case GROUP_ITEM_P_POINT:
			nodeA->getTag() == GROUP_ITEM ?
				static_cast<P_Point*>(nodeA)->DoOnCollect(_player) :
				static_cast<P_Point*>(nodeB)->DoOnCollect(_player);
			break;
		case GROUP_ITEM_BLUE_POINT:
			nodeA->getTag() == GROUP_ITEM ?
				static_cast<BluePoint*>(nodeA)->DoOnCollect(_player) :
				static_cast<BluePoint*>(nodeB)->DoOnCollect(_player);
			break;
		case GROUP_ITEM_BOMB:
			nodeA->getTag() == GROUP_ITEM ?
				static_cast<Bomb*>(nodeA)->DoOnCollect(_player) :
				static_cast<Bomb*>(nodeB)->DoOnCollect(_player);
			break;
		case GROUP_ITEM_LIFE:
			nodeA->getTag() == GROUP_ITEM ?
				static_cast<LifePiece*>(nodeA)->DoOnCollect(_player) :
				static_cast<LifePiece*>(nodeB)->DoOnCollect(_player);
			break;
		case GROUP_ITEM_GREENPOINT:
			nodeA->getTag() == GROUP_ITEM ?
				static_cast<GreenPoint*>(nodeA)->DoOnCollect(_player) :
				static_cast<GreenPoint*>(nodeB)->DoOnCollect(_player);
			break;
		}
		CCLOG("item删除");
		break;
	case GROUP_PLAYER + GROUP_DOOR:
		CCLOG("Teleport");
		info_temp = _player->info;
		info_temp.dir = _player->getPosition();
		info_temp._bombs_cd = 0;
		info_temp._invincibled = 0;
		nodeA->getTag() == GROUP_DOOR ?
			temp = static_cast<Door*>(nodeA)->getNum() :
			temp = static_cast<Door*>(nodeB)->getNum();
		Scene* scene;
		switch (temp) {
		case 0:
			info_temp.dir = Vec2(50, 100);
			scene = StageOP::createScene();
			break;
		case 1:
			info_temp.dir = Vec2(250, 250);
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

void Stage::refresh(float dt) {
	std::string str = "Score:  ";
	str += tostr(_player->getScore());
	_labelScore->setString(str.c_str());

	str = "Hp:  ";
	str += tostr(_player->getHp());
	_labelHp->setString(str.c_str());

	str = "Bomb:  ";
	str += tostr(_player->getBombs());
	_labelBomb->setString(str.c_str());

	str = "Power:  ";
	str += tostr_power(_player->getPower() / 100.0) + " / 4.00";
	_labelPower->setString(str.c_str());

	str = "MaxPoint:  ";
	str += tostr(_player->getScoreGetMax());
	_labelScoreGetMax->setString(str.c_str());

	str = "Graze:  ";
	str += tostr(_player->getGraze());
	_labelGraze->setString(str.c_str());

}

