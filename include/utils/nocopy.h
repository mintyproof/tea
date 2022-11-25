#ifndef TEA_UTILS_NOCOPY_H
#define TEA_UTILS_NOCOPY_H

namespace tea {

// a utility class that, when inherited, makes the child class unable to be copied.
// this is accomplished by simply deleting the copy constructor and copy assignment operator.
class NoCopy {
public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    NoCopy& operator= (const NoCopy&) = delete;
};

}

#endif // TEA_UTILS_NOCOPY_H