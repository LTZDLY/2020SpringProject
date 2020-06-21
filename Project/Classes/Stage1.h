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

#ifndef __STAGE1_H__
#define __STAGE1_H__

#include "cocos2d.h"
#include "Headers.h"

class Stage : public cocos2d::Scene
{
private:
public:
	static std::vector<int> aa;
	Player* _player;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	void addKeyboardListener();
	void addContactListener();
    CREATE_FUNC(Stage);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	bool onConcactBegin(cocos2d::PhysicsContact & contact);

	void refresh(float dt);
	cocos2d::Label* _labelScore;
	cocos2d::Label* _labelHp;
	cocos2d::Label* _labelBomb;
	cocos2d::Label* _labelPower;
	cocos2d::Label* _labelScoreGetMax;
	cocos2d::Label* _labelGraze;

protected:
};

class StageOP : public Stage {
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(StageOP);
	StageOP();
};

class Stage1 : public Stage {
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Stage1);
	Stage1();
};




#endif // __STAGE1_H__