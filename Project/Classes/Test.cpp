/****************************************************************************

 ****************************************************************************/


#include "Test.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"


USING_NS_CC;

Scene* Test::createScene()
{
	return Test::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Test::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto i = AudioEngine::play2d("music/00.mp3", true, 1.0f);
	AudioEngine::preload("music/cancel00.mp3");
	AudioEngine::preload("music/ok00.mp3");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Test::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	auto ttf1 = Label::createWithTTF("play", "fonts/Marker Felt.ttf", 24);
	auto mymenu1 = MenuItemLabel::create(ttf1, CC_CALLBACK_1(Test::menuPlayCallback, this));
	mymenu1->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 3 * ttf1->getContentSize().height));

	auto ttf2 = Label::createWithTTF("unknow", "fonts/Marker Felt.ttf", 24);
	auto mymenu2 = MenuItemLabel::create(ttf2, CC_CALLBACK_1(Test::menuPlayCallback, this));
	mymenu2->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 4 * ttf2->getContentSize().height));

	auto ttf3 = Label::createWithTTF("record", "fonts/Marker Felt.ttf", 24);
	auto mymenu3 = MenuItemLabel::create(ttf3, CC_CALLBACK_1(Test::menuRecordCallback, this));
	mymenu3->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 5 * ttf3->getContentSize().height));

	auto ttf4 = Label::createWithTTF("quit", "fonts/Marker Felt.ttf", 24);
	auto mymenu4 = MenuItemLabel::create(ttf4, CC_CALLBACK_1(Test::menuCloseCallback, this));
	mymenu4->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 6 * ttf4->getContentSize().height));

	auto mymenu = Menu::create(mymenu1, mymenu2, mymenu3, mymenu4, nullptr);
	mymenu->setPosition(Vec2(0,0));
	this->addChild(mymenu);


	return true;
}


void Test::menuCloseCallback(Ref* pSender)
{

	AudioEngine::end();
	auto play = cocos2d::CallFunc::create([]() {
		AudioEngine::play2d("music/cancel00.mp3", false, 1.0f);
	});
	auto delay = DelayTime::create(0.5f);
	auto end = cocos2d::CallFunc::create([]() {
		Director::getInstance()->end();
	});
	this->runAction(Sequence::create(play, delay, end, nullptr));

}
void Test::menuPlayCallback(Ref* pSender)
{
	AudioEngine::end();
	auto play = cocos2d::CallFunc::create([]() {
		AudioEngine::play2d("music/ok00.mp3", false, 1.0f);
	});
	auto delay = DelayTime::create(0.3f);
	auto tran = cocos2d::CallFunc::create([]() {
		Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
	});
	this->runAction(Sequence::create(play, delay, tran, nullptr));
}
void Test::menuRecordCallback(Ref* pSender)
{
	AudioEngine::end();
	AudioEngine::play2d("music/ok00.mp3", false, 1.0f);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, HelloWorld::createScene()));
}