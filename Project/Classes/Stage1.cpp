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


std::vector<int> roomStat = {0,0,0,0,0,0};

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os << t; return os.str(); }
std::string tostr_power(float t) { std::ostringstream os; os << std::setiosflags(std::ios::fixed) << std::setprecision(2) << t; return os.str(); }

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
	this->addChild(door, 9999);

	//制造障碍
	static int num_LOP = cocos2d::random(0, 7);
	switch (num_LOP)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 200);
			barrier->DoOnCreate(num_LOP);
			this->addChild(barrier, 9999);
		}
		break;
	default:
		break;
	}

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


	if (roomStat[0] == 0) {
        int enemyType = random(1, 1);
	    int num;
	    if (enemyType >= 5)num = random(1, 2);
	    else num = random(1, 4);
	    static float temp;
	    temp = 160 - 25 * (num - 1);
	    auto create = CallFunc::create([=]() {
		    switch (enemyType) {
		    case 1:
			    auto _enemy = chaseEnemy::create();
			    _enemy->setPosition(Vec2(176.5, temp));
			    _enemy->DoOnCreated(5);
			    _enemy->DoOnFrame(_player);
			    this->addChild(_enemy, GROUP_ENEMY);
			    break;
		    }
		    temp += 50;
	    });
		auto delay = cocos2d::DelayTime::create(0.000000001);
	    this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));
	}
	
	roomStat[0] = 1;

	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(2);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(0);
	this->addChild(door2, 9999);

	static int num_L1 = 3;
	switch (num_L1)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L1);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L1);
		this->addChild(barrier, 9999);
		break;
		}
		/*
		if (roomStat[0] == 0) {
			auto _enemy = Sprite::create("monster.png");
			_enemy->setTag(GROUP_ENEMY);

			auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			enemybody->setContactTestBitmask(1);
			enemybody->setCollisionBitmask(1);
			enemybody->setCategoryBitmask(1);
			enemybody->setTag(GROUP_ENEMY);
			enemybody->setDynamic(true);
			enemybody->setGravityEnable(false);
			_enemy->setPhysicsBody(enemybody);

			_enemy->setPosition(Vec2(150, 250));
			this->addChild(_enemy, GROUP_ENEMY);

			auto shootStar = CallFunc::create([=]() {
				Bullet *dankumu = Bullet::create("grain.png");

				auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
				physicsBody->setDynamic(false);
				physicsBody->setContactTestBitmask(0xFFFFFFFF);
				dankumu->setPhysicsBody(physicsBody);
				dankumu->setTag(GROUP_ENEMY_BULLET);
				//屏幕右下角坐标(26.5,0)
				dankumu->setPosition(_enemy->getPosition());
				dankumu->setAngle(0);
				dankumu->aim = true;
				dankumu->setVelocit(3);
				dankumu->setRot(0);
				//dankumu->setRotVelocity(10);
				dankumu->setAcceleration(0);
				dankumu->setAccAngle(-90);
				dankumu->DoOnCreate(_player);
				dankumu->DoOnFrame();
				this->addChild(dankumu, GROUP_ENEMY_BULLET);
				BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
				//dankumu->setBlendFunc(cbl);

				auto p = P_Point::create();
				p->setPosition(_enemy->getPosition());
				p->DoOnCreate();
				p->setScale(1.2f);
				this->addChild(p, GROUP_ITEM);
			});
			auto delay = cocos2d::DelayTime::create(1);
			_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));
		
			roomStat[0] = 1;
		}*/
	

}

Scene* Stage2::createScene()
{
	return Stage2::create();
}

Stage2::Stage2()
{

	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);


	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(3);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(1);
	this->addChild(door2, 9999);

	static int num_L2 = cocos2d::random(0, 7);
	switch (num_L2)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L2);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L2);
		this->addChild(barrier, 9999);
		break;
	}

	/*
	if (roomStat[1] == 0) {
		auto _enemy = Sprite::create("monster.png");
		_enemy->setTag(GROUP_ENEMY);

		auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		enemybody->setContactTestBitmask(1);
		enemybody->setCollisionBitmask(1);
		enemybody->setCategoryBitmask(1);
		enemybody->setTag(GROUP_ENEMY);
		enemybody->setDynamic(true);
		enemybody->setGravityEnable(false);
		_enemy->setPhysicsBody(enemybody);

		_enemy->setPosition(Vec2(150, 250));
		this->addChild(_enemy, GROUP_ENEMY);

		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("grain.png");

			auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			dankumu->setPhysicsBody(physicsBody);
			dankumu->setTag(GROUP_ENEMY_BULLET);
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(_enemy->getPosition());
			dankumu->setAngle(0);
			dankumu->aim = true;
			dankumu->setVelocit(3);
			dankumu->setRot(0);
			//dankumu->setRotVelocity(10);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->DoOnCreate(_player);
			dankumu->DoOnFrame();
			this->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(1);
		_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));

		roomStat[1] = 1;
	}*/


}


Scene* Stage3::createScene()
{
	return Stage3::create();
}

Stage3::Stage3()
{

	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);


	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(4);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(2);
	this->addChild(door2, 9999);

	static int num_L3 = cocos2d::random(0, 7);
	switch (num_L3)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L3);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L3);
		this->addChild(barrier, 9999);
		break;
	}
	/*
	if (roomStat[2] == 0) {
		auto _enemy = Sprite::create("monster.png");
		_enemy->setTag(GROUP_ENEMY);

		auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		enemybody->setContactTestBitmask(1);
		enemybody->setCollisionBitmask(1);
		enemybody->setCategoryBitmask(1);
		enemybody->setTag(GROUP_ENEMY);
		enemybody->setDynamic(true);
		enemybody->setGravityEnable(false);
		_enemy->setPhysicsBody(enemybody);

		_enemy->setPosition(Vec2(150, 250));
		this->addChild(_enemy, GROUP_ENEMY);

		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("grain.png");

			auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			dankumu->setPhysicsBody(physicsBody);
			dankumu->setTag(GROUP_ENEMY_BULLET);
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(_enemy->getPosition());
			dankumu->setAngle(0);
			dankumu->aim = true;
			dankumu->setVelocit(3);
			dankumu->setRot(0);
			//dankumu->setRotVelocity(10);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->DoOnCreate(_player);
			dankumu->DoOnFrame();
			this->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(1);
		_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));

		roomStat[2] = 1;
	}*/


}


Scene* Stage4::createScene()
{
	return Stage4::create();
}

Stage4::Stage4()
{

	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);


	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(5);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(3);
	this->addChild(door2, 9999);

	static int num_L4 = cocos2d::random(0, 7);
	switch (num_L4)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L4);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L4);
		this->addChild(barrier, 9999);
		break;
	}
	/*
	if (roomStat[3] == 0) {
		auto _enemy = Sprite::create("monster.png");
		_enemy->setTag(GROUP_ENEMY);

		auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		enemybody->setContactTestBitmask(1);
		enemybody->setCollisionBitmask(1);
		enemybody->setCategoryBitmask(1);
		enemybody->setTag(GROUP_ENEMY);
		enemybody->setDynamic(true);
		enemybody->setGravityEnable(false);
		_enemy->setPhysicsBody(enemybody);

		_enemy->setPosition(Vec2(150, 250));
		this->addChild(_enemy, GROUP_ENEMY);

		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("grain.png");

			auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			dankumu->setPhysicsBody(physicsBody);
			dankumu->setTag(GROUP_ENEMY_BULLET);
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(_enemy->getPosition());
			dankumu->setAngle(0);
			dankumu->aim = true;
			dankumu->setVelocit(3);
			dankumu->setRot(0);
			//dankumu->setRotVelocity(10);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->DoOnCreate(_player);
			dankumu->DoOnFrame();
			this->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(1);
		_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));

		roomStat[3] = 1;
	}*/


}


Scene* Stage5::createScene()
{
	return Stage5::create();
}

Stage5::Stage5()
{

	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);



	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(6);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(4);
	this->addChild(door2, 9999);

	static int num_L5 = cocos2d::random(0, 7);
	switch (num_L5)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L5);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L5);
		this->addChild(barrier, 9999);
		break;
	}
	/*
	if (roomStat[4] == 0) {
		auto _enemy = Sprite::create("monster.png");
		_enemy->setTag(GROUP_ENEMY);

		auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		enemybody->setContactTestBitmask(1);
		enemybody->setCollisionBitmask(1);
		enemybody->setCategoryBitmask(1);
		enemybody->setTag(GROUP_ENEMY);
		enemybody->setDynamic(true);
		enemybody->setGravityEnable(false);
		_enemy->setPhysicsBody(enemybody);

		_enemy->setPosition(Vec2(150, 250));
		this->addChild(_enemy, GROUP_ENEMY);

		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("grain.png");

			auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			dankumu->setPhysicsBody(physicsBody);
			dankumu->setTag(GROUP_ENEMY_BULLET);
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(_enemy->getPosition());
			dankumu->setAngle(0);
			dankumu->aim = true;
			dankumu->setVelocit(3);
			dankumu->setRot(0);
			//dankumu->setRotVelocity(10);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->DoOnCreate(_player);
			dankumu->DoOnFrame();
			this->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(1);
		_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));

		roomStat[4] = 1;
	}*/


}

Scene* Stage6::createScene()
{
	return Stage6::create();
}

