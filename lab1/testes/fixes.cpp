#include "../application/model/Astroid.h"
#include "math.h"
#include <iostream>

int main() {
    Models::Astroid astroid;
    astroid.getYfromX(astroid.getR()) == astroid.getR();
    astroid.getYfromX(-astroid.getR()) == astroid.getR();
    return 0;
}