/*
 * W D E B U G . H P P
 * (c) Charybdis Limited, 1998. All Rights Reserved
 */

/*
    wdebug

    A brief description of the class should go in here
*/

#ifndef _WDEBUG_HPP
#define _WDEBUG_HPP

#include "base/base.hpp"
#include "ctl/vector.hpp"
#include "stdlib/string.hpp"

class W4dSceneManager;

using string = std::string;

class wdebug
// Canonical form revoked
{
public:
    wdebug(W4dSceneManager* pSourceSceneManager);
    ~wdebug();

    void CLASS_INVARIANT;
    void add(const string& error);
    void display();

private:
    wdebug();

    friend std::ostream& operator<<(std::ostream& o, const wdebug& t);

    wdebug(const wdebug&);
    wdebug& operator=(const wdebug&);

    using errorlist = ctl_vector<string>;

    errorlist errors;
    W4dSceneManager* pSceneManager_;
};

#endif

/* End WDEBUG.HPP ***************************************************/
