/****************************************************************************

 ****************************************************************************/


#include "Welcome.h"
#include "Test.h"
USING_NS_CC;

Scene* Welcome::createScene()
{
	return Welcome::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Welcome::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//cocos2d::AudioEngine::play2d("music/pop.mp3", true, 0.1f);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Welcome", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
		label->setOpacity(0);
	}

	// add "Welcome" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
		sprite->setOpacity(0);

		auto in = cocos2d::FadeIn::create(1.0f);
		auto delay = cocos2d::DelayTime::create(1.0f);
		auto out = cocos2d::FadeOut::create(1.0f);
		auto del = cocos2d::RemoveSelf::create();

		auto cfunc = cocos2d::CallFunc::create([](){
			Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Test::createScene()));
		});

		auto seq = cocos2d::Sequence::create(in, delay, out, del, cfunc, nullptr);
		label->runAction(seq->clone());
		sprite->runAction(seq);
	}
	return true;
}


void Welcome::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	//Director::getInstance()->end();
	Director::getInstance()->replaceScene(TransitionFade::create(2.0f, Test::createScene()));

	/*To navigate back to native iOS screen(if present) without quitting the application,
	do not use Director::getInstance()->end() as given above,
	instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);

}