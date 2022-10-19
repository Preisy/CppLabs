#include "Builder.h"
#include "UsersController.h"
#include "MarksController.h"
#include "Dialog.h"

#include "memory"

// todo add 345432e asgfhgff

int main() {
    Builder builder;
    auto uc = std::make_unique<Controllers::UsersController>(
            Controllers::UsersController());
    builder.addController(std::move(uc));
    auto mc = std::make_unique<Controllers::MarksController>(
            Controllers::MarksController());
    builder.addController(std::move(mc));

//    builder.useSessionLogging(std::ofstream("../../log.txt"));

    builder.build();

    Dialog dialog = Dialog(std::cin, std::cout);
    dialog.connectToApi(&builder);

    return dialog.run();
}