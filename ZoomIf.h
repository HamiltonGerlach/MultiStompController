#ifndef ZOOMIF_H
#define ZOOMIF_H

#include "Arduino.h"
#include "Array.h"
#include "MultistompController.h"
#include "ZoomMsg.h"

typedef Array<byte, ZOOM_PATCH_LENGTH> _zoomPatchType;
typedef Array<byte, ZOOM_IDENTITY_LENGTH> _zoomIdType;

// Zoom interface class
class ZoomIf {
  public:
    static Stream *Com;
    static byte Channel;
    static _zoomPatchType Buffer;
    
    #if ZOOM_SRAM_MEM
      static _zoomPatchType PatchMem[ZOOM_SRAM_PATCHES];
    #endif
    
    static void Init(Stream *Com, byte Channel);
    static bool IdentityRequest();
    
    static void ParamEnable();
    static void ParamDisable();
    static void ParamEdit(byte Slot, byte Param, int Value);
        
    static void SwitchOn(byte PN, byte Slot);
    static void SwitchOff(byte PN, byte Slot);
    static void SwitchEffects(byte PN, bool *StateVector);
    
    static _zoomPatchType RequestPatch(byte PN);
    static void MemStore(byte PN);
    static void CachePatches();
    static void SetPatchEffects(byte PN, byte StateVector);
    static byte StateMask(bool StateVector[]);
    
    static void Tuner(bool State);
    static void Patch(byte PN);
    
  private:
    ZoomIf();
};

#endif
