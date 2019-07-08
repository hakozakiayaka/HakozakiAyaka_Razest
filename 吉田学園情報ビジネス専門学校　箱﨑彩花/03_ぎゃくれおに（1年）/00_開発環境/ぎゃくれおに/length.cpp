//=============================================================================
//
// ���C�t���� [lenght.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "length.h"
#include "player.h"
#include "input.h"
#include "time.h"
#include "fade.h"
#include "frame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LENGTH		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LENGTH1		"data/TEXTURE/Length.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_POLYGON			(122)							//�X�R�A�̍ő包��
#define MAX_TEXTURE			(2)								//�X�R�A�̍ő包��
#define MAX_LENGTH_TEX		(120)							//�X�R�A�̍ő包��
#define MAX_LENGTH_NUM		(2)								//�X�R�A�̍ő包��

#define LENGTH_SIZE			(15)
#define TEXLENGTH_SIZE_X	(1)
#define TEXLENGTH_SIZE_Y	(20)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLength(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLength[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLength = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
int						g_nLength;								// �X�R�A
D3DXVECTOR3				g_posLength;
D3DXVECTOR3				g_posTexLength;
bool					g_bLengthTex[MAX_LENGTH_TEX];

//=============================================================================
// ����������
//=============================================================================
void InitLength(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���l
	g_posLength = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	//�Q�[�W
	g_posTexLength = D3DXVECTOR3(SCREEN_WIDTH / 2 - 57, SCREEN_HEIGHT / 2, 0.0f);

	for (int nCount = 0; nCount < MAX_LENGTH_TEX; nCount++)
	{
		g_bLengthTex[nCount] = true;
	}

	// �X�R�A�̏�����
	g_nLength = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_LENGTH,			// �t�@�C���̖��O
							&g_pTextureLength[0]);	// �e�N�X�`���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_LENGTH1,		// �t�@�C���̖��O
							&g_pTextureLength[1]);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLength(pDevice);

	//����������
	AddLength(120, LengthTex_Init);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLength(void)
{
	int nCountTex;
	// �e�N�X�`���̊J��
	for (nCountTex = 0; nCountTex < MAX_TEXTURE; nCountTex++)
	{
		if (g_pTextureLength[nCountTex] != NULL)
		{
			g_pTextureLength[nCountTex] -> Release();
			g_pTextureLength[nCountTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLength != NULL)
	{
		g_pVtxBuffLength->Release();
		g_pVtxBuffLength = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLength(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLength(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCountTex;
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLength, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	for (nCountTex = 0; nCountTex < MAX_POLYGON; nCountTex++)
	{
		if (nCountTex < MAX_LENGTH_NUM)
		{
			pDevice->SetTexture(0, g_pTextureLength[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex, 2);
		}
		else if (g_bLengthTex[nCountTex - MAX_LENGTH_NUM] == true)
		{
			pDevice->SetTexture(0, g_pTextureLength[1]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex , 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLength(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLength;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLength,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLength->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLength = 0; nCntLength < MAX_POLYGON; nCntLength++)
	{
		if (nCntLength < MAX_LENGTH_NUM)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posLength.x - LENGTH_SIZE, g_posLength.y - LENGTH_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posLength.x + LENGTH_SIZE, g_posLength.y - LENGTH_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posLength.x - LENGTH_SIZE, g_posLength.y + LENGTH_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posLength.x + LENGTH_SIZE, g_posLength.y + LENGTH_SIZE, 0.0f);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			g_posLength.x += 28;
		}
		else
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posTexLength.x - TEXLENGTH_SIZE_X, g_posTexLength.y - TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTexLength.x + TEXLENGTH_SIZE_X, g_posTexLength.y - TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTexLength.x - TEXLENGTH_SIZE_X, g_posTexLength.y + TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTexLength.x + TEXLENGTH_SIZE_X, g_posTexLength.y + TEXLENGTH_SIZE_Y, 0.0f);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_posTexLength.x += 1;
		}
		
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�F��ς��鏈��
		if (nCntLength >= MAX_POLYGON - 60)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else if (nCntLength >= MAX_POLYGON - 90)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
		}
		else if (nCntLength >= MAX_POLYGON - 110)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		}
		else
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLength->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddLength(int nLength, LENGTHTEX Length)
{
	// ���_����ݒ�
	VERTEX_2D *pVtx;

	Time *pTime = GetTime();

	int nCntLength = 0;
	int aNumber[MAX_LENGTH_NUM];
	int nCntDeleteLeg = 0;

	//�����Ă����������ɓ����
	g_nLength += nLength;

	if (Length == LengthTex_DAMAGE)
	{
		//�摜�����ԕ��������Ă���
		g_bLengthTex[pTime->Lenght] = false;
	}
	//�񕜂���ꍇ
	if (Length == LengthTex_HIL)
	{
		for (int nCount = 11; nCount >= 0; nCount--)
		{
			if (g_bLengthTex[nCount] == false)
			{
				g_bLengthTex[nCount] = true;

				//�e�N�X�`���̑���
				g_bLengthTex[pTime->Lenght + g_bLengthTex[nCount]];
			}
		}
	}
	//�K�\�������؂ꂽ�ꍇ
	if (g_nLength == 0)
	{
		SetFade(MODE_RESULT);
	}
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLength->Lock(0, 0, (void**)&pVtx, 0);

	/*aNumber[0] = g_nLength % 100 / 10;
	aNumber[1] = g_nLength % 10;*/

	for (nCntLength = 0; nCntLength < MAX_LENGTH_NUM; nCntLength++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntLength] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntLength] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntLength] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntLength] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLength->Unlock();
}