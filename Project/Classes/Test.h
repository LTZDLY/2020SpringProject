/****************************************************************************

 ****************************************************************************/



#ifndef __TEST_H__
#define __TEST_H__

#include "cocos2d.h"

class Test : public cocos2d::Scene
{
private:
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuPlayCallback(cocos2d::Ref* pSender);
	void menuRecordCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Test);
};



#endif //__TEST_H__