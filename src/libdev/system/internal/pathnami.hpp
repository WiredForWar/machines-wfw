/***********************************************************

  P A T H N A M I . H P P
  Copyright (c) 1998 Charybdis Limited, All rights reserved.

***********************************************************/

#ifndef _SYSTEM_INTERNAL_PATHNAME_IMPL_HPP
#define _SYSTEM_INTERNAL_PATHNAME_IMPL_HPP

#include "system/pathname.hpp"

// Pattern: Pimple-Implementation part.
class SysPathNameImpl
// Memberwise Cannonical.
{
public:
    std::string pathname_;

    // If this is a relative pathname this includes the root directory.
    std::string fullPathname_;
    SysPathName::Components components_;

    // True iff the pathname has been explicitly set.
    bool set_{};

    size_t rootId_{};
    bool fullPathnameSet_{};
    bool componentsSet_{};

    bool containsCapitals_{};
};

#endif /* _SYSTEM_INTERNAL_PATHNAME_IMPL_HPP **************/
