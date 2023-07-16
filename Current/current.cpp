#include <iostream>
#include <string>

#include "current_compiler.hpp"
#include "CVM.hpp"

class Commands {

    public:
        std::string compile_current = "current";
        std::string interpret       = "cvm";
};





int main (int argc, char* argv[]) {
    Commands CMDs;

    if (argc <= 1) {
        std::cout << "Help:\ncurrent current [directory]\tcompiles a directory.\ncurrent cvm [directory]\t\truns compiled code." << std::endl;

    } else if (argv[1] == CMDs.compile_current) {
        std::cout << "current compiler" << std::endl;
        if (argc == 3) {
            current_bundle(argv[2], "curr", "crbc");
        } else {
            std::cout << "Missing argument: directory" << std::endl;
        }

    } else if (argv[1] == CMDs.interpret) {
        if (argc == 3) {
            bundle_CVM(argv[2], "crbc");
        } else {
            std::cout << "Missing argument: directory" << std::endl;
        }
    }
}