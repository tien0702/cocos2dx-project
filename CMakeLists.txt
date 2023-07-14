#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME Project)

project(${APP_NAME})

if(XCODE)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET)
        SET (CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 8.0)
    endif()
endif()

if(NOT DEFINED BUILD_ENGINE_DONE) # to test Project into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/.idea/.gitignore
     Classes/.idea/Classes.iml
     Classes/.idea/misc.xml
     Classes/.idea/modules.xml
     Classes/.idea/vcs.xml
     Classes/.idea/workspace.xml
     Classes/Ability/ActiveSkill.cpp
     Classes/Ability/SerpentScrew.cpp
     Classes/AppDelegate.cpp
     Classes/AudioManager/AudioManager.cpp
     Classes/Camera/CameraFollow.cpp
     Classes/Chapter/Chapter.cpp
     Classes/Chapter/ChapterInfo.cpp
     Classes/Chapter/ChapterInforRenderer.cpp
     Classes/Chapter/ChapterMap.cpp
     Classes/Chapter/ChapterMapInfo.cpp
     Classes/Chapter/EnemyWave.cpp
     Classes/Chapter/LocationInfoBtn.cpp
     Classes/Chapter/ReplayChapter.cpp
     Classes/Character/Character.cpp
     Classes/Character/CharacterAttack.cpp
     Classes/Character/CharacterObserver.cpp
     Classes/Character/CharacterSubject.cpp
     Classes/Character/State/CharacterAttackState.cpp
     Classes/Character/State/CharacterDashState.cpp
     Classes/Character/State/CharacterDieState.cpp
     Classes/Character/State/CharacterIdleState.cpp
     Classes/Character/State/CharacterMoveState.cpp
     Classes/Character/State/CharacterPrepareDash.cpp
     Classes/Character/State/CharacterSpawnState.cpp
     Classes/Character/State/CharacterState.cpp
     Classes/Character/State/CharacterStateMachine.cpp
     Classes/Character/State/CharacterUseSkillState.cpp
     Classes/Combat/InfoTargetEnemy.cpp
     Classes/Common.cpp
     Classes/ConsumableItem/ConsumableItem.cpp
     Classes/ConsumableItem/IConsumableItem.cpp
     Classes/Convert.cpp
     Classes/DamagerSystem/DamageMessage.cpp
     Classes/DamagerSystem/Power.cpp
     Classes/Enemy/Enemy.cpp
     Classes/Enemy/EnemyPool.cpp
     Classes/Enemy/State/EnemyAttackState.cpp
     Classes/Enemy/State/EnemyChasingState.cpp
     Classes/Enemy/State/EnemyDieState.cpp
     Classes/Enemy/State/EnemyIdleState.cpp
     Classes/Enemy/State/EnemyMoveState.cpp
     Classes/Enemy/State/EnemyRangedAttack.cpp
     Classes/Enemy/State/EnemySpawnState.cpp
     Classes/Enemy/State/EnemyState.cpp
     Classes/Enemy/State/EnemyStateFactory.cpp
     Classes/Enemy/State/EnemyStateMachine.cpp
     Classes/Enemy/State/EnemyTakeHitState.cpp
     Classes/Enemy/State/EnemyTransitionState.cpp
     Classes/Entity/BaseStat.cpp
     Classes/Entity/Bonus.cpp
     Classes/Entity/BonusLevel.cpp
     Classes/Entity/DetectEntity.cpp
     Classes/Entity/Entity.cpp
     Classes/Entity/EntityHealth.cpp
     Classes/Entity/EntityMana.cpp
     Classes/Entity/EntityObserver.cpp
     Classes/Entity/EntitySubject.cpp
     Classes/Entity/Stat.cpp
     Classes/Equipment/IEquipment.cpp
     Classes/Equipment/Weapon/IWeapon.cpp
     Classes/Equipment/Weapon/MagicBook.cpp
     Classes/GameConfig.cpp
     Classes/GameData/AbilityData.cpp
     Classes/GameData/ChapterData.cpp
     Classes/GameData/ConsumableItemData.cpp
     Classes/GameData/Database.cpp
     Classes/GameData/EntityData.cpp
     Classes/GameData/ItemData.cpp
     Classes/GameData/PlayerData.cpp
     Classes/GameData/PowerData.cpp
     Classes/GameData/RewardData.cpp
     Classes/GameData/SkillData.cpp
     Classes/GameData/SQLite/shell.c
     Classes/GameData/SQLite/sqlite3.c
     Classes/GameData/WeaponData.cpp
     Classes/GameReward/BonusCard.cpp
     Classes/GameReward/BonusDeck.cpp
     Classes/GameReward/BonusRenderer.cpp
     Classes/GameReward/Chest.cpp
     Classes/GameReward/Coin.cpp
     Classes/GameReward/Reward.cpp
     Classes/GameReward/RewardRenderer.cpp
     Classes/GTimer.cpp
     Classes/HelloWorldScene.cpp
     Classes/Input/ButtonNormalATK.cpp
     Classes/Input/ButtonSkill.cpp
     Classes/Input/Input.cpp
     Classes/Input/Joystick.cpp
     Classes/Input/JoystickMove.cpp
     Classes/Input/PlayerInput.cpp
     Classes/Inventory/DetailTable/ComsumableItemDetailTable.cpp
     Classes/Inventory/DetailTable/DetailTable.cpp
     Classes/Inventory/DetailTable/WeaponDetailTable.cpp
     Classes/Inventory/IInventoryContainer.cpp
     Classes/Inventory/InventoryBase.cpp
     Classes/Inventory/Item/IItemInventory.cpp
     Classes/Inventory/PlayerInventory.cpp
     Classes/Inventory/SlotBox/SlotBox.cpp
     Classes/Inventory/SlotBox/SlotBoxEquipment.cpp
     Classes/Manager/GameManager.cpp
     Classes/Map/GameMap.cpp
     Classes/Map/Gate.cpp
     Classes/Player/AttributeLayer.cpp
     Classes/Player/CharacterWindowView.cpp
     Classes/Player/IInforLayer.cpp
     Classes/Player/InformationScene.cpp
     Classes/Player/OptionLayer.cpp
     Classes/Player/Player.cpp
     Classes/Player/SkillBtnShowDetail.cpp
     Classes/Player/StatRenderer.cpp
     Classes/Projectile/IProjectile.cpp
     Classes/Projectile/Projectile.cpp
     Classes/Projectile/ProjectilePool.cpp
     Classes/Scaler.cpp
     Classes/Scene/HomeScene.cpp
     Classes/Scene/LoadingScene.cpp
     Classes/Scene/LoseGame.cpp
     Classes/Scene/PlayerInventoryScene.cpp
     Classes/Scene/SettingScene.cpp
     Classes/Scene/SettingSceneInGame.cpp
     Classes/Scene/ShopScene.cpp
     Classes/Scene/SkillCollection.cpp
     Classes/Scene/SummaryGame.cpp
     Classes/Scene/TestScene.cpp
     Classes/Scene/WinGame.cpp
     Classes/Scene/WorldMap.cpp
     Classes/Settings/Setting.cpp
     Classes/Shop/BoxContainer.cpp
     Classes/Shop/ContainerScrollView.cpp
     Classes/Shop/DetailItem.cpp
     Classes/Shop/HorizontalLayout.cpp
     Classes/Shop/ItemShopSlot.cpp
     Classes/Shop/RowItem.cpp
     Classes/Shop/ShopContainer.cpp
     Classes/Shop/VerticalLayout.cpp
     Classes/Skill/ActivationStrategy/ActivationFactory.cpp
     Classes/Skill/ActivationStrategy/ActivationStrategy.cpp
     Classes/Skill/ActivationStrategy/AoEActivation.cpp
     Classes/Skill/ActivationStrategy/AoEDelayActivation.cpp
     Classes/Skill/ActivationStrategy/DashActivation.cpp
     Classes/Skill/ActivationStrategy/ProjectileActivation.cpp
     Classes/Skill/Effect/BurntEffect.cpp
     Classes/Skill/Effect/FreezeEffect.cpp
     Classes/Skill/Effect/KnockbackEffect.cpp
     Classes/Skill/Effect/ParalyzeEffect.cpp
     Classes/Skill/Effect/SkillEffect.cpp
     Classes/Skill/ISkill.cpp
     Classes/Skill/PassiveSkill.cpp
     Classes/Skill/Skill.cpp
     Classes/Skill/SkillInfo.cpp
     Classes/Skill/StateMachine/CastingState.cpp
     Classes/Skill/StateMachine/CooldownState.cpp
     Classes/Skill/StateMachine/LockedState.cpp
     Classes/Skill/StateMachine/ReadyState.cpp
     Classes/Skill/StateMachine/SkillState.cpp
     Classes/Skill/StateMachine/SkillStateMachine.cpp
     Classes/Skill/StateMachine/TargetingState.cpp
     Classes/Skill/TargetingStrategy/TargetAreaAroundSelf.cpp
     Classes/Skill/TargetingStrategy/TargetingFactory.cpp
     Classes/Skill/TargetingStrategy/TargetingStrategy.cpp
     Classes/Skill/TargetingStrategy/TargetProjectile.cpp
     Classes/Skill/TargetingStrategy/TargetSelectArea.cpp
     Classes/UI/BounceLayer.cpp
     Classes/UI/CharacterStateUI.cpp
     Classes/UI/CoinBar.cpp
     Classes/UI/Effect.cpp
     Classes/UI/Entity/HPBarPool.cpp
     Classes/UI/Entity/HPBarVisual.cpp
     Classes/UI/FloatingNumber.cpp
     Classes/UI/FloatingTextNofify.cpp
     Classes/UI/HUDLayer.cpp
     Classes/UI/Skill/SkillDetailRenderer.cpp
     Classes/UI/Skill/SkillEquipRenderer.cpp
     Classes/UI/Skill/SkillListRenderer.cpp
     )
