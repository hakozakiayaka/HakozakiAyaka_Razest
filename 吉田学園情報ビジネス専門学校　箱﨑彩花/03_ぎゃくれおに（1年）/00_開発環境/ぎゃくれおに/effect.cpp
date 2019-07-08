//=========================================================================================================================
//
//�G�t�F�N�g���� [effect.cpp]
//Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
//�C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "effect.h"		//�G�t�F�N�g
#include "shadow.h"		//�e
#include "input.h"		//�L�[�{�[�h

//*************************************************************************************************************************
//�}�N����`
//*************************************************************************************************************************
#define	MAX_EFFECT				(1000)									//�G�t�F�N�g�̍ő吔
#define	TEXTURE_EFFECT_NAME		"data\\TEXTURE\\effect000.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT_NAME1	"data\\TEXTURE\\kemuri.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_EFFECT_NAME2	"data\\TEXTURE\\hi.jpg"					//�ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_TEX					(3)										//���		
	
//*************************************************************************************************************************
//�O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureEffect[MAX_TEX] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffEffect = NULL;				//���_�o�b�t�@�ւ̃|�C���^
EFFECT							g_Effect[MAX_EFFECT];					//�G�t�F�N�g�̏��
int								g_nCntEffectState;						//��ԃJ�E���^
int								g_nCountTime;							//�b���J�E���g

//=========================================================================================================================
//�G�t�F�N�g����������
//=========================================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾
	int nCntEffect;		//�G�t�F�N�g�J�E���^

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//�G�t�F�N�g���J�E���g
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].Type = EFFECTTYPE_NONE;					
		g_Effect[nCntEffect].fRadius = 0.0f;							
		g_Effect[nCntEffect].nLife = 0;							
		g_Effect[nCntEffect].bUse = false;								
	}
	g_nCntEffectState = 0;			//��Ԃ�������
	g_nCountTime = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		TEXTURE_EFFECT_NAME,
		&g_pTextureEffect[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		TEXTURE_EFFECT_NAME1,
		&g_pTextureEffect[1]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		TEXTURE_EFFECT_NAME1,
		&g_pTextureEffect[2]
	);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);

	//���_���̍쐬
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//�G�t�F�N�g���J�E���g
		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//�G�t�F�N�g�I������
