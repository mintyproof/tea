#ifndef TEA_ASSETS_H
#define TEA_ASSETS_H

#include <memory>
#include <string>
#include <vector>
#include "image/image.h"
#include "sound/sound.h"

namespace Tea {
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();

        bool load_raw(const std::string& path, std::vector<uint8_t>& out);
        bool load_string(const std::string& path, std::string& out);

        std::unique_ptr<Image> load_image(const std::string& path);
        std::unique_ptr<Sound> load_sound(const std::string& path);
    };
}

#endif