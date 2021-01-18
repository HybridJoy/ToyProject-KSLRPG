#include "MenuSelect.h"
#include "GameOverScene.h"
#include "GameStartScene.h"

MenuSelect:: MenuSelect()
{}

MenuSelect::~MenuSelect()
{}

Scene* MenuSelect::createScene(MenuType m)
{
	Scene *scene = Scene::create();

    MenuSelect *layer = MenuSelect::create(m);

	scene->addChild(layer);

	return scene;
}


MenuSelect* MenuSelect::create(MenuType m)
{
    auto menu = new MenuSelect();
    if( menu && menu->init(m) ) {
        menu->autorelease();
        return menu;
    }
    delete menu;
    menu = NULL;
    return NULL;
}


bool MenuSelect::init(MenuType m)
{
	if(!Layer::init()) 
		return false;

	switch (m)
	{
	case HELP:
		{
			//add HELP content
			auto bg = Sprite::create("Helpbackground.png");
			//bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			bg->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2);

			this->addChild(bg,99,135);
			backBotton();
		}
		break;
	case MONSTER:
		{
			//add MONSTER content
			log("=======case========");
			auto bg = Sprite::create("Monster log.png");
			//bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			bg->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2);
			this->addChild(bg,99,136);
			monsterBotton();
			backBotton();
		}
		break;
	case ABOUT:
		{
			//add ABOUT content
			auto bg = Sprite::create("Aboutbackground.png");
			//bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			bg->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2);
			this->addChild(bg,99,137);
			backBotton();
		}
		break;
	case EXIT:
			Director::getInstance()->end();
		break;
	case START:
		{
			//auto scene = Level1Scene::createScene();
			//Director::getInstance()->replaceScene(scene);
		}
		break;
	default:
		break;
	}

	return true;
}

void MenuSelect::backBotton()
{
	//back to menu
	auto gameBack1 = Sprite::create("Back_up.png");
	auto gameBack2 = Sprite::create("Back_down.png");
	auto menuItemBack4 = MenuItemSprite::create(gameBack1, gameBack2, [](Ref *){
		auto scene = GameStartScene :: createScene();
		Director::getInstance()->replaceScene(scene);
	});
	menuItemBack4->setPosition(VISIBLE_SIZE.width - gameBack1->getContentSize().width,VISIBLE_SIZE.height - gameBack1->getContentSize().height);
	menuItemBack4->setScale(2.0f);
	auto menu4 = Menu::create(menuItemBack4, NULL);
	menu4->setPosition(Point::ZERO);
	this->addChild(menu4,1111,138);
}

//check monster infor
void MenuSelect::monsterBotton()
{

	//mon1 infor
	auto mon1 = Sprite::create("1.png");
	auto menuItemBack = MenuItemSprite::create(mon1, mon1, [this](Ref *){
		auto mon1Infor = Sprite::create("111.png");
		mon1Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon1Infor,99,139);
	});
	menuItemBack->setPosition(75,370);
	auto menu1 = Menu::create(menuItemBack, NULL);
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1,99,138);

	//mon2 infor
	auto mon2 = Sprite::create("2.png");
	auto menuItemBack2 = MenuItemSprite::create(mon2, mon2, [this](Ref *){
		auto mon2Infor = Sprite::create("222.png");
		mon2Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon2Infor,99,141);

	});
	menuItemBack2->setPosition(162,370);
	auto menu2 = Menu::create(menuItemBack2, NULL);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2,99,140);

	//mon3 infor
	auto mon3 = Sprite::create("3.png");
	auto menuItemBack3 = MenuItemSprite::create(mon3, mon3, [this](Ref *){
		auto mon3Infor = Sprite::create("333.png");
		mon3Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon3Infor,99,143);

	});
	menuItemBack3->setPosition(250,370);
	auto menu3 = Menu::create(menuItemBack3, NULL);
	menu3->setPosition(Point::ZERO);
	this->addChild(menu3,99,142);

	//mon4 infor
	auto mon4 = Sprite::create("4.png");
	auto menuItemBack4 = MenuItemSprite::create(mon4, mon4, [this](Ref *){
		auto mon4Infor = Sprite::create("444.png");
		mon4Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon4Infor,99,145);
	});
	menuItemBack4->setPosition(75,225);
	auto menu4 = Menu::create(menuItemBack4, NULL);
	menu4->setPosition(Point::ZERO);
	this->addChild(menu4,99,144);

	//mon5 infor
	auto mon5 = Sprite::create("5.png");
	auto menuItemBack5 = MenuItemSprite::create(mon5, mon5, [this](Ref *){
		auto mon5Infor = Sprite::create("555.png");
		mon5Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon5Infor,99,147);
	});
	menuItemBack5->setPosition(162,225);
	auto menu5 = Menu::create(menuItemBack5, NULL);
	menu5->setPosition(Point::ZERO);
	this->addChild(menu5,99,146);

	//mon6 infor
	auto mon6 = Sprite::create("6.png");
	auto menuItemBack6 = MenuItemSprite::create(mon6, mon6, [this](Ref *){
		auto mon6Infor = Sprite::create("666.png");
		mon6Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon6Infor,99,148);
	});
	menuItemBack6->setPosition(250,225);
	auto menu6 = Menu::create(menuItemBack6, NULL);
	menu6->setPosition(Point::ZERO);
	this->addChild(menu6,99,147);

	//mon7 infor
	auto mon7 = Sprite::create("7.png");
	auto menuItemBack7 = MenuItemSprite::create(mon7, mon7, [this](Ref *){
		auto mon7Infor = Sprite::create("777.png");
		mon7Infor->setPosition(VISIBLE_SIZE.width*0.75,VISIBLE_SIZE.height*0.5);
		this->addChild(mon7Infor,99,150);
	});
	menuItemBack7->setPosition(80,80);
	auto menu7 = Menu::create(menuItemBack7, NULL);
	menu7->setPosition(Point::ZERO);
	this->addChild(menu7,99,149);
}