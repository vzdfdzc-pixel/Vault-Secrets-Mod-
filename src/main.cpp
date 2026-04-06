#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;

// ── Datos ──────────────────────────────────────────────────────────
struct VaultEntry { const char* name; std::vector<std::string> codes; };
static std::vector<VaultEntry> getVaults() {
    return {
        { "[ THE VAULT ]",
          { "Lenny","Blockbite","Spooky","Neverending",
            "Mule","Ahead","Gandalfpotter","Sparky",
            "Robotop","Finalboss" }
        },
        { "[ VAULT OF SECRETS ]",
          { "Thechickenisonfire","Octocube","Seven",
            "Gimmiethecolor","Brainpower","D4shG30me7ry",
            "Thechickenisready","Glubfub" }
        },
        { "[ CHAMBER OF TIME ]",
          { "Volcano","River","Silence","Darkness",
            "Hunger","Givemehelper","Backontrack" }
        },
        { "[ WRAITH VAULT ]",
          { "Citadel","Backondash","Skylinept2",
            "Randomgauntlet","Brainpowah47","Gdawards",
            "Retrospective","Duckstep","Ncsalbum",
            "Geometry","Ruins","Buttonmasher",
            "Putyahandsup","Cheatcodes","Boogie",
            "Backstreetboy","Noelelectra","Touchgrass",
            "Checksteam","Key","Gd2025","Spacegauntlet",
            "Iaminpain","Wellmet","Bussin","Gullible" }
        }
    };
}

// ── Popup de códigos ───────────────────────────────────────────────
class VaultPopup : public CCLayerColor {
    static inline const float W = 340;
    static inline const float H = 280;

    bool init() {
        if (!CCLayerColor::initWithColor({ 0, 0, 0, 210 })) return false;

        auto ws = CCDirector::get()->getWinSize();
        setContentSize({ W, H });
        setPosition({ (ws.width - W) / 2, (ws.height - H) / 2 });

        // Borde cyan
        auto border = CCLayerColor::create({ 0, 255, 200, 80 });
        border->setContentSize({ W, H });
        border->setPosition({ 0, 0 });
        addChild(border, 0);

        // Título
        auto title = CCLabelBMFont::create("> VAULT_CODES.EXE <", "bigFont.fnt");
        title->setScale(0.45f);
        title->setColor({ 0, 255, 200 });
        title->setPosition({ W / 2, H - 15 });
        addChild(title, 2);

        // Scroll
        auto scroll = ScrollLayer::create({ W - 16, H - 45 });
        scroll->setPosition({ 8, 30 });

        float totalH = 10;
        for (auto& v : getVaults())
            totalH += 28 + v.codes.size() * 18 + 10;

        auto content = CCLayer::create();
        content->setContentSize({ W - 16, totalH });

        float yPos = totalH - 10;
        for (auto& v : getVaults()) {
            yPos -= 22;
            auto hdr = CCLabelBMFont::create(v.name, "bigFont.fnt");
            hdr->setScale(0.38f);
            hdr->setColor({ 0, 255, 200 });
            hdr->setPosition({ (W - 16) / 2, yPos });
            content->addChild(hdr);

            yPos -= 4;
            auto sep = CCLayerColor::create({ 0, 255, 200, 50 });
            sep->setContentSize({ W - 36, 1 });
            sep->setPosition({ 10, yPos });
            content->addChild(sep);

            for (auto& code : v.codes) {
                yPos -= 18;
                auto lbl = CCLabelBMFont::create(
                    (">> " + code).c_str(), "chatFont.fnt"
                );
                lbl->setScale(0.55f);
                lbl->setColor({ 180, 255, 220 });
                lbl->setAnchorPoint({ 0, 0.5f });
                lbl->setPosition({ 12, yPos });
                content->addChild(lbl);
            }
            yPos -= 10;
        }

        scroll->m_contentLayer->addChild(content);
        scroll->moveToTop();
        addChild(scroll, 1);

        // Botón cerrar
        auto closeSpr = CCLabelBMFont::create("[ CLOSE ]", "bigFont.fnt");
        closeSpr->setScale(0.38f);
        closeSpr->setColor({ 255, 80, 80 });

        auto closeMenu = CCMenu::create();
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSpr, this,
            menu_selector(VaultPopup::onClose)
        );
        closeMenu->addChild(closeBtn);
        closeMenu->setPosition({ W / 2, 15 });
        addChild(closeMenu, 3);

        CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(this, -600, true);
        setTouchEnabled(true);
        return true;
    }

    void onClose(CCObject*) {
        CCDirector::get()->getTouchDispatcher()->removeDelegate(this);
        removeFromParentAndCleanup(true);
    }

