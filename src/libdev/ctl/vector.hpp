/*
 * V E C T O R . H P P
 * (c) Charybdis Limited, 1996. All Rights Reserved.
 */

/*
    ctl_vector

    This is a version of the STL vector class that can be derived from (it
    has a virtual destructor). It also performs error checking on the
    debug version.
*/

#ifndef _CTL_VECTOR_HPP
#define _CTL_VECTOR_HPP

//////////////////////////////////////////////////////////////////////

#include "base/persist.hpp"
#include <vector>

//////////////////////////////////////////////////////////////////////

template <class T> class ctl_vector : public std::vector<T>
{
public:
    using std::vector<T>::vector;
    // ctl_vector( size_type n );
    virtual ~ctl_vector() {};

private:
    PER_MEMBER_PERSISTENT_DEFAULT_VIRTUAL(ctl_vector)
};

PER_DEFINE_PERSISTENT_INLINE_T1(ctl_vector);

//////////////////////////////////////////////////////////////////////

template <class T> bool operator==(const ctl_vector<T>&, const ctl_vector<T>&);

template <class T> bool operator<(const ctl_vector<T>&, const ctl_vector<T>&);

template <class T> std::ostream& operator<<(std::ostream&, const ctl_vector<T>&);

//////////////////////////////////////////////////////////////////////

template <> class ctl_vector<bool> : public std::vector<int>
{
}; // Changed specialization for STL bool vector

#ifdef _INLINE
#include "ctl/vector.itp"
#ifndef NDEBUG
#include "ctl/private/vecbit.itp"
#include "ctl/private/vecit.itp"
#include "ctl/private/veccit.itp"
#endif
#endif

// #ifdef _INSTANTIATE_TEMPLATE_CLASSES
//     #include "ctl/vector.ctp"
// #endif

// #ifdef _INSTANTIATE_TEMPLATE_FUNCTIONS
#include "ctl/vector.ctf"
// #endif

//////////////////////////////////////////////////////////////////////

enum class VectorFlavour
{
    CTL,
    CTL_P,

    CTL_NB,
    // A non-bloated ctl_vector. This achieves the lack of bloat by defining an
    // underlying rep_type which is simply a vector of raw memory storage, each
    // element of which is the same size as the data type we actually want to
    // store. Vectors of various different base sizes are pre instantiated in
    // the ctl library so that it should not be necessary to instantiate this
    // vector at all.
};

const char* getVectorClassName(VectorFlavour flavour);

inline const char* getVectorClassName(VectorFlavour flavour)
{
    switch (flavour)
    {
        case VectorFlavour::CTL:
            return "ctl_vector";
        case VectorFlavour::CTL_P:
            return "ctl_pvector";
        case VectorFlavour::CTL_NB:
            return "ctl_nb_vector";
    }

    return nullptr;
}

template <typename T> void perWrite(PerOstream& ostr, const std::vector<T>& ob, VectorFlavour flavour)
{
    PER_WRITE_RAW_OBJECT(ostr, ob.size());

    if (flavour == VectorFlavour::CTL)
    {
        // Reserved
        PER_WRITE_RAW_OBJECT(ostr, ob.size());

        // Capacity
        PER_WRITE_RAW_OBJECT(ostr, ob.size());
    }

    for (const T& value : ob)
    {
        ostr << value;
    }
}

template <typename T> void perRead(PerIstream& istr, std::vector<T>& ob, VectorFlavour flavour)
{
    ob.clear();

    std::size_t size;
    PER_READ_RAW_OBJECT(istr, size);

    if (flavour == VectorFlavour::CTL)
    {
        std::size_t reserved;
        PER_READ_RAW_OBJECT(istr, reserved);
        std::size_t capacity;
        PER_READ_RAW_OBJECT(istr, capacity);

        ob.reserve(size == 0 ? reserved : capacity);
    }
    else
    {
        ob.reserve(size);
    }

    for (std::size_t i = 0; i < size; ++i)
    {
        T t {};
        istr >> t;
        ob.push_back(t);
    }
}

template <typename T> void perWriteAsVectorImpl(PerOstream& ostr, const std::vector<T>& ob, VectorFlavour flavour)
{
    const char* pClassName = getVectorClassName(flavour);
    Persistence ::instance().writeObjectPre(ostr, (static_cast<const void*>(&ob)), pClassName);
    perWrite(ostr, ob, flavour);
    Persistence ::instance().writeObjectPost((static_cast<const void*>(&ob)), pClassName);
}

template <typename T> void perReadAsVectorImpl(PerIstream& istr, std::vector<T>& ob, VectorFlavour flavour)
{
    const char* pClassName = getVectorClassName(flavour);
    Persistence ::instance().readObjectPre(istr, (static_cast<const void*>(&ob)), pClassName);
    perRead(istr, ob, flavour);
    Persistence ::instance().readObjectPost((static_cast<const void*>(&ob)), pClassName);
}

template <typename T> void perWriteAsVector(PerOstream& ostr, const std::vector<T>& ob)
{
    perWriteAsVectorImpl(ostr, ob, VectorFlavour::CTL);
}

template <typename T> void perWriteAsPVector(PerOstream& ostr, const std::vector<T>& ob)
{
    perWriteAsVectorImpl(ostr, ob, VectorFlavour::CTL_P);
}

template <typename T> void perWriteAsNBVector(PerOstream& ostr, const std::vector<T>& ob)
{
    perWriteAsVectorImpl(ostr, ob, VectorFlavour::CTL_NB);
}

template <typename T> void perReadAsVector(PerIstream& istr, std::vector<T>& ob)
{
    perReadAsVectorImpl(istr, ob, VectorFlavour::CTL);
}

template <typename T> void perReadAsPVector(PerIstream& istr, std::vector<T>& ob)
{
    perReadAsVectorImpl(istr, ob, VectorFlavour::CTL_P);
}

template <typename T> void perWrite(PerOstream& ostr, const std::vector<T>& ob)
{
    static_assert(!std::is_pointer_v<T>);
    perWrite(ostr, ob, VectorFlavour::CTL);
}

template <typename T> void perRead(PerIstream& istr, std::vector<T>& ob)
{
    static_assert(!std::is_pointer_v<T>);
    perRead(istr, ob, VectorFlavour::CTL);
}

template <typename T> PerOstream& operator<<(PerOstream& ostr, const std::vector<T>& ob)
{
    static_assert(!std::is_pointer_v<T>);
    perWriteAsVector(ostr, ob);
    return ostr;
}

template <typename T> PerIstream& operator>>(PerIstream& istr, std::vector<T>& ob)
{
    static_assert(!std::is_pointer_v<T>);
    perReadAsVector(istr, ob);
    return istr;
}

#endif /* #ifndef _CTL_VECTOR_HPP  */
