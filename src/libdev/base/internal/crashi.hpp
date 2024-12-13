/*
 * C R A S H I . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    BaseCrashInternal

    Functions to deal with clearing up in the event of
    a crash or an assertion.
*/

#ifndef _BASE_CRASHI_HPP
#define _BASE_CRASHI_HPP

#include "base/base.hpp"

#include "ctl/vector.hpp"

#include <iostream>
#include <set>

class BaseCrashInternal
// Canonical form revoked
{
public:
    //  Singleton class
    static BaseCrashInternal& instance();
    ~BaseCrashInternal();

    using PFn = void (*)();
    //  Add a function to the list of functions to be
    //  called should a crash or an assertion occur.
    void addCrashFunction(PFn);

    void handleCrash() const;

    // Add / remove a stream to the list of streams to be closed
    // should a crash or an assertion occur
    void addCrashStream(std::ofstream&);
    void removeCrashStream(std::ofstream&);

    void CLASS_INVARIANT;

private:
    friend std::ostream& operator<<(std::ostream& o, const BaseCrashInternal& t);

    BaseCrashInternal(const BaseCrashInternal&);
    BaseCrashInternal& operator=(const BaseCrashInternal&);

    BaseCrashInternal();

    //  Functions to be called in the event of a crash
    ctl_vector<PFn> functions_;

    //  Streams to be closed in the event of a crash
    using Streams = std::set<std::ofstream*>;
    Streams streams_;
};

#endif

/* End CRASHI.HPP ***************************************************/
