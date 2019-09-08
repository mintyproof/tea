#include "assets.h"
#include "sound/sound_loader.h"
#include "image/image_loader.h"

#include <fstream>
#include <iostream>
#include <utility>

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(tea);

namespace Tea {
    AssetManager::AssetManager() = default;
    AssetManager::~AssetManager() = default;

    bool AssetManager::load_raw(const std::string &name, std::vector<uint8_t>& out) {
        // Check embedded resources
        auto fs = cmrc::tea::get_filesystem();
        if (fs.exists(name)) {
            auto file = fs.open(name);

            out.insert(out.begin(), file.begin(), file.end());
            return true;
        }

        // Then read file
        std::ifstream stream;
        stream.open(name, std::ifstream::in | std::ifstream::binary);

        // Check if file exists
        if (!stream.is_open()) return false;

        out.insert(out.begin(), (std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        return true;
    }

    bool AssetManager::load_string(const std::string &name, std::string& out) {
        // TODO: don't copy again here
        std::vector<uint8_t> data;
        if (!this->load_raw(name, data)) return false;
        out.insert(out.begin(), data.begin(), data.end());
        return true;
    }

    std::unique_ptr<Image> AssetManager::load_image(const std::string &path) {
        std::vector<uint8_t> data;
        if (!load_raw(path, data)) return std::unique_ptr<Image>(nullptr);
        return ImageLoader::load(std::move(data));
    }

    std::unique_ptr<Sound> AssetManager::load_sound(const std::string &path) {
        std::vector<uint8_t> data;
        if (!load_raw(path, data)) return std::unique_ptr<Sound>(nullptr);
        return SoundLoader::load_ogg(std::move(data));
    }
}