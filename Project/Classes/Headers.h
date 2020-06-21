/****************************************************************************
这里是声明所有子弹类的地方

若需声明自定义子弹请继承自Bullet类
并且根据需求进行函数重载

所有的自定义Sprite类请一定记得重载create函数！！！
 ****************************************************************************/

#ifndef __HEADERS_H__
#define __HEADERS_H__

#include "Player.h"
#include "Bullet.h"
#include "Item.h"

#define PI (acos(-1))
#define GROUP_ENEMY_BULLET 256
#define GROUP_ENEMY 16
#define GROUP_PLAYER_BULLET 32
#define GROUP_PLAYER_PDD 1024
#define GROUP_PLAYER_GRAZE 2048
#define GROUP_PLAYER 64
#define GROUP_ITEM 128

#endif //__HEADERS_H__