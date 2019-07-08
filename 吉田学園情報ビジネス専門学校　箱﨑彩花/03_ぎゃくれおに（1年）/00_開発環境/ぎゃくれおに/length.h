//=============================================================================
//
// ���C�t���� [length.h]
// Author :  �L�n�@���u
//
//=============================================================================
#ifndef _LENGTH_H_
#define _LENGTH_H_

#include "main.h"

typedef enum
{
	LengthTex_Init = 0,
	LengthTex_DAMAGE,
	LengthTex_HIL,
	LengthTex_MAX,
}LENGTHTEX;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLength(void);
void UninitLength(void);
void UpdateLength(void);
void DrawLength(void);

void AddLength(int nLength, LENGTHTEX Length);
#endif