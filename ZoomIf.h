#ifndef ZOOMIF_H
#define ZOOMIF_H

#include "Arduino.h"
#include "Array.h"
#include "Timer.h"
#include "ZoomMsg.h"

typedef Array<byte, ZOOM_PATCH_LENGTH>    _zoomPatchType;
typedef Array<byte, ZOOM_IDENTITY_LENGTH> _zoomIdType;
typedef Array<bool, ZOOM_EFF_NO>          _zoomStateVector;


// Zoom interface class
class ZoomIf {
  public:
    static Timer Clock;
    static Stream *Com;
    static byte Channel;
    static bool TunerState;
    static byte CurrentPatch;
    static byte CurrentFocus;
    static byte CurrentEffects;
    static _zoomPatchType Buffer;
    
    static bool PatchModified[MEM_PATCH_NUM];
    static byte EffectStates[MEM_PATCH_NUM];
    
    #if !EEPROM_ENABLED
      static _zoomPatchType PatchMem[SRAM_PATCH_NUM];
    #else
      static void FlashWrite(unsigned int Address);
      static void FlashRead(unsigned int Address);
      static unsigned int FlashPatchAddress(byte PN);
    #endif
    
    static void Init(Stream *Com, byte Channel);
    static bool IdentityRequest();
    
    static void Tuner(bool State);
    
    static void ParamEnable();
    static void ParamDisable();
    static void ParamEdit(byte Slot, byte Param, int Value);
        
    static void SwitchOn(byte PN, byte Slot);
    static void SwitchOff(byte PN, byte Slot);
    
    static void OnManualSwitch(byte Slot, bool State);
    
    static void RequestPatch(byte PN);
    static void MemStore(byte PN);
    static void CachePatches();
    static void UpdatePatches();
    static void UpdateCurrentPatch();
    static void RestorePatch(byte PN);
    static void SetModified(byte PN);
    
    static byte GetPatchEffects(byte PN);
    static void SetPatchEffects(byte PN, byte Mask, bool Send = false);
    static void FocusEffect(byte Effect);
    
    static void Patch(byte PN, bool Restore = false, bool Force = false);
    
    static void LogMem();
    static void LogBuffer();
    
    static void HandleInput();
    
    static void EmptyPatch();
    static void ReadPatch(byte PN);
    static void SendPatch();
    
    static int GetParam(byte Effect, byte Parameter);
    static void SetParam(byte Effect, byte Parameter, int Value);
    
  private:
    ZoomIf();
    ~ZoomIf();
};

#endif
