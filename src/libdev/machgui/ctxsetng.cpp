/*
 * C T X S E T N G . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "machgui/ctxsetng.hpp"
#include "machgui/ui/MenuButton.hpp"
#include "machgui/ui/MenuStyle.hpp"
#include "machgui/ui/MenuText.hpp"
#include "machgui/startup.hpp"
#include "machgui/ui/ScrollableText.hpp"
#include "machgui/ui/VerticalScrollBar.hpp"
#include "machgui/gui.hpp"
#include "machgui/sslistbx.hpp"
#include "machgui/sslistit.hpp"
#include "machgui/dbsystem.hpp"
#include "machgui/dbplanet.hpp"
#include "machgui/dbscenar.hpp"
#include "machgui/dbscenar.hpp"
#include "machgui/dbtexdat.hpp"
#include "machgui/database.hpp"
#include "machgui/strtdata.hpp"
#include "machgui/dropdwnc.hpp"
#include "machgui/ui/Text.hpp"
#include "machlog/network.hpp"
#include "gui/scrolbut.hpp"
#include "gui/font.hpp"
#include "gui/painter.hpp"
#include "machgui/internal/strings.hpp"
#include <stdarg.h>
#include "network/netnet.hpp"
#include "network/session.hpp"
#include "machgui/menus_helper.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////

class MachGuiMPMapSizeListBoxItem : public MachGuiSingleSelectionListBoxItem
// Canonical form revoked
{
public:
    MachGuiMPMapSizeListBoxItem(
        MachGuiStartupScreens* pStartupScreens,
        MachGuiSingleSelectionListBox* pListBox,
        size_t width,
        MachGuiDbSystem& system,
        MachGuiCtxSettings* pSettingsCtx)
        : MachGuiSingleSelectionListBoxItem(pStartupScreens, pListBox, width, system.menuString())
        , system_(system)
        , pSettingsCtx_(pSettingsCtx)
    {
    }

    ~MachGuiMPMapSizeListBoxItem() override { }

protected:
    void select() override
    {
        MachGuiSingleSelectionListBoxItem::select();

        pSettingsCtx_->updateTerrainTypeList(system_);
    }

private:
    MachGuiMPMapSizeListBoxItem(const MachGuiMPMapSizeListBoxItem&);
    MachGuiMPMapSizeListBoxItem& operator=(const MachGuiMPMapSizeListBoxItem&);

    // Data members...
    MachGuiDbSystem& system_;
    MachGuiCtxSettings* pSettingsCtx_;
};

//////////////////////////////////////////////////////////////////////////////////////////////

class MachGuiMPTerrainTypeListBoxItem : public MachGuiSingleSelectionListBoxItem
// Canonical form revoked
{
public:
    MachGuiMPTerrainTypeListBoxItem(
        MachGuiStartupScreens* pStartupScreens,
        MachGuiSingleSelectionListBox* pListBox,
        size_t width,
        MachGuiDbPlanet& planet,
        MachGuiCtxSettings* pSettingsCtx)
        : MachGuiSingleSelectionListBoxItem(pStartupScreens, pListBox, width, planet.menuString())
        , planet_(planet)
        , pSettingsCtx_(pSettingsCtx)
    {
    }

    ~MachGuiMPTerrainTypeListBoxItem() override { }

protected:
    void select() override
    {
        MachGuiSingleSelectionListBoxItem::select();

        pSettingsCtx_->updateScenarioList(planet_);
    }

private:
    MachGuiMPTerrainTypeListBoxItem(const MachGuiMPTerrainTypeListBoxItem&);
    MachGuiMPTerrainTypeListBoxItem& operator=(const MachGuiMPTerrainTypeListBoxItem&);

    // Data members...
    MachGuiDbPlanet& planet_;
    MachGuiCtxSettings* pSettingsCtx_;
};

//////////////////////////////////////////////////////////////////////////////////////////////

class MachGuiMPScenarioListBoxItem : public MachGuiSingleSelectionListBoxItem
// Canonical form revoked
{
public:
    MachGuiMPScenarioListBoxItem(
        MachGuiStartupScreens* pStartupScreens,
        MachGuiSingleSelectionListBox* pListBox,
        size_t width,
        MachGuiDbScenario& scenario,
        MachGuiCtxSettings* pSettingsCtx)
        : MachGuiSingleSelectionListBoxItem(pStartupScreens, pListBox, width, scenario.menuString())
        , scenario_(scenario)
        , pSettingsCtx_(pSettingsCtx)
    {
    }

    ~MachGuiMPScenarioListBoxItem() override { }

protected:
    void select() override
    {
        MachGuiSingleSelectionListBoxItem::select();

        pSettingsCtx_->updateSelectedScenario(scenario_);
    }

private:
    MachGuiMPScenarioListBoxItem(const MachGuiMPScenarioListBoxItem&);
    MachGuiMPScenarioListBoxItem& operator=(const MachGuiMPScenarioListBoxItem&);

    // Data members...
    MachGuiDbScenario& scenario_;
    MachGuiCtxSettings* pSettingsCtx_;
};

//////////////////////////////////////////////////////////////////////////////////////////////
#define LB_MINX 61
#define LB_MAXX 266
#define MAPSIZE_LB_MINY 15
#define MAPSIZE_LB_MAXY 84
#define TERRAINTYPE_LB_MINY 127
#define TERRAINTYPE_LB_MAXY 280
#define SCENARIO_LB_MINY 305
#define SCENARIO_LB_MAXY 457
#define SETTINGS_LB_MINY 19
#define SETTINGS_LB_MAXY 205
#define SETTINGS_LB_MINX 369
#define SETTINGS_LB_MAXX 601

MachGuiCtxSettings::MachGuiCtxSettings(MachGuiStartupScreens* pStartupScreens)
    : MachGui::GameMenuContext("sp", pStartupScreens)
{
    const auto& topLeft = getBackdropTopLeft();

    // Regular menu buttons...
    MachGuiMenuButton* pOKBtn = new MachGuiMenuButton(
        pStartupScreens,
        pStartupScreens,
        Gui::Box(302, 420, 444, 451) * MachGui::menuScaleFactor(),
        IDS_MENUBTN_OK,
        MachGui::ButtonEvent::OK);
    MachGuiMenuButton* pCancelBtn = new MachGuiMenuButton(
        pStartupScreens,
        pStartupScreens,
        Gui::Box(472, 420, 607, 451) * MachGui::menuScaleFactor(),
        IDS_MENUBTN_CANCEL,
        MachGui::ButtonEvent::EXIT);

    pCancelBtn->escapeControl(true);
    pOKBtn->defaultControl(true);

    // Disable OK button if we are not the host
    if (! pStartupScreens_->startupData()->isHost())
    {
        pOKBtn->disabled(true);
        pOKBtn->hasFocus(false);
        pCancelBtn->hasFocus(true);
    }

    // Scenario description
    pScenarioDesc_
        = new MachGuiScrollableText(pStartupScreens, Gui::Box(353, 288, 576, 384) * MachGui::menuScaleFactor());
    MachGuiVerticalScrollBar::createWholeBar(
        pStartupScreens,
        Gui::Coord(576, 288) * MachGui::menuScaleFactor(),
        96 * MachGui::menuScaleFactor(),
        pScenarioDesc_);

    // Display mapsize list box heading
    GuiResourceString mapsizeHeading(IDS_MENULB_MAPSIZE);
    GuiBmpFont font(GuiBmpFont::getFont(MachGui::Menu::largeFontLight()));
    MachGuiMenuText* pMapSizeText = new MachGuiMenuText(
        pStartupScreens,
        Gui::Box(
            Gui::Coord(LB_MINX, MAPSIZE_LB_MINY) * MachGui::menuScaleFactor(),
            Gui::Size(font.textWidth(mapsizeHeading.asString()), font.charHeight() + 2)),
        IDS_MENULB_MAPSIZE,
        MachGui::Menu::largeFontLight());

    // Display planet list box heading
    GuiResourceString terrainHeading(IDS_MENULB_TERRAINTYPE);
    MachGuiMenuText* pTerrainText = new MachGuiMenuText(
        pStartupScreens,
        Gui::Box(
            Gui::Coord(LB_MINX, TERRAINTYPE_LB_MINY) * MachGui::menuScaleFactor(),
            Gui::Size(font.textWidth(terrainHeading.asString()), font.charHeight() + 2)),
        IDS_MENULB_TERRAINTYPE,
        MachGui::Menu::largeFontLight());

    // Display scenario list box heading
    GuiResourceString scenarioHeading(IDS_MENULB_SCENARIO);
    MachGuiMenuText* pScenarioText = new MachGuiMenuText(
        pStartupScreens,
        Gui::Box(
            Gui::Coord(LB_MINX, SCENARIO_LB_MINY) * MachGui::menuScaleFactor(),
            Gui::Size(font.textWidth(scenarioHeading.asString()), font.charHeight() + 2)),
        IDS_MENULB_SCENARIO,
        MachGui::Menu::largeFontLight());

    // Display settings list box heading
    GuiResourceString settingsHeading(IDS_MENULB_SETTINGS);
    MachGuiMenuText* pSettingsText = new MachGuiMenuText(
        pStartupScreens,
        Gui::Box(
            Gui::Coord(SETTINGS_LB_MINX, SETTINGS_LB_MINY) * MachGui::menuScaleFactor(),
            Gui::Size(font.textWidth(settingsHeading.asString()), font.charHeight() + 2)),
        IDS_MENULB_SETTINGS,
        MachGui::Menu::largeFontLight());

    // Create system list box
    pMapSizeList_ = new MachGuiSingleSelectionListBox(
        pStartupScreens,
        pStartupScreens,
        Gui::Box(
            MachGui::menuScaleFactor() * LB_MINX,
            pMapSizeText->absoluteBoundary().maxCorner().y() - topLeft.first,
            MachGui::menuScaleFactor() * LB_MAXX,
            MachGui::menuScaleFactor() * MAPSIZE_LB_MAXY),
        1000 * MachGui::menuScaleFactor(),
        MachGuiSingleSelectionListBoxItem::reqHeight(),
        1);
    // Create planet list box
    pTerrainTypeList_ = new MachGuiSingleSelectionListBox(
        pStartupScreens,
        pStartupScreens,
        Gui::Box(
            MachGui::menuScaleFactor() * LB_MINX,
            pTerrainText->absoluteBoundary().maxCorner().y() - topLeft.first,
            MachGui::menuScaleFactor() * LB_MAXX,
            MachGui::menuScaleFactor() * TERRAINTYPE_LB_MAXY),
        1000 * MachGui::menuScaleFactor(),
        MachGuiSingleSelectionListBoxItem::reqHeight(),
        1);
    // Create scenario list box
    pScenarioList_ = new MachGuiSingleSelectionListBox(
        pStartupScreens,
        pStartupScreens,
        Gui::Box(
            MachGui::menuScaleFactor() * LB_MINX,
            pScenarioText->absoluteBoundary().maxCorner().y() - topLeft.first,
            MachGui::menuScaleFactor() * LB_MAXX,
            MachGui::menuScaleFactor() * SCENARIO_LB_MAXY),
        1000 * MachGui::menuScaleFactor(),
        MachGuiSingleSelectionListBoxItem::reqHeight(),
        1);

    // Create settings list box
    pSettingsList_ = new GuiSimpleScrollableList(
        pStartupScreens,
        Gui::Box(
            MachGui::menuScaleFactor() * SETTINGS_LB_MINX,
            pSettingsText->absoluteBoundary().maxCorner().y() - topLeft.first,
            MachGui::menuScaleFactor() * SETTINGS_LB_MAXX,
            MachGui::menuScaleFactor() * SETTINGS_LB_MAXY),
        (SETTINGS_LB_MAXX - SETTINGS_LB_MINX) / 2 * MachGui::menuScaleFactor(),
        MachGuiDropDownListBoxCreator::reqHeight() + 1 * MachGui::menuScaleFactor(),
        1);

    updateMapSizeList();
    initSettings();

    TEST_INVARIANT;
}

MachGuiCtxSettings::~MachGuiCtxSettings()
{
    TEST_INVARIANT;
}

void MachGuiCtxSettings::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachGuiCtxSettings& t)
{

    o << "MachGuiCtxSettings " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachGuiCtxSettings " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

// virtual
void MachGuiCtxSettings::update()
{
    animations_.update();
}

void MachGuiCtxSettings::updateMapSizeList()
{
    bool firstItem = true;

    MachGuiMPMapSizeListBoxItem* pSelectItem = nullptr;

    // for ( MachGuiDatabase::TerrainSize loop = MachGuiDatabase::SMALL; loop <= MachGuiDatabase::LARGE; ++loop )
    for (MachGuiDatabase::TerrainSize loop = MachGuiDatabase::SMALL; loop <= MachGuiDatabase::LARGE;
         loop = _STATIC_CAST(MachGuiDatabase::TerrainSize, _STATIC_CAST(uint, loop) + 1))
    {
        MachGuiDbSystem& system = MachGuiDatabase::instance().multiPlayerSystem(loop);

        MachGuiMPMapSizeListBoxItem* pItem = new MachGuiMPMapSizeListBoxItem(
            pStartupScreens_,
            pMapSizeList_,
            MachGui::menuScaleFactor() * (LB_MAXX - LB_MINX),
            system,
            this);
        // Select first item in list or previously selected item
        if (firstItem)
        {
            firstItem = false;
            pSelectItem = pItem;
        }
        else if (&system == &pStartupScreens_->startupData()->scenario()->planet().system())
        {
            pSelectItem = pItem;
        }
    }

    pSelectItem->selectThisItem();

    pMapSizeList_->childrenUpdated();
}

void MachGuiCtxSettings::updateTerrainTypeList(MachGuiDbSystem& system)
{
    // Delete all items from list
    pTerrainTypeList_->deleteAllItems();

    // Insert new items into list
    uint numPlanets = system.nPlanets();
    bool firstItem = true;
    MachGuiMPTerrainTypeListBoxItem* pSelectItem = nullptr;

    for (uint loop = 0; loop < numPlanets; ++loop)
    {
        MachGuiDbPlanet& planet = system.planet(loop);

        MachGuiMPTerrainTypeListBoxItem* pItem = new MachGuiMPTerrainTypeListBoxItem(
            pStartupScreens_,
            pTerrainTypeList_,
            MachGui::menuScaleFactor() * (LB_MAXX - LB_MINX),
            planet,
            this);
        // Select first item in list or previously selected item
        if (firstItem)
        {
            firstItem = false;
            pSelectItem = pItem;
        }
        else if (&planet == &pStartupScreens_->startupData()->scenario()->planet())
        {
            pSelectItem = pItem;
        }
    }

    pSelectItem->selectThisItem();

    pTerrainTypeList_->childrenUpdated();
}

void MachGuiCtxSettings::updateScenarioList(MachGuiDbPlanet& planet)
{
    // Delete all items from list
    pScenarioList_->deleteAllItems();

    // Insert new items into list
    uint numScenarios = planet.nScenarios();
    bool firstItem = true;
    MachGuiMPScenarioListBoxItem* pSelectItem = nullptr;

    for (uint loop = 0; loop < numScenarios; ++loop)
    {
        MachGuiDbScenario& scenario = planet.scenario(loop);

        MachGuiMPScenarioListBoxItem* pItem = new MachGuiMPScenarioListBoxItem(
            pStartupScreens_,
            pScenarioList_,
            MachGui::menuScaleFactor() * (LB_MAXX - LB_MINX),
            scenario,
            this);
        // Select first item in list or previously selected item
        if (firstItem)
        {
            firstItem = false;
            pSelectItem = pItem;
        }
        else if (&scenario == pStartupScreens_->startupData()->scenario())
        {
            pSelectItem = pItem;
        }
    }

    pSelectItem->selectThisItem();

    pScenarioList_->childrenUpdated();
}

void MachGuiCtxSettings::updateSelectedScenario(MachGuiDbScenario& scenario)
{
    pSelectedScenario_ = &scenario;
    pScenarioDesc_->setText(scenario.textData().campaignText());
}

// virtual
bool MachGuiCtxSettings::okayToSwitchContext()
{
    if (pStartupScreens_->lastButtonEvent() == MachGui::ButtonEvent::OK)
    {
        ASSERT(pStartupScreens_->startupData()->isHost(), "Only host should be able to change multiplayer settings");

        // Set scenario and settings before we send a message to all the players.
        pStartupScreens_->startupData()->scenario(pSelectedScenario_);
        pStartupScreens_->startupData()->fogOfWar(pFogOfWarSelector_->text());
        pStartupScreens_->startupData()->resources(pResourcesSelector_->text());
        pStartupScreens_->startupData()->startingResources(pStartingResourcesSelector_->text());
        pStartupScreens_->startupData()->startingPosition(pStartingPosSelector_->text());
        pStartupScreens_->startupData()->victoryCondition(pVictorySelector_->text());
        pStartupScreens_->startupData()->numPlayers(pSelectedScenario_->maxPlayers());
        pStartupScreens_->startupData()->techLevel(pTechLevelSelector_->text());
        pStartupScreens_->startupData()->broadcastAlliances(pAlliancesSelector_->text());
        pStartupScreens_->startupData()->disableFirstPerson(pDisableFirstPersonSelector_->text());

        // Based on the maximum number of players allowed in this multiplayer game update the
        // player slots to "open" or "unavailable".
        for (int loop = 0; loop < 4; ++loop)
        {
            if (loop < pSelectedScenario_->maxPlayers())
            {
                if (pStartupScreens_->startupData()->players()[loop].status_
                    == MachGuiStartupData::PlayerInfo::UNAVAILABLE)
                {
                    pStartupScreens_->startupData()->players()[loop].setPlayerName(MachGui::openText());
                }
            }
            else
            {
                pStartupScreens_->startupData()->players()[loop].setPlayerName(MachGui::unavailableText());
            }
        }
        // Updates clients
        pStartupScreens_->startupData()->sendUpdatePlayersMessage();
        pStartupScreens_->startupData()->sendUpdateGameSettingsMessage();
    }

    return true;
}

void MachGuiCtxSettings::initSettings()
{
    // Delete all items from list
    pSettingsList_->deleteAllChildren();

    // Add "fog of war" setting...
    addSetting(pFogOfWarSelector_, IDS_MENU_FOGOFWAR, 2, IDS_MENU_ON, IDS_MENU_OFF);
    pFogOfWarSelector_->text(pStartupScreens_->startupData()->fogOfWarStr());

    // Add "resource" setting...
    addSetting(pResourcesSelector_, IDS_MENU_RESOURCES, 3, IDS_MENU_HIGH, IDS_MENU_MEDIUM, IDS_MENU_LOW);
    pResourcesSelector_->text(pStartupScreens_->startupData()->resourcesStr());

    // Add "starting resource" setting...
    addSetting(
        pStartingResourcesSelector_,
        IDS_MENU_STARTINGRESOURCES,
        6,
        IDS_MENU_DEFAULT,
        IDS_MENU_RESOURCESLEVEL1,
        IDS_MENU_RESOURCESLEVEL2,
        IDS_MENU_RESOURCESLEVEL3,
        IDS_MENU_RESOURCESLEVEL4,
        IDS_MENU_RESOURCESLEVEL5);
    pStartingResourcesSelector_->text(pStartupScreens_->startupData()->startingResourcesStr());

    // Add "starting pos" setting...
    addSetting(pStartingPosSelector_, IDS_MENU_STARTPOS, 2, IDS_MENU_STARTFIXED, IDS_MENU_STARTRANDOM);
    pStartingPosSelector_->text(pStartupScreens_->startupData()->startingPositionStr());

    // Add "victory conditions" setting...
    addSetting(
        pVictorySelector_,
        IDS_MENU_VICTORYCONDITION,
        12,
        IDS_MENU_DEFAULT,
        IDS_MENU_VICTORYTANNIHILATION,
        IDS_MENU_VICTORYDESTROYPOD,
        IDS_MENU_VICTORYTIMED5,
        IDS_MENU_VICTORYTIMED10,
        IDS_MENU_VICTORYTIMED15,
        IDS_MENU_VICTORYTIMED30,
        IDS_MENU_VICTORYTIMED45,
        IDS_MENU_VICTORYTIMED60,
        IDS_MENU_VICTORYTIMED90,
        IDS_MENU_VICTORYTIMED120,
        IDS_MENU_VICTORYTIMED180);
    pVictorySelector_->text(pStartupScreens_->startupData()->victoryConditionStr());

    // Add "tech level" setting...
    addSetting(
        pTechLevelSelector_,
        IDS_MENU_STARTINGTECHLEVEL,
        4,
        IDS_MENU_DEFAULT,
        IDS_MENU_TECHLEVELLOW,
        IDS_MENU_TECHLEVELMED,
        IDS_MENU_TECHLEVELHIGH);
    pTechLevelSelector_->text(pStartupScreens_->startupData()->techLevelStr());

    // Add "broadcast alliances" setting...
    addSetting(pAlliancesSelector_, IDS_MENU_BROADCAST_ALLIANCE, 2, IDS_MENU_ON, IDS_MENU_OFF);
    pAlliancesSelector_->text(pStartupScreens_->startupData()->broadcastAlliancesStr());

    // Add "disable first person" setting...
    addSetting(pDisableFirstPersonSelector_, IDS_MENU_DISABLE_FIRST_PERSON, 2, IDS_MENU_ON, IDS_MENU_OFF);
    pDisableFirstPersonSelector_->text(pStartupScreens_->startupData()->disableFirstPersonStr());

    pSettingsList_->childrenUpdated();
}

void MachGuiCtxSettings::addSetting(MachGuiDropDownListBoxCreator*& pCreator, uint labelStrId, int numStrs, ...)
{
    const int width = (SETTINGS_LB_MAXX - SETTINGS_LB_MINX) / 2;

    va_list marker;

    va_start(marker, numStrs); // Initialize variable arguments.

    GuiResourceString labelStr(labelStrId);
    GuiStrings strings;
    MachGuiText* pText = new MachGuiText(pSettingsList_, width * Gui::uiScaleFactor(), labelStr.asString());
    pText->setTextOffset(Gui::Coord(1, 1) * Gui::uiScaleFactor());

    while (numStrs)
    {
        --numStrs;

        int listBoxStrId = va_arg(marker, int);

        GuiResourceString listBoxStr(listBoxStrId);
        strings.push_back(listBoxStr.asString());
    }

    pCreator = new MachGuiDropDownListBoxCreator(
        pSettingsList_,
        pStartupScreens_,
        width * Gui::uiScaleFactor(),
        strings,
        true);

    va_end(marker); // Reset variable arguments.
}

/* End CTXSETNG.CPP *************************************************/
