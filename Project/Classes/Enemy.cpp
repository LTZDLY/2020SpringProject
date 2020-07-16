/*
	这是一个经过一定努力还是异常简陋的怪物类
	自定义敌人继承自Enemy
	注意重载DoOnCreated DoOnFrame
	pwq from ddl前的pfr
*/

#include "Enemy.h"


Enemy* Enemy::create(const char* pszFileName)
{
	Enemy* enemyA = new Enemy();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void Enemy::setHP(float hp)
{
	this->healthPoint = hp;
}

float Enemy::getHP(float hp)
{
	return this->healthPoint;
}

void Enemy::DoOnCreated(float hp, float hitbox) {
	this->setHP(hp);
	this->setTag(GROUP_ENEMY);
	auto enemybody = cocos2d::PhysicsBody::createCircle(hitbox, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
	enemybody->setContactTestBitmask(0x03);
	enemybody->setCollisionBitmask(0x97);
	enemybody->setCategoryBitmask(0x04);
	enemybody->setTag(GROUP_ENEMY);
	enemybody->setDynamic(true);
	enemybody->setGravityEnable(false);
	this->setPhysicsBody(enemybody);
	int flag = cocos2d::random(0, 10);
	
	if (flag >= 9)
	{
		itemsDrop.lifeNum += 1;
	}
	flag = cocos2d::random(0, 10);
	if (flag >= 6)
	{
		srand((unsigned)(time(NULL)));
		itemsDrop.blueNum += 1;
	}
	
}

void Enemy::DoOnFrame() { }

void Enemy::beHit(float dmg, Player* thePlayer, int& num)
{
	this->healthPoint -= dmg;
	if (healthPoint <= 0) DoOnDestroy(thePlayer);
	num--;
}

void Enemy::DoOnDestroy(Player*	thePlayer)
{
	auto pDrop = cocos2d::CallFunc::create([=]() {
		if (itemsDrop.pNum == 0) return;
		auto p = P_Point::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto blueDrop = cocos2d::CallFunc::create([=]() {
		if (itemsDrop.blueNum == 0) return;
		auto p = BluePoint::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto bombDrop = cocos2d::CallFunc::create([=]() {
		if (itemsDrop.bombNum == 0) return;
		auto p = Bomb::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto lifeDrop = cocos2d::CallFunc::create([=]() {
		if (itemsDrop.lifeNum == 0) return;
		auto p = LifePiece::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto delay = cocos2d::DelayTime::create(0.00001);
	auto a = cocos2d::Repeat::create(static_cast<cocos2d::Spawn*>(cocos2d::Spawn::create(pDrop, delay, nullptr)), itemsDrop.pNum);
	auto b = cocos2d::Repeat::create(static_cast<cocos2d::Spawn*>(cocos2d::Spawn::create(blueDrop, delay, nullptr)), itemsDrop.blueNum);
	auto c = cocos2d::Repeat::create(static_cast<cocos2d::Spawn*>(cocos2d::Spawn::create(bombDrop, delay, nullptr)), itemsDrop.bombNum);
	auto d = cocos2d::Repeat::create(static_cast<cocos2d::Spawn*>(cocos2d::Spawn::create(lifeDrop, delay, nullptr)), itemsDrop.lifeNum);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(cocos2d::Sequence::create(cocos2d::Spawn::create(a, b, c, d, nullptr), remove, nullptr));


	auto aaa = cocos2d::Sprite::create("Images/misc_05.png");
	aaa->setPosition(this->getPosition());
	this->getParent()->addChild(aaa, GROUP_ENEMY);
	aaa->setScale(0.0);
	auto actionBy = cocos2d::ScaleTo::create(0.5f, 3.0f);
	auto actionRote = cocos2d::RotateBy::create(0.5f, 180);
	auto actionFade = cocos2d::FadeOut::create(0.5f);
	auto sss = cocos2d::Spawn::create(actionBy, actionRote, actionFade, nullptr);
	aaa->runAction(cocos2d::Sequence::create(sss, remove->clone(), nullptr));
}

myEnemy* myEnemy::create(const char* pszFileName)
{
	myEnemy* enemyA = new myEnemy();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void myEnemy::DoOnCreated()//生成瞬间执行动作
{
	this->setTag(GROUP_ENEMY);
	auto enemybody = cocos2d::PhysicsBody::createCircle(7.0f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	enemybody->setContactTestBitmask(0x03);
	enemybody->setCollisionBitmask(0x17);
	enemybody->setCategoryBitmask(0x04);
	enemybody->setTag(GROUP_ENEMY);
	enemybody->setDynamic(true);
	enemybody->setGravityEnable(false);
	this->setPhysicsBody(enemybody);

	auto rotateBy = cocos2d::RotateBy::create(0.5f, 180.0f);
	auto sequence = cocos2d::Sequence::create(rotateBy, rotateBy->clone(), nullptr);
	this->runAction(sequence);
}

void myEnemy::DoOnFrame()//每隔一段时间随机移动
{
	auto a = cocos2d::CallFunc::create([=]() {
		auto x = cocos2d::random(-5.0, 5.0) * 10;
		auto y = cocos2d::random(-5.0, 5.0) * 10;
		auto move1 = cocos2d::MoveBy::create(1, cocos2d::Vec2(x, 0));
		auto move2 = cocos2d::MoveBy::create(1, cocos2d::Vec2(0, y));
		this->runAction(cocos2d::Sequence::create(move1, move2, nullptr));
	});
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(a, delay, nullptr))));
}

chaseEnemy* chaseEnemy::create()
{
	const char* pszFileName = "images/enemy/enemy_10.png";
	chaseEnemy* enemyA = new chaseEnemy();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		enemyA->setScale(1.2f);
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void chaseEnemy::DoOnFrame(Player* player)
{
	itemsDrop.pNum = 3;
	itemsDrop.blueNum = 0;
	itemsDrop.lifeNum = 0;
	itemsDrop.bombNum = 0;
	this->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	auto a = cocos2d::CallFunc::create([=] {
		auto from = this->getPosition();
		auto to = player->getPosition();
		auto sec = to - from;
		sec.normalize();
		sec *= 1;
		auto move = cocos2d::MoveBy::create(1.0 / 30.0, sec);
		auto rote = cocos2d::RotateBy::create(1.0 / 30.0, 30);
		this->runAction(move);
		this->runAction(rote);
	});
	auto delay = cocos2d::DelayTime::create(1.0 / 30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(a, delay, nullptr))));

	ang = 0;
	auto shootStar = cocos2d::CallFunc::create([=]() {

		Bullet *dankumu = Bullet::create("images/bullet/ellipse.png");

		dankumu->setTag(GROUP_ENEMY_BULLET);
		//屏幕右下角坐标(26.5,0)
		auto v = this->getContentSize();
		dankumu->setPosition(v / 2);
		dankumu->setRotVelocity(7);
		dankumu->setRot(ang);
		dankumu->setDestroyable(false);
		dankumu->setVelocit(0);
		dankumu->DoOnCreate(player, 30.0);
		dankumu->DoOnFrame();
		auto sc = cocos2d::ScaleTo::create(0.001, 5, 0.2);
		dankumu->runAction(sc);
		this->addChild(dankumu, GROUP_ENEMY_BULLET);
		ang += 360 / 3;
	});
	auto delayNo = cocos2d::DelayTime::create(0.00001);
	this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delayNo, nullptr)), 3));
}

littleRed* littleRed::create()
{
	const char* pszFileName = "images/enemy/enemy_06.png";
	littleRed* enemyA = new littleRed();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void littleRed::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 5;
	auto abb = cocos2d::CallFunc::create([=]() {
		auto x = cocos2d::random(-5.0, 5.0) * 10;
		auto y = cocos2d::random(-5.0, 5.0) * 10;
		auto to1 = this->getPosition() + cocos2d::Vec2(x, 0);
		if (to1.x < 50) to1.x = 50;
		if (to1.x > 300) to1.x = 300;
		auto to2 = cocos2d::Vec2(to1.x, this->getPositionY() + y);
		if (to2.y < 20) to2.y = 20;
		if (to2.y > 300) to2.y = 300;
		auto move1 = cocos2d::MoveTo::create(1, to1);
		auto move2 = cocos2d::MoveTo::create(1, to2);
		this->runAction(cocos2d::Sequence::create(move1, move2, nullptr));
	});
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(abb, delay, nullptr))));

	auto kaihua = cocos2d::CallFunc::create([=]() {
		a = 0.0;
		auto shootStar = cocos2d::CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("images/bullet/smallball.png");
			//屏幕右下角坐标(26.5,0)
			dankumu->setPosition(this->getPosition());
			dankumu->setVelocit(3);
			dankumu->setAngle(a);
			dankumu->setAim(true);
			dankumu->DoOnCreate(player, 3.0);
			dankumu->DoOnFrame();
			this->getParent()->addChild(dankumu, GROUP_ENEMY_BULLET);
			a += 360.0 / static_cast<float>(way);
		});
		auto delay = cocos2d::DelayTime::create(0.0001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delay, nullptr)), way));
	});
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(kaihua, delay->clone(), nullptr))));
}

