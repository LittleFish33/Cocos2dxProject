#include "RankListScene.h"
#include "SimpleAudioEngine.h"
#include "GameSettingScene.h"
#include "../ShareSingleton.h"
#include "GamePauseScene.h"
#include <tinyxml2/tinyxml2.h>
//#include <json/document.h>
using namespace tinyxml2;
using namespace CocosDenshion;
USING_NS_CC;

Scene* RankListScene::createScene()
{
    return RankListScene::create();
}

/* 当文件不存在时，打印有用的错误消息而不是分段错误 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in RankListSceneScene.cpp\n");
}

/* 初始化场景函数 */
bool RankListScene::init()
{
#pragma region Cocos2dx自动生成的内容：一些基本配置

	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#pragma endregion
	CCLOG(ShareSingleton::GetInstance()->xmlPath.c_str());

#pragma region 排行榜前5名
	handleRankList();

#pragma endregion 


#pragma region UI界面 背景图片
	
	auto bg = Sprite::create("bg/startSceneBackground.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg, 0);

#pragma endregion

#pragma region  预添加音效和背景音乐

	auto audio = SimpleAudioEngine::getInstance();
	/*预加载并循环播放背景音乐*/
	audio->playBackgroundMusic("music/RankListSceneBgm.mp3", true);
	audio->setBackgroundMusicVolume(0.80);

	/*预加载音效*/
	audio->preloadEffect("music/ClickCamera.wav");
	audio->setEffectsVolume(0.80);

	/*返回菜单按钮*/
	auto ReturnToMenuSceneItem = CCMenuItemImage::create(
		"button/back2-normal.png",
		"button/back2-selected.png",
		this,
		menu_selector(GamePauseScene::ReturnToMenuSceneCallback)
	);
	ReturnToMenuSceneItem->setPosition(Vec2(visibleSize.width / 2, 80));

	Menu* pMenu = Menu::create(ReturnToMenuSceneItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);
#pragma endregion
	CCLOG(ShareSingleton::GetInstance()->xmlPath.c_str());
    return true;
}

/* 从xml文件得到排行榜 */
void RankListScene::handleRankList()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	string xmlPath = ShareSingleton::GetInstance()->xmlPath;
	auto doc = new tinyxml2::XMLDocument();
	doc->Parse(FileUtils::getInstance()->getStringFromFile(xmlPath.c_str()).c_str());
	auto root = doc->RootElement();

	map<string, int> rankList;
	for (auto e = root->FirstChildElement() + 1; e; e = e->NextSiblingElement())
	{
		int number = 0;
		sscanf(e->FirstChild()->Value(), "%d", &number);
		rankList.insert(pair<string, int>(e->Value(), number));
	}
	int count = 5 > rankList.size() ? rankList.size() : 5;
	for (int x = 0; x < count; ++x) {
		pair<string, int> temp("NONE", -1000);
		for (auto m = rankList.begin(); m != rankList.end(); m++) {
			if (m->second > temp.second) {
				temp.first = m->first;
				temp.second = m->second;
			}
		}
		for (auto m = rankList.begin(); m != rankList.end(); m++) {
			if (m->second == temp.second) {
				rankList.erase(m);
				break;
			}
		}

		int score = temp.second;
		char cStr[10];
		sprintf(cStr, "%d", score);

		char cStr2[10];
		sprintf(cStr2, "%d", x+1);
		string str1 = cStr2;
		string str = str1 + ". " + temp.first+ ": " + cStr;

		Label* rank = Label::createWithTTF(str.c_str(), "fonts/comicsansms.ttf", 30);
		rank->setPosition(visibleSize.width / 2, visibleSize.height - 80 * (x + 3.5));
		rank->setColor(Color3B(255, 255, 255));
		ranks.push_back(rank);
		addChild(rank, 1);
	}
}