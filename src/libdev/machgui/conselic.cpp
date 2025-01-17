/*
 * C O N S E L I C . C P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "conselic.hpp"

#include "machgui/actbmpnm.hpp"
#include "machgui/actnamid.hpp"
#include "machgui/ingame.hpp"
#include "machgui/commands/command.hpp"
#include "gui/restring.hpp"
#include "machlog/machlog.hpp"
#include "machlog/races.hpp"
#include "machlog/consitem.hpp"
#include "machphys/machphys.hpp"
#include "machgui/internal/strings.hpp"
#include "machgui/internal/mgsndman.hpp"

MachConstructionSelectIcon::MachConstructionSelectIcon(
    GuiDisplayable* pParent,
    MachInGameScreen* pInGameScreen,
    const MachLogConstructionItem& consItem)
    : GuiIcon(
        pParent,
        Gui::Coord(0, 0), // Will be relocated by icon sequence parent
        MachGui::getScaledImage(MachActorBitmaps::name(
            consItem.constructionType(),
            consItem.subType(),
            consItem.hwLevel(),
            consItem.weaponCombo(),
            MachLogRaces::instance().playerRace())))
    , pInGameScreen_(pInGameScreen)
    , consItem_(consItem)
{

    TEST_INVARIANT;
}

MachConstructionSelectIcon::~MachConstructionSelectIcon()
{
    TEST_INVARIANT;
}

void MachConstructionSelectIcon::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachConstructionSelectIcon& t)
{

    o << "MachConstructionSelectIcon " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachConstructionSelectIcon " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

// virtual
void MachConstructionSelectIcon::doBeDepressed(const GuiMouseEvent&)
{
    // Dispatch the type info to the active command
    // TBD:
    // Weapon combo needs to be passed though as well to allow different turret combinations.
    // needs a change to MGCommand which isn't needed right now so I'm not doing it.
    pInGameScreen_->activeCommand().typeData(
        consItem_.constructionType(),
        consItem_.subType(),
        consItem_.hwLevel()
        /*consItem_.weaponCombo()*/);

    MachGuiSoundManager::instance().playSound("gui/sounds/igclick.wav");
}

// virtual
void MachConstructionSelectIcon::doBeReleased(const GuiMouseEvent&)
{
}

// static
size_t MachConstructionSelectIcon::reqHeight()
{
    return 42 * Gui::uiScaleFactor(); // TODO : Remove hard coded value
}

// static
size_t MachConstructionSelectIcon::reqWidth()
{
    return 42 * Gui::uiScaleFactor(); // TODO : Remove hard coded value
}

// virtual
void MachConstructionSelectIcon::doHandleMouseEnterEvent(const GuiMouseEvent& mouseEvent)
{
    GuiIcon::doHandleMouseEnterEvent(mouseEvent);

    GuiString prompt = MachLogActorStringIdRestorer::getActorPromptText(
        consItem_.constructionType(),
        consItem_.subType(),
        consItem_.weaponCombo(),
        consItem_.hwLevel(),
        IDS_CONSTRUCT_PROMPT,
        IDS_CONSTRUCT_WITH_WEAPON_PROMPT);

    // Add bmu cost to end of prompt text
    char buffer[20];
    //  itoa( consItem_.buildingCost(), buffer, 10 );
    sprintf(buffer, "%d", consItem_.buildingCost());
    GuiResourceString bmuCostText(IDS_COST, GuiString(buffer));

    prompt += " " + bmuCostText.asString();

    pInGameScreen_->setCursorPromptText(prompt);
}

// virtual
void MachConstructionSelectIcon::doHandleMouseExitEvent(const GuiMouseEvent& mouseEvent)
{
    // Clear the cursor prompt string
    pInGameScreen_->clearCursorPromptText();

    GuiIcon::doHandleMouseExitEvent(mouseEvent);
}

/* End CONSELIC.CPP *************************************************/