littleGreen* littleGreen::create()
{
	const char* pszFileName = "images/enemy/enemy_07.png";
	littleGreen* enemyA = new littleGreen();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void littleGreen::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 7;
	this->itemsDrop.blueNum += 2;
	auto abb = cocos2d::CallFunc::create([=]() {
		auto from = this->getPosition();
		auto x = cocos2d::random(3.0, 5.0) * 20 * (cocos2d::random(0, 1) * 2 - 1);
		auto y = cocos2d::random(3.0, 4.0) * 10 * (cocos2d::random(0, 1) * 2 - 1);
		auto to = from + cocos2d::Vec2(x, y);
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create(1, to);
		this->runAction(move);
	});
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(abb, delay, nullptr))));
	auto anggg = cocos2d::random(0, 3) * 90;
	auto kaihua = cocos2d::CallFunc::create([=]() {
		a = anggg - 180 + cocos2d::random(-10, 10) - (way - 1) * 5;
		auto shootStar = cocos2d::CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("images/bullet/grain.png");
			dankumu->setPosition(this->getPosition());
			dankumu->setVelocit(5);
			dankumu->setAngle(a);
			dankumu->setAcceleration(0.1);
			dankumu->setAccAngle(anggg);
			dankumu->DoOnCreate(player, 1.5);
			dankumu->DoOnFrame();
			this->getParent()->addChild(dankumu, GROUP_ENEMY_BULLET);
			a += 10;
		});
		auto delay = cocos2d::DelayTime::create(0.0001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delay, nullptr)), way));
	});
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(kaihua, delay->clone(), nullptr))));
}

