
#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;

class VaultCodesPopup : public geode::Popup<> {
protected:
    bool setup() override {
        setTitle("Códigos de Vaults");
        auto winSize = m_mainLayer->getContentSize();

        struct VaultEntry {
            std::string vault;
            std::vector<std::string> codes;
        };

        std::vector<VaultEntry> vaults = {
            { "The Vault",
              { "Sparky", "Spooky", "Ahead", "Neverending",
                "Mule", "Blockbite", "Gimmie", "Freeze",
                "Cruise", "Ganon" }
            },
            { "Vault of Secrets",
              { "Octopus", "Robotop", "Neverending", "Ahead",
                "Porcupy", "Thechickenisonfire", "Gimmie", "Sparky" }
            },
            { "Chamber of Time",
              { "Silence", "Retray", "Timelybird",
                "Hexagons", "Glubfub", "Vaultkeeper" }
            }
        };

        float totalH = 0;
        for (auto& v : vaults)
            totalH += 25 + v.codes.size() * 18 + 8;

        auto scroll = ScrollLayer::create({ winSize.width - 20, winSize.height - 60 });
        scroll->setPosition({ 10, 10 });

        float yPos = totalH;
        auto content = CCLayer::create();
        content->setContentSize({ winSize.width - 20, totalH });

        for (auto& v : vaults) {
            yPos -= 20;
            auto title = CCLabelBMFont::create(v.vault.c_str(), "goldFont.fnt");
            title->setScale(0.6f);
            title->setPosition({ (winSize.width - 20) / 2, yPos });
            content->addChild(title);
            yPos -= 5;

            for (auto& code : v.codes) {
                yPos -= 18;
                auto lbl = CCLabelBMFont::create(("• " + code).c_str(), "chatFont.fnt");
                lbl->setScale(0.55f);
                lbl->setAnchorPoint({ 0, 0.5f });
                lbl->setPosition({ 15, yPos });
                content->addChild(lbl);
            }
            yPos -= 8;
        }

        scroll->m_contentLayer->addChild(content);
        scroll->moveToTop();
        m_mainLayer->addChild(scroll);
        return true;
    }

public:
    static VaultCodesPopup* create() {
        auto ret = new VaultCodesPopup();
        if (ret->initAnchored(320, 240)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class $modify(MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto ws = CCDirector::get()->getWinSize();

        auto spr = CCSprite::createWithSpriteFrameName("GJ_lock_open_001.png");
        spr->setScale(1.1f);

        auto btn = CCMenuItemSpriteExtra::create(
            spr, this,
            menu_selector(MenuLayerExt::onVaultCodes)
        );

        auto menu = CCMenu::create();
        menu->addChild(btn);
        menu->setPosition({ ws.width - 25, ws.height / 2 });
        addChild(menu, 100);

        return true;
    }

    void onVaultCodes(CCObject*) {
        VaultCodesPopup::create()->show();
    }
};
