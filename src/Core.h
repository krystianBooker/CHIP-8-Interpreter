#ifndef CHIP8_INTERPRETER_CORE_H
#define CHIP8_INTERPRETER_CORE_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <array>

#define WIDTH 64
#define HEIGHT 32

class Core {
public:
    //2048 pixels (64 x 32) State of either 1 or 0
    unsigned char Graphics[WIDTH * HEIGHT] = {0};

    //Chip 8 has a HEX based keypad 0x0-0xF
    unsigned char Key[16]{0};

    // 0x00E0 - Clears the screen
    // 0xDXYN - Draws a sprite on the screen
    bool DrawFlag{false};
    bool BeepFlag{false};

    void Initialize();

    void LoadGame(const char *romName);

    void EmulateCycle();

    static int GetWidth();

    static int GetHeight();

private:
    unsigned char chip8_fontset[80] =
            {
                    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                    0x20, 0x60, 0x20, 0x20, 0x70, // 1
                    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
            };

    //Chip 8s opcodes are all two bytes long.
    //unsigned short has the length of two bytes.
    unsigned short opcode{0};

    /*
     * Chip 8 has 4K of memory
     * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
     * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
     * 0x200-0xFFF - Program ROM and work RAM
    */
    unsigned char memory[4096] = {0};

    //Chip 8 has 15 8-bit general purpose registers
    //Name from V0-VE. The 16th register is the 'carry flag'
    unsigned char V[16] = {0};

    //The index register (I) and program count (pc) can
    //have a value from 0x000 to 0xFFF
    unsigned short I{0};
    unsigned short pc{0};

    //60 Hz
    unsigned char delayTimer{0};
    unsigned char soundTimer{0};

    //Anytime you perform a jump or call a subroutine,
    //store the program counter in the stack before proceeding
    unsigned short stack[16] = {0};
    unsigned short sp = {0};

    bool debug = {false};

    unsigned short getX() const;

    unsigned short getY() const;

    unsigned short getNN() const;

    unsigned short getNNN() const;

    void clearDisplay();

    void unknownOpcode() const;
};

#endif //CHIP8_INTERPRETER_CORE_H