bigBound* bigBound::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	bigBound* enemyA = new bigBound();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void bigBound::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 10;
	this->itemsDrop.blueNum += 5;
	this->itemsDrop.bombNum += 1;
	auto abb = cocos2d::CallFunc::create([=]() {
		auto from = this->getPosition();
		auto x = cocos2d::random(3.0, 5.0) * 10 * (cocos2d::random(0, 1) * 2 - 1);
		auto y = cocos2d::random(3.0, 4.0) * 7 * (cocos2d::random(0, 1) * 2 - 1);
		auto to = from + cocos2d::Vec2(x, y);
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move_ease_in = cocos2d::EaseExponentialOut::create(cocos2d::MoveTo::create(3, to));
		this->runAction(move_ease_in);
	});
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(abb, delay, nullptr))));
	auto anggg = cocos2d::random(0, 3) * 90;
	auto kaihua = cocos2d::CallFunc::create([=]() {
		a = cocos2d::random(0, 360);
		auto shootStar = cocos2d::CallFunc::create([=]() {
			Bullet *dankumu = Bullet::create("images/bullet/grain.png");
			dankumu->setPosition(this->getPosition());
			dankumu->setVelocit(3);
			dankumu->setAngle(a);
			dankumu->setRebound(true);
			dankumu->DoOnCreate(player, 1.5);
			dankumu->DoOnFrame();
			this->getParent()->addChild(dankumu, GROUP_ENEMY_BULLET);
			a += 360.0 / static_cast<float>(way);
		});
		auto delay = cocos2d::DelayTime::create(0.0001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delay, nullptr)), way));
	});
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(kaihua, delay->clone(), nullptr))));
}

