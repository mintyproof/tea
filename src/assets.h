#ifndef TEA_ASSETS_H
#define TEA_ASSETS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace Tea {
    class Asset {
    public:
        Asset(std::string name, std::vector<uint8_t> data);
        std::string&          get_name();
        std::vector<uint8_t>& get_data();

    private:
        std::string          name;
        std::vector<uint8_t> data;
    };

    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        Asset* find_asset(std::string name);

    private:
        std::unordered_map<std::string, Asset> loaded_assets;
    };
}

#endif