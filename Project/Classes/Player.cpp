/****************************************************************************
这里是实现所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#include "Player.h"

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

void Player::DoOnFrame() {

	Player::DoDefaultAction();
}

void Player::DoDefaultAction() {
	auto a = cocos2d::CallFunc::create([=]()
	{
		auto now = this->getPosition();
		auto to = now;
		if (shift == false) {
			if (pdd.alpha > 0) pdd.alpha -= 15;
			v_ = 8.0;
		}
		else {
			if (pdd.alpha < 255) pdd.alpha += 15;
			v_ = 3.0;
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
		
		switch (keyboardnum) {
		case 1:
			to.x -= v_;
			break;
		case 2:
			to.x += v_;
			break;
		case 4:
			to.y += v_;
			break;
		case 8:
			to.y -= v_;
			break;
		case 5:
			to.x -= v_ * sqrt(2) / 2.0;
			to.y += v_ * sqrt(2) / 2.0;
			break;
		case 9:
			to.x -= v_ * sqrt(2) / 2.0;
			to.y -= v_ * sqrt(2) / 2.0;
			break;
		case 6:
			to.x += v_ * sqrt(2) / 2.0;
			to.y += v_ * sqrt(2) / 2.0;
			break;
		case 10:
			to.x += v_ * sqrt(2) / 2.0;
			to.y -= v_ * sqrt(2) / 2.0;
			break;
		}
		if (to.x < 10) to.x = 10;
		if (to.x > 400) to.x = 400;
		if (to.y < 10) to.y = 10;
		if (to.y > 400) to.y = 400;
		auto move = cocos2d::MoveTo::create((1.0 / 30.0), to);
		this->pdd.pdd1->runAction(cocos2d::Sequence::create(move->clone() , nullptr));
		this->pdd.pdd2->runAction(cocos2d::Sequence::create(move->clone(), nullptr));
		this->runAction(cocos2d::Sequence::create(move, nullptr));
	});
	auto delay = cocos2d::DelayTime::create((1.0 / 30.0));
	this->runAction(cocos2d::RepeatForever::create(static_cast<cocos2d::Sequence *>(cocos2d::Sequence::create(a, delay, nullptr))));
}