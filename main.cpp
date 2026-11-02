#include "Machine.h"
#include "ConsoleUI.h" // (Or whatever your UI header is named)

int main() {
    Machine machine;
    ConsoleUI ui(machine);
    ui.start();
    return 0;
}