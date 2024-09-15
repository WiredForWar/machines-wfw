/*
 * C M D C O N S T . H P P
 * (c) Charybdis Limited, 1997. All Rights Reserved
 */

/*
    MachGuiRecycleCommand

    Implement interaction for the Construct command
*/

#ifndef _MACHGUI_CMDRECYC_HPP
#define _MACHGUI_CMDRECYC_HPP

#include "machgui/commands/command.hpp"

#include "machgui/gui.hpp"

// Forward refs
class MachPhysConstruction;
class MachLogConstruction;
class MachLogAdministrator;
class W4dDomain;
class MachLogSmelter;

// orthodox canonical (revoked)
class MachGuiRecycleCommand : public MachGuiCommand
{
public:
    // ctor.
    MachGuiRecycleCommand(MachInGameScreen* pInGameScreen);

    // dtor
    ~MachGuiRecycleCommand() override;

    /////////////////////////////////////////////////
    // Inherited from MachGuiCommand

    // Return new instance of this command
    std::unique_ptr<MachGuiCommand> clone() const override;

    // The resource file id of the prompt to be displayed when the cursor moves
    // over the command icon
    uint cursorPromptStringId() const override;

    // The resource file id of the prompt to be displayed when the command is clicked
    uint commandPromptStringid() const override;

    // reference to the up and down bitmap names for this command
    const std::pair<std::string, std::string>& iconNames() const override;

    // respond to pick on pActor in the world view window.
    // ctrl/shift/altPressed indicate which modifier keys were pressed at the time.
    void pickOnActor(MachActor* pActor, bool ctrlPressed, bool shiftPressed, bool altPressed) override;

    // Respond to cursor at location on the terrain.
    // ctrl/shift/altPressed indicate which modifier keys are pressed.
    // Returns 2d cursor to be displayed.
    MachGui::Cursor2dType
    cursorOnTerrain(const MexPoint3d& location, bool ctrlPressed, bool shiftPressed, bool altPressed) override;

    // Respond to cursor on pActor in the world view window.
    // ctrl/shift/altPressed indicate which modifier keys are pressed.
    // Returns 2d cursor to be displayed.
    MachGui::Cursor2dType
    cursorOnActor(MachActor* pActor, bool ctrlPressed, bool shiftPressed, bool altPressed) override;

    // Set the type data associated with the command.
    void typeData(MachLog::ObjectType objectType, int subType, uint level) override;

    // True if this is a kind of command that actor can ever execute.
    bool canActorEverExecute(const MachActor& actor) const override;

    // True iff there is an administer version of the command for squadrons
    // with an administrator. Default implementation returns false.
    bool canAdminApply() const override;

    // True if the interaction for the command is complete
    bool isInteractionComplete() const override;

    /////////////////////////////////////////////////
    // Hot key processing
    bool processButtonEvent(const DevButtonEvent&) override;

    void CLASS_INVARIANT;

    friend std::ostream& operator<<(std::ostream& o, const MachGuiRecycleCommand& t);

private:
    // Operation deliberately revoked
    MachGuiRecycleCommand(const MachGuiRecycleCommand&);
    MachGuiRecycleCommand& operator=(const MachGuiRecycleCommand&);
    bool operator==(const MachGuiRecycleCommand&);

    /////////////////////////////////////////////////
    // Inherited from MachGuiCommand

    // Execute the command for pActor
    bool doApply(MachActor* pActor, std::string* pReason) override;

    // Execute the command as a sqaudron whose most intelligent administrator
    // is pAdministrator. If successful return true. Otherwise false, with
    // a prompt std::string indicating reason for failure in pReason.
    bool doAdminApply(MachLogAdministrator* pAdministrator, std::string* pReason) override;
    // PRE( canAdminApply() );

    /////////////////////////////////////////////////

    // Data members
    bool hadFinalPick_; // True when valid location for the mine has been picked
    MachLogConstruction* pSmeltingBuilding_;
};

#endif

/* End CMDCONST.HPP **************************************************/