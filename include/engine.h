#ifndef TEA_ENGINE_H
#define TEA_ENGINE_H

#include <string>
#include <vector>

#include "scripting/scripting.h"

namespace tea {

class Engine {
public:
    explicit Engine(std::vector<std::string> args);

    int run();
private:
    std::vector<std::string> args;
    std::unique_ptr<Scripting> scripting;
};

}

#endif  // TEA_ENGINE_H
