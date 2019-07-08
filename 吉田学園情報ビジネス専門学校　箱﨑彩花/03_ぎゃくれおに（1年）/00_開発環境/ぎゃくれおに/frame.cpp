//-----------------------------------------------------------------------------
//
//���L���̏���[frame.cpp]
//Author : �L�n���u
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "frame.h"
#include "camera.h"
#include "game.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define	TEXTURE_FRAME1 "data/TEXTURE/bunkatu.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME2 "data/TEXTURE/���o�܂�.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define FRAME_SIZE_X	(640)							//�g�̉���
#define FRAME_SIZE_Y	(360)							//�g�̏c��
#define HINODE_SIZE_X	(95)							//�g�̉���
#define HINODE_SIZE_Y	(65)							//�g�̏c��
#define MAX_TEXTURE		(2)								//�e�N�X�`���̍ő吔

//-----------------------------------------------------------------------------
//�O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;					//���_�o�b�t�@�ւ̃|�C���^
int						g_nFrame;								//�g�̐��l
D3DXVECTOR3				g_posFrame;								//�t���[���̒��S���W
D3DXVECTOR3				g_posHinode;							//���o�̒��S���W

//-----------------------------------------------------------------------------
//���L���̏���������
//-----------------------------------------------------------------------------
void InitFrame(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	Camera pCamera = *GetCamera();				//�J�����̃f�o�C�X�̎擾						
	MODE pMode = *GetMode();					//���[�h�̃|�C���^
	int				  nCntFrame;				//���L���̃J�E���g
	VERTEX_2D		  *pVtx;					//���_����ݒ�

	//���L���̏�����
	g_posFrame = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);		//�g�̏������W
	g_posHinode = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -24, 0.0f);		//�g�̏������W

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�g
		pDevice,
		TEXTURE_FRAME1,
		&g_pTextureFrame[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//���o
		pDevice,
		TEXTURE_FRAME2,
		&g_pTextureFrame[1]
	);


	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (pMode != MODE_TITLE)
		{
			if (nCntFrame == 0)
			{//�g
			 //�g�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (nCntFrame == 1)
			{//�g
			 //�g�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posHinode.x - (HINODE_SIZE_X), g_posHinode.y - (HINODE_SIZE_Y), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posHinode.x + (HINODE_SIZE_X), g_posHinode.y - (HINODE_SIZE_Y), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posHinode.x - (HINODE_SIZE_X), g_posHinode.y + (HINODE_SIZE_Y), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posHinode.x + (HINODE_SIZE_X), g_posHinode.y + (HINODE_SIZE_Y), 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
		}
		pVtx += 4; //���_�f�[�^�̃|�C���^��4�i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}

//-----------------------------------------------------------------------------
//���L���̏I������
//-----------------------------------------------------------------------------
void UninitFrame(void)
{
	//���[�J���ϐ��錾
	int nCntFrame; //�J�E���g

				   //�e�N�X�`���̔j��
	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//-----------------------------------------------------------------------------
//���L���̍X�V����
//-----------------------------------------------------------------------------
void UpdateFrame(void)
{

}

//-----------------------------------------------------------------------------
//���L���̕`�揈��
//-----------------------------------------------------------------------------
void DrawFrame(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	MODE pMode = *GetMode();
	int	nCntFrame;						//���L���̃J�E���g

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFrame[nCntFrame]);

		//�e�N�X�`���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntFrame, 2);
	}
}