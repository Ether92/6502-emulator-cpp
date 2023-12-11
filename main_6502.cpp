#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialize() {
        for(u32 i = 0; i < MAX_MEM; i++) {
            Data[i] = 0;
        }
    }

    // read 1 byte
    Byte operator[](u32 Address) const {
        // assert here address is < MAX_MEM
        return Data[Address];
    }
};


struct CPU {
    

    Word PC; //Program Counter
    Word SP; //Stack Pointer

    Byte A, X, Y; //Registers

    Byte C : 1; //status flags: Carry Flag
    Byte Z : 1; //status flags: Zero
    Byte I : 1; //status flags: Interrupt Disable Flag
    Byte D : 1; //status flags: Decimal Mode Flag
    Byte B : 1; //status flags: Break Command Flag
    Byte V : 1; //status flags: Overflow Flag
    Byte N : 1; //status flags: Negative Flag

    void Reset( Mem& memory) {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialize();
    }

    Byte FetchByte(u32& Cycles, Mem& memory) {
        Byte data = memory[PC];
        PC++;
        Cycles--;
    }

    void Execute(u32 Cycles, Mem& memory) {
        while (Cycles > 0) {
            Byte Ins = FetchByte(Cycles, memory);
            (void) Ins;
        }
    }
}

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset(mem);
    cpu.Execute(2, mem);
    return 0;
}