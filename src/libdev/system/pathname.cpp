/*
 * P A T H N A M E . C P P
 * (c) Charybdis Limited, 1995 - 1997. All Rights Reserved.
 */

//////////////////////////////////////////////////////////////////////

#include "base/error.hpp"
#include "ctl/vector.hpp"

#include "system/pathname.hpp"
#include "system/internal/pathnami.hpp"

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cctype>

#define CB_SYS_PATHNAME_DEPIMPL                                                                                        \
    CB_DEPIMPL(std::string, pathname_);                                                                                     \
    CB_DEPIMPL(std::string, fullPathname_);                                                                                 \
    CB_DEPIMPL(ctl_vector<std::string>, components_);                                                                       \
    CB_DEPIMPL(bool, set_);                                                                                            \
    CB_DEPIMPL(size_t, rootId_);                                                                                       \
    CB_DEPIMPL(bool, fullPathnameSet_);                                                                                \
    CB_DEPIMPL(bool, componentsSet_);                                                                                  \
    CB_DEPIMPL(bool, containsCapitals_);

// Used in the persistence functions.
#define CB_FRIEND_DEPIMPL(type, name, objectRef)                                                                       \
    PRE(objectRef.pImpl_);                                                                                             \
    type& name = objectRef.pImpl_->name

// Allows other SysPathNames' members to be used.
#define CB_PEER_PTR_DEPIMPL(objectPtr, name) objectPtr->pImpl_->name
#define CB_PEER_REF_DEPIMPL(objectRef, name) objectRef.pImpl_->name

//////////////////////////////////////////////////////////////////////

PER_DEFINE_PERSISTENT(SysPathName);

SysPathName::SysPathName()

    : pImpl_(new SysPathNameImpl())
{
    CB_SYS_PATHNAME_DEPIMPL;

    set_ = false;
    fullPathnameSet_ = false;
    componentsSet_ = false;
    rootId_ = 0;
    containsCapitals_ = false;

    LOG_CONSTRUCTION;

    POST(! set());
}

SysPathName::SysPathName(const char* path)

    : pImpl_(new SysPathNameImpl())
{
    CB_SYS_PATHNAME_DEPIMPL;

    LOG_CONSTRUCTION;

    pathname_ = path;
    set_ = true;
    fullPathnameSet_ = false;
    componentsSet_ = false;
    rootId_ = 0;
    containsCapitals_ = checkForCapitals(std::string(path));

    createComponents();

    POST(set());
}

SysPathName::SysPathName(const std::string& path)
    : pImpl_(new SysPathNameImpl())
{
    CB_SYS_PATHNAME_DEPIMPL;

    LOG_CONSTRUCTION;

    pathname_ = path;
    set_ = true;
    fullPathnameSet_ = false;
    componentsSet_ = false;
    rootId_ = 0;
    containsCapitals_ = checkForCapitals(path);

    createComponents();

    POST(set());
}

SysPathName::SysPathName(const SysPathName& path)

    : pImpl_(new SysPathNameImpl(*path.pImpl_))
{
    LOG_CONSTRUCTION;

    POST(*this == path);
}

extern bool traceStack;

SysPathName::~SysPathName()
{
    delete pImpl_;

    LOG_DESTRUCTION;
}

void SysPathName::createFromComponents(const Components& newComponents)
{
    CB_SYS_PATHNAME_DEPIMPL;

    //  Set up the component list for this, making sure that any
    //  directories followed by '..' are cancelled correctly.

    components_.erase(components_.begin(), components_.end());
    components_.reserve(newComponents.size());

    for (Components::const_iterator i = newComponents.begin(); i != newComponents.end(); ++i)
    {
        bool cancelPrevious = false;

        if ((*i) == ".." && ! components_.empty())
        {
            //  If the preceeding component was . or .. don't cancel it.
            if (components_.back() != ".." && components_.back() != ".")
                cancelPrevious = true;
        }

        if (cancelPrevious)
            components_.pop_back();
        else
            components_.push_back(*i);
    }

    createPathnameFromComponents();

    POST(set());
}

