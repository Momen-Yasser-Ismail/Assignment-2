#include "../Headers/Machine.h"
#include "../Headers/ConsoleUI.h"

int main() {
    Machine machine;
    ConsoleUI ui(machine);
    ui.start();
    return 0;
}