#ifndef PATCHMAP_H
#define PATCHMAP_H

#include "Arduino.h"
#include "ZoomMsg.h"

#define ZOOM_EFF_ON_BIT 0

#define ZOOM_PATCH_OFFSET_EFF_ON_1 6
#define ZOOM_PATCH_OFFSET_EFF_ON_2 26
#define ZOOM_PATCH_OFFSET_EFF_ON_3 47
#define ZOOM_PATCH_OFFSET_EFF_ON_4 67
#define ZOOM_PATCH_OFFSET_EFF_ON_5 88
#define ZOOM_PATCH_OFFSET_EFF_ON_6 108

#define ZOOM_PATCH_OFFSET_FOCUS_BIT_0 130
#define ZOOM_PATCH_OFFSET_FOCUS_BIT_1 125
#define ZOOM_PATCH_OFFSET_FOCUS_BIT_2 129

#define ZOOM_PATCH_INDEX_FOCUS_BIT_0 0
#define ZOOM_PATCH_INDEX_FOCUS_BIT_1 3
#define ZOOM_PATCH_INDEX_FOCUS_BIT_2 6

#define TBL_FOCUS_1 3
#define TBL_FOCUS_2 1
#define TBL_FOCUS_3 6
#define TBL_FOCUS_4 2
#define TBL_FOCUS_5 4
#define TBL_FOCUS_6 0

const byte FocusTable[ZOOM_EFF_NO] = {TBL_FOCUS_1, TBL_FOCUS_2, TBL_FOCUS_3,
                                      TBL_FOCUS_4, TBL_FOCUS_5, TBL_FOCUS_6};

const byte PatchFxOffsets[ZOOM_EFF_NO] = {ZOOM_PATCH_OFFSET_EFF_ON_1,
                                         ZOOM_PATCH_OFFSET_EFF_ON_2,
                                         ZOOM_PATCH_OFFSET_EFF_ON_3,
                                         ZOOM_PATCH_OFFSET_EFF_ON_4,
                                         ZOOM_PATCH_OFFSET_EFF_ON_5,
                                         ZOOM_PATCH_OFFSET_EFF_ON_6};

                                             
const PROGMEM byte _EmptyPatch[ZOOM_PATCH_LENGTH] =
 { 0xF0, 0x52, 0x00, 0x58, 0x28,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F, 0x45, 0x00, 0x6D, 0x70, 0x74,
   0x79, 0x20, 0x20, 0x20, 0x00, 0x20, 0x20, 0x00, 0xF7 };

#endif
