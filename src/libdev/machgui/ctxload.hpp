/*
 * C T X L O A D . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    MachGuiCtxLoad

    A brief description of the class should go in here
*/

#ifndef _MACHGUI_CTXLOAD_HPP
#define _MACHGUI_CTXLOAD_HPP

#include "machgui/GameMenuContext.hpp"

class MachGuiDbSavedGame;
class MachGuiSingleSelectionListBox;
class MachGuiMenuButton;

class MachGuiCtxLoad : public MachGui::GameMenuContext
// Canonical form revoked
{
public:
    MachGuiCtxLoad(MachGuiStartupScreens* pStartupScreens);
    ~MachGuiCtxLoad() override;

    void CLASS_INVARIANT;

    void update() override;

    bool okayToSwitchContext() override;

    void buttonEvent(MachGui::ButtonEvent) override;

    void selectedSaveGame(MachGuiDbSavedGame*);

    void deleteSavedGame();

    void autoLoadGame();

protected:
    void updateSaveGameList();

private:
    friend std::ostream& operator<<(std::ostream& o, const MachGuiCtxLoad& t);

    MachGuiCtxLoad(const MachGuiCtxLoad&);
    MachGuiCtxLoad& operator=(const MachGuiCtxLoad&);

    // Data members...
    MachGuiSingleSelectionListBox* pSaveGameList_;
    MachGuiDbSavedGame* pSelectedSaveGame_;
    bool autoLoadGame_{};
    MachGuiMenuButton* pDeleteBtn_;
    MachGuiMenuButton* pOkBtn_;
};

#endif

/* End CTXLOAD.HPP **************************************************/
