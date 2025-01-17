/*
 * A C T W I N . C P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

//  Definitions of non-inline non-template methods and global functions

#include "base/diag.hpp"
#include "stdlib/string.hpp"
#include "mathex/point2d.hpp"
#include "utility/linetok.hpp"
#include "sim/manager.hpp"
#include "machlog/actworl.hpp"
#include "machlog/scenario.hpp"
#include "machlog/races.hpp"
#include "machlog/score.hpp"

PER_DEFINE_PERSISTENT(MachLogWinOrLoseAction);

MachLogWinOrLoseAction::MachLogWinOrLoseAction(SimCondition* pCondition, bool enabled)
    : SimAction(pCondition, enabled)
{
    TEST_INVARIANT;
}

// virtual
MachLogWinOrLoseAction::~MachLogWinOrLoseAction()
{
    TEST_INVARIANT;
}

void MachLogWinOrLoseAction::CLASS_INVARIANT
{
    INVARIANT(this != nullptr);
}

std::ostream& operator<<(std::ostream& o, const MachLogWinOrLoseAction& t)
{

    o << "MachLogWinOrLoseAction " << static_cast<const void*>(&t) << " start" << std::endl;
    o << "MachLogWinOrLoseAction " << static_cast<const void*>(&t) << " end" << std::endl;

    return o;
}

// virtual
void MachLogWinOrLoseAction::doAction()
{
    MachLogRaces& races = MachLogRaces::instance();
    MachPhys::Race raceWithHighestScore = MachPhys::N_RACES;
    int highestScore = 0;
    for (MachPhys::Race i : MachPhys::AllRaces)
    {
        HAL_STREAM("checking score for race " << i << " score: " << races.score(i) << std::endl);
        if (races.score(i).grossScore() > highestScore)
        {
            highestScore = races.score(i).grossScore();
            raceWithHighestScore = i;
        }
    }

    if (raceWithHighestScore == race_)
        races.hasWon(race_, true);
    else
        races.hasLost(race_, true);
}

std::unique_ptr<MachLogWinOrLoseAction>
MachLogWinOrLoseAction::newFromParser(SimCondition* pCondition, bool enabled, UtlLineTokeniser* pParser)
{
    std::unique_ptr<MachLogWinOrLoseAction> pResult(new MachLogWinOrLoseAction(pCondition, enabled));
    for (std::size_t i = 0; i < pParser->tokens().size(); ++i)
    {
        const std::string& token = pParser->tokens()[i];
        if (token == "RACE")
            pResult->race_ = MachLogScenario::machPhysRace(pParser->tokens()[i + 1]);
    }
    return pResult;
}

// virtual
void MachLogWinOrLoseAction::doOutputOperator(std::ostream& o) const
{
    SimAction::doOutputOperator(o);
    o << "Race " << race_ << std::endl;
}

void perWrite(PerOstream& ostr, const MachLogWinOrLoseAction& action)
{
    const SimAction& base1 = action;

    ostr << base1;
    ostr << action.race_;
}

void perRead(PerIstream& istr, MachLogWinOrLoseAction& action)
{
    SimAction& base1 = action;

    istr >> base1;
    istr >> action.race_;
}

MachLogWinOrLoseAction::MachLogWinOrLoseAction(PerConstructor con)
    : SimAction(con)
{
}

std::unique_ptr<MachLogWinOrLoseAction> MachLogWinOrLoseAction::newDynamic(SimCondition* pCondition, bool enabled, MachPhys::Race race)
{
    std::unique_ptr<MachLogWinOrLoseAction> pResult(new MachLogWinOrLoseAction(pCondition, enabled));
    pResult->race_ = race;
    return pResult;
}

/* End ACTREINF.CPP *************************************************/
