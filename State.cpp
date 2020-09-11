#include "Arduino.h"
#include "State.h"
#include "ZoomIf.h"


byte StateMask(_zoomStateVector States) {
  byte Out = 0;

  for (int i = 0; i < ZOOM_EFF_NO; i++) {
    if (States[i]) BIT_SET(Out, i);
  }

  return Out;
}


_zoomStateVector StateVector(byte States) {
  _zoomStateVector Out;
  ARRAY_FILL(Out.data, ZOOM_EFF_NO, false);

  for (int i = 0; i < ZOOM_EFF_NO; i++) {
    if (BIT_CHECK(States, i)) Out[i] = true; 
  }

  return Out;
}