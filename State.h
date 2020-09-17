#ifndef STATE_H
#define STATE_H

#define BIT(bit) (1 << bit)

#define BIT_SET(arg, bit) arg |= (1 << bit)
#define BIT_CLR(arg, bit) arg &= ~(1 << bit)
#define BIT_FLIP(arg, bit) arg ^= (1 << bit)
#define BIT_CHECK(arg, bit) ((!!((arg) & (1 << (bit)))) == 1)

#define BITMASK_SET(arg, mask) arg |= mask
#define BITMASK_CLEAR(arg, mask) arg &= (~mask)
#define BITMASK_FLIP(arg, mask) arg ^= mask
#define BITMASK_CHECK_ALL(arg, mask) !~((~(mask)) | (arg))
#define BITMASK_CHECK_ANY(arg, mask) ((arg) & (mask))

#define ADD_STATE(state, s) state |= s
#define RST_STATE(state) state = 0

enum MemMode {
    SRAM = 0,
    EEPROM = BIT(0)
};

#endif