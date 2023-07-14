#ifndef __PLAYER_INVENTORY_SCENE_H__
#define __PLAYER_INVENTORY_SCENE_H__

#include "cocos2d.h"
#include "Inventory/InventoryBase.h"
#include "Player/Player.h"
#include "ui/CocosGUI.h"
#include "GameData/ItemData.h"

USING_NS_CC;

namespace MyGame
{
	enum class IvnType
	{
		IvnWeap,
		IvnItem,
		AllIvnType
	};

	class PlayerInventoryScene : public Scene
	{
	public:
		virtual bool init();
		CREATE_FUNC(PlayerInventoryScene);
	private:
		static const int TagIvnLayer = 17;
		Rect _fixedVisible;

		std::string _backBTPath;
		std::string _backgroundPath;
		std::string _navBarPath;
		std::string _buttonNormalBGPath;
		std::string _buttonSelectedBGPath;

		InventoryBase* _ivns[(int)IvnType::AllIvnType];
		ui::Button* _buttons[(int)IvnType::AllIvnType];
		IvnType _currentIvn = IvnType::IvnWeap;

		TTFConfig _font;
		Label* _currentName;
	private:
		void backToMainScene();
		bool initNavBar();
		bool loadButtons();
		bool loadInventory();
		bool loadProperties();
		void changeIvn(IvnType newIndex);
	};
}

#endif // !__PLAYER_INVENTORY_SCENE_H__