list(APPEND GAME_HEADER
     Classes/Ability/ActiveSkill.h
     Classes/Ability/SerpentScrew.h
     Classes/AppDelegate.h
     Classes/AudioManager/AudioManager.h
     Classes/Bitmask.h
     Classes/Camera/CameraFollow.h
     Classes/Chapter/Chapter.h
     Classes/Chapter/ChapterInfo.h
     Classes/Chapter/ChapterInforRenderer.h
     Classes/Chapter/ChapterMap.h
     Classes/Chapter/ChapterMapInfo.h
     Classes/Chapter/EnemyWave.h
     Classes/Chapter/LocationInfoBtn.h
     Classes/Chapter/ReplayChapter.h
     Classes/Character/Character.h
     Classes/Character/CharacterAttack.h
     Classes/Character/CharacterObserver.h
     Classes/Character/CharacterSubject.h
     Classes/Character/State/CharacterAttackState.h
     Classes/Character/State/CharacterDashState.h
     Classes/Character/State/CharacterDieState.h
     Classes/Character/State/CharacterIdleState.h
     Classes/Character/State/CharacterMoveState.h
     Classes/Character/State/CharacterPrepareDash.h
     Classes/Character/State/CharacterSpawnState.h
     Classes/Character/State/CharacterState.h
     Classes/Character/State/CharacterStateMachine.h
     Classes/Character/State/CharacterUseSkillState.h
     Classes/Combat/InfoTargetEnemy.h
     Classes/Common.h
     Classes/ConsumableItem/ConsumableItem.h
     Classes/ConsumableItem/IConsumableItem.h
     Classes/Convert.h
     Classes/DamagerSystem/DamageMessage.h
     Classes/DamagerSystem/Power.h
     Classes/Enemy/Enemy.h
     Classes/Enemy/EnemyPool.h
     Classes/Enemy/State/EnemyAttackState.h
     Classes/Enemy/State/EnemyChasingState.h
     Classes/Enemy/State/EnemyDieState.h
     Classes/Enemy/State/EnemyIdleState.h
     Classes/Enemy/State/EnemyMoveState.h
     Classes/Enemy/State/EnemyRangedAttack.h
     Classes/Enemy/State/EnemySpawnState.h
     Classes/Enemy/State/EnemyState.h
     Classes/Enemy/State/EnemyStateFactory.h
     Classes/Enemy/State/EnemyStateMachine.h
     Classes/Enemy/State/EnemyTakeHitState.h
     Classes/Enemy/State/EnemyTransitionState.h
     Classes/Entity/BaseStat.h
     Classes/Entity/Bonus.h
     Classes/Entity/BonusLevel.h
     Classes/Entity/DetectEntity.h
     Classes/Entity/Entity.h
     Classes/Entity/EntityHealth.h
     Classes/Entity/EntityMana.h
     Classes/Entity/EntityObserver.h
     Classes/Entity/EntitySubject.h
     Classes/Entity/Stat.h
     Classes/Equipment/IEquipment.h
     Classes/Equipment/Weapon/IWeapon.h
     Classes/Equipment/Weapon/MagicBook.h
     Classes/GameConfig.h
     Classes/GameData/AbilityData.h
     Classes/GameData/ChapterData.h
     Classes/GameData/ConsumableItemData.h
     Classes/GameData/Database.h
     Classes/GameData/EntityData.h
     Classes/GameData/ItemData.h
     Classes/GameData/PlayerData.h
     Classes/GameData/PowerData.h
     Classes/GameData/RewardData.h
     Classes/GameData/SkillData.h
     Classes/GameData/SQLite/sqlite3.h
     Classes/GameData/SQLite/sqlite3ext.h
     Classes/GameData/WeaponData.h
     Classes/GameReward/BonusCard.h
     Classes/GameReward/BonusDeck.h
     Classes/GameReward/BonusRenderer.h
     Classes/GameReward/Chest.h
     Classes/GameReward/Coin.h
     Classes/GameReward/Reward.h
     Classes/GameReward/RewardRenderer.h
     Classes/GTimer.h
     Classes/HelloWorldScene.h
     Classes/Input/ButtonNormalATK.h
     Classes/Input/ButtonSkill.h
     Classes/Input/Input.h
     Classes/Input/Joystick.h
     Classes/Input/JoystickMove.h
     Classes/Input/PlayerInput.h
     Classes/Inventory/DetailTable/ComsumableItemDetailTable.h
     Classes/Inventory/DetailTable/DetailTable.h
     Classes/Inventory/DetailTable/WeaponDetailTable.h
     Classes/Inventory/IInventoryContainer.h
     Classes/Inventory/InventoryBase.h
     Classes/Inventory/Item/IItemInventory.h
     Classes/Inventory/PlayerInventory.h
     Classes/Inventory/SlotBox/SlotBox.h
     Classes/Inventory/SlotBox/SlotBoxEquipment.h
     Classes/Manager/GameManager.h
     Classes/Map/GameMap.h
     Classes/Map/Gate.h
     Classes/ObjectInfo/CoinInfo.h
     Classes/ObjectInfo/EntityInfo.h
     Classes/ObjectInfo/ItemInfo.h
     Classes/ObjectTag.h
     Classes/Player/AttributeLayer.h
     Classes/Player/CharacterWindowView.h
     Classes/Player/IInforLayer.h
     Classes/Player/InformationScene.h
     Classes/Player/OptionLayer.h
     Classes/Player/Player.h
     Classes/Player/SkillBtnShowDetail.h
     Classes/Player/StatRenderer.h
     Classes/Projectile/IProjectile.h
     Classes/Projectile/Projectile.h
     Classes/Projectile/ProjectilePool.h
     Classes/Scaler.h
     Classes/Scene/HomeScene.h
     Classes/Scene/LoadingScene.h
     Classes/Scene/LoseGame.h
     Classes/Scene/PlayerInventoryScene.h
     Classes/Scene/SettingScene.h
     Classes/Scene/SettingSceneInGame.h
     Classes/Scene/ShopScene.h
     Classes/Scene/SkillCollection.h
     Classes/Scene/SummaryGame.h
     Classes/Scene/TestScene.h
     Classes/Scene/WinGame.h
     Classes/Scene/WorldMap.h
     Classes/Settings/Setting.h
     Classes/Shop/BoxContainer.h
     Classes/Shop/ContainerScrollView.h
     Classes/Shop/DetailItem.h
     Classes/Shop/HorizontalLayout.h
     Classes/Shop/ItemShopSlot.h
     Classes/Shop/RowItem.h
     Classes/Shop/ShopContainer.h
     Classes/Shop/VerticalLayout.h
     Classes/Skill/ActivationStrategy/ActivationFactory.h
     Classes/Skill/ActivationStrategy/ActivationStrategy.h
     Classes/Skill/ActivationStrategy/AoEActivation.h
     Classes/Skill/ActivationStrategy/AoEDelayActivation.h
     Classes/Skill/ActivationStrategy/DashActivation.h
     Classes/Skill/ActivationStrategy/ProjectileActivation.h
     Classes/Skill/Effect/BurntEffect.h
     Classes/Skill/Effect/FreezeEffect.h
     Classes/Skill/Effect/KnockbackEffect.h
     Classes/Skill/Effect/ParalyzeEffect.h
     Classes/Skill/Effect/SkillEffect.h
     Classes/Skill/ISkill.h
     Classes/Skill/PassiveSkill.h
     Classes/Skill/Skill.h
     Classes/Skill/SkillInfo.h
     Classes/Skill/StateMachine/CastingState.h
     Classes/Skill/StateMachine/CooldownState.h
     Classes/Skill/StateMachine/LockedState.h
     Classes/Skill/StateMachine/ReadyState.h
     Classes/Skill/StateMachine/SkillState.h
     Classes/Skill/StateMachine/SkillStateMachine.h
     Classes/Skill/StateMachine/SkillStateType.h
     Classes/Skill/StateMachine/TargetingState.h
     Classes/Skill/TargetingStrategy/TargetAreaAroundSelf.h
     Classes/Skill/TargetingStrategy/TargetingFactory.h
     Classes/Skill/TargetingStrategy/TargetingStrategy.h
     Classes/Skill/TargetingStrategy/TargetProjectile.h
     Classes/Skill/TargetingStrategy/TargetSelectArea.h
     Classes/UI/BounceLayer.h
     Classes/UI/CharacterStateUI.h
     Classes/UI/CoinBar.h
     Classes/UI/Effect.h
     Classes/UI/Entity/HPBarPool.h
     Classes/UI/Entity/HPBarVisual.h
     Classes/UI/FloatingNumber.h
     Classes/UI/FloatingTextNofify.h
     Classes/UI/HUDLayer.h
     Classes/UI/Skill/SkillDetailRenderer.h
     Classes/UI/Skill/SkillEquipRenderer.h
     Classes/UI/Skill/SkillListRenderer.h
     )

if(ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
         proj.android/app/jni/hellocpp/main.cpp
         )
elseif(LINUX)
    list(APPEND GAME_SOURCE
         proj.linux/main.cpp
         )
elseif(WINDOWS)
    list(APPEND GAME_HEADER
         proj.win32/main.h
         proj.win32/resource.h
         )
    list(APPEND GAME_SOURCE
         proj.win32/main.cpp
         proj.win32/game.rc
         ${common_res_files}
         )
elseif(APPLE)
    if(IOS)
        list(APPEND GAME_HEADER
             proj.ios_mac/ios/AppController.h
             proj.ios_mac/ios/RootViewController.h
             )
        set(APP_UI_RES
            proj.ios_mac/ios/LaunchScreen.storyboard
            proj.ios_mac/ios/LaunchScreenBackground.png
            proj.ios_mac/ios/Images.xcassets
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/ios/main.m
             proj.ios_mac/ios/AppController.mm
             proj.ios_mac/ios/RootViewController.mm
             proj.ios_mac/ios/Prefix.pch
             ${APP_UI_RES}
             )
    elseif(MACOSX)
        set(APP_UI_RES
            proj.ios_mac/mac/Icon.icns
            proj.ios_mac/mac/Info.plist
            )
        list(APPEND GAME_SOURCE
             proj.ios_mac/mac/main.cpp
             proj.ios_mac/mac/Prefix.pch
             ${APP_UI_RES}
             )
    endif()
    list(APPEND GAME_SOURCE ${common_res_files})
endif()

# mark app complie info and libs info
set(all_code_files
    ${GAME_HEADER}
    ${GAME_SOURCE}
    )
if(NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
)

# mark app resources
setup_cocos_app_config(${APP_NAME})
if(APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")

    if(MACOSX)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist")
    elseif(IOS)
        set_xcode_property(${APP_NAME} INFOPLIST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/ios/Info.plist")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif()

    # For code-signing, set the DEVELOPMENT_TEAM:
    #set_xcode_property(${APP_NAME} DEVELOPMENT_TEAM "GRLXXXX2K9")
elseif(WINDOWS)
    cocos_copy_target_dll(${APP_NAME})
endif()

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()
