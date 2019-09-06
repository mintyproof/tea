#ifndef TEA_ASSETS_H
#define TEA_ASSETS_H

#include <memory>
#include <string>
#include <vector>

namespace Tea {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        bool load_raw(const std::string& path, std::vector<uint8_t>& out);
        bool load_string(const std::string& path, std::string& out);

        template <class T> std::unique_ptr<T> load(const std::string& path) {
            std::vector<uint8_t> data;
            if (!this->load_raw(path, data)) return std::unique_ptr<T>(nullptr);
            return T::load(path, std::move(data));
        }
    };
}

#endif