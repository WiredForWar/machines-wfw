/*
 * P A T H N A M E . H P P
 * (c) Charybdis Limited, 1995 - 1997. All Rights Reserved.
 */

/*
    SysPathName

    Provide a means of storing and combining pathnames. Also provide
    methods to find out if a given file or directory exists.
*/

#ifndef _SYS_PATHNAME_HPP
#define _SYS_PATHNAME_HPP

//////////////////////////////////////////////////////////////////////

#include "base/persist.hpp"
#include "base/tracker.hpp"

#include "stdlib/string.hpp"
#include <cstring>

//////////////////////////////////////////////////////////////////////

template <class T> class ctl_vector;

class SysPathNameImpl;

// Pattern: Pimple-Interface class.
class SysPathName
// Memberwise cannonical.
{
public:
    // This forces client files to include std::string and ctl_vector.
    using Components = ctl_vector<std::string>;

    SysPathName();
    // POST( not set() );
    SysPathName(const char* path);
    // POST( set() );
    SysPathName(const std::string& path);
    // POST( set() );
    SysPathName(const SysPathName& path);
    // POST( set() == path,set() );

    ~SysPathName();

    //  Set the root directory to be used by relative pathnames
    static void rootDirectory(const SysPathName& directory);

    //  Set the root directory from the given environment variable
    static void rootEnvironmentVariable(const std::string& environmentVariable);

    static SysPathName rootDirectory();

    const std::string& pathname() const;
    // PRE( set() )

    const char* c_str() const;

    //  True iff this pathname has been explicitly set - i.e. it hasn't been
    //  constructed by the default constructor.
    bool set() const;

    // Return true iff the pathname exists and is a file or a directory
    // POST( iff( result, existsAsDirectory() || existsAsFile() ) );
    bool exists() const;
    // PRE( set() )

    // Return true iff the pathname exists and is a directory
    bool existsAsDirectory() const;
    // PRE( set() )

    // Return true iff the pathname exists and is a file
    bool existsAsFile() const;
    // PRE( set() )

    static bool existsAsFile(const std::string& path);

    // Return true if the pathname has capitals. Use when wanting to check for files again in lowercase.
    bool containsCapitals() const;

    // CASE INSENSITIVE - Return true iff the pathname exists and is a file
    bool insensitiveExistsAsFile() const;

    // Return true iff the last section of the pathname has an extension
    bool hasExtension() const;
    // PRE( set() )

    // Return the extension of the pathname without the '.'
    // PRE( hasExtension() );
    std::string extension() const;
    // PRE( set() )

    // Set the extension of the pathname
    void extension(const std::string& newExtension);
    // PRE( set() )
    // POST( hasExtension() );

    // Return the directory part of the pathname
    std::string directory() const;
    // PRE( set() )
    // PRE( exists() );

    // Return the filename part of the pathname
    const std::string& filename() const;
    // PRE( set() )
    // PRE( existsAsFile() );

    // Return true iff the pathname is an absolute pathname
    bool isAbsolute() const;
    // PRE( set() )

    // Return true iff the pathname is a relative pathname
    bool isRelative() const;
    // PRE( set() )

    // Split the pathname into its component parts
    const Components& components() const;
    // PRE( set() )

    //  Set up the pathname from the given components
    void createFromComponents(const Components& newComponents);

    //  Remove the last component in the path name
    void pop_back();
    //  PRE( components().size() > 0 );

    // Combine the two pathnames. If nextPath is an absolute pathname, this will be set to nextPath.
    // If nextPath is a relative pathname, this will be set to the pathname that you get by following
    // this, then following nextPath.
    void combine(const SysPathName& nextPath);
    // PRE( set() )

    SysPathName& operator=(const char*);
    // POST( set() );
    SysPathName& operator=(const std::string&);
    // POST( set() );
    SysPathName& operator=(const SysPathName& rhs);
    // POST( set() = rhs.set() );

    //  Return true iff the given prefix is actually a prefix of this
    bool hasPrefix(const SysPathName& prefix) const;

    //  Remove the given prefix from this
    void removePrefix(const SysPathName& prefix);
    //  PRE( hasPrefix( prefix );

    friend std::ostream& operator<<(std::ostream& o, const SysPathName& p);

    PER_MEMBER_PERSISTENT_DEFAULT(SysPathName)

private:
    SysPathNameImpl* pImpl_;

    static std::string& internalRootDirectory();
    static bool& internalRootDirectorySet();
    static size_t& currentRootId();

    static std::string separator();
    static char extensionCharacter();

    void createComponents() const;

    void createPathnameFromComponents();

    bool checkForCapitals(const std::string& path) const;

    PER_FRIEND_READ_WRITE(SysPathName)
    OBJECT_TRACKER(SysPathName);
};

bool operator==(const SysPathName& a, const SysPathName& b);
bool operator<(const SysPathName& a, const SysPathName& b);

PER_DECLARE_PERSISTENT(SysPathName);

#endif
