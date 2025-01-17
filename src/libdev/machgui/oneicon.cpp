/*
 * O N E I C O N . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "stdlib/string.hpp"
#include "machgui/corral.hpp"
#include "machgui/oneicon.hpp"
#include "machgui/ingame.hpp"
#include "machgui/actnamid.hpp"
#include "machgui/controlp.hpp"
#include "machgui/internal/strings.hpp"
#include "machlog/actor.hpp"
#include "machlog/machine.hpp"
#include "machlog/constron.hpp"
#include "machlog/races.hpp"
#include "machlog/canattac.hpp"
#include "machlog/rescarr.hpp"
#include "machlog/technici.hpp"
#include "machlog/spy.hpp"
#include "machlog/construc.hpp"
#include "machlog/mine.hpp"
#include "machlog/hwlab.hpp"
#include "machlog/factory.hpp"
#include "machlog/minesite.hpp"
#include "machlog/network.hpp"
#include "gui/gui.hpp"
#include "gui/painter.hpp"
#include "gui/icon.hpp"
#include "gui/restring.hpp"
#include "gui/event.hpp"
#include "machphys/objdata.hpp"
#include "machphys/machphys.hpp"
#include "machphys/rcardata.hpp"
#include "machphys/techdata.hpp"
#include "machphys/slocdata.hpp"
#include "machphys/ctordata.hpp"
#include "machphys/factdata.hpp"
#include "machphys/harddata.hpp"
#include "system/pathname.hpp"
#include "machgui/internal/mgsndman.hpp"

#include "render/TextOptions.hpp"

using SysPathNames = std::pair<SysPathName, SysPathName>;

class MachGuiSelectInsideBuildingIcon : public GuiIcon
// Canonical form revoked
{
public:
    MachGuiSelectInsideBuildingIcon(
        GuiDisplayable* pParent,
        Gui::Coord rel,
        const SysPathNames& bitmap,
        MachInGameScreen* pInGameScreen)
        : GuiIcon(pParent, rel, bitmap)
        , pConstruction_(nullptr)
        , pInGameScreen_(pInGameScreen)
    {
    }

    ~MachGuiSelectInsideBuildingIcon() override { }

    void setConstruction(MachLogConstruction* pConstruction) { pConstruction_ = pConstruction; }

    static size_t reqWidth() { return 24 * Gui::uiScaleFactor(); }
    static size_t reqHeight() { return 24 * Gui::uiScaleFactor(); }

    void doHandleMouseEnterEvent(const GuiMouseEvent& mouseEvent) override
    {
        GuiIcon::doHandleMouseEnterEvent(mouseEvent);

        GuiResourceString prompt(IDS_SELECTINSIDEBUILDING);
        // Set the cursor prompt
        pInGameScreen_->setCursorPromptText(prompt.asString());
    }

    void doHandleMouseExitEvent(const GuiMouseEvent& mouseEvent) override
    {
        GuiIcon::doHandleMouseExitEvent(mouseEvent);

        // Clear the cursor prompt
        pInGameScreen_->clearCursorPromptText();
    }

    void doBeDepressed(const GuiMouseEvent&) override
    {
        MachGuiSoundManager::instance().playSound("gui/sounds/igclick.wav");
    }

    void doBeReleased(const GuiMouseEvent& event) override
    {
        if (pConstruction_)
        {
            if (! event.isCtrlPressed())
            {
                pInGameScreen_->deselectAll();
            }

            MachLogRaces& races = MachLogRaces::instance();
            MachPhys::Race playerRace = races.playerRace();

            // Iterate through all machines inside building selecting fristd::endly machines
            const MachLogConstruction* pConstConstruction = pConstruction_;
            for (MachLogConstruction::Machines::const_iterator iter = pConstConstruction->machines().begin();
                 iter != pConstConstruction->machines().end();
                 ++iter)
            {
                if ((*iter)->selectionState() != MachLog::SELECTED && (*iter)->race() == playerRace)
                {
                    pInGameScreen_->select(*iter);
                }
            }
        }
    }

private:
    MachGuiSelectInsideBuildingIcon(const MachGuiSelectInsideBuildingIcon&);
    MachGuiSelectInsideBuildingIcon& operator=(const MachGuiSelectInsideBuildingIcon&);
    bool operator==(const MachGuiSelectInsideBuildingIcon&);

    // Data members...
    MachLogConstruction* pConstruction_;
    MachInGameScreen* pInGameScreen_;
};

class MachGuiInHeadIcon : public GuiIcon
// Canonical form revoked
{
public:
    MachGuiInHeadIcon(
        GuiDisplayable* pParent,
        Gui::Coord rel,
        const SysPathNames& bitmap,
        MachInGameScreen* pInGameScreen)
        : GuiIcon(pParent, rel, bitmap)
        , pMachine_(nullptr)
        , pInGameScreen_(pInGameScreen)
    {
    }

    ~MachGuiInHeadIcon() override { }

    void setMachine(MachLogMachine* pMachine)
    {
        pMachine_ = pMachine;

        if (pMachine_)
        {
            switch (pMachine_->race())
            {
                case MachPhys::RED:
                    bitmap(MachGui::getScaledImage("gui/misc/red/inhead.bmp"));
                    break;
                case MachPhys::GREEN:
                    bitmap(MachGui::getScaledImage("gui/misc/green/inhead.bmp"));
                    break;
                case MachPhys::BLUE:
                    bitmap(MachGui::getScaledImage("gui/misc/blue/inhead.bmp"));
                    break;
                case MachPhys::YELLOW:
                    bitmap(MachGui::getScaledImage("gui/misc/yellow/inhead.bmp"));
                    break;
                    DEFAULT_ASSERT_BAD_CASE(pMachine_->race());
            }
        }
    }

    static size_t reqWidth() { return 24 * Gui::uiScaleFactor(); }
    static size_t reqHeight() { return 24 * Gui::uiScaleFactor(); }

    void doHandleMouseEnterEvent(const GuiMouseEvent& mouseEvent) override
    {
        GuiIcon::doHandleMouseEnterEvent(mouseEvent);

        GuiResourceString prompt(IDS_INHEAD);
        // Set the cursor prompt
        pInGameScreen_->setCursorPromptText(prompt.asString());
    }

    void doHandleMouseExitEvent(const GuiMouseEvent& mouseEvent) override
    {
        GuiIcon::doHandleMouseExitEvent(mouseEvent);

        // Clear the cursor prompt
        pInGameScreen_->clearCursorPromptText();
    }

    void doBeDepressed(const GuiMouseEvent&) override
    {
        MachGuiSoundManager::instance().playSound("gui/sounds/igclick.wav");
    }

    void doBeReleased(const GuiMouseEvent&) override
    {
        if (pMachine_)
        {
            pInGameScreen_->switchToInHead();
        }
    }

private:
    MachGuiInHeadIcon(const MachGuiInHeadIcon&);
    MachGuiInHeadIcon& operator=(const MachGuiInHeadIcon&);
    bool operator==(const MachGuiInHeadIcon&);

    // Data members...
    MachLogMachine* pMachine_;
    MachInGameScreen* pInGameScreen_;
};

MachGuiCorralSingleIconInfo::MachGuiCorralSingleIconInfo(
    GuiDisplayable* pParent,
    Gui::Coord rel,
    MachInGameScreen* pInGameScreen)
    : GuiDisplayable(
        pParent,
        Gui::Boundary(
            rel.x(),
            rel.y(),
            rel.x() + MachGuiCorralSingleIconInfo::reqWidth(),
            rel.y() + MachGuiCorralSingleIconInfo::reqHeight()))
    , pActor_(nullptr)
    , pInGameScreen_(pInGameScreen)
{
    TEST_INVARIANT;
}

MachGuiCorralSingleIconInfo::~MachGuiCorralSingleIconInfo()
{
    TEST_INVARIANT;
}

void MachGuiCorralSingleIconInfo::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachGuiCorralSingleIconInfo& t)
{

    o << "MachGuiCorralSingleIconInfo " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachGuiCorralSingleIconInfo " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

// static
size_t MachGuiCorralSingleIconInfo::reqWidth()
{
    return 93 * Gui::uiScaleFactor();
}

// static
size_t MachGuiCorralSingleIconInfo::reqHeight()
{
    return 47 * Gui::uiScaleFactor();
}

// virtual
bool MachGuiCorralSingleIcon::beNotified(W4dSubject* pSubject, W4dSubject::NotificationEvent event, int clientData)
{
    PRE(pSubject == pActor_);

    switch (event)
    {
        case W4dSubject::DELETED:
            isObservingActor_ = false;
            pActor_ = nullptr;
            pIconInfo_->setActor(nullptr);
            pSelectInsideBuildingIcon_->isVisible(false);
            pInHeadIcon_->isVisible(false);
            changed();
            break;
        case W4dSubject::CLIENT_SPECIFIC:
            if (clientData == MachLog::HEALTH_STATUS_CHANGED || clientData == MachLog::PERCENTAGE_COMPLETE_CHANGED
                || clientData == MachLog::TELEPORTED_OUT_OF_WORLD || clientData == MachLog::ENTERED_WORLD
                || clientData == MachLog::RACE_CHANGED || clientData == MachLog::CHANGED_CAMOUFLAGE_STATUS
                || clientData == MachLog::CHANGED_MINERALS_CARRIED
                || clientData == MachLog::CHANGED_N_MACHINES_INSIDE_CONSTRUCTION)
            {
                setActor(pActor_, true);
            }
            break;
    }

    return isObservingActor_;
}

void MachGuiCorralSingleIconInfo::doDisplay()
{
    // Redraw the control panel background
    pInGameScreen_->controlPanel().redrawAreaImmediate(*this);

    // Load and display the string for the info
    if (pActor_)
    {
        MachLogActorStringIdRestorer infoStringId;

        GuiResourceString::Id id = infoStringId.stringId(pActor_);
        GuiResourceString iconInfo(id);
        std::string concat = iconInfo.asString();
        concat += "\n";

        MachPhys::Race playerRace = MachLogRaces::instance().playerRace();

        if (pActor_->objectIsConstruction() && ! pActor_->asConstruction().isComplete())
        {
            // Only display extra info if the actor is ours.
            if (pActor_->race() == playerRace)
            {
                char buffer[20];

                // Display percentage complete
                //              itoa( pActor_->asConstruction().percentageComplete(), buffer, 10 );
                sprintf(buffer, "%d", pActor_->asConstruction().percentageComplete());
                GuiResourceString percentCompleteText(IDS_PERCENTAGECOMPLETE, GuiString(buffer));
                concat += percentCompleteText.asString();
                concat += "\n";
            }
        }
        else
        {
            const MachPhysObjectData& objData = pActor_->objectData();
            char buffer[20];
            char buffer2[20];

            MachPhys::ArmourUnits maxAp = objData.armour();
            MachPhys::ArmourUnits ap = pActor_->armour();
            MachPhys::HitPointUnits maxHp = objData.hitPoints();
            MachPhys::HitPointUnits hp = pActor_->hp();

            if (pActor_->race() == playerRace)
            {
                // Display actor specific info
                std::string actorSpecificInfoStr;

                // Can attack info
                if (pActor_->objectIsCanAttack())
                {
                    //                  itoa( pActor_->asCanAttack().getMaximumWeaponRange(), buffer, 10 );
                    sprintf(buffer, "%d", (uint)pActor_->asCanAttack().getMaximumWeaponRange());
                    GuiResourceString weaponRangeStr(IDS_WEAPONRANGE);
                    actorSpecificInfoStr = weaponRangeStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Resource carrier info
                else if (
                    pActor_->objectType() == MachLog::RESOURCE_CARRIER
                    && pActor_->asResourceCarrier().isNormalResourceCarrier())
                {
                    //                  itoa( pActor_->asResourceCarrier().data().capacity(), buffer, 10 );
                    //                  itoa( pActor_->asResourceCarrier().amountCarried(), buffer2, 10 );
                    sprintf(buffer, "%d", pActor_->asResourceCarrier().data().capacity());
                    sprintf(buffer2, "%d", pActor_->asResourceCarrier().amountCarried());
                    GuiResourceString capacityStr(IDS_CAPACITY);
                    actorSpecificInfoStr = capacityStr.asString() + " ";
                    actorSpecificInfoStr += buffer2;
                    actorSpecificInfoStr += "/";
                    actorSpecificInfoStr += buffer;
                }
                // Technician info
                else if (pActor_->objectType() == MachLog::TECHNICIAN)
                {
                    //                  itoa( pActor_->asTechnician().data().researchRate(), buffer, 10 );
                    sprintf(buffer, "%d", pActor_->asTechnician().data().researchRate());
                    GuiResourceString researchPointsStr(IDS_MACHINERESEARCHPOINTS);
                    actorSpecificInfoStr = researchPointsStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Spy info
                else if (pActor_->objectType() == MachLog::SPY_LOCATOR)
                {
                    //                  itoa( pActor_->asSpyLocator().data().mineCapacity(), buffer, 10 );
                    //                  itoa( pActor_->asSpyLocator().nMines(), buffer2, 10 );
                    sprintf(buffer, "%d", pActor_->asSpyLocator().data().mineCapacity());
                    sprintf(buffer2, "%d", pActor_->asSpyLocator().nMines());
                    GuiResourceString minesStr(IDS_MINESHELD);
                    actorSpecificInfoStr = minesStr.asString() + " ";
                    actorSpecificInfoStr += buffer2;
                    actorSpecificInfoStr += "/";
                    actorSpecificInfoStr += buffer;
                }
                // Geo info
                else if (pActor_->objectType() == MachLog::GEO_LOCATOR)
                {
                    //                  itoa( pActor_->asMachine().machineData().scannerRange(), buffer, 10 );
                    sprintf(buffer, "%d", (uint)pActor_->asMachine().machineData().scannerRange());
                    GuiResourceString locateRangeStr(IDS_LOCATERANGE);
                    actorSpecificInfoStr = locateRangeStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Constructor info
                else if (pActor_->objectType() == MachLog::CONSTRUCTOR)
                {
                    //                  itoa( pActor_->asConstructor().data().constructionRate(), buffer, 10 );
                    sprintf(buffer, "%d", pActor_->asConstructor().data().constructionRate());
                    GuiResourceString constructRateStr(IDS_CONSTRUCTRATE);
                    actorSpecificInfoStr = constructRateStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Mine info. BMU's left in mine.
                else if (pActor_->objectType() == MachLog::MINE)
                {
                    MachPhys::BuildingMaterialUnits bmusLeft = 0;

                    if (pActor_->asMine().hasMineralSite())
                    {
                        bmusLeft = _CONST_CAST(const MachLogMine&, pActor_->asMine()).mineralSite().amountOfOre();
                    }

                    // Add BMU info
                    //                  itoa( bmusLeft, buffer, 10 );
                    sprintf(buffer, "%d", bmusLeft);
                    GuiResourceString remainingBmuStr(IDS_REMAININGBMU);
                    actorSpecificInfoStr = remainingBmuStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Factory info.
                else if (pActor_->objectType() == MachLog::FACTORY)
                {
                    // Add BMU info
                    //                  itoa( pActor_->asFactory().data().buildRate(), buffer, 10 );
                    sprintf(buffer, "%d", pActor_->asFactory().data().buildRate());
                    GuiResourceString buildRateStr(IDS_BUILDRATE);
                    actorSpecificInfoStr = buildRateStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }
                // Lab info.
                else if (pActor_->objectType() == MachLog::HARDWARE_LAB)
                {
                    // Add Research Rate info
                    //                  itoa( pActor_->asHardwareLab().totalResearchRate(), buffer, 10 );
                    sprintf(buffer, "%d", (uint)pActor_->asHardwareLab().totalResearchRate());
                    GuiResourceString researchPointsStr(IDS_RESEARCHPOINTSINLAB);
                    actorSpecificInfoStr = researchPointsStr.asString() + " ";
                    actorSpecificInfoStr += buffer;
                }

                if (actorSpecificInfoStr != "")
                {
                    concat += actorSpecificInfoStr;
                    concat += "\n";
                }
            }

            // Display armour info
            //          itoa( ap, buffer, 10 );
            //          itoa( maxAp, buffer2, 10 );
            sprintf(buffer, "%d", ap);
            sprintf(buffer2, "%d", maxAp);
            GuiStrings insertStrings;
            insertStrings.reserve(2);
            insertStrings.push_back(GuiString(buffer));
            insertStrings.push_back(GuiString(buffer2));
            GuiResourceString apStr(IDS_ARMOUR, insertStrings);
            concat += apStr.asString();
            concat += "\n";

            // Display hp info
            //          itoa( hp, buffer, 10 );
            //          itoa( maxHp, buffer2, 10 );
            sprintf(buffer, "%d", hp);
            sprintf(buffer2, "%d", maxHp);
            GuiStrings insertStrings2;
            insertStrings2.reserve(2);
            insertStrings2.push_back(GuiString(buffer));
            insertStrings2.push_back(GuiString(buffer2));
            GuiResourceString hpStr(IDS_HITPOINTS, insertStrings2);
            concat += hpStr.asString();
        }

        // Render the text
        Gui::Coord textPos(absoluteBoundary().minCorner());
        Render::TextOptions options;
        options.setColor(MachGui::OFFWHITE());
        options.setShadow(1, 1, Gui::BLACK());

        const int fontPixelSize = MachGui::corralInfoFontSize();
        GuiPainter::instance().drawText(textPos, concat.c_str(), options, fontPixelSize);
    }
}

void MachGuiCorralSingleIconInfo::setActor(MachActor* pActor)
{
    pActor_ = pActor;
}

// virtual
void MachGuiCorralSingleIcon::domainDeleted(W4dDomain*)
{
}

MachGuiCorralSingleIcon::MachGuiCorralSingleIcon(
    GuiDisplayable* pParent,
    const Gui::Coord& rel,
    MachInGameScreen* pInGameScreen)
    : GuiDisplayable(
        pParent,
        Gui::Boundary(
            rel.x(),
            rel.y(),
            rel.x() + MachGuiCorralSingleIcon::reqWidth(),
            rel.y() + MachGuiCorralSingleIcon::reqHeight()))
    , pInGameScreen_(pInGameScreen)
    , pIcon_(nullptr)
    , pActor_(nullptr)
    , isObservingActor_(false)
{
    pIconInfo_
        = new MachGuiCorralSingleIconInfo(this, Gui::Coord(MachGuiCorralResource::buttonWidth(), 0), pInGameScreen_);
    pSelectInsideBuildingIcon_ = new MachGuiSelectInsideBuildingIcon(
        this,
        Gui::Coord(MachGuiCorralResource::buttonWidth() + MachGuiCorralSingleIconInfo::reqWidth(), 0),
        SysPathNames(
            MachGui::getScaledImagePath("gui/misc/contents.bmp"),
            MachGui::getScaledImagePath("gui/misc/contents.bmp")),
        pInGameScreen_);
    pInHeadIcon_ = new MachGuiInHeadIcon(
        this,
        Gui::Coord(MachGuiCorralResource::buttonWidth() + MachGuiCorralSingleIconInfo::reqWidth(), 0),
        SysPathNames(
            MachGui::getScaledImagePath("gui/misc/red/inhead.bmp"),
            MachGui::getScaledImagePath("gui/misc/red/inhead.bmp")),
        pInGameScreen_);
}

// virtual
MachGuiCorralSingleIcon::~MachGuiCorralSingleIcon()
{
    if (isObservingActor_ && pActor_)
        pActor_->detach(this);
}

// static
size_t MachGuiCorralSingleIcon::reqWidth()
{
    return MachGuiCorralResource::buttonWidth() + MachGuiCorralSingleIconInfo::reqWidth()
        + MachGuiSelectInsideBuildingIcon::reqWidth();
}

// static
size_t MachGuiCorralSingleIcon::reqHeight()
{
    return MachGuiCorralResource::buttonHeight();
}

void MachGuiCorralSingleIcon::setActor(MachActor* pActor)
{
    PRE(pActor);

    setActor(pActor, false);
}

void MachGuiCorralSingleIcon::setActor(MachActor* pActor, bool forceUpdate)
{
    PRE(pIconInfo_);
    PRE(pActor);

    if (pActor_ != pActor || forceUpdate) // Check to see if single icon corral is already displaying this actor
    {
        // Set up observer relationship
        if (pActor_ != pActor)
        {
            // Stop observing actor
            if (isObservingActor_ && pActor_)
                pActor_->detach(this);

            // Start observing new actor
            pActor->attach(this);
            isObservingActor_ = true;

            // Actor has changes so we need a new icon
            delete pIcon_;
            pIcon_ = new MachGuiCorralResource(this, Gui::Coord(0, 0), pActor, pInGameScreen_);
        }

        pActor_ = pActor;

        pIconInfo_->setActor(pActor);

        if (pActor->objectIsConstruction())
        {
            if (pActor->objectType() == MachLog::MISSILE_EMPLACEMENT)
            {
                // Originally missile emplacements ( apart from the silo ) could be
                // embodied, this is currently no-longer true but leave the code in anyway
                // so if anyone changes there mind then...
                /*if ( pActor->subType() == MachPhys::ICBM )
                {
                    // Silo cannot be embodied.
                    pSelectInsideBuildingIcon_->isVisible( false );
                    pInHeadIcon_->isVisible( false );
                }
                else
                {
                    MachLogRaces& races = MachLogRaces::instance();
                    MachPhys::Race playerRace = races.playerRace();

                    if ( pActor->race() == playerRace )
                    {
                        pInHeadIcon_->isVisible( true );
                    }
                    else
                    {
                        pInHeadIcon_->isVisible( false );
                    }
                    pSelectInsideBuildingIcon_->isVisible( false );
                }*/

                pSelectInsideBuildingIcon_->isVisible(false);
                pInHeadIcon_->isVisible(false);
            }
            else
            {
                pSelectInsideBuildingIcon_->setConstruction(&pActor->asConstruction());

                pInHeadIcon_->isVisible(false);
                pSelectInsideBuildingIcon_->isVisible(false);

                const MachLogConstruction& construction = pActor->asConstruction();

                // Only make "select all inside building" button visible if there are fristd::endly
                // machines in the building
                bool friendlyMachineInside = false;
                MachPhys::Race playerRace = MachLogRaces::instance().playerRace();

                for (MachLogConstruction::Machines::const_iterator iter = construction.machines().begin();
                     iter != construction.machines().end() && ! friendlyMachineInside;
                     ++iter)
                {
                    if ((*iter)->race() == playerRace)
                    {
                        friendlyMachineInside = true;
                    }
                }

                if (friendlyMachineInside)
                {
                    pSelectInsideBuildingIcon_->isVisible(true);
                }
            }
        }
        else if (pActor->objectIsMachine())
        {
            MachPhys::Race playerRace = MachLogRaces::instance().playerRace();

            pSelectInsideBuildingIcon_->isVisible(false);

            // Check that machine can be entered...
            bool headIconVisible = pActor->race() == playerRace && ! pActor->asMachine().insideAPC();

            // Extra check if multiplayer game cus you can disable 1st person
            if (headIconVisible && pInGameScreen_->isFirstPersonDisabled())
            {
                headIconVisible = false;
            }

            pInHeadIcon_->isVisible(headIconVisible);
            pInHeadIcon_->setMachine(&pActor->asMachine());
        }

        changed();
    }
}

// virtual
void MachGuiCorralSingleIcon::doDisplay()
{
    pInGameScreen_->controlPanel().redrawAreaImmediate(*this);
}

void MachGuiCorralSingleIcon::clear()
{
    if (isObservingActor_ && pActor_)
        pActor_->detach(this);

    pActor_ = nullptr;
    isObservingActor_ = false;
    pSelectInsideBuildingIcon_->isVisible(false);
    pInHeadIcon_->isVisible(false);
    pIconInfo_->setActor(nullptr);
    changed();
}

/* End ONEICON.CPP **************************************************/