bigCross* bigCross::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	bigCross* enemyA = new bigCross();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void bigCross::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 10;
	this->itemsDrop.blueNum += 5;
	this->itemsDrop.lifeNum += 1;
	auto ang = cocos2d::random(0, 360);
	auto shootStar2 = cocos2d::CallFunc::create([=]() {
		temp1 = cocos2d::random(0, 360);
		temp2 = 0;
		auto shootStar = cocos2d::CallFunc::create([=]() {
			jiaocha* dankumu = jiaocha::create("grain.png");
			dankumu->setPosition(this->getPosition());
			dankumu->DoOnCreate(3, temp1, temp2);
			dankumu->DoOnFrame(1.5);
			this->getParent()->addChild(dankumu);
			temp2++;
			temp1 += 360.0 / static_cast<float>(way);
		});
		auto delay_no = cocos2d::DelayTime::create(0.000000001);
		auto kaihua = cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar, delay_no, nullptr)), way);
		this->runAction(kaihua);
	});
	auto delay = cocos2d::DelayTime::create(2);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar2, delay, nullptr))));
}


midRed* midRed::create()
{
	const char* pszFileName = "images/enemy/enemy_03.png";
	midRed* enemyA = new midRed();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void midRed::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 5;
	this->itemsDrop.blueNum += 2;
	auto abb = cocos2d::CallFunc::create([=]() {
		auto from = this->getPosition();
		auto x = cocos2d::random(3.0, 5.0) * 20 * (cocos2d::random(0, 1) * 2 - 1);
		auto y = cocos2d::random(3.0, 4.0) * 10 * (cocos2d::random(0, 1) * 2 - 1);
		auto to = from + cocos2d::Vec2(x, y);
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create(1, to);
		this->runAction(move);
	});

	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(abb, delay, nullptr))));
	auto shootStar2 = cocos2d::CallFunc::create([=]() {
		temp1 = (way - 1) * 25;
		auto shootStar = cocos2d::CallFunc::create([=]() {
			auto dankumu = Follow::create("images/bullet/lightball_dark.png");
			dankumu->setPosition(this->getPosition());
			dankumu->DoOnCreate(player, 5.0);
			dankumu->DoOnFrame(player);
			dankumu->setVelocit(2);
			dankumu->setAngle(temp1);
			dankumu->setAim(true);
			this->getParent()->addChild(dankumu);
			temp1 += 50;
		});
		auto delay = cocos2d::DelayTime::create(0.0001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delay, nullptr)), way));
	});
	auto delay_b = cocos2d::DelayTime::create(5);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar2, delay_b, nullptr))));
}



bigBloom* bigBloom::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	bigBloom* enemyA = new bigBloom();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void bigBloom::DoOnFrame(Player* player, int way) {
	this->itemsDrop.pNum += 10;
	this->itemsDrop.blueNum += 3;
	this->itemsDrop.lifeNum += 1;
	auto shootStar3 = cocos2d::CallFunc::create([=]() {
		temp0 = cocos2d::random(0.0, 360.0);
		auto shootStar2 = cocos2d::CallFunc::create([=]() {
			auto shootStar = cocos2d::CallFunc::create([=]() {
				if (temp5 == 10) {
					temp5 = 0;
					temp0 += 360.0 / static_cast<float>(way);
					temp1 = temp0;
					temp2 = temp0;
					temp3 = 3;
					temp4 = 4;
				}
				Bullet* dankumu1 = Bullet::create("images/bullet/circle.png");
				dankumu1->setPosition(this->getPosition());
				dankumu1->setAngle(temp1);
				dankumu1->setVelocit(temp4);
				dankumu1->DoOnCreate(player, 1.5);
				dankumu1->DoOnFrame();
				this->getParent()->addChild(dankumu1);
				Bullet* dankumu2 = Bullet::create("images/bullet/circle.png");
				dankumu2->setPosition(this->getPosition());
				dankumu2->setAngle(temp2);
				dankumu2->setVelocit(temp4);
				dankumu2->DoOnCreate(player, 1.5);
				dankumu2->DoOnFrame();
				this->getParent()->addChild(dankumu2);
				temp1 -= temp3;
				temp2 += temp3;
				temp3 -= 0.15;
				temp4 -= 0.3;
				temp5++;
			});
			auto delay_no = cocos2d::DelayTime::create(0.000000001);
			auto kaihua = cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar, delay_no, nullptr)), 10);
			this->runAction(kaihua);
		});
		auto delay = cocos2d::DelayTime::create(0.00001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar2, delay, nullptr)), way));
	});
	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar3, delay, nullptr))));

}


Boss1* Boss1::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	Boss1* enemyA = new Boss1();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void Boss1::DoOnFrame(Player* player) {
	this->itemsDrop.pNum += 20;
	this->itemsDrop.blueNum += 20;
	auto abb = cocos2d::CallFunc::create([=]() {
		auto from = this->getPosition();
		auto x = cocos2d::random(3.0, 5.0) * 20 * (cocos2d::random(0, 1) * 2 - 1);
		auto y = cocos2d::random(3.0, 4.0) * 10 * (cocos2d::random(0, 1) * 2 - 1);
		auto to = from + cocos2d::Vec2(x, y);
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create(1, to);
		this->runAction(move);
	});

	this->rr = -90;
	this->a = 0;
	this->b = 0.1;
	auto shootStar2 = cocos2d::CallFunc::create([=]() {
		auto shootStar = cocos2d::CallFunc::create([=]() {
			auto a = this->getPosition();
			a.x += 20 * (float)cos(this->r * acos(-1) / 180);
			a.y += 20 * (float)sin(this->r * acos(-1) / 180);
			auto bullet = Bullet::create("grain.png");
			bullet->setAngle(r);
			bullet->setVelocit(4);
			bullet->setPosition(a);
			bullet->DoOnCreate(player, 1.5);
			bullet->DoOnFrame();
			this->getParent()->addChild(bullet);
			this->r += 360.0 / 8.0;
		});
		this->r = this->rr;
		this->a -= this->b;
		this->rr -= this->a;
		auto delay_no = cocos2d::DelayTime::create(0.00000001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar, delay_no, nullptr)), 8));
	});
	auto delay_no = cocos2d::DelayTime::create(0.00000000001);
	auto delay = cocos2d::DelayTime::create(0.05);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar2, delay, nullptr))));
}


Boss2* Boss2::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	Boss2* enemyA = new Boss2();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void Boss2::DoOnFrame(Player* player) {
	this->itemsDrop.pNum += 10;
	this->itemsDrop.blueNum += 5;
	this->itemsDrop.lifeNum += 1;
	auto ang = cocos2d::random(0, 360);
	auto shootStar2 = cocos2d::CallFunc::create([=]() {
		temp1 = cocos2d::random(0, 360);
		temp2 = 0;
		auto shootStar = cocos2d::CallFunc::create([=]() {
			jiaocha* dankumu = jiaocha::create("grain.png");
			dankumu->setPosition(this->getPosition());
			dankumu->DoOnCreate(4, temp1, temp2);
			dankumu->DoOnFrame(1.5);
			this->getParent()->addChild(dankumu);
			temp2++;
			temp1 += 360.0 / static_cast<float>(100);
		});
		auto delay_no = cocos2d::DelayTime::create(0.000000001);
		auto kaihua = cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar, delay_no, nullptr)), 100);
		this->runAction(kaihua);
	});
	auto delay = cocos2d::DelayTime::create(1);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar2, delay, nullptr))));
}


