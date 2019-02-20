#ifndef TEA_ASSETS_H
#define TEA_ASSETS_H

#include <optional>
#include <string>
#include <vector>

namespace Tea {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        bool load_asset(std::string path, std::vector<uint8_t>& out);
        bool load_asset(std::string path, std::string& out);
    };
}

#endif