#include "Builder.h"
#include "AstroidController.h"
#include "Dialog.h"

#include "memory"
#include <iostream>


int main() {
    Builder builder;
    auto mc = std::make_unique<Controllers::AstroidController>(Controllers::AstroidController());
    builder.addController(std::move(mc));

//    builder.useSessionLogging(std::ofstream("../../log.txt"));

    builder.build();

    Dialog dialog = Dialog(std::cin, std::cout);
    dialog.connectToApi(&builder);

    return dialog.run();
}