#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

void showVaultCodes() {
    std::string text =
        "<cr>The Vault:</c>\n"
        "Sparky, Spooky, Ahead, Neverending,\n"
        "Mule, Blockbite, Gimmie, Freeze,\n"
        "Cruise, Ganon\n\n"
        "<cg>Vault of Secrets:</c>\n"
        "Octopus, Robotop, Porcupy,\n"
        "Thechickenisonfire, Neverending\n\n"
        "<cy>Chamber of Time:</c>\n"
        "Silence, Retray, Timelybird,\n"
        "Hexagons, Glubfub, Vaultkeeper";

    FLAlertLayer::create(
        nullptr,
        "Vault Codes",
        text,
        "OK",
        nullptr,
        380
    )->show();
}

struct VaultCodesHook : Modify<VaultCodesHook, MenuLayer> {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto ws = CCDirector::get()->getWinSize();

        auto spr = CCSprite::createWithSpriteFrameName("GJ_lock_open_001.png");
        spr->setScale(1.1f);

        auto btn = CCMenuItemSpriteExtra::create(
            spr, this,
            menu_selector(VaultCodesHook::onVaultBtn)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({ ws.width - 25, ws.height / 2 });
        addChild(menu, 100);

        return true;
    }

    void onVaultBtn(CCObject*) {
        showVaultCodes();
    }
};
