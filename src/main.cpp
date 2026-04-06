
#include <Geode/Geode.hpp>
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

        auto scroll = ScrollLayer::create({ winSize.width - 20, winSize.height - 60 });
        scroll->setPosition({ 10, 10 });

        float totalH = 0;
        for (auto& v : vaults)
            totalH += 25 + v.codes.size() * 18 + 8;

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
        if (ret->init(320, 240, "GJ_square01.png")) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class DraggableButton : public CCSprite {
    bool m_dragging = false;
    CCPoint m_offset;

public:
    static DraggableButton* create() {
        auto ret = new DraggableButton();
        if (ret->initWithSpriteFrameName("GJ_lock_open_001.png")) {
            ret->autorelease();
            ret->setScale(1.1f);
            ret->setOpacity(200);
            auto ws = CCDirector::get()->getWinSize();
            ret->setPosition({ ws.width - 25, ws.height / 2 });
            return ret;
        }
        delete ret;
        return nullptr;
    }

    bool ccTouchBegan(CCTouch* touch, CCEvent*) override {
        auto loc = touch->getLocation();
        if (boundingBox().containsPoint(loc)) {
            m_dragging = true;
            m_offset = getPosition() - loc;
            return true;
        }
        return false;
    }

    void ccTouchMoved(CCTouch* touch, CCEvent*) override {
        if (m_dragging)
            setPosition(touch->getLocation() + m_offset);
    }

    void ccTouchEnded(CCTouch* touch, CCEvent*) override {
        if (m_dragging) {
            m_dragging = false;
            float dist = ccpDistance(touch->getLocation(),
                                     touch->getStartLocation());
            if (dist < 10) {
                VaultCodesPopup::create()->show();
            }
        }
    }
};

class $modify(MenuLayer) {
    bool init() override {
        if (!MenuLayer::init()) return false;

        auto btn = DraggableButton::create();
        btn->setTag(9999);
        addChild(btn, 100);

        CCDirector::get()->getTouchDispatcher()->addTargetedDelegate(
            btn, -500, true
        );

        return true;
    }
};
