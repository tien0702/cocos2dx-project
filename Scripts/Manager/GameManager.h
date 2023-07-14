#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Chapter/ChapterMap.h"
#include "Chapter/Chapter.h"
#include "Character/Character.h"

using namespace MyGame;

class GameManager
{
public:
	static GameManager* getIns();
	Chapter* getChapter() { return this->_chapter; }
	void playChapterID(int id);
	void startGame();
	void exitGame();

	void setGameMap(GameMap* map) { this->_map = map; }
	Character* getCharacter();
	GameMap* getCurrentMap() { return this->_map; }
private:
	static GameManager* _instance;
	GameManager();

	// Properties
	Scene* _chapterScene;
	Chapter* _chapter;
	GameMap* _map;
};

#endif // !__GAME_MANAGER_H__
