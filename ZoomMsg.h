#ifndef ZOOM_MSG_H
#define ZOOM_MSG_H

#include "MultistompController.h"

#define ZOOM_DEVICE_MS50G   0x58
#define ZOOM_DEVICE_MS60B   0x5F
#define ZOOM_DEVICE_MS70CDR 0x61

#define ZOOM_MSG_BEGIN      {0xF0, 0x52, 0x00, Z_ID}
#define ZOOM_MSG_END        {0xF7}
#define ZOOM_MSG_PC         {0xC0, 0x00}
#define ZOOM_MSG_TUNER_ON   {0xB0, 0x4A, 0x7F}
#define ZOOM_MSG_TUNER_OFF  {0xB0, 0x4A, 0x00}
#define ZOOM_MSG_PRM_ENA    {0xF0, 0x52, 0x00, Z_ID, 0x50, 0xF7}
#define ZOOM_MSG_PRM_DEA    {0xF0, 0x52, 0x00, Z_ID, 0x51, 0xF7}
#define ZOOM_MSG_EFF_ON     {0xF0, 0x52, 0x00, Z_ID, 0x31, 0x00, 0x00, 0x01, 0x00, 0xF7}
#define ZOOM_MSG_EFF_OFF    {0xF0, 0x52, 0x00, Z_ID, 0x31, 0x00, 0x00, 0x00, 0x00, 0xF7}
#define ZOOM_MSG_PRM_EDIT   {0xF0, 0x52, 0x00, Z_ID, 0x31, 0x00, 0x00, 0x00, 0x00, 0xF7}

#define ZOOM_MSG_UNKNOWN    {0xF0, 0x52, 0x00, Z_ID, 0x60, 0xF7}

#define ZOOM_MSG_IDENTITY_REQUEST   {0xF0, 0x7E, 0x00, 0x06, 0x01, 0xF7}
#define ZOOM_MSG_PATCH_REQUEST      {0xF0, 0x52, 0x00, Z_ID, 0x29, 0xF7}
#define ZOOM_MSG_IDENTITY_RETURN    {0xF0, 0x7E, 0x00, 0x06, 0x02, 0x52, Z_ID, 0x00, 0x00, 0x00, 0x33, 0x2E, 0x30, 0x30, 0xF7}

#define ZOOM_MSG_OFFSET_EFF_ON_1 6
#define ZOOM_MSG_OFFSET_EFF_ON_2 26
#define ZOOM_MSG_OFFSET_EFF_ON_3 47
#define ZOOM_MSG_OFFSET_EFF_ON_4 67
#define ZOOM_MSG_OFFSET_EFF_ON_5 88
#define ZOOM_MSG_OFFSET_EFF_ON_6 108

#define ZOOM_INI_DELAY 0
#define ZOOM_INI_WAIT 1000
#define ZOOM_MSG_RX_TIMEOUT 2000

#define ZOOM_PATCH_NO 50
#define ZOOM_PATCH_LENGTH 146
#define ZOOM_IDENTITY_LENGTH 15
#define ZOOM_PARAM_LENGTH 10

#define ZOOM_EFF_NO 6
#define ZOOM_EFF_ON_BIT 0

#define ZOOM_EFF_FOCUS_BIT_0_OFFSET 130
#define ZOOM_EFF_FOCUS_BIT_1_OFFSET 125
#define ZOOM_EFF_FOCUS_BIT_2_OFFSET 129

#define ZOOM_EFF_FOCUS_BIT_0_INDEX 0
#define ZOOM_EFF_FOCUS_BIT_1_INDEX 3
#define ZOOM_EFF_FOCUS_BIT_2_INDEX 6

#define TBL_FOCUS_1 3
#define TBL_FOCUS_2 1
#define TBL_FOCUS_3 6
#define TBL_FOCUS_4 2
#define TBL_FOCUS_5 4
#define TBL_FOCUS_6 0


#endif