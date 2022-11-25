#include "core/engine.h"

/*
#include <iostream>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(tea);

void res_fs_iterate(cmrc::embedded_filesystem res_fs, int depth, const std::string& path) { // NOLINT(misc-no-recursion)
    for (auto content : res_fs.iterate_directory(path)) {
        std::cout << std::string(depth * 2, ' ');
        if (content.is_directory()) {
            std::cout << content.filename() << "/" << std::endl;
            res_fs_iterate(res_fs, depth + 1, path + "/" + content.filename());
        } else {
            std::cout << content.filename() << std::endl;
        }
    }
}

void res_test() {
    auto res_fs = cmrc::tea::get_filesystem();
    res_fs_iterate(res_fs, 0, "");
}
*/

int main(int argc, char* argv[]) {
    // collate program arguments into a vector of strings, excluding the first argument
    // (since the first argument is the launch path, which we don't want to expose to projects)
    std::vector<std::string> args(argv + 1, argv + argc);

    tea::Engine engine_instance = tea::Engine(args);
    int run_result = engine_instance.run();

    return run_result;
}