Boss3* Boss3::create()
{
	const char* pszFileName = "images/enemy/enemy_05.png";
	Boss3* enemyA = new Boss3();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void Boss3::DoOnFrame(Player* player) {
	auto abb = cocos2d::CallFunc::create([=]() {
		auto from = this->getPosition();
		auto x = cocos2d::random(3.0, 5.0) * 5 * (cocos2d::random(0, 1) * 2 - 1);
		auto y = cocos2d::random(3.0, 4.0) * 3 * (cocos2d::random(0, 1) * 2 - 1);
		auto to = from + cocos2d::Vec2(x, y);
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create(1, to);
		this->runAction(move);
	});

	auto delay = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(abb, delay, nullptr))));

	temp2 = 20;
	auto shootStar5 = cocos2d::CallFunc::create([=]() {
		temp5 = cocos2d::random(0.0, 360.0);
		auto shootStar4 = cocos2d::CallFunc::create([=]() {
			auto dankumu = Bullet::create("images/bullet/middleball.png");
			dankumu->setPosition(this->getPosition());
			dankumu->setAngle(temp5);
			dankumu->setVelocit(4);
			dankumu->DoOnCreate(player, 4);
			dankumu->DoOnFrame();
			this->getParent()->addChild(dankumu);
			temp5 += 360.0 / 20.0;
		});
		auto delayNo = cocos2d::DelayTime::create(0.001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar4, delayNo, nullptr)), 20));
	});
	auto delayMb = cocos2d::DelayTime::create(1);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar5, delayMb, nullptr))));
	auto shootStar3 = cocos2d::CallFunc::create([=]() {
		temp2 = cocos2d::random(0.0, 360.0);
		auto shootStar2 = cocos2d::CallFunc::create([=]() {
			auto shootStar = cocos2d::CallFunc::create([=]() {
				if (temp4 == 10) {
					temp4 = 0;
					temp1 = 10;
					temp2 += 30;
				}
				Speed* dankumu = Speed::create("images/bullet/ofuda.png");
				dankumu->setPosition(this->getPosition());
				dankumu->setAngle(temp2);
				dankumu->setVelocit(temp1);
				dankumu->DoOnCreate(player, 1.5);
				dankumu->DoOnFrame(player);
				this->getParent()->addChild(dankumu);
				Speed* dankumu2 = Speed::create("images/bullet/ofuda.png");
				dankumu2->setPosition(this->getPosition());
				dankumu2->setAngle(temp2 + 5);
				dankumu2->setVelocit(temp1);
				dankumu2->DoOnCreate(player, 1.5);
				dankumu2->DoOnFrame(player);
				this->getParent()->addChild(dankumu2);
				temp1 -= 0.8;
				temp4++;
			});
			auto delay_no = cocos2d::DelayTime::create(0.000000001);
			auto kaihua = cocos2d::Repeat::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shootStar, delay_no, nullptr)), 10);
			this->runAction(kaihua);
		});
		auto delay = cocos2d::DelayTime::create(0.2);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar2, delay, nullptr)),7));
	});
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar3, delay->clone(), nullptr))));
}


/*
template<class T> void Enemy::Drop(T, Player* thePlayer) {
	auto itemDrop = cocos2d::CallFunc::create([=]() {
		auto p = T::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto delay = cocos2d::DelayTime::create(0.00001);
	auto a = cocos2d::Repeat::create(static_cast<cocos2d::Spawn*>(cocos2d::Spawn::create(pDrop, delay, nullptr)), itemsDrop.pNum);
}
*/