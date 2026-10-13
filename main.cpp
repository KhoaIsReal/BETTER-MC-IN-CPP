#include "window.h"

int main() {
    Window window(800, 600, "Better Minecraft in C++");

    window.run(nullptr);

    return 0;
}