//=========================================================================================================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount] ->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=========================================================================================================================
//�G�t�F�N�g�X�V����
//=========================================================================================================================
void UpdateEffect(void)
{
	//�G�t�F�N�g�J�E���^
	int nCntEffect;			

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;		

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//�G�t�F�N�g���J�E���g
		if (g_Effect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���ꍇ

			//�e�����Ă���
			//SetPositionShadow(g_Effect[nCntEffect].nIdxShadow, g_Effect[nCntEffect].pos, g_Effect[nCntEffect].rot);

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_BULLET)
			{//�e�G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				//g_Effect[nCntEffect].nLife--;
				g_Effect[nCntEffect].fRadius -= 0.2f;

				if (/*g_Effect[nCntEffect].nLife <= 0 || */g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
					g_Effect[nCntEffect].bUse = false;

					//�g���Ă���e��false
					//DeleteShadow(g_Effect[nCntEffect].nIdxShadow);
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION2 || g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{//�����G�t�F�N�g�̏ꍇ
				 //���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}

				if (g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION)
			{//���΃G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				//move�ɏd��
				g_Effect[nCntEffect].move.y -= 0.05f;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				//�o�E���h�̏���
				if (g_Effect[nCntEffect].pos.y <= 0)
				{
					g_Effect[nCntEffect].move.y = (g_Effect[nCntEffect].posOld.y - g_Effect[nCntEffect].pos.y) * 2;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{//���G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				//�o�E���h�̏���
				if (g_Effect[nCntEffect].pos.y <= 0)
				{
					g_Effect[nCntEffect].move.y = (g_Effect[nCntEffect].posOld.y - g_Effect[nCntEffect].pos.y) * 2;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE)
			{//�΃G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 1.0f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 1.0f;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{//�΂̕��G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//���C�t��0�ȉ��̏ꍇ
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SNOW)
			{//��G�t�F�N�g�̏ꍇ
				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				//g_Effect[nCntEffect].nLife--;
				   //move�ɏd��
				g_Effect[nCntEffect].move.y = -1.0f;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				//g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					//g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					//g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				if (g_Effect[nCntEffect].pos.y <= 0)
				{//���C�t��0�ȉ��̏ꍇ
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RAIN)
			{//�J�G�t�F�N�g�̏ꍇ
			 //g_Effect[nCntEffect].nLife--;

				//���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius - 20, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius - 20, 0.0f);

				//move�ɏd��
				g_Effect[nCntEffect].move.y = -3.0f;
				g_Effect[nCntEffect].move.x = 0;
				g_Effect[nCntEffect].move.z = 0;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//�ړ��l���

				//g_Effect[nCntEffect].nLife--;				//��������

				//���a����
				if (g_Effect[nCntEffect].nLife > 0)
				{
					//g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					//g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				if (g_Effect[nCntEffect].pos.y <= 0)
				{//���C�t��0�ȉ��̏ꍇ
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
		}
	}
	/*if (g_nCountTime >= 600 && g_nCountTime <= 1199)
	{*/
		////�J�̃G�t�F�N�g
		//SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		//SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		//SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		//SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		//SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
	/*}
	if (g_nCountTime == 1200)
	{
		g_nCountTime = 0;
	}*/
	g_nCountTime++;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//�G�t�F�N�g�`�揈��
//=========================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X���擾
	int nCntEffect;		//�G�t�F�N�g�J�E���^

	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//�v�Z�p�}�g���b�N�X

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p����Ă���ꍇ
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//�t�s���ݒ�
			g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_Effect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_Effect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_Effect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_Effect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_Effect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;

			//��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Effect[nCntEffect].rot.y, g_Effect[nCntEffect].rot.x, g_Effect[nCntEffect].rot.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxRot);						//�ۑ�

			//�ʒu�𔽉f																													//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);						//�ۑ�

			//���[���h�}�g���b�N�X�̐ݒ�																														//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//�A���t�@�e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//�A���t�@�e�X�g����
			//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//��r���@�i���傫���j�j
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{
				//���Z�����̐ݒ�
				pDevice->SetRenderState
				(
					D3DRS_BLENDOP,
					D3DBLENDOP_REVSUBTRACT
				);
				pDevice->SetRenderState
				(
					D3DRS_SRCBLEND,
					D3DBLEND_SRCALPHA
				);
				pDevice->SetRenderState
				(
					D3DRS_DESTBLEND,
					D3DBLEND_ONE

				);
			}
			else
			{
				//���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_Effect[nCntEffect].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//���u�����f�B���O�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���c
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//��r���@�i���傫���j�j
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
	}

}

//=========================================================================================================================
//�e�G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife,int nType)
{
	int nCntEffect;			//�G�t�F�N�g�J�E���^

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//�G�t�F�N�g���J�E���g
		if (g_Effect[nCntEffect].bUse == false)
		{//�G�t�F�N�g���g�p����Ă��Ȃ�
			g_Effect[nCntEffect].pos = pos;			//pos�l���
			g_Effect[nCntEffect].col = col;			//col�l���
			g_Effect[nCntEffect].Type = Type;		//��ސݒ�
			g_Effect[nCntEffect].fRadius = fRadius;	//���a�ݒ�
			g_Effect[nCntEffect].nLife = nLife;		//�����ݒ�
			g_Effect[nCntEffect].nType = nType;		//���
			g_Effect[nCntEffect].bUse = true;		//�g�p���Ă�����

			//���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_Effect[nCntEffect].col;
			//�@���x�N�g��
			pVtx[nCntEffect * 4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//�p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nType)
{
	//�G�t�F�N�g�J�E���^
	int nCntEffect;			
	//�G�t�F�N�g���J�E���^
	int nCount = 0;			

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;		

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//�G�t�F�N�g���J�E���g
		if (g_Effect[nCntEffect].bUse == false)
		{//�G�t�F�N�g���g�p����Ă��Ȃ�
			g_Effect[nCntEffect].pos = pos;			//pos�l���
			g_Effect[nCntEffect].Type = Type;		//��ސݒ�
			g_Effect[nCntEffect].nLife = nLife;		//�����ݒ�
			g_Effect[nCntEffect].nType = nType;		//���
			g_Effect[nCntEffect].bUse = true;		//�g�p���Ă�����

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION2 || g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				//�ړ������_����
				g_Effect[nCntEffect].move.x = sinf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.y = cosf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.z = tanf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION || g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE || g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE || g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{
				//�ړ������_����
				//g_Effect[nCntEffect].move.x = sinf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f) * ((rand() % 4) + 1);
				//g_Effect[nCntEffect].move.z = tanf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);

				g_Effect[nCntEffect].move.x = sinf((-D3DX_PI * (nCntEffect * (1.0f / (20 / 2)))))* 0.5f;
				//g_Effect[nCntEffect].move.y = 30.0f;
				//pVtx[���_�ԍ�].y = �c�̃J�E���g�񐔁@* �c�̕�
				g_Effect[nCntEffect].move.z = cosf((-D3DX_PI * (nCntEffect * (1.0f / (20 / 2)))))* 0.5f;
			}

 			int nNumber = rand() % 4 + 1;

			//col�l���
			if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION2)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.8f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.8f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.8f, 0.6f, 0.8f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.8f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.8f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.8f, 0.6f, 0.8f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SNOW)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RAIN)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
			}

			g_Effect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	//���a�ݒ�

			//���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_Effect[nCntEffect].col;

			//�J�E���g�𑫂�
			nCount++;
			if (nCount == nSetMax)
			{//�����ő吔�ɂȂ����ꍇ
				//�e������
				//g_Effect[nCount].nIdxShadow = SetShadow(g_Effect[nCount].pos, g_Effect[nCount].rot, 2, 2);
				break;
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}