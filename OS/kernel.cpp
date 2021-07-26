#include "KernelCall.h"
#include "Types.h"
#include "Console.h"

extern "C" int ENTRY(); // extern so the linked assembly can call
extern "C" int BootDrive;

class Kernel {
public: 
    Kernel() {Setup();}
    void Setup() {
        // initialize the console
        Console::Initialize();
        Console::ResetCol();

        // initialize the KernelCall API
        KernelCore::Initialize();
        Console::SuccessMsg("Boot success!");
    }
};
// the entry point of the operating system, called on boot
int ENTRY() {
    Kernel maink = Kernel();
}