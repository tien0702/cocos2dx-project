#ifndef __INVENTORY_BASE_H__
#define __INVENTORY_BASE_H__

#include "Inventory/IInventoryContainer.h"
#include "Inventory/SlotBox/SlotBox.h"
#include "Inventory/DetailTable/DetailTable.h"

USING_NS_CC;

namespace MyGame
{
	enum class SortItemType {
		UpQuality,
		DownQuality
	};

	class InventoryBase : public IInventoryContainer, public Layer
	{
	public:
		virtual bool init();
		virtual void addItem(IItemInventory* item);
		virtual void removeItem(IItemInventory* item);
		virtual void drawBySortType(SortItemType type);
	protected:
		static const int TagSrcoll = 10;
		CC_SYNTHESIZE(ItemType, _typeItemContains, TypeItemContains);
		CC_SYNTHESIZE(Size, _ivnSize, IvnSize);
		CC_SYNTHESIZE(std::string, _bgPath, BGPath);
		CC_SYNTHESIZE(std::string, _selectedPath, SelectedPath);
		std::map<IItemInventory*, SlotBox*> _items;
		CC_SYNTHESIZE(DetailTable*, _detailTable, IvnDetailTable);
		Sprite* _background;
		Sprite* _selected;
		SortItemType _sortType;
	protected:
		std::vector<IItemInventory*>* getItemsWithSortType(SortItemType type);
		std::vector<SlotBox*>* getSlotBoxWithSortType(SortItemType type);
	};
}

#endif // !__INVENTORY_BASE_H__
