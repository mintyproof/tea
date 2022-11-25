#ifndef TEA_CORE_ENGINE_H
#define TEA_CORE_ENGINE_H

#include <string>
#include <vector>

#include "scripting/scripting.h"
#include "utils/nocopy.h"
#include "core/platform.h"

namespace tea {

class Engine : public NoCopy {
public:
    explicit Engine(std::vector<std::string> args);

    int run();
private:
    std::vector<std::string> args;
    std::unique_ptr<Scripting> scripting;
};

}

#endif  // TEA_CORE_ENGINE_H
