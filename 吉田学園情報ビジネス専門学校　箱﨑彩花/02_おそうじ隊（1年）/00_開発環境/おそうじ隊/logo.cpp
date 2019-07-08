//===============================================================================
//
// ���S��� [logo.cpp]
// Author : �����ʉ�
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "logo.h"

//==============================================================================
//�}�N����`
//===============================================================================
#define LOGO_TEX	"data/TEXTURE/mio.jpg"	//�ǂݍ��ރe�N�X�`��

//===============================================================================
//�O���[�o���ϐ��錾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Logo g_Logo;

//===============================================================================
//���S��ʏ���������
//===============================================================================
void InitLogo(void)
{
	//�ϐ��錾
	VERTEX_2D * pVtx;							//���_���ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�\���̂̏�����
	g_Logo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	g_Logo.state = LOGOSTATE_NONE;						//���S
	g_Logo.bUse = false;

	//�f�o�C�X���擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, LOGO_TEX, &g_pTextureLogo);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL);

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.state == LOGOSTATE_LOGO)
	{
		//�w�i�̍��W�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);

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

		//�w�i�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLogo->Unlock();
}

//===============================================================================
//���S��ʏI������
//===============================================================================
void UninitLogo(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}
}

//===============================================================================
//���S��ʍX�V����
//===============================================================================
void UpdateLogo(void)
{
}

//===============================================================================
//���S��ʕ`�揈��
//===============================================================================
void DrawLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLogo);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===============================================================================
//���S�̐ݒ�
//===============================================================================
void SetLogo(D3DXVECTOR3 pos, int nTexType, LogoState state)
{
	g_Logo.pos = pos;
	g_Logo.nTexType = nTexType;
	g_Logo.state = LOGOSTATE_LOGO;
	g_Logo.bUse = true;
}