#ifndef TEA_ASSET_H
#define TEA_ASSET_H

#include <string>

namespace Tea {
    class Asset {
    public:
        explicit Asset() {}
        Asset(const Asset&) = delete;
        Asset& operator=(const Asset&) = delete;
    };
}

#endif
