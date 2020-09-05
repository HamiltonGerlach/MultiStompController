#ifndef ZOOMIF_H
#define ZOOMIF_H

#include "Arduino.h"
#include "Array.h"
#include "MultistompController.h"
#include "ZoomMsg.h"

typedef Array<byte, ZOOM_PATCH_LENGTH> _zoomPatchType;
typedef Array<byte, ZOOM_IDENTITY_LENGTH> _zoomIdType;
typedef Array<bool, ZOOM_EFF_NO> _zoomStateVector;

const byte FocusTable[ZOOM_EFF_NO] = {TBL_FOCUS_1, TBL_FOCUS_2, TBL_FOCUS_3,
                                      TBL_FOCUS_4, TBL_FOCUS_5, TBL_FOCUS_6};

// Zoom interface class
class ZoomIf {
  public:
    static Stream *Com;
    static byte Channel;
    static byte CurrentPatch;
    static byte CurrentEffects;
    static byte CurrentFocus;
    static _zoomPatchType Buffer;
    
    #if ZOOM_SRAM_MEM
      static _zoomPatchType PatchMem[ZOOM_SRAM_PATCHES];
      static bool PatchModified[ZOOM_SRAM_PATCHES];
    #endif
    
    static void Init(Stream *Com, byte Channel);
    static bool IdentityRequest();
    
    static void Tuner(bool State);
    
    static void ParamEnable();
    static void ParamDisable();
    static void ParamEdit(byte Slot, byte Param, int Value);
        
    static void SwitchOn(byte PN, byte Slot);
    static void SwitchOff(byte PN, byte Slot);
    static void SwitchEffects(byte PN, byte StateMask);
    
    static _zoomPatchType RequestPatch(byte PN);
    static void MemStore(byte PN);
    static void CachePatches();
    static void RestorePatch(byte PN);
    static void SetModified(byte PN);
    
    static _zoomStateVector GetPatchEffects(byte PN);
    static void SetPatchEffects(byte PN, byte StateMask);
    static void FocusEffect(byte Effect);
    
    static void Patch(byte PN);
    static void Patch(byte PN, bool Force);
    
    static byte StateMask(_zoomStateVector StateVector);
    static _zoomStateVector StateVector(byte StateMask);
    
    static void LogMem();
    static void LogBuffer();
    
  private:
    ZoomIf();
};

#endif
