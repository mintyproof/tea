#include <string>
#include <unordered_map>
#include <vector>

namespace Tea {
    class Asset {
    public:
        Asset(std::vector<uint8_t> data);
        std::vector<uint8_t>& get_data();

    private:
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