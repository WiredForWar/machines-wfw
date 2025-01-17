/*
 * A C T R E I N F . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    MachLogVoiceMailAction

    This action class can play a verbal email
*/

#ifndef _MACHLOG_ACTVMAIL_HPP
#define _MACHLOG_ACTVMAIL_HPP

#include "base/base.hpp"
#include "sim/action.hpp"
#include "machlog/vmdata.hpp"
#include "machphys/machphys.hpp"

#include <memory>

class UtlLineTokeniser;
class SimCondition;

class MachLogVoiceMailAction : public SimAction
// Canonical form revoked
{
public:
    ~MachLogVoiceMailAction() override;
    static std::unique_ptr<MachLogVoiceMailAction> newFromParser(SimCondition*, bool enabled, UtlLineTokeniser*);

    void CLASS_INVARIANT;

    PER_MEMBER_PERSISTENT_VIRTUAL(MachLogVoiceMailAction);
    PER_FRIEND_READ_WRITE(MachLogVoiceMailAction);

protected:
    void doAction() override;
    void doOutputOperator(std::ostream&) const override;

private:
    MachLogVoiceMailAction(SimCondition*, bool enabled);
    friend std::ostream& operator<<(std::ostream& o, const MachLogVoiceMailAction& t);

    MachLogVoiceMailAction(const MachLogVoiceMailAction&);
    MachLogVoiceMailAction& operator=(const MachLogVoiceMailAction&);

    VoiceMailID mailID_;
    MachPhys::Race race_;
};

PER_DECLARE_PERSISTENT(MachLogVoiceMailAction);

#endif

/* End ACTREINF.HPP *************************************************/
