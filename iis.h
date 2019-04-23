//=========================================================
// File Name : iis.h
// Function  : iis Init
//=========================================================

#ifndef __IIS_H__
#define __IIS_H__

#ifdef __cplusplus
extern "C" {
#endif

void IIS_Test(void);
void Play_Wave_IIS(void);
void RecordSound_ViaMICIn_IIS(void);
void RecordSound_ViaLineIn_IIS(void);


void Init1341(void);

#ifdef __cplusplus
}
#endif

#endif    //__IIS_H__
