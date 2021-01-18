#ifndef	_MENUSELECT__H_
#define _MENUSELECT__H_

#include "CommonData.h"


USING_NS_CC;

class  MenuSelect: public Layer {
public:
     MenuSelect();

	~MenuSelect();

    static MenuSelect* create(MenuType);

	static Scene* createScene(MenuType);

    bool init(MenuType);

	void backBotton(); //button of back to menu

	void monsterBotton();//button of monster imfor
};

#endif