Stage6::Stage6()
{

	_player = _player->create("player.png");
	_player->info = info_temp;
	_player->DoOnCreate();
	_player->DoOnFrame();
	_player->setPosition(info_temp.dir);
	_player->Atk();


	this->addChild(_player, GROUP_PLAYER);



	auto door1 = Door::create("CloseNormal.png");
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(0);
	this->addChild(door1, 9999);

	auto door2 = Door::create("CloseNormal.png");
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(5);
	this->addChild(door2, 9999);

	static int num_L6 = cocos2d::random(0, 7);
	switch (num_L6)
	{
	case 1:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 160.5);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		break;
	case 2:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 200 - i);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		break;
	case 3:
		for (int i = 0; i <= 140; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(176.5, 230 - i);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(110 + i, 165);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 50; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240 - i, 165);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		break;
	case 4:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 150);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120 + i, 220);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		break;
	case 5:
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(120, 200 - i);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		for (int i = 0; i <= 100; i += 33) {
			auto barrier = Barriers::create("change.jpg");
			barrier->setPosition(240, 200 - i);
			barrier->DoOnCreate(num_L6);
			this->addChild(barrier, 9999);
		}
		break;
	case 6:
		auto barrier = Barriers::create("change.jpg");
		barrier->setPosition(176.5, 160.5);
		barrier->DoOnCreate(num_L6);
		this->addChild(barrier, 9999);
		break;
	}
	/*
	if (roomStat[5] == 0) {
		auto _enemy = Sprite::create("monster.png");
		_enemy->setTag(GROUP_ENEMY);

		auto enemybody = PhysicsBody::createCircle(7.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
		enemybody->setContactTestBitmask(1);
		enemybody->setCollisionBitmask(1);
		enemybody->setCategoryBitmask(1);
		enemybody->setTag(GROUP_ENEMY);
		enemybody->setDynamic(true);
		enemybody->setGravityEnable(false);
		_enemy->setPhysicsBody(enemybody);

		_enemy->setPosition(Vec2(150, 250));
		this->addChild(_enemy, GROUP_ENEMY);

		auto shootStar = CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("grain.png");

			auto physicsBody = PhysicsBody::createCircle(1.0f, PhysicsMaterial(1.0f, 0.0f, 0.0f));
			physicsBody->setDynamic(false);
			physicsBody->setContactTestBitmask(0xFFFFFFFF);
			dankumu->setPhysicsBody(physicsBody);
			dankumu->setTag(GROUP_ENEMY_BULLET);
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(_enemy->getPosition());
			dankumu->setAngle(0);
			dankumu->aim = true;
			dankumu->setVelocit(3);
			dankumu->setRot(0);
			//dankumu->setRotVelocity(10);
			dankumu->setAcceleration(0);
			dankumu->setAccAngle(-90);
			dankumu->DoOnCreate(_player);
			dankumu->DoOnFrame();
			this->addChild(dankumu, GROUP_ENEMY_BULLET);
			BlendFunc cbl = { backend::BlendFactor::DST_COLOR,backend::BlendFactor::ONE };
			//dankumu->setBlendFunc(cbl);

			auto p = P_Point::create();
			p->setPosition(_enemy->getPosition());
			p->DoOnCreate();
			p->setScale(1.2f);
			this->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(1);
		_enemy->runAction(RepeatForever::create(static_cast<Spawn *>(Spawn::create(shootStar, delay, nullptr))));

		roomStat[5] = 1;
	}*/


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
	background1->drawSolidRect(origin, winSize, cocos2d::Color4F(0.8, 0.8, 0.8, 0.8));
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
	case GROUP_BARRIERS + GROUP_ENEMY_BULLET:

		//这里写障碍物消弹或是反弹

		break;
	case GROUP_BARRIERS + GROUP_PLAYER_BULLET:



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
		default:
			break;
		}
		CCLOG("item删除");
		break;
	case GROUP_PLAYER + GROUP_DOOR:
		CCLOG("Teleport");
		info_temp = _player->info;
		info_temp.dir = _player->getPosition();
		nodeA->getTag() == GROUP_DOOR ?
			temp = static_cast<Door*>(nodeA)->getNum() :
			temp = static_cast<Door*>(nodeB)->getNum();
		Scene* scene;
		switch (temp) {
		case 0:
			scene = StageOP::createScene();
			break;
		case 1:
			info_temp.dir = Vec2(176.5,70);
			scene = Stage1::createScene();
			break;
		case 2:
			info_temp.dir = Vec2(176.5, 70);
			scene = Stage2::createScene();
			break;
		case 3:
			info_temp.dir = Vec2(176.5, 70);
			scene = Stage3::createScene();
			break;
		case 4:
			info_temp.dir = Vec2(176.5, 70);
			scene = Stage4::createScene();
			break;
		case 5:
			info_temp.dir = Vec2(176.5, 70);
			scene = Stage5::createScene();
			break;
		case 6:
			info_temp.dir = Vec2(176.5, 70);
			scene = Stage6::createScene();
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
	_labelPower->setString(str.c_str());

	str = "Bomb:  ";
	str += tostr_power(_player->getBombs());
	_labelPower->setString(str.c_str());

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

