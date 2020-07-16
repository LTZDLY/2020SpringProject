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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class HelloWorld : public cocos2d::Scene
{
private:
	Player* _player;
	cocos2d::Sprite* _enemy;
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	void addKeyboardListener();
	void addContactListener();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void HelloWorld::addMonster(float dt);
	void HelloWorld::addbullet(float dt); 
	void HelloWorld::addPlayer(float dt);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	bool onConcactBegin(cocos2d::PhysicsContact & contact);
	float temp;
	float temp2;
	float temp3;
	float temp4;
	cocos2d::Label*   _labelPosition;
};

/*
class MyEnemy : public cocos2d::Sprite {
	void MyEnemy::DoOnFrame();
};
//样例代码，并未测试过有效性
*/



#endif // __HELLOWORLD_SCENE_H__