void SysPathName::createPathnameFromComponents()
{
    CB_SYS_PATHNAME_DEPIMPL;

    pathname_ = "";

    for (Components::const_iterator i = components_.begin(); i != components_.end(); ++i)
    {
        pathname_ += (*i);

        Components::const_iterator j = i;
        ++j;

        if (j != components_.end())
            pathname_ += separator();
    }

    set_ = true;
    fullPathnameSet_ = false;

    POST(set());
}

const std::string& SysPathName::pathname() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    const std::string* pResult;

    if (internalRootDirectorySet() && isRelative())
    {
        if (! fullPathnameSet_ || rootId_ != currentRootId())
        {
            SysPathName temp(internalRootDirectory());
            temp.combine(*this);

            SysPathName* nonConstThis = _CONST_CAST(SysPathName*, this);

            CB_PEER_PTR_DEPIMPL(nonConstThis, fullPathname_) = temp.pathname();
            CB_PEER_PTR_DEPIMPL(nonConstThis, fullPathnameSet_) = true;
            CB_PEER_PTR_DEPIMPL(nonConstThis, rootId_) = currentRootId();
        }

        pResult = &fullPathname_;
    }
    else
        pResult = &pathname_;

    return *pResult;
}

const char* SysPathName::c_str() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    return pathname().c_str();
}

bool SysPathName::exists() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    bool result = existsAsDirectory() || existsAsFile();

    POST(iff(result, existsAsDirectory() || existsAsFile()));

    return result;
}

bool SysPathName::existsAsDirectory() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(*this);

    bool result = false;
    unsigned attr;

    struct stat info;
    if (stat(pathname().c_str(), &info) != 0)
    {
    }
    else if (info.st_mode & S_IFDIR)
    {
        result = true;
    }

    return result;
}

bool SysPathName::existsAsFile() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(*this);
    PRE_INFO(pathname().c_str());

    std::ifstream f(pathname().c_str());
    return f.good();
}

bool SysPathName::existsAsFile(const std::string& path)
{
    std::ifstream f(path);
    return f.good();
}

bool SysPathName::checkForCapitals(const std::string& path) const
{
    if (path.length() <= 0)
    {
        return false;
    }

    // start from back
    for (auto c = path.cend(); c > path.cbegin(); --c)
    {
        const unsigned char curChar = static_cast<unsigned char>(*c);
        if (std::isupper(curChar) != 0)
        {
            return true;
        }
    }

    return false;
}

bool SysPathName::containsCapitals() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    return containsCapitals_;
}

bool SysPathName::insensitiveExistsAsFile() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    if (! containsCapitals_)
    {
        return existsAsFile();
    }

    std::string path = std::string(pathname());
    std::transform(path.begin(), path.end(), path.begin(), [](unsigned char c) { return std::tolower(c); });

    std::ifstream f(path.c_str());
    return f.good();
}

bool SysPathName::isAbsolute() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(*this);

    bool result = false;

    if (pathname_.length() >= 1 && pathname_[0] == '/')
        result = true;

    if (pathname_.length() >= 2 && pathname_[1] == ':')
        result = true;

    return result;
}

bool SysPathName::isRelative() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(*this);

    return ! isAbsolute();
}

void SysPathName::combine(const SysPathName& nextPath)
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    if (nextPath.isAbsolute())
        *this = nextPath;
    else
    {

        char ch = pathname_[pathname_.length() - 1];

        if (ch == '\\' || ch == '/')
            pathname_ += CB_PEER_REF_DEPIMPL(nextPath, pathname_);
        else
            pathname_ += separator() + CB_PEER_REF_DEPIMPL(nextPath, pathname_);
    }

    fullPathnameSet_ = false;
    componentsSet_ = false;
}

const SysPathName::Components& SysPathName::components() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    if (! componentsSet_)
        createComponents();

    return components_;
}

