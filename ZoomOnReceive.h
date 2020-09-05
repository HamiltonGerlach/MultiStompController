#ifndef ZOOM_ONRECEIVE_H
#define ZOOM_ONRECEIVE_H

enum StateMode {
    None = 0,
    PatchChange = BIT(0),
    FocusChange = BIT(1),
    SetEffects  = BIT(2),
    SetParams   = BIT(3),
    CustomMsg   = BIT(4)
};

#define ADD_STATE(state, new) state |= new

#endif