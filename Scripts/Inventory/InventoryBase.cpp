#include "InventoryBase.h"
#include "Inventory/DetailTable/WeaponDetailTable.h"
#include "Inventory/DetailTable/ComsumableItemDetailTable.h"
#include "AudioManager/AudioManager.h"

int getHeightScroll(int size, int w)
{
	return (size % w == 0) ? (size / w) : (size / w + 1);
}

bool MyGame::InventoryBase::init()
{
	if (!Layer::init()) {
		log("Init Inventory name %s failed!", _invName.c_str());
		return false;
	}

	_ivnSize.width = 8;
	_ivnSize.height = 5;
	_maxVolume = 0;

	_bgPath = "FHD/Background/InvContainer.png";
	_selectedPath = "FHD/Background/SelectedItem.png";
	_invIcon = "FHD/Icon/rune-icon.png";

	_background = Sprite::create(_bgPath);
	_selected = Sprite::create(_selectedPath);
	_selected->retain();

	switch (_typeItemContains)
	{
	case MyGame::ItemType::WeaponType:
		_detailTable = WeaponDetailTable::create();
		break;
	case MyGame::ItemType::ComsumableType:
		_detailTable = ConsumableDetailTable::create();
		break;
	case MyGame::ItemType::CollectableType:
		break;
	default:
		break;
	}
	//
	Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 posBG, posScroll, posTable;
	posBG = screenSize / 2;
	int distance = 10;
	int maxW = _background->getContentSize().width + distance + _detailTable->getBackground()->getContentSize().width;
	Size size = Size(maxW, _background->getContentSize().height);

	posBG.x = screenSize.width / 2 - (size.width / 2 - _background->getContentSize().width / 2);

	posTable.x = _background->getContentSize().width / 2 + _detailTable->getBackground()->getContentSize().width / 2 + 10;
	posTable.y = 0;

	posTable.x = posBG.x + distance + _detailTable->getBackground()->getContentSize().width / 2 + _background->getContentSize().width / 2;
	posTable.y = screenSize.height / 2;

	_background->setPosition(posBG);
	_detailTable->setPosition(posTable);

	this->addChild(_background);
	this->addChild(_detailTable);

	return true;
}

void MyGame::InventoryBase::addItem(IItemInventory* item)
{
	if (item == nullptr) return;
	if (item->getType() != _typeItemContains) return;
	SlotBox* slotBox = new SlotBox(item);
	slotBox->init();
	slotBox->retain();
	_items.insert(std::pair<IItemInventory*, SlotBox*>(item, slotBox));
	slotBox->addTouchEventListener([=](Ref* pSender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			AudioManager::getIns()->playeButtonEffect();
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
		{
			_selected->removeFromParent();
			slotBox->addChild(_selected, 1);
			_detailTable->showItem(slotBox);
		}
		break;
		default:
			break;
		}
		});
}

void MyGame::InventoryBase::removeItem(IItemInventory* item)
{
	if (item == nullptr) return;
	_items.erase(item);
}

void MyGame::InventoryBase::drawBySortType(SortItemType type)
{
	auto slotBox = this->getSlotBoxWithSortType(type);
	if (slotBox->size() == 0) return;
	_sortType = type;
	ui::ScrollView* ivnScroll = ui::ScrollView::create();
	Size innerSize = _background->getContentSize();
	int heightScroll = getHeightScroll(slotBox->size(), _ivnSize.width);
	int widthSrcoll = _ivnSize.width;
	_detailTable->showItem(slotBox->at(0));
	_selected->removeFromParent();
	_selected->setPosition(slotBox->at(0)->getContentSize() / 2);
	//_items.at(items->at(0))->addChild(_selected);
	slotBox->at(0)->addChild(_selected);

	int border = 5;
	innerSize.height = (_background->getContentSize().height / _ivnSize.height) * heightScroll - border;
	innerSize.width = innerSize.width - border;
	if (heightScroll < _ivnSize.height) innerSize.height = _background->getContentSize().height;

	ivnScroll->setDirection(ui::ScrollView::Direction::VERTICAL);
	ivnScroll->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ivnScroll->setBounceEnabled(true);
	ivnScroll->setScrollBarOpacity(0);
	ivnScroll->jumpToTop();
	ivnScroll->setContentSize(_background->getContentSize());
	ivnScroll->setInnerContainerSize(innerSize);


	for (int y = 0; y < heightScroll; ++y)
	{
		for (int x = 0; x < widthSrcoll; ++x)
		{
			if (y * widthSrcoll + x == slotBox->size())
				break;
			int index = y * widthSrcoll + x;
			SlotBox* box = _items[slotBox->at(index)->getInvItem()];
			Vec2 pos;
			pos.x = + (float)((float)(x)+0.5f) / (float)(widthSrcoll);
			pos.x *= (innerSize.width - border * 2);
			pos.x += border;
			pos.y = (float)((float)(y)+0.5f) / (float)((heightScroll > _ivnSize.height) ? (heightScroll) : (_ivnSize.height));
			pos.y *= innerSize.height;
			pos.y = innerSize.height - pos.y - border;
			box->setPosition(pos);
			if (box->getParent() != nullptr) box->removeFromParent();
			ivnScroll->addChild(box, 10);
		}
	}

	ivnScroll->setTag(TagSrcoll);
	ivnScroll->setPosition(_background->getPosition());
	this->removeChildByTag(TagSrcoll);
	this->addChild(ivnScroll);
}

std::vector<MyGame::IItemInventory*>* MyGame::InventoryBase::getItemsWithSortType(SortItemType type)
{
	std::vector<IItemInventory*>* items = new std::vector<IItemInventory*>();

	// Convert map to list
	std::for_each(_items.begin(), _items.end(), [=](const std::pair<IItemInventory*, SlotBox*>& ref) {
		items->push_back(ref.first);
		});

	// Sort
	std::sort(items->begin(), items->end(),
		[=](IItemInventory*& i1, IItemInventory*& i2) {
			switch (type)
			{
			case MyGame::SortItemType::UpQuality:
				return i1->getQuality() > i2->getQuality();
			case MyGame::SortItemType::DownQuality:
				return i1->getQuality() < i2->getQuality();
			default:
				return i1->getQuality() > i2->getQuality();
			}
		});

	return items;
}

std::vector<MyGame::SlotBox*>* MyGame::InventoryBase::getSlotBoxWithSortType(SortItemType type)
{
	std::vector<SlotBox*>* slotBoxs = new std::vector<SlotBox*>();

	// Convert map to list
	std::for_each(_items.begin(), _items.end(), [=](const std::pair<IItemInventory*, SlotBox*>& ref) {
		slotBoxs->push_back(ref.second);
		});

	// Sort
	std::sort(slotBoxs->begin(), slotBoxs->end(),
		[=](SlotBox*& i1, SlotBox*& i2) {
			switch (type)
			{
			case MyGame::SortItemType::UpQuality:
				return i1->getInvItem()->getQuality() > i2->getInvItem()->getQuality();
			case MyGame::SortItemType::DownQuality:
				return i1->getInvItem()->getQuality() < i2->getInvItem()->getQuality();
			default:
				return i1->getInvItem()->getQuality() > i2->getInvItem()->getQuality();
			}
		});

	return slotBoxs;
}