void SysPathName::createComponents() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    SysPathName* nonConstThis = _CONST_CAST(SysPathName*, this);

    CB_PEER_PTR_DEPIMPL(nonConstThis, components_)
        .erase(
            CB_PEER_PTR_DEPIMPL(nonConstThis, components_).begin(),
            CB_PEER_PTR_DEPIMPL(nonConstThis, components_).end());

    //  This code should be improved when we get a complete string class

    const char* separators = "\\/";
    size_t index = 0;
    size_t lastIndex = 0;

    //  Use a local vector to store the indices of the separators. This is so we can
    //  reserve exactly the correct size for the components_ vector.
    ctl_vector<size_t> indices;
    indices.reserve(64);

    //  skip over the possible '\\' at the start of an absolute
    //  networked pathname
    if (isAbsolute())
        index += 2;

    for (; index < pathname_.length(); ++index)
    {
        if (strchr(separators, pathname_[index]) != nullptr)
        {
            indices.push_back(index);
            lastIndex = index + 1;

            //  Make sure that the pathname uses the standard separator everywhere

            pathname_[index] = separator()[0];
        }
    }

    if (lastIndex != index)
        indices.push_back(index);

    // Now push the actual strings into the components vector
    size_t size = indices.size();
    if (size != 0)
    {
        lastIndex = 0;
        CB_PEER_PTR_DEPIMPL(nonConstThis, components_).reserve(size);
        for (size_t i = 0; i != size; ++i)
        {
            index = indices[i];
            CB_PEER_PTR_DEPIMPL(nonConstThis, components_).push_back(pathname_.substr(lastIndex, index - lastIndex));
            lastIndex = index + 1;
        }
    }

    CB_PEER_PTR_DEPIMPL(nonConstThis, componentsSet_) = true;
}

//  static
std::string SysPathName::separator()
{
    static std::string separator_ = "/";

    return separator_;
}

//  static
char SysPathName::extensionCharacter()
{
    return '.';
}

bool SysPathName::hasExtension() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(*this);

    bool result = false;

    if (components().size() != 0)
    {
        if (strchr(components().back().c_str(), extensionCharacter()) != nullptr)
            result = true;
    }

    return result;
}

std::string SysPathName::extension() const
{
    PRE(set());

    PRE(hasExtension());

    const char* pExtension = strchr(components().back().c_str(), extensionCharacter());

    return std::string(pExtension + 1);
}

void SysPathName::extension(const std::string& newExtension)
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    if (hasExtension())
    {
        const char* pExtension = strchr(components().back().c_str(), extensionCharacter());

        if (newExtension == "")
        {
            components_.back() = components().back().substr(0, pExtension - components().back().c_str());
        }
        else
        {
            components_.back() = components().back().substr(0, pExtension - components().back().c_str())
                + extensionCharacter() + newExtension;
        }
    }
    else if (newExtension != "")
    {
        components_.back() = components().back() + extensionCharacter() + newExtension;
    }

    createPathnameFromComponents();

    fullPathnameSet_ = false;

    POST(implies(newExtension != "", hasExtension()));
}

std::string SysPathName::directory() const
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(set());

    PRE_INFO(pathname());
    PRE(exists());

    if (existsAsDirectory())
        return pathname();

    //  Make sure that the lazy evaluation is updated
    components();

    std::string result;
    bool finished = false;

    for (Components::const_iterator i = components_.begin(); ! finished; ++i)
    {
        Components::const_iterator j = i;
        ++j;

        if (j == components_.end())
            finished = true;

        if (! finished)
        {
            result += (*i);

            //  See if there is an entry following this

            Components::const_iterator k = j;
            ++k;

            if (k != components_.end())
                result += separator();
        }
    }

    return result;
}

const std::string& SysPathName::filename() const
{
    PRE(set());

    PRE_INFO(*this);

    PRE(existsAsFile());
    ALWAYS_ASSERT(existsAsFile(), ("File not found: " + pathname()).c_str());

    return components().back();
}

SysPathName& SysPathName::operator=(const SysPathName& rhs)
{
    if (this != &rhs)
    {
        SysPathNameImpl* pNewImpl = new SysPathNameImpl(*rhs.pImpl_);
        delete pImpl_;
        pImpl_ = pNewImpl;
    }

    POST(*this == rhs);
    return *this;
}

