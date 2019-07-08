//===============================================================================
//
// �^�C�g����� [title.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "title.h"
#include "logo.h"
#include "BG.h"
#include "sound.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define TITLE_TEX1	"data/TEXTURE/title_logo.png"	//�ǂݍ��ރe�N�X�`��
#define TITLE_TEX2	"data/TEXTURE/enter_logo.png"	//�ǂݍ��ރe�N�X�`��

#define TIMERIMIT							(60 * 3)											//��������
#define MAX_TEX							(2)													//�e�N�X�`���̍ő吔

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCntTimeTitle = 0;															//�^�C�g����ʂ��烉���L���O��ʂւ̐؂�ւ��̃J�E���^�[
Title g_Title;																			//�\���̂̕ϐ�

//===============================================================================
//�^�C�g����ʏ���������
//===============================================================================
void InitTitle(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	InitBG();
	SetBG(3);

	//�\���̂̏�����
	g_Title.state = TITLESTATE_NORMAL;
	g_Title.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Title.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_Title.fFlash = 0.05f;
	g_Title.nCnt = 0;
	g_Title.bUse = false;

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_TEX1, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEX2, &g_pTextureTitle[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g�����S���W�ݒ�------------------------------------------------------------------------------------------------------------------
	pVtx[0].pos = D3DXVECTOR3(160.0f, 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1130.0f, 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(160.0f, 450.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1130.0f, 450.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//�^�C�g�����S�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//�G���^�[���W�ݒ�------------------------------------------------------------------------------------------------------------------
	pVtx[4].pos = D3DXVECTOR3(300.0f, 500.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(980.0f, 500.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(300.0f, 650.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(980.0f, 650.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[5].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[6].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[7].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//�^�C�g�����S�e�N�X�`���̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//�^�C�g����ʏI������
//===============================================================================
void UninitTitle(void)
{
	UninitBG();

	//�e�N�X�`���̔j��
	for (int nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}

//===============================================================================
//�^�C�g����ʍX�V����
//===============================================================================
void UpdateTitle(void)
{
	//�t�F�[�h���擾
	FADE g_fade = GetFade();
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^

	UpdateBG();

	//��ʐ؂�ւ��J�E���^�[
	g_nCntTimeTitle++;

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		PlaySound(SOUND_LABEL_SE_DECIDE);
		if (g_fade != FADE_OUT)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			//���[�h�ݒ�
			SetFade(MODE_TUTORIAL);
		}
	}
	else if (g_nCntTimeTitle % 300 == 0)
	{
		if (g_fade != FADE_OUT)
		{	//�t�F�[�h�A�E�g����Enter�L�[�������Ȃ�����
			//���[�h�ݒ�
			SetFade(MODE_RANKING);
		}
	}

	//�v�b�V���G���^�[�̓_��
	if (g_Title.nCnt >= 50)
	{
		g_Title.fFlash *= -1;
		g_Title.nCnt = 0;
	}

	g_Title.nCnt++;
	g_Title.col.a += g_Title.fFlash;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�F�ݒ�
	pVtx[4].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[5].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[6].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);
	pVtx[7].col = D3DXCOLOR(1.0, 1.0, 1.0, g_Title.col.a);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//�^�C�g����ʕ`�揈��
//===============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	DrawBG();

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TEX; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTitle, 2);
	}
}