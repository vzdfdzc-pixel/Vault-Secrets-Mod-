
#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/ui/Popup.hpp>
using namespace geode::prelude;

// ── Datos de vaults ────────────────────────────────────────────────
struct VaultData {
    const char* name;
    const char* color;
    std::vector<std::string> codes;
};

static std::vector<VaultData> getVaults() {
    return {
        { "[ THE VAULT ]", "<cr>",
          { "Lenny", "Blockbite", "Spooky", "Neverending",
            "Mule", "Ahead", "Gandalfpotter", "Sparky",
            "Robotop", "Finalboss" }
        },
        { "[ VAULT OF SECRETS ]", "<cg>",
          { "Thechickenisonfire", "Octocube", "Seven",
            "Gimmiethecolor", "Brainpower", "D4shG30me7ry",
            "Thechickenisready", "Glubfub" }
        },
        { "[ CHAMBER OF TIME ]", "<cy>",
          { "Volcano", "River", "Silence", "Darkness",
            "Hunger", "Givemehelper", "Backontrack" }
        },
        { "[ WRAITH VAULT ]", "<cp>",
          { "Citadel", "Backondash", "Skylinept2",
            "Randomgauntlet", "Brainpowah47", "Gdawards",
            "Retrospective", "Duckstep", "Ncsalbum",
            "Geometry", "Ruins", "Buttonmasher",
            "Putyahandsup", "Cheatcodes", "Boogie",
            "Backstreetboy", "Noelelectra", "Touchgrass",
            "Checksteam", "Key", "Gd2025", "Spacegauntlet",
            "Iaminpain", "Wellmet", "Bussin", "Gullible" }
        }
    };
}

// ── Popup cyberpunk scrolleable ────────────────────────────────────
class VaultPopup : public geode::Popup<> {
protected:
    bool setup() override {
        auto winSize = m_mainLayer->getContentSize();
        float W = winSize.width;
        float H = winSize.height;

        // Fondo oscuro extra
        auto bg = CCLayerColor::create({ 0, 0, 0, 180 });
        bg->setContentSize(winSize);
        bg->setPosition({ 0, 0 });
        m_mainLayer->addChild(bg, -1);

        // Título cyberpunk
        auto title = CCLabelBMFont::create(
            "> VAULT_CODES.EXE <", "bigFont.fnt"
        );
        title->setScale(0.55f);
        title->setColor({ 0, 255, 200 });
        title->setPosition({ W / 2, H - 18 });
        m_mainLayer->addChild(title, 2);

        // Línea decorativa
        auto line = CCLayerColor::create({ 0, 255, 200, 100 });
        line->setContentSize({ W - 20, 2 });
        line->setPosition({ 10, H - 30 });
        m_mainLayer->addChild(line, 2);

        // ScrollLayer
        float scrollH = H - 50;
        auto scroll = ScrollLayer::create({ W - 20, scrollH });
        scroll->setPosition({ 10, 10 });

        // Calcular altura total del contenido
        auto vaults = getVaults();
        float totalH = 10;
        for (auto& v : vaults)
            totalH += 30 + v.codes.size() * 20 + 15;

        auto content = CCLayer::create();
        content->setContentSize({ W - 20, totalH });

        float yPos = totalH - 10;

        for (auto& v : vaults) {
            // Header de vault
            yPos -= 25;
            auto header = CCLabelBMFont::create(v.name, "bigFont.fnt");
            header->setScale(0.45f);
            header->setColor({ 0, 255, 200 });
            header->setPosition({ (W - 20) / 2, yPos });
            content->addChild(header);

            yPos -= 5;
            // Línea bajo header
            auto sep = CCLayerColor::create({ 0, 255, 200, 60 });
            sep->setContentSize({ W - 40, 1 });
            sep->setPosition({ 10, yPos });
            content->addChild(sep);

            // Códigos
            for (auto& code : v.codes) {
                yPos -= 20;
                std::string display = "  >> " + code;
                auto lbl = CCLabelBMFont::create(
                    display.c_str(), "chatFont.fnt"
                );
                lbl->setScale(0.6f);
                lbl->setColor({ 180, 255, 220 });
                lbl->setAnchorPoint({ 0, 0.5f });
                lbl->setPosition({ 15, yPos });
                content->addChild(lbl);
            }
            yPos -= 15;
        }

        scroll->m_contentLayer->addChild(content);
        scroll->moveToTop();
        m_mainLayer->addChild(scroll, 1);

        // Botón cerrar estilo cyberpunk
        auto closeLbl = CCLabelBMFont::create(
            "[ CLOSE ]", "bigFont.fnt"
        );
        closeLbl->setScale(0.4f);
        closeLbl->setColor({ 255, 80, 80 });

        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeLbl, this,
            menu_selector(VaultPopup::onClose)
        );

