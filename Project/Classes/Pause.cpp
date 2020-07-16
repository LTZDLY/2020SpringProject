/****************************************************************************

 ****************************************************************************/


#include "Pause.h"
#include "Test.h"

USING_NS_CC;

Scene* Pause::createScene()
{
	return Pause::create();
}
Scene* GameOver::createScene()
{
	return GameOver::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Pause::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Pause::menuCloseCallback, this));

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

	auto ttf1 = Label::createWithTTF("Return", "fonts/Marker Felt.ttf", 24);
	auto mymenu1 = MenuItemLabel::create(ttf1, CC_CALLBACK_1(Pause::menuReturnCallback, this));
	mymenu1->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 5 * ttf1->getContentSize().height));

	auto ttf2 = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24);
	auto mymenu2 = MenuItemLabel::create(ttf2, CC_CALLBACK_1(Pause::menuCloseCallback, this));
	mymenu2->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 6 * ttf2->getContentSize().height));

	auto mymenu = Menu::create(mymenu1, mymenu2, nullptr);
	mymenu->setPosition(Vec2(0,0));
	this->addChild(mymenu);


	return true;
}


void Pause::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Test::createScene()));
}
void Pause::menuReturnCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
}
bool GameOver::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameOver::menuCloseCallback, this));

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

	auto ttf1 = Label::createWithTTF("GameOver", "fonts/Marker Felt.ttf", 30);
	ttf1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 4 * ttf1->getContentSize().height));
	this->addChild(ttf1);

	auto ttf2 = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24);
	auto mymenu2 = MenuItemLabel::create(ttf2, CC_CALLBACK_1(GameOver::menuCloseCallback, this));
	mymenu2->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 10 * ttf2->getContentSize().height));

	auto mymenu = Menu::create(mymenu2, nullptr);
	mymenu->setPosition(Vec2(0,0));
	this->addChild(mymenu);


	return true;
}


void GameOver::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Test::createScene()));
}