SysPathName& SysPathName::operator=(const std::string& rhs)
{
    CB_SYS_PATHNAME_DEPIMPL;

    set_ = true;
    pathname_ = rhs;
    createComponents();
    rootId_ = 0;
    fullPathnameSet_ = false;
    componentsSet_ = false;

    POST(set());
    return *this;
}

SysPathName& SysPathName::operator=(const char* rhs)
{
    CB_SYS_PATHNAME_DEPIMPL;

    set_ = true;
    pathname_ = rhs;
    createComponents();
    rootId_ = 0;
    fullPathnameSet_ = false;
    componentsSet_ = false;

    POST(set());

    return *this;
}

std::ostream& operator<<(std::ostream& o, const SysPathName& p)
{
    o << p.pathname();

    return o;
}

bool operator==(const SysPathName& a, const SysPathName& b)
{
    //  Since DOS pathnames are case insensitive do a case insensitive compare.

    return strcasecmp(a.pathname().c_str(), b.pathname().c_str()) == 0;
}

bool operator<(const SysPathName& a, const SysPathName& b)
{
    //  Since DOS pathnames are case insensitive do a case insensitive compare.

    return strcasecmp(a.pathname().c_str(), b.pathname().c_str()) < 0;
}

// static
void SysPathName::rootDirectory(const SysPathName& directory)
{
    internalRootDirectory() = directory.pathname();
    ++currentRootId();

    if (directory.pathname().length() > 0)
        internalRootDirectorySet() = true;
    else
        internalRootDirectorySet() = false;
}

//  Set the root directory from the given environment variable
// static
void SysPathName::rootEnvironmentVariable(const std::string& environmentVariable)
{
    char* value = getenv(environmentVariable.c_str());

    if (value)
    {
        internalRootDirectory() = value;
        ++currentRootId();
        internalRootDirectorySet() = true;
    }
    else
        internalRootDirectorySet() = false;
}

// static
SysPathName SysPathName::rootDirectory()
{
    return internalRootDirectory();
}

// static
std::string& SysPathName::internalRootDirectory()
{
    static std::string rootDirectory_;

    return rootDirectory_;
}

// static
bool& SysPathName::internalRootDirectorySet()
{
    static bool internalRootDirectorySet_ = false;

    return internalRootDirectorySet_;
}

bool SysPathName::set() const
{
    CB_DEPIMPL(bool, set_);

    return set_;
}

// static
size_t& SysPathName::currentRootId()
{
    static size_t internalId_ = 10;

    return internalId_;
}

static const char SET = 0;
static const char NOT_SET = 1;

void perWrite(PerOstream& ostr, const SysPathName& name)
{
    if (name.set())
    {
        PER_WRITE_RAW_OBJECT(ostr, SET);
        ostr << name.pathname();
    }
    else
        PER_WRITE_RAW_OBJECT(ostr, NOT_SET);
}

void perRead(PerIstream& istr, SysPathName& name)
{
    char set;
    PER_READ_RAW_OBJECT(istr, set);

    if (set == SET)
    {
        istr >> CB_PEER_REF_DEPIMPL(name, pathname_);
        CB_PEER_REF_DEPIMPL(name, set_) = true;

        //  This is just to make sure that all of the internal stuff
        //  gets properly set for this pathname.

        std::string n1 = name.pathname();
        name = n1;
    }
    else
        CB_PEER_REF_DEPIMPL(name, set_) = false;
}

bool SysPathName::hasPrefix(const SysPathName& prefix) const
{
    const Components& prefixComponents = prefix.components();
    const Components& thisComponents = components();

    bool result = false;

    if (thisComponents.size() >= prefixComponents.size()
        && equal(prefixComponents.begin(), prefixComponents.end(), thisComponents.begin()))
    {
        result = true;
    }

    return result;
}

void SysPathName::removePrefix(const SysPathName& prefix)
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(hasPrefix(prefix));

    Components newComponents(components().begin() + prefix.components().size(), components().end());

    createFromComponents(newComponents);
}

void SysPathName::pop_back()
{
    CB_SYS_PATHNAME_DEPIMPL;

    PRE(components().size() > 0);

    Components comp = components();

    comp.pop_back();

    createFromComponents(comp);
}

EXISTS(SysPathName);
