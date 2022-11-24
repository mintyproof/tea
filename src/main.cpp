#include <vector>
#include "engine.h"

int main(int argc, char* argv[]) {
    // collate program arguments into a vector of strings, excluding the first argument
    // (since the first argument is the launch path, which we don't want to expose to projects)
    std::vector<std::string> args(argv + 1, argv + argc);

    tea::Engine engine_instance = tea::Engine(args);
    int run_result = engine_instance.run();

    return run_result;
}