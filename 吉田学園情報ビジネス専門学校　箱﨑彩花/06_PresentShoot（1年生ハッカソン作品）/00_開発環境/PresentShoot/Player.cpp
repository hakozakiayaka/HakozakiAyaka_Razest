//=============================================================================
//
// �v���[���[���� [player.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "player.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "game.h"
#include "present.h"
#include "enemy.h"
#include "life.h"
#include "effect.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURENAME		"data\\TEXTURE\\santa.png"		//�ǂ݂��ރe�N�X�`���̖��O
#define PLAYER_SPEED	(1.0f)							//�v���C���[�̃X�s�[�h
#define PLAYER_ANIM		(20.0f)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
VERTEX_2D				g_aVertex[4];				//���_�����i�[����
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Player					g_player;					//�v���C���[�̃|�C���^
int						g_nCntEffect;					//���Ԃ̃J�E���^�[

//=============================================================================
//	���_���̐ݒ�
//=============================================================================
void InitPlayer(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//����������
	g_player.nCounterAnim = 0;							//�J�E���^�[������������
	g_player.nPatternAnim = 0;							//�p�^�[��No.������������
	g_player.nLife = PLAYER_LIFE;						//�v���C���[�̃��C�t
	g_player.pos = D3DXVECTOR3(100.0f, 200.0f, 0.0f);	//�����ʒu
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	g_player.posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����l
	g_player.nDirectionMove = 0;
	g_player.bDisp = true;
	g_nCntEffect = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
								TEXTURENAME,
								&g_pTexturePlayer);

	//���_�o�b�t�@�̐���
	pDevice -> CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								  D3DUSAGE_WRITEONLY,
								  FVF_VERTEX_2D,
								  D3DPOOL_MANAGED,
								  &g_pVtxBuffPlayer,
								  NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//========================================================================================
//�I������
//========================================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//========================================================================================
//�X�V����
//========================================================================================
void UpdatePlayer(void)
{
	//�ϐ��錾
	g_player.nCounterAnim++;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	if (g_player.bDisp == true)
	{
		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;

		//���Ԃ����Z����
		g_nCntEffect++;

		//�G�t�F�N�g
		SetEffect(g_player.pos, D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f), 2.0f, 1);

		switch (g_player.state)
		{
		case PLAYERSTATE_APPEAR:
			g_player.nCntstate--;
			if (g_player.nCntstate <= 0)
			{
				g_player.state = PLAYERSTATE_NOMAL;

			}
			break;

		case PLAYERSTATE_NOMAL:

			break;

		case PLAYERSTATE_DAMAGE:
			g_player.nCntstate--;
			if (g_player.nCntstate <= 0)
			{
				g_player.state = PLAYERSTATE_APPEAR;
				//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

																//���_�o�b�t�@�̃A�����b�N
				g_pVtxBuffPlayer->Unlock();
			}

			break;

		case PLAYERSTATE_DEATH:
			if (g_player.nCntstate <= 0)
			{
				g_player.posMove.y += 0.3f;
				g_player.pos.y += g_player.posMove.y;

				g_player.state = PLAYERSTATE_APPEAR;
				//���_�����b�N���Ē��_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

				pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j

																//���_�o�b�t�@�̃A�����b�N
				g_pVtxBuffPlayer->Unlock();
			}
			break;
		}

		//�A�j���[�V�����̏���
		if ((g_player.nCounterAnim % 30) == 0)
		{
			g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
		}

		//�ړ�����
		if (GetKeyboardPress(DIK_D) == true)
		{//�E�ɐi��
			g_player.nDirectionMove = 0;

			g_player.move.x += sinf(D3DX_PI * 0.5) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * 0.5) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//���ɐi��
			g_player.nDirectionMove = 1;

			g_player.move.x += sinf(D3DX_PI * -0.5) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI * -0.5) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//���ɐi��
			g_player.move.x += sinf(0.0f) * PLAYER_SPEED;
			g_player.move.y += cosf(0.0f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//��ɐi��
			g_player.move.x += sinf(D3DX_PI) * PLAYER_SPEED;
			g_player.move.y += cosf(D3DX_PI) * PLAYER_SPEED;
		}

		//�v���[���g�𗎂Ƃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetPresent(rand() % 4, g_player.pos);
		}

		//�ړ��͈͏���
		if (g_player.pos.x + POSCENTER_X > SCREEN_WIDTH)
		{
			g_player.pos.x = SCREEN_WIDTH - POSCENTER_X;
		}
		else if (g_player.pos.x - POSCENTER_X < 0.0f)
		{
			g_player.pos.x = 0.0f + POSCENTER_X;
		}

		if (g_player.pos.y - POSCENTER_Y < 0.0f)
		{
			g_player.pos.y = 0.0f + POSCENTER_Y;
		}
		else if (g_player.pos.y + POSCENTER_Y > 400)
		{
			g_player.pos.y = 400 - POSCENTER_Y;
		}

		//�ʒu�X�V
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//����
		g_player.move.x += (0.0f - g_player.move.x) * 0.2f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.2f;

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y - POSCENTER_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - POSCENTER_X, g_player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + POSCENTER_X, g_player.pos.y, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		if (g_player.nDirectionMove == 0)
		{//�E�����̎�
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[0].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
		if (g_player.nDirectionMove == 1)
		{//���Ɍ����Ă���Ƃ�
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_player.nPatternAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * g_player.nPatternAnim, 1.0f);
		}
	
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//========================================================================================
//�`�揈��
//========================================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

		//�f�o�C�X�̎擾
		pDevice = GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		if (g_player.bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
}

//========================================================================================
//�v���C���[�̏��
//========================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;
	SetLife(g_player.nLife);

	VERTEX_2D *pVtx;// ���_���̍쐬
					//���_�o�b�t�@�����b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (g_player.nLife <= 0)
	{
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCntstate = 60;
		g_player.bDisp = false;
		SetGameState(GAMESTATE_END_OVER);

	}
	else
	{
		g_player.state = PLAYERSTATE_DAMAGE;

		g_player.nCntstate = 5;

		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//��ڂ̒��_�̐F�w��i�E���j
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);//�O�ڂ̒��_�̐F�w��i�E���j
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

}