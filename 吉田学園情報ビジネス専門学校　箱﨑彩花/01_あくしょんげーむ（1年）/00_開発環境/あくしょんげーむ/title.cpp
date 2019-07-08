//===============================================================================
//
// �^�C�g����� [title.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include"tutorial.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "title.h"

//===============================================================================
//�}�N����`
//===============================================================================
#define TITLE_BG					"data/TEXTURE/title2.jpg"				//�ǂݍ��ރe�N�X�`��
#define TITLE_LOGO		"data/TEXTURE/title_logo1.png"	//�ǂݍ��ރe�N�X�`��
#define PUSH_ENTER	"data/TEXTURE/pushenter.png"	//�ǂݍ��ރe�N�X�`��
#define TITLE_GIRL		"data/TEXTURE/girl1.png"				//�ǂݍ��ރe�N�X�`��
#define MAX_TEXTURE					(5)									//�e�N�X�`���̖���

#define TITLE_POS_X						(0)													//�w�i�̍���X���W
#define TITLE_POS_Y						(0)													//�w�i�̍���Y���W
#define TITLE_WIDTH					(SCREEN_WIDTH)							//�w�i�̕�
#define TITLE_HEIGHT					(SCREEN_HEIGHT)							//�w�i�̍���

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;					//���_�o�b�t�@�ւ̃|�C���^
TITLE g_nTitle;

//===============================================================================
//�^�C�g����ʏ���������
//===============================================================================
void InitTitle(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�\���̂̏�����
	g_nTitle.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	g_nTitle.Flash = 0.05f;
	g_nTitle.nCnt = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_BG, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_LOGO, &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, PUSH_ENTER, &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_GIRL, &g_pTextureTitle[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//���S�w�i�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(120, 130, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(680, 130, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(120, 400, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(680, 400, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���S�w�i�F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//���S�w�i�e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//�v�b�V���G���^�[�̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(150, 500, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(680, 500, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(150, 550, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(680, 550, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�v�b�V���G���^�[�̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//�v�b�V���G���^�[�̃e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//=============================================================================
	//�L�����̍��W�ݒ�
	pVtx[0].pos = D3DXVECTOR3(900, 350, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1240, 350, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(900, 700, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1240, 700, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�L�����̐F�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

	//�L�����̃e�N�X�`���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//===============================================================================
//�^�C�g����ʏI������
//===============================================================================
void UninitTitle(void)
{
	int nCnt;

	//�e�N�X�`���̔j��
	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
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
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^

	//�t�F�[�h���擾
	FADE g_fade;
	g_fade = GetFade();

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

	//�v�b�V���G���^�[�̓_��
	if (g_nTitle.nCnt >= 50)
	{
		g_nTitle.Flash *= -1;
		g_nTitle.nCnt = 0;
	}

	g_nTitle.nCnt++;
	g_nTitle.col.a += g_nTitle.Flash;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�v�b�V���G���^�[�̐F�ݒ�
	pVtx[8].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[9].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[10].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);
	pVtx[11].col = D3DXCOLOR(1.0, 1.0, 1.0, g_nTitle.col.a);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

}

//===============================================================================
//�^�C�g����ʕ`�揈��
//============================================================ n===================
void DrawTitle(void)
{
	int nCnt;
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}