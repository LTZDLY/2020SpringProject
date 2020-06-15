/****************************************************************************

 ****************************************************************************/



#ifndef __WELCOME_H__
#define __WELCOME_H__

#include "cocos2d.h"

class Welcome : public cocos2d::Scene
{
private:
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Welcome);
};



#endif //__WELCOME_H__