        auto closeMenu = CCMenu::create();
        closeMenu->addChild(closeBtn);
        closeMenu->setPosition({ W / 2, 8 });
        m_mainLayer->addChild(closeMenu, 3);

        return true;
    }

    void onClose(CCObject*) {
        this->removeFromParent();
    }

public:
    static VaultPopup* create() {
        auto ret = new VaultPopup();
        if (ret->initAnchored(340, 260)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// ── Selector de ícono ──────────────────────────────────────────────
class IconPickerPopup : public geode::Popup<> {
    static inline const char* icons[] = {
        "GJ_lock_open_001.png",
        "GJ_lockGray_001.png",
        "GJ_completesIcon_001.png",
        "GJ_infoIcon_001.png",
        "GJ_plusBtn_001.png",
        "GJ_starsIcon_001.png",
        "GJ_coinsIcon2_001.png",
        "GJ_hammerIcon_001.png",
        "GJ_diamond_001.png",
        "GJ_sIcon_001.png"
    };
    static inline int iconCount = 10;

protected:
    bool setup() override {
        auto winSize = m_mainLayer->getContentSize();
        float W = winSize.width;

        setTitle("Elegir Icono");

        auto scroll = ScrollLayer::create({ W - 20, 160 });
        scroll->setPosition({ 10, 30 });

        float totalW = iconCount * 55.0f;
        auto content = CCLayer::create();
        content->setContentSize({ totalW, 160 });

        for (int i = 0; i < iconCount; i++) {
            auto spr = CCSprite::createWithSpriteFrameName(icons[i]);
            if (!spr) continue;
            spr->setScale(1.2f);

            auto btn = CCMenuItemSpriteExtra::create(
                spr, this,
                menu_selector(IconPickerPopup::onPickIcon)
            );
            btn->setTag(i);

            auto menu = CCMenu::create();
            menu->addChild(btn);
            menu->setPosition({ i * 55.0f + 27, 80 });
            content->addChild(menu);
        }

        scroll->m_contentLayer->addChild(content);
        m_mainLayer->addChild(scroll, 1);

        return true;
    }

    void onPickIcon(CCObject* sender) {
        int idx = static_cast<CCNode*>(sender)->getTag();
        if (idx >= 0 && idx < iconCount) {
            Mod::get()->setSavedValue<std::string>(
                "btn-icon", icons[idx]
            );
            FLAlertLayer::create(
                nullptr, "OK",
                "Icono guardado!\nReiniciá el nivel o menú para verlo.",
                "OK", nullptr
            )->show();
        }
        this->removeFromParent();
    }

public:
    static IconPickerPopup* create() {
        auto ret = new IconPickerPopup();
        if (ret->initAnchored(320, 220)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

// ── Helper: crear menú con botón ───────────────────────────────────
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

    // Botón principal
    auto mainBtn = CCMenuItemSpriteExtra::create(spr, target, vaultSel);

    // Botón pequeño para cambiar ícono
    auto editSpr = CCSprite::createWithSpriteFrameName(
        "GJ_editBtn_001.png"
    );
    if (editSpr) editSpr->setScale(0.5f);
    CCMenuItemSpriteExtra* editBtn = nullptr;
    if (editSpr)
        editBtn = CCMenuItemSpriteExtra::create(editSpr, target, iconSel);

    auto menu = CCMenu::create();
    menu->addChild(mainBtn);
    if (editBtn) {
        editBtn->setPosition({ 20, -18 });
        menu->addChild(editBtn);
    }
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
            addChild(createVaultMenu(
                this,
                menu_selector(MenuLayerHook::onVault),
                menu_selector(MenuLayerHook::onEditIcon)
            ), 100);
        }
        return true;
    }

    void onVault(CCObject*) { VaultPopup::create()->show(); }
    void onEditIcon(CCObject*) { IconPickerPopup::create()->show(); }
};

// ── Hook PlayLayer ─────────────────────────────────────────────────
struct PlayLayerHook : Modify<PlayLayerHook, PlayLayer> {
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        auto where = Mod::get()->getSettingValue<std::string>("show-where");
        if (where == "everywhere" || where == "levels-only") {
            addChild(createVaultMenu(
                this,
                menu_selector(PlayLayerHook::onVault),
                menu_selector(PlayLayerHook::onEditIcon)
            ), 100);
        }
        return true;
    }

    void onVault(CCObject*) { VaultPopup::create()->show(); }
    void onEditIcon(CCObject*) { IconPickerPopup::create()->show(); }
};
