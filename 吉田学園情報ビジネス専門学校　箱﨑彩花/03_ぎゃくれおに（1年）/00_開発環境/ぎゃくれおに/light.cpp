//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "light.h"		//���C�g
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIGHT		(3)			//���C�g�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DLIGHT9 g_Light[MAX_LIGHT];		//���C�g�̏��
int g_nCntDiffuse = 0;				//�b���J�E���g

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void InitLight(void)
{
	MODE pMode = *GetMode();
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3 vecDir[MAX_LIGHT];

	// ���C�g�̕����̐ݒ�
	/*vecDir[0] = D3DXVECTOR3(0.2f, -1.0f, -0.4f);
	vecDir[1] = D3DXVECTOR3(0.0f, -1.0f, -0.4f);
	vecDir[2] = D3DXVECTOR3(-0.2f, -1.0f, -0.4f);*/

	//// ���C�g�̕����̐ݒ�
	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, -0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
	
	if (pMode == MODE_TITLE)
	{
		// ���C�g�̊g�U����ݒ�
		g_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//if (g_nCntDiffuse >= 600 && g_nCntDiffuse <= 699)
	//{
	//	// ���C�g�̊g�U����ݒ�
	//	g_Light[0].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//	g_Light[1].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//	g_Light[2].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//}
	//if (g_nCntDiffuse == 700)
	//{
	//	g_nCntDiffuse = 0;
	//}
	//g_nCntDiffuse++;

	// ���C�g���N���A����
	ZeroMemory(&g_Light, sizeof(D3DLIGHT9));

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		// ���C�g�̎�ނ�ݒ�
		g_Light[nCount].Type = D3DLIGHT_DIRECTIONAL;

		//���K������
		D3DXVec3Normalize(&vecDir[nCount], &vecDir[nCount]);
		g_Light[nCount].Direction = vecDir[nCount];

		// ���C�g��ݒ肷�� ����������Ȃ��ƁA���C�g���S���g���Ȃ�
		pDevice->SetLight(nCount, &g_Light[nCount]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCount, TRUE);
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
	MODE pMode = *GetMode();

	if (pMode == MODE_GAME)
	{
		if (g_nCntDiffuse >= 0 && g_nCntDiffuse <= 1799)
		{
			// ���C�g�̊g�U����ݒ�
			g_Light[0].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.4f);
			g_Light[1].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.4f);
			g_Light[2].Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.4f);
		}
		else if (g_nCntDiffuse >= 1800 && g_nCntDiffuse <= 3599)
		{
			// ���C�g�̊g�U����ݒ�
			g_Light[0].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
			g_Light[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
			g_Light[2].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
		}
		if (g_nCntDiffuse >= 3600 && g_nCntDiffuse <= 5399)
		{
			//�f�o�b�N�p
			// ���C�g�̊g�U����ݒ�0.35f,1.0f
			g_Light[0].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
			g_Light[1].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
			g_Light[2].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
		}
		if (g_nCntDiffuse >= 5400 && g_nCntDiffuse <= 7200)
		{
			//�f�o�b�N�p
			// ���C�g�̊g�U����ݒ�0.35f,1.0f
			g_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	g_nCntDiffuse++;
	}
}

