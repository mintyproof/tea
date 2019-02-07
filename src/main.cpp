#include "engine.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string main_module = "main";
    std::string main_class = "Main";
    if (argc >= 2) {
        std::string main_path = argv[1];
        if (main_path.find("::") == std::string::npos) {
            std::cerr << "Argument must be of format module::Class" << std::endl;
            return 1;
        }
        main_module = main_path.substr(0, main_path.find("::"));
        main_class = main_path.substr(main_path.find("::") + 2);
    }

    Tea::Engine().run(main_module, main_class);
}