//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �����ʉ�
//
//=============================================================================
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT (3)		//���C�g�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_light[MAX_LIGHT];	//���C�g�̎��

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir;											//�ݒ�p�����̃x�N�g��
	int nCntLight;

	// ���C�g���N���A����
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));
	}
	
	// ���C�g�̎�ނ�ݒ�
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;
	}

	// ���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

	// ���C�g1�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������
	g_light[0].Direction = vecDir;

	// ���C�g2�̕����̐ݒ�
	vecDir = D3DXVECTOR3(-1.0f, 0.8f, -0.6f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������
	g_light[1].Direction = vecDir;

	// ���C�g3�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.8f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//���K������
	g_light[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);
	}

	// ���C�g��L���ɂ���
	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void UpdateLight(void)
{
}