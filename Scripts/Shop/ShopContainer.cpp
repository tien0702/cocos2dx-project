#include "ShopContainer.h"
#include "AudioManager/AudioManager.h"

MyGame::ShopContainer* MyGame::ShopContainer::create(std::string backgroundPath, std::vector<IItemInventory*> items, int maxColumn, DetailItem* detailItem)
{
	auto layer = new (std::nothrow) ShopContainer();
	if (layer && layer->init(backgroundPath, items, maxColumn, detailItem))
	{
		layer->autorelease();
		return layer;
	}
	return nullptr;
}

bool MyGame::ShopContainer::init(std::string backgroundPath, std::vector<IItemInventory*> items, int maxColumn, DetailItem* detailItem)
{
	if (!Node::init())
	{
		return false;
	}
	_items = items;
	_maxItems = maxColumn;
	_detailItem = detailItem;
	_boxScrollview = ContainerScrollView::create(Size(_maxItems, 0));
	_boxScrollview->setBackground(Sprite::create(backgroundPath), Size(10, 10));

	loadComponent();
	loadSlots();
	loadContainer();

	this->addChild(_boxScrollview);

	selectItemSlot(_slots.front());
	return true;
}

bool MyGame::ShopContainer::loadComponent()
{
	_boxScrollview->setLineHeight(10);
	_boxScrollview->setBorderBackground(10);
	_selectedBorder = Sprite::create("FHD/Button/SelectedItem.png");
	_selectedBorder->retain();
	_selectedItemSlot = nullptr;

	return true;
}

std::vector<RowItem*> MyGame::ShopContainer::getRowItems(std::vector<MyGame::IItemInventory*> items, int maxItems)
{
	std::vector<RowItem*> rowItems;

	int currentItemIndex = 0;
	while (currentItemIndex < items.size())
	{
		auto row = RowItem::create(_boxScrollview->getInnerContainer()->getContentSize());
		for (int i = 0; i < maxItems; ++i)
		{
			row->addChild(_slots.at(currentItemIndex));
			currentItemIndex++;
			if (currentItemIndex >= items.size()) break;
		}
		rowItems.push_back(row);
	}

	return rowItems;
}

void MyGame::ShopContainer::selectItemSlot(ItemShopSlot* itemSlot)
{
	_selectedItemSlot = itemSlot;

	_selectedBorder->removeFromParent();
	_selectedBorder->setPosition(_selectedItemSlot->getContentSize() / 2);
	_selectedItemSlot->addChild(_selectedBorder, INT_MAX);
	_detailItem->renderItem(_selectedItemSlot->getItem());
}

bool MyGame::ShopContainer::loadSlots()
{
	for (auto item : _items)
	{
		auto slot = ItemShopSlot::create(item);
		slot->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case cocos2d::ui::Widget::TouchEventType::BEGAN:
				AudioManager::getIns()->playeButtonEffect();
				break;
			case cocos2d::ui::Widget::TouchEventType::ENDED:
			{
				selectItemSlot(slot);
			}
			break;
			default:
				break;
			}
			});
		_slots.push_back(slot);
	}

	return true;
}

bool MyGame::ShopContainer::loadContainer()
{
	auto row = getRowItems(_items, _maxItems);

	for (int i = row.size() - 1; i >= 0; --i)
	{
		_boxScrollview->addChild(row.at(i));
	}
	return true;
}