public:
    static VaultPopup* create() {
        auto ret = new VaultPopup();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// ── Selector de íconos ─────────────────────────────────────────────
class IconPickerPopup : public CCLayerColor {
    static inline const char* icons[] = {
        "GJ_lock_open_001.png",
        "GJ_lockGray_001.png",
        "GJ_infoIcon_001.png",
        "GJ_starsIcon_001.png",
        "GJ_coinsIcon2_001.png",
        "GJ_hammerIcon_001.png",
        "GJ_diamond_001.png",
        "GJ_sIcon_001.png",
        "GJ_completesIcon_001.png",
        "GJ_timeIcon_001.png"
    };
    static inline int iconCount = 10;
    static inline const float W = 320;
    static inline const float H = 180;

    bool init() {
        if (!CCLayerColor::initWithColor({ 0, 0, 0, 210 })) return false;

        auto ws = CCDirector::get()->getWinSize();
        setContentSize({ W, H });
        setPosition({ (ws.width - W) / 2, (ws.height - H) / 2 });

        auto border = CCLayerColor::create({ 0, 255, 200, 80 });
        border->setContentSize({ W, H });
        addChild(border, 0);

        auto title = CCLabelBMFont::create("> ELEGIR ICONO <", "bigFont.fnt");
        title->setScale(0.4f);
        title->setColor({ 0, 255, 200 });
        title->setPosition({ W / 2, H - 15 });
        addChild(title, 2);

        // Scroll horizontal de íconos
        auto scroll = ScrollLayer::create({ W - 16, 100 });
        scroll->setPosition({ 8, 45 });

        float totalW = iconCount * 55.0f;
        auto content = CCLayer::create();
        content->setContentSize({ totalW, 100 });

        for (int i = 0; i < iconCount; i++) {
            auto spr = CCSprite::createWithSpriteFrameName(icons[i]);
            if (!spr) continue;
            spr->setScale(1.1f);

            auto btn = CCMenuItemSpriteExtra::create(
                spr, this,
                menu_selector(IconPickerPopup::onPick)
            );
            btn->setTag(i);

            auto m = CCMenu::create();
            m->addChild(btn);
            m->setPosition({ i * 55.0f + 27, 50 });
            content->addChild(m);
        }

        scroll->m_contentLayer->addChild(content);
        addChild(scroll, 1);

        // Botón cerrar
        auto closeSpr = CCLabelBMFont::create("[ CANCEL ]", "bigFont.fnt");
        closeSpr->setScale(0.35f);
        closeSpr->setColor({ 255, 80, 80 });
        auto closeMenu = CCMenu::create();
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSpr, this,
            menu_selector(IconPickerPopup::onClose)
        );
        closeMenu->addChild(closeBtn);
        closeMenu->setPosition({ W / 2, 20 });
        addChild(closeMenu, 3);

        CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(this, -600, true);
        return true;
    }

    void onPick(CCObject* sender) {
        int idx = static_cast<CCNode*>(sender)->getTag();
        if (idx >= 0 && idx < iconCount)
            Mod::get()->setSavedValue<std::string>("btn-icon", icons[idx]);
        CCDirector::get()->getTouchDispatcher()->removeDelegate(this);
        removeFromParentAndCleanup(true);
        FLAlertLayer::create(nullptr, "OK",
            "Icono guardado! Reinicia el menu para verlo.",
            "OK", nullptr)->show();
    }

    void onClose(CCObject*) {
        CCDirector::get()->getTouchDispatcher()->removeDelegate(this);
        removeFromParentAndCleanup(true);
    }

public:
    static IconPickerPopup* create() {
        auto ret = new IconPickerPopup();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// ── Helper botón ───────────────────────────────────────────────────
CCMenu* createVaultMenu(CCObject* target,
                        SEL_MenuHandler vaultSel,
                        SEL_MenuHandler iconSel) {
    auto ws = CCDirector::get()->getWinSize();
    float px = (float)Mod::get()->getSettingValue<double>("btn-x");
    float py = (float)Mod::get()->getSettingValue<double>("btn-y");

    std::string iconName = Mod::get()->getSavedValue<std::string>(
        "btn-icon", "GJ_lock_open_001.png"
    );
    auto spr = CCSprite::createWithSpriteFrameName(iconName.c_str());
    if (!spr)
        spr = CCSprite::createWithSpriteFrameName("GJ_lock_open_001.png");
    spr->setScale(1.1f);

    auto mainBtn = CCMenuItemSpriteExtra::create(spr, target, vaultSel);

    auto editSpr = CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
    auto menu = CCMenu::create();
    menu->addChild(mainBtn);
    if (editSpr) {
        editSpr->setScale(0.45f);
        auto editBtn = CCMenuItemSpriteExtra::create(editSpr, target, iconSel);
        editBtn->setPosition({ 22, -20 });
        menu->addChild(editBtn);
    }
    menu->setPosition({ ws.width * px, ws.height * py });
    menu->setTouchPriority(-500);
    return menu;
}

// ── Hooks ──────────────────────────────────────────────────────────
struct MenuLayerHook : Modify<MenuLayerHook, MenuLayer> {
    bool init() {
        if (!MenuLayer::init()) return false;
        auto where = Mod::get()->getSettingValue<std::string>("show-where");
        if (where == "everywhere" || where == "menu-only")
            addChild(createVaultMenu(this,
                menu_selector(MenuLayerHook::onVault),
                menu_selector(MenuLayerHook::onIcon)), 100);
        return true;
    }
    void onVault(CCObject*) {
        auto p = VaultPopup::create();
        if (p) addChild(p, 200);
    }
    void onIcon(CCObject*) {
        auto p = IconPickerPopup::create();
        if (p) addChild(p, 200);
    }
};

struct PlayLayerHook : Modify<PlayLayerHook, PlayLayer> {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        auto where = Mod::get()->getSettingValue<std::string>("show-where");
        if (where == "everywhere" || where == "levels-only")
            addChild(createVaultMenu(this,
                menu_selector(PlayLayerHook::onVault),
                menu_selector(PlayLayerHook::onIcon)), 100);
        return true;
    }
    void onVault(CCObject*) {
        auto p = VaultPopup::create();
        if (p) addChild(p, 200);
    }
    void onIcon(CCObject*) {
        auto p = IconPickerPopup::create();
        if (p) addChild(p, 200);
    }
};
