#ifndef ZOOMIF_H
#define ZOOMIF_H

#include "Arduino.h"
#include "Array.h"
#include "MultistompController.h"
#include "ZoomMsg.h"


// Controller struct
class ZoomIf {
  public:
    static Stream *Com;
    static byte Channel;
    
    #if ZOOM_SRAM_MEM
      static byte PatchMem[ZOOM_SRAM_PATCHES][ZOOM_PATCH_LENGTH];
    #endif
    
    static void Init(Stream *Com, byte Channel);
    static bool IdentityRequest();
    
    static void ParamEnable();
    static void ParamDisable();
    static void ParamEdit(byte Slot, byte Param, int Value);
        
    static void SwitchOn(byte PN, byte Slot);
    static void SwitchOff(byte PN, byte Slot);
    
    static void SetEffects(byte PN, bool *StateVector);
    static Array<byte, ZOOM_PATCH_LENGTH> RequestPatch(byte PN);
    
    static void Tuner(bool State);
    static void Patch(byte PN);
    
  private:
    ZoomIf();
};

#endif
