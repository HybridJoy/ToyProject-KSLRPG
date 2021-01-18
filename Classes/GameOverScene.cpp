#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	score = 0;
}

GameOverScene::~GameOverScene()
{
	score = 0;
}

void GameOverScene::setScore(int new_score)
{
	score = new_score;
}

int GameOverScene::getScore()
{
	return score;
}

GameOverScene* GameOverScene::create(int score)
{
	auto pp = new GameOverScene();

    if (pp && pp->init(score))
    { 
        pp->autorelease(); 
        return pp; 
    } 
    else 
    { 
        delete pp; 
        pp = NULL; 
        return NULL; 
    } 
}

Scene* GameOverScene::createScene(int score)
{
	auto scene = Scene::create();

	auto layer = GameOverScene::create(score);

	scene->addChild(layer);

	return scene;
}



bool GameOverScene::init(int score)
{
	if(!Layer::init()) 
		return false;

	//add gameover menu
	auto bg = Sprite::create("HelloWorld.png");
	//bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	bg->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2);
	this->addChild(bg,0,15);

	//restart game
	auto gameBack = Sprite::create("CloseNormal.png");//createWithSpriteFrameName
	auto menuItemBack = MenuItemSprite::create(gameBack, gameBack, [](Ref *){
		// auto scene = Level1Scene::createScene();
		// Director::getInstance()->replaceScene(scene);
		// Director::getInstance()->resume();
	});
	menuItemBack->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2.5);
	
	auto menu1 = Menu::create(menuItemBack, NULL);
	menu1->setPosition(Point::ZERO);
	this->addChild(menu1,99,105);

	//exit game
	auto gameExit = Sprite::create("CloseNormal.png");
	auto menuItemBack2 = MenuItemSprite::create(gameExit, gameExit, [](Ref *){
		Director::getInstance()->end();
	});
	menuItemBack2->setPosition(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/2.5-60);
	auto menu2 = Menu::create(menuItemBack2, NULL);
	menu2->setPosition(Point::ZERO);
	this->addChild(menu2,99,106);

	return true;
}