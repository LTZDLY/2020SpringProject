/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "AudioEngine.h"

Player* Player::create(const char *filename)
{
	Player *sprite = new Player();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Player::DoOnCreate() {
	this->setTag(GROUP_PLAYER);
	pdd.pdd1->setPosition(convertToNodeSpace(this->getPosition()));
	pdd.pdd2->setPosition(convertToNodeSpace(this->getPosition()));
	pdd.pdd1->setOpacity(0);
	pdd.pdd2->setOpacity(0);
	this->addChild(pdd.pdd1, GROUP_PLAYER_PDD);
	this->addChild(pdd.pdd2, GROUP_PLAYER_PDD);
	pdd.pdd1->setTag(GROUP_PLAYER_GRAZE);
	auto grazebody = cocos2d::PhysicsBody::createCircle(9.0f, cocos2d::PhysicsMaterial(0.0f, 0.0f, 0.0f));
	grazebody->setContactTestBitmask(0x08);//和谁碰撞会处理响应函数
	grazebody->setCollisionBitmask(0x08);//能和谁碰撞
	grazebody->setCategoryBitmask(0x40);//我是谁
	grazebody->setTag(GROUP_PLAYER_GRAZE);
	grazebody->setDynamic(false);
	grazebody->setGravityEnable(false);
	pdd.pdd1->setPhysicsBody(grazebody);


	auto playbody = cocos2d::PhysicsBody::createCircle(1.5f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	playbody->setContactTestBitmask(0x3D);//和谁碰撞会处理响应函数
	playbody->setCollisionBitmask(0x3D);//能和谁碰撞
	playbody->setCategoryBitmask(0x01);//我是谁
	playbody->setTag(GROUP_PLAYER);
	playbody->setDynamic(false);
	playbody->setGravityEnable(false);
	this->setPhysicsBody(playbody);
};
void Player::DoOnFrame() {

	Player::DoDefaultAction();
}

void Player::DoDefaultAction() {
	auto Move = cocos2d::CallFunc::create([=]()
	{
		if (info._invincibled > 0) {
			info._invincibled--;
			if (info._invincibled_cd > 0) info._invincibled_cd--;
			else {
				if (this->getOpacity() == 255) this->setOpacity(100);
				else this->setOpacity(255);
			}
		}
		if (info.shift == false) {
			if (pdd.alpha > 0) pdd.alpha = 0;
			this->info._v = 6.0;
		}
		else {
			if (pdd.alpha < 255) pdd.alpha += 15;
			this->info._v = 2.5;
		}
		this->pdd.rot1 += 5;
		auto ang1 = this->pdd.rot1;
		auto rota1 = cocos2d::RotateTo::create((0.000001), -ang1);
		auto fade = cocos2d::FadeTo::create(0.00001, pdd.alpha);
		this->pdd.pdd1->runAction(cocos2d::Sequence::create(fade->clone(), rota1, nullptr));

		this->pdd.rot2 -= 5;
		auto ang2 = this->pdd.rot2;
		auto rota2 = cocos2d::RotateTo::create((0.000001), -ang2);
		this->pdd.pdd2->runAction(cocos2d::Sequence::create(fade, rota2, nullptr));

		if (this->info._hit_cd != 0) {
			this->info._hit_cd--;
			return;
		}

		if (info._invincibled == 0 && this->getOpacity() != 255) this->setOpacity(255);
		if (this->info._collect == false) this->info._collect = true;
		
		auto now = this->getPosition();
		auto to = now;
		switch (info.keyboardnum) {
		case 1:
			to.x -= this->info._v;
			if (info.shift == false) this->info._angle = 180;
			break;
		case 2:
			to.x += this->info._v;
			if (info.shift == false) this->info._angle = 0;
			break;
		case 4:
			to.y += this->info._v;
			if (info.shift == false) this->info._angle = 90;
			break;
		case 8:
			to.y -= this->info._v;
			if (info.shift == false) this->info._angle = 270;
			break;
		case 5:
			to.x -= this->info._v * sqrt(2) / 2.0;
			to.y += this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 135;
			break;
		case 9:
			to.x -= this->info._v * sqrt(2) / 2.0;
			to.y -= this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 225;
			break;
		case 6:
			to.x += this->info._v * sqrt(2) / 2.0;
			to.y += this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 45;
			break;
		case 10:
			to.x += this->info._v * sqrt(2) / 2.0;
			to.y -= this->info._v * sqrt(2) / 2.0;
			if (info.shift == false) this->info._angle = 315;
			break;
		}
		if (to.x < 50) to.x = 50;
		if (to.x > 300) to.x = 300;
		if (to.y < 20) to.y = 20;
		if (to.y > 300) to.y = 300;
		auto move = cocos2d::MoveTo::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(Move, delay, nullptr))));
}
void Player::Atk() {
	static int fromAngle;
	static float setV;
	auto shoot = cocos2d::CallFunc::create([=]() {
		if (this->info._bullet_cd > 0) {
			this->info._bullet_cd--;
			return;
		}
		if (this->info.shoot == false) return;
		this->info._bullet_cd = 10;
		int times = this->info._powers / 100;
		fromAngle = (-2) * (times - 1);
		setV = 8;
		auto shootone = cocos2d::CallFunc::create([=]() {
			auto bullet = PCommonShot::create("playerbullet.png");
			bullet->setPosition(this->getPosition());
			bullet->setAngle(this->info._angle + fromAngle);
			bullet->setVelocit(setV);
			bullet->DoOnCreate(1);
			this->getParent()->addChild(bullet, GROUP_PLAYER_BULLET);
			bullet->DoOnFrame();
			fromAngle += 4;
			setV += 0.1;
		});
		auto delay_no = cocos2d::DelayTime::create(0.01);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(shootone, delay_no, nullptr)), times));
	});
	auto delay_shoot = cocos2d::DelayTime::create(1.0/30.0);
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(shoot, delay_shoot, nullptr))));
}

void Player::beHit(Bullet* dankumu)
{
	if (dankumu->getDestoryable() == true) {
		auto remove = cocos2d::RemoveSelf::create();
		dankumu->runAction(remove);
	}
	if (this->info._invincibled == 0) {
		this->info._hp -= dankumu->getDmg();
		cocos2d::AudioEngine::play2d("music/pldead00.mp3", false, 0.2f);
		this->info._collect = false;
		this->setInvincibled(120);
		this->setHitCd(30);
		this->powerDrop(50);

		float x = 50;
		float r = dankumu->getAngle() + cocos2d::random(-0.7, 0.7);
		cocos2d::Vec2 to = { x*cos(r),x*sin(r) };
		auto move_ease_in = cocos2d::EaseExponentialOut::create(cocos2d::MoveBy::create(1.5, to));
		this->runAction(move_ease_in);
		this->info._hit_flag = true;

		auto drop = cocos2d::CallFunc::create([=]() {
			auto p = P_Point::create();
			p->setPosition(this->getPosition());
			p->DoOnCreate();
			p->DoOnFrame(this);
			p->setScale(1.2f);
			this->getParent()->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(0.00001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(drop, delay, nullptr)), 3));
	}
}

void Player::beHit(Enemy* enemy)
{
	if (this->info._invincibled == 0) {
		this->info._hp -= 1;
		cocos2d::AudioEngine::play2d("music/pldead00.mp3", false, 0.2f);
		this->info._collect = false;
		this->setInvincibled(120);
		this->setHitCd(30);
		this->powerDrop(50);

		float x = 50;
		float r = cocos2d::random(0.0, 2 * PI);
		cocos2d::Vec2 to = { x*cos(r),x*sin(r) };
		auto move_ease_in = cocos2d::EaseExponentialOut::create(cocos2d::MoveBy::create(1.5, to));
		this->runAction(move_ease_in);
		this->info._hit_flag = true;

		auto drop = cocos2d::CallFunc::create([=]() {
			auto p = P_Point::create();
			p->setPosition(this->getPosition());
			p->DoOnCreate();
			p->DoOnFrame(this);
			p->setScale(1.2f);
			this->getParent()->addChild(p, GROUP_ITEM);
		});
		auto delay = cocos2d::DelayTime::create(0.00001);
		this->runAction(cocos2d::Repeat::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(drop, delay, nullptr)), 3));
	}
}

void Player::setInvincibled(int t) { this->info._invincibled = t; }
void Player::powerAdd(int p) {
	if (this->info._powers + p >= 400) this->info._powers = 400;
	else this->info._powers += p; 
}
void Player::powerDrop(int p){
	if (this->info._powers - p <= 100) this->info._powers = 100;
	else this->info._powers -= p;
}
void Player::scoreAdd(LONG32 s) { this->info._score += s; }
void Player::grazeAdd(int n) { 
	this->info._graze += n; 
	this->info._graze_temp -= n;
	if (this->info._graze_temp == 0) {
		this->info._graze_temp = 10;
		this->info._score_get_max += 10;
	}
}
void Player::setHitCd(int t) { this->info._hit_cd = t; }
LONG32 Player::getScoreGetMax() { return this->info._score_get_max; }
LONG64 Player::getScore() { return this->info._score; }
LONG32 Player::getGraze() { return this->info._graze; }
int Player::getPower() { return this->info._powers; }
float Player::getHp() { return this->info._hp; }
int Player::getBombs() { return this->info._bombs; }

void Player::setBomb() {
	auto node = this->getParent();
	std::vector<cocos2d::Color3B> col;
	std::vector<PBomb*> spr;
	col.push_back(cocos2d::Color3B(255, 0, 0));
	col.push_back(cocos2d::Color3B(255, 155, 0));
	col.push_back(cocos2d::Color3B(255, 255, 0));
	col.push_back(cocos2d::Color3B(0, 255, 0));
	col.push_back(cocos2d::Color3B(0, 255, 255));
	col.push_back(cocos2d::Color3B(0, 0, 255));
	col.push_back(cocos2d::Color3B(255, 0, 255));
	static float ang[7];
	for (int i = 0; i < 7; i++) {
		spr.push_back(PBomb::create());
		spr[i]->setScale(3.0);
		ang[i] = i * 360.0 / 7.0;
		spr[i]->setAngle(ang[i]);
		spr[i]->setColor(col[i]);
		spr[i]->DoOnCreate(10);
		spr[i]->setDmg(10);
		spr[i]->DoDefaultAction();
		spr[i]->setPosition(this->getPosition());
		node->addChild(spr[i]);
	}
}

PCommonShot* PCommonShot::create(const char *filename)
{
	PCommonShot *sprite = new PCommonShot();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void PCommonShot::DoOnCreate(float f) {
	auto physicsBody = cocos2d::PhysicsBody::createCircle(f, cocos2d::PhysicsMaterial(1.0f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setContactTestBitmask(0x04);
	physicsBody->setCollisionBitmask(0x04);
	physicsBody->setCategoryBitmask(0x02);
	this->setPhysicsBody(physicsBody);
	this->setTag(GROUP_PLAYER_BULLET);
}
void PCommonShot::DoOnFrame() {
	this->DoDefaultAction();
}

void PCommonShot::DoDefaultAction() {
	auto Move = cocos2d::CallFunc::create([=]() {
		auto now = this->getPosition();
		auto to = cocos2d::Vec2(0, 0);
		to.x += this->_velocity * cos(this->_angle / 180.0 * PI);
		to.y += this->_velocity * sin(this->_angle / 180.0 * PI);;
		auto move = cocos2d::MoveBy::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
		if ((now.x < 0 || now.x > 350 || now.y < -30 || now.y > 350)) {
			auto remove = cocos2d::RemoveSelf::create();
			this->runAction(remove);
			CCLOG("destory");
		}
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(Move, delay, nullptr))));
}
void PCommonShot::setVelocit(float v) { this->_velocity = v; }
void PCommonShot::setAngle(float r) {
	this->_angle = r;
	auto rota = cocos2d::RotateTo::create((0.0), -r);
	this->runAction(cocos2d::Sequence::create(rota, nullptr));
}
void PCommonShot::setDmg(float d) { this->_dmg = d; }
float PCommonShot::getDmg() { return this->_dmg; }
void PCommonShot::Hit(Player* player, Enemy* enemy) {
	player->scoreAdd(30);
	auto remove = cocos2d::RemoveSelf::create();
	this->runAction(remove);
	enemy->beHit(this, player);
}

PBomb* PBomb::create()
{
	const char *filename = "images/bomb_ef.png";
	PBomb *sprite = new PBomb();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void PBomb::DoDefaultAction() {
	vv = 1;
	ang = this->_angle;
	auto Move = cocos2d::CallFunc::create([=]() {
		this->setVelocit(vv);
		this->setAngle(ang);
		ang += 10.0;
		vv += 0.2;
		auto now = this->getPosition();
		auto to = cocos2d::Vec2(0, 0);
		to.x += this->_velocity * cos(this->_angle / 180.0 * PI);
		to.y += this->_velocity * sin(this->_angle / 180.0 * PI);;
		auto move = cocos2d::MoveBy::create((1.0 / 30.0), to);
		this->runAction(cocos2d::Sequence::create(move, nullptr));
		this->_timer++;
		if (this->_timer > 180 && (now.x < -100 || now.x > 450 || now.y < -130 || now.y > 450)) {
			auto remove = cocos2d::RemoveSelf::create();
			this->runAction(remove);
			CCLOG("destory");
		}
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Spawn *>(cocos2d::Spawn::create(Move, delay, nullptr))));
}
