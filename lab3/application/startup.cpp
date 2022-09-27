#include "Builder.h"
#include "TerminalController.h"
#include "Dialog.h"

#include "memory"
#include <iostream>
#include "uniquePtrAllocator.h"


int main() {
    Builder builder;
    auto mc = std::make_unique<Controllers::TerminalController>(Controllers::TerminalController());
    builder.addController(std::move(mc));

//    builder.useSessionLogging(std::ofstream("../../log.txt"));

    builder.build();

    Dialog dialog = Dialog(std::cin, std::cout);
    dialog.connectToApi(&builder);

    return dialog.run();
}