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


std::vector<int> roomStat = { 0,0,0,0,0,0 };

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


	auto door = Door::create("tele.png");
	door->setScale(0.5);
	door->setPosition(176.5, 300);
	door->DoOnCreate(1);
	this->addChild(door, 9999);

	auto sprite = Sprite::create("images/stage1.png");
	sprite->setPosition(176.5, 155);
	sprite->setScale(0.8);
	this->addChild(sprite, 1);


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

	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(2);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
	door2->setPosition(176.5, 20);
	door2->DoOnCreate(0);
	this->addChild(door2, 9999);

	static int num_L1 = cocos2d::random(1, 6);
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

	if (roomStat[0] == 1) return;
	int enemyType = 2;
	int num = cocos2d::random(1, 3);
	this->enemyNum = num;
	temp = 160 - 25 * (num - 1);
	auto create = CallFunc::create([=]() {
		auto enemy = littleRed::create();
		enemy->setPosition(Vec2(176.5, temp));
		enemy->DoOnCreated(5, 5);
		enemy->DoOnFrame(_player, 5);
		this->addChild(enemy, GROUP_ENEMY);
		temp += 50;
	});
	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));
	roomStat[0] = 1;

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


	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(3);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
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

	if (roomStat[1] == 1) return;
	int enemyType = random(1, 3);
	int num = random(2, 4);
	if (enemyType == 1) num = random(1, 2);
	this->enemyNum = num;
	temp = 160 - 25 * (num - 1);
	auto create = CallFunc::create([=]() {
		auto enemy1 = chaseEnemy::create();
		auto enemy2 = littleRed::create();
		auto enemy3 = littleGreen::create();
		switch (enemyType) {
		case 1:
			enemy1->setPosition(Vec2(176.5, temp));
			enemy1->DoOnCreated(5, 7);
			enemy1->DoOnFrame(_player);
			this->addChild(enemy1, GROUP_ENEMY);
			break;
		case 2:
			enemy2->setPosition(Vec2(176.5, temp));
			enemy2->DoOnCreated(5, 5);
			enemy2->DoOnFrame(_player, 15);
			this->addChild(enemy2, GROUP_ENEMY);
			break;
		case 3:
			enemy3->setPosition(Vec2(176.5, temp));
			enemy3->DoOnCreated(5, 5);
			enemy3->DoOnFrame(_player, 10);
			this->addChild(enemy3, GROUP_ENEMY);
			break;
		}
		temp += 50;
	});
	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));
	roomStat[1] = 1;

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


	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(4);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
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
	if (roomStat[2] == 1) return;

	int enemyType = random(4, 5);
	int num = random(2, 4);
	this->enemyNum = num;
	temp = 160 - 25 * (num - 1);
	auto create = CallFunc::create([=]() {
		auto enemy4 = midRed::create();;
		auto enemy5 = bigBound::create();
		switch (enemyType)
		{
		case 4:
			enemy4->setPosition(Vec2(176.5, temp));
			enemy4->DoOnCreated(5, 5);
			enemy4->DoOnFrame(_player, 5 - num);
			this->addChild(enemy4, GROUP_ENEMY);
			break;
		case 5:
			enemy5->setPosition(Vec2(176.5, temp));
			enemy5->DoOnCreated(10, 7);
			enemy5->DoOnFrame(_player, 5 * (5 - num));
			this->addChild(enemy5, GROUP_ENEMY);
			break;
		}
		temp += 50;
	});

	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));

	roomStat[2] = 1;


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


	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(5);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
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
	
	if (roomStat[3] == 1) return;

	int enemyType = random(6, 9);
	int num = random(2, 4);
	if (enemyType == 6)num++;
	if (enemyType == 9)num--;
	this->enemyNum == num;
	temp = 160 - 25 * (num - 1);
	auto create = CallFunc::create([=]() {
		auto enemy6 = midRed::create();
		auto enemy7 = bigBound::create();
		auto enemy8 = bigCross::create();
		auto enemy9 = bigBloom::create();
		switch (enemyType) {
		case 6:
			enemy6->setPosition(Vec2(176.5, temp));
			enemy6->DoOnCreated(10, 7);
			enemy6->DoOnFrame(_player, (7 - num));
			this->addChild(enemy6, GROUP_ENEMY);
			break;
		case 7:
			enemy7->setPosition(Vec2(176.5, temp));
			enemy7->DoOnCreated(10, 7);
			enemy7->DoOnFrame(_player, 5 * (6 - num));
			this->addChild(enemy7, GROUP_ENEMY);
			break;
		case 8:
			enemy8->setPosition(Vec2(176.5, temp));
			enemy8->DoOnCreated(10, 10 * (6 - num));
			enemy8->DoOnFrame(_player, 30);
			this->addChild(enemy8, GROUP_ENEMY);
			break;
		case 9:
			enemy9->setPosition(Vec2(176.5, temp));
			enemy9->DoOnCreated(10, 7);
			enemy9->DoOnFrame(_player, 2 * (5 - num));
			this->addChild(enemy9, GROUP_ENEMY);
			break;
		}
	temp += 50;
	});
	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create, delay, nullptr)), num));

	roomStat[3] = 1;


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



	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(6);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
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
	if (roomStat[4] == 1) return;


	int enemyType1 = random(1, 3);
	int num1 = random(3, 5);
	if (enemyType1 == 1) num1 = random(2, 3);

	int enemyType2 = random(6, 9);
	int num2 = random(2, 4);
	if (enemyType2 == 6)num2++;
	if (enemyType2 == 9)num2--;

	this->enemyNum = num1 + num2;
	temp = 160 - 25 * (num1 - 1);
	auto create1 = CallFunc::create([=]() {
		auto enemy1 = chaseEnemy::create();
		auto enemy2 = littleRed::create();
		auto enemy3 = littleGreen::create();
		switch (enemyType1) {
		case 1:
			enemy1->setPosition(Vec2(176.5, temp));
			enemy1->DoOnCreated(5, 7);
			enemy1->DoOnFrame(_player);
			this->addChild(enemy1, GROUP_ENEMY);
			break;
		case 2:
			enemy2->setPosition(Vec2(176.5, temp));
			enemy2->DoOnCreated(5, 5);
			enemy2->DoOnFrame(_player, 15);
			this->addChild(enemy2, GROUP_ENEMY);
			break;
		case 3:
			enemy3->setPosition(Vec2(176.5, temp));
			enemy3->DoOnCreated(5, 5);
			enemy3->DoOnFrame(_player, 10);
			this->addChild(enemy3, GROUP_ENEMY);
			break;
		}
		temp += 50;
	});
	auto delay = cocos2d::DelayTime::create(0.0001);
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create1, delay, nullptr)), num1));

	temp = 160 - 25 * (num1 - 1);
	auto create2 = CallFunc::create([=]() {
		auto enemy6 = midRed::create();
		auto enemy7 = bigBound::create();
		auto enemy8 = bigCross::create();
		auto enemy9 = bigBloom::create();
		switch (enemyType2) {
		case 6:
			enemy6->setPosition(Vec2(176.5, temp));
			enemy6->DoOnCreated(10, 7);
			enemy6->DoOnFrame(_player, (7 - num2));
			this->addChild(enemy6, GROUP_ENEMY);
			break;
		case 7:
			enemy7->setPosition(Vec2(176.5, temp));
			enemy7->DoOnCreated(10, 7);
			enemy7->DoOnFrame(_player, 5 * (6 - num2));
			this->addChild(enemy7, GROUP_ENEMY);
			break;
		case 8:
			enemy8->setPosition(Vec2(176.5, temp));
			enemy8->DoOnCreated(10, 10 * (6 - num2));
			enemy8->DoOnFrame(_player, 30);
			this->addChild(enemy8, GROUP_ENEMY);
			break;
		case 9:
			enemy9->setPosition(Vec2(176.5, temp));
			enemy9->DoOnCreated(10, 7);
			enemy9->DoOnFrame(_player, 2 * (6 - num2));
			this->addChild(enemy9, GROUP_ENEMY);
			break;
		}
		temp += 50;
	});
	this->runAction(Repeat::create(static_cast<Spawn *>(Spawn::create(create2, delay->clone(), nullptr)), num2));

	roomStat[4] = 1;


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



	auto door1 = Door::create("tele.png");
	door1->setScale(0.5);
	door1->setPosition(176.5, 300);
	door1->DoOnCreate(7);
	this->addChild(door1, 9999);

	auto door2 = Door::create("tele.png");
	door2->setScale(0.5);
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
	if (roomStat[5] == 1) return;

	int enemyType = random(1, 3);
	int num = 1;
	this->enemyNum = num;
	auto enemy1 = Boss1::create();
	auto enemy2 = Boss2::create();
	auto enemy3 = Boss3::create();
	switch (enemyType) {
	case 1:
		enemy1->setPosition(Vec2(176.5, 250));
		enemy1->DoOnCreated(5, 5);
		enemy1->DoOnFrame(_player);
		this->addChild(enemy1, GROUP_ENEMY);
		break;
	case 2:
		enemy2->setPosition(Vec2(176.5, 250));
		enemy2->DoOnCreated(5, 5);
		enemy2->DoOnFrame(_player);
		this->addChild(enemy2, GROUP_ENEMY);
		break;
	case 3:
		enemy3->setPosition(Vec2(176.5, 250));
		enemy3->DoOnCreated(5, 5);
		enemy3->DoOnFrame(_player);
		this->addChild(enemy3, GROUP_ENEMY);
		break;
	}

	roomStat[5] = 1;

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
			static_cast<PCommonShot*>(nodeA)->Hit(_player, static_cast<Enemy*>(nodeB), this->enemyNum) :
			static_cast<PCommonShot*>(nodeB)->Hit(_player, static_cast<Enemy*>(nodeA), this->enemyNum);
		CCLOG("p_b删除，e掉血");
		break;
	case GROUP_PLAYER_BOMB + GROUP_ENEMY:
		nodeA->getTag() == GROUP_PLAYER_BOMB ?
			static_cast<PBomb*>(nodeA)->Hit(_player, static_cast<Enemy*>(nodeB), this->enemyNum) :
			static_cast<PBomb*>(nodeB)->Hit(_player, static_cast<Enemy*>(nodeA), this->enemyNum);
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
			scene = StageOP::createScene();
			break;
		case 1:
			info_temp.dir = Vec2(176.5, 70);
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
		case 7:
			scene = GameOver::createScene();
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

	if (_player->getHp() <= 0) {
		Director::getInstance()->replaceScene(TransitionFade::create(2.0f, GameOver::createScene()));
	}
}

