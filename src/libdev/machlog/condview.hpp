/*
 * C O N D V I E W . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    MachLogCameraViewCondition

    This condition will fire an action if the user is viewing a certain location.
*/

#ifndef _MACHLOG_CONDVIEW_HPP
#define _MACHLOG_CONDVIEW_HPP

#include "base/base.hpp"
#include "mathex/point3d.hpp"
#include "mathex/angle.hpp"
#include "phys/phys.hpp"

#include "sim/conditio.hpp"

class UtlLineTokeniser;

class MachLogCameraViewCondition : public SimCondition
// Canonical form revoked
{
public:
    static MachLogCameraViewCondition* newFromParser(UtlLineTokeniser*);

    bool doHasConditionBeenMet() const override;

    ~MachLogCameraViewCondition() override;

    void CLASS_INVARIANT;

    PER_MEMBER_PERSISTENT_VIRTUAL(MachLogCameraViewCondition);
    PER_FRIEND_READ_WRITE(MachLogCameraViewCondition);

protected:
    const PhysRelativeTime& recommendedCallBackTimeGap() const override;
    void doOutputOperator(std::ostream&) const override;

private:
    MachLogCameraViewCondition(const std::string& keyName, const MexPoint3d&, const MexRadians&);

    friend std::ostream& operator<<(std::ostream& o, const MachLogCameraViewCondition& t);

    MachLogCameraViewCondition(const MachLogCameraViewCondition&);
    MachLogCameraViewCondition& operator=(const MachLogCameraViewCondition&);

    MexPoint3d location_;
    MexRadians angle_;
};

PER_DECLARE_PERSISTENT(MachLogCameraViewCondition);

#endif

/* End CONDTIME.HPP *************************************************/
