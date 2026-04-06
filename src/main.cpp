#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;

// ── Mostrar códigos ────────────────────────────────────────────────
void showVaultCodes() {
    std::string text =
        "<cr>The Vault:</c>\n"
        "Lenny, Blockbite, Spooky, Neverending,\n"
        "Mule, Ahead, Gandalfpotter, Sparky,\n"
        "Robotop, Finalboss\n\n"
        "<cg>Vault of Secrets:</c>\n"
        "Thechickenisonfire, Octocube, Seven,\n"
        "Gimmiethecolor, Brainpower, D4shG30me7ry,\n"
        "Thechickenisready, Glubfub\n\n"
        "<cy>Chamber of Time:</c>\n"
        "Volcano, River, Silence, Darkness,\n"
        "Hunger, Givemehelper, Backontrack\n\n"
        "<cp>Wraith Vault:</c>\n"
        "Citadel, Backondash, Skylinept2,\n"
        "Randomgauntlet, Brainpowah47, Gdawards,\n"
        "Retrospective, Duckstep, Ncsalbum,\n"
        "Geometry, Ruins, Buttonmasher,\n"
        "Putyahandsup, Cheatcodes, Boogie,\n"
        "Backstreetboy, Noelelectra, Touchgrass,\n"
        "Checksteam, Key, Gd2025, Spacegauntlet,\n"
        "Iaminpain, Wellmet, Bussin, Gullible";

    FLAlertLayer::create(
        nullptr,
        "Vault Codes",
        text,
        "OK",
        nullptr,
        400
    )->show();
}

// ── Botón helper ───────────────────────────────────────────────────
CCMenu* createVaultButton(CCObject* target, SEL_MenuHandler selector) {
    auto ws = CCDirector::get()->getWinSize();

    float px = Mod::get()->getSettingValue<double>("btn-x");
    float py = Mod::get()->getSettingValue<double>("btn-y");

    auto spr = CCSprite::createWithSpriteFrameName("GJ_lock_open_001.png");
    spr->setScale(1.1f);

    auto btn = CCMenuItemSpriteExtra::create(spr, target, selector);

    auto menu = CCMenu::create();
    menu->addChild(btn);
    menu->setPosition({ ws.width * px, ws.height * py });
    menu->setTouchPriority(-500);
    return menu;
}

// ── Hook MenuLayer ─────────────────────────────────────────────────
struct MenuLayerHook : Modify<MenuLayerHook, MenuLayer> {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto where = Mod::get()->getSettingValue<std::string>("show-where");
        if (where == "everywhere" || where == "menu-only") {
            auto menu = createVaultButton(
                this,
                menu_selector(MenuLayerHook::onVaultBtn)
            );
            addChild(menu, 100);
        }

        return true;
    }

    void onVaultBtn(CCObject*) {
        showVaultCodes();
    }
};

// ── Hook PlayLayer ─────────────────────────────────────────────────
struct PlayLayerHook : Modify<PlayLayerHook, PlayLayer> {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        auto where = Mod::get()->getSettingValue<std::string>("show-where");
        if (where == "everywhere" || where == "levels-only") {
            auto menu = createVaultButton(
                this,
                menu_selector(PlayLayerHook::onVaultBtn)
            );
            addChild(menu, 100);
        }

        return true;
    }

    void onVaultBtn(CCObject*) {
        showVaultCodes();
    }
};
