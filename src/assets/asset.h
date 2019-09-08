#ifndef TEA_ASSET_H
#define TEA_ASSET_H

#include <string>

namespace Tea {
    class Asset {
    public:
        const std::string &get_filename() const;

    private:
        std::string filename;
    };
}

#endif
