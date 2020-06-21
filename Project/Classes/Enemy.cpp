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

void Enemy::DoOnCreated(int hp) {
	this->setHP(hp);
	this->setTag(GROUP_ENEMY);
	auto enemybody = cocos2d::PhysicsBody::createCircle(5.0f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	enemybody->setContactTestBitmask(0x03);
	enemybody->setCollisionBitmask(0x17);
	enemybody->setCategoryBitmask(0x04);
	enemybody->setTag(GROUP_ENEMY);
	enemybody->setDynamic(true);
	enemybody->setGravityEnable(false);
	this->setPhysicsBody(enemybody);
	srand((unsigned)(time(NULL)));

	if ((rand() % 100) + 1 < 20)
	{
		srand((unsigned)(time(NULL)));
		itemsDrop.lifeNum = rand() % 3 + 1;
	}
	else
	{
		srand((unsigned)(time(NULL)));
		itemsDrop.blueNum = rand() % 3 + 1;
	}
}

void Enemy::DoOnFrame() { }

void Enemy::beHit(PCommonShot* pb, Player* thePlayer)
{
	this->healthPoint -= pb->getDmg();
	if (healthPoint <= 0)
		DoOnDestroy(thePlayer);
}

void Enemy::DoOnDestroy(Player*	thePlayer)
{
	auto pDrop = cocos2d::CallFunc::create([=]() {
		auto p = P_Point::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto blueDrop = cocos2d::CallFunc::create([=]() {
		auto p = BluePoint::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto bombDrop = cocos2d::CallFunc::create([=]() {
		auto p = Bomb::create();
		p->setPosition(this->getPosition());
		p->DoOnCreate();
		p->DoOnFrame(thePlayer);
		p->setScale(1.2f);
		this->getParent()->addChild(p, GROUP_ITEM);
	});
	auto lifeDrop = cocos2d::CallFunc::create([=]() {
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
	itemsDrop.pNum = 2;
	itemsDrop.blueNum = 2;

	auto a = cocos2d::CallFunc::create([=] {
		auto from = this->getPosition();
		auto to = player->getPosition();
		auto sec = to - from;
		sec.normalize();
		sec *= 2;
		auto move = cocos2d::MoveBy::create(1.0 / 30.0, sec);
		auto rote = cocos2d::RotateBy::create(1.0 / 30.0, 30);
		this->runAction(move);
		this->runAction(rote);
	});
	auto delay = cocos2d::DelayTime::create(1.0 / 30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence*>(cocos2d::Sequence::create(a, delay, nullptr))));


	auto shootStar = cocos2d::CallFunc::create([=]() {

		Bullet *dankumu = Bullet::create("images/bullet/smallball.png");

		dankumu->setTag(GROUP_ENEMY_BULLET);
		//屏幕右下角坐标(26.5,0)
		dankumu->setPosition(this->getPosition());
		dankumu->setAngle(0);
		dankumu->setAim(true);
		dankumu->setVelocit(3);
		dankumu->setRot(0);
		//dankumu->setRotVelocity(10);
		dankumu->setAcceleration(0);
		dankumu->setAccAngle(-90);
		dankumu->setRebound(false);
		dankumu->DoOnCreate(player, 1.0);
		dankumu->DoOnFrame();
		this->getParent()->addChild(dankumu, GROUP_ENEMY_BULLET);
	});
	auto delay_b = cocos2d::DelayTime::create(3);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootStar, delay_b, nullptr))));
}

littleRed* littleRed::create(const char* pszFileName)
{
	littleRed* enemyA = new littleRed();
	if (enemyA && enemyA->initWithFile(pszFileName))
	{
		enemyA->autorelease();
		return enemyA;
	}
	CC_SAFE_DELETE(enemyA);
	return nullptr;
}

void littleRed::DoOnFrame(Player *)
{
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