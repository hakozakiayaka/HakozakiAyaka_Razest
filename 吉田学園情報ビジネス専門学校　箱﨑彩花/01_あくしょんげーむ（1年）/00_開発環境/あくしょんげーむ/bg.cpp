//===============================================================================
//
// wi [bg.cpp]
// Author :  ú±ÊÔ
//
//===============================================================================
#include "main.h"
#include"bg.h"
#include "game.h"

//==============================================================================
//}Nè`
//===============================================================================
#define BG_TEXTURE		 "data/TEXTURE/sky005.jpg"						//wi@ÇÝÞeNX`
#define BG_TEXTURE1	 "data/TEXTURE/kanban1.png"				//ÅÂ@ÇÝÞeNX`
#define MAX_BG							(3)													//eNX`Ì

#define BG_POS_X						(0)													//wiÌ¶ãXÀW
#define BG_POS_Y						(0)													//wiÌ¶ãYÀW
#define BG_WIDTH						(SCREEN_WIDTH)							//wiÌ
#define BG_HEIGHT					(SCREEN_HEIGHT)							//wiÌ³
#define VERTEX_NUMBER			(4)													//¸_

//===============================================================================
//O[oÏé¾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_BG] = {};				//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;	//¸_obt@ÖÌ|C^
float g_nBg;

//===============================================================================
//wiú»
//===============================================================================
void InitBG(void)
{
	//Ïé¾
	VERTEX_2D * pVtx;						//¸_îñÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice;	//foCXÖÌ|C^

	//foCXðæ¾
	pDevice = GetDevice();

	//Xe[Wðæ¾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE, &g_pTextureBG[0]);

	if (pStage == GAMESTAGE_SELECT)
	{	//IðæÊÌ¾¯gp
		D3DXCreateTextureFromFile(pDevice, BG_TEXTURE1, &g_pTextureBG[1]);
	}

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUMBER * MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//wiÌÀWÝè
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//rhwÌÝè
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//wiFÝè
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//eNX`ÌÀWÝè
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//IðæÊ---------------------------------------------
	if (pStage == GAMESTAGE_SELECT)
	{
		//wiÌÀWÝè
		pVtx[0].pos = D3DXVECTOR3(200, 70, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1000, 70, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(200, 450, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000, 450, 0.0f);

		//rhwÌÝè
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//wiFÝè
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//eNX`ÌÀWÝè
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	pVtx += 4;

	//¸_obt@ðAbN·é
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//wiI¹
//===============================================================================
void UninitBG(void)
{
	int nCntBg;

	//eNX`Ìjü
	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_pTextureBG[nCntBg] != NULL)
		{
			g_pTextureBG[nCntBg]->Release();
			g_pTextureBG[nCntBg] = NULL;
		}
	}

	//¸_obt@Ìjü
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//===============================================================================
//wiXV
//===============================================================================
void UpdateBG(void)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^

	//Xe[Wðæ¾
	GAMESTAGE pStage;
	pStage = GetGameStage();

	g_nBg += 0.0001f;

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//wiÌÀWÝè
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

	//eNX`ÌÀWÝè
	pVtx[0].tex = D3DXVECTOR2(0.0f + g_nBg, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f + g_nBg, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + g_nBg, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + g_nBg, 1.0f);

	pVtx += 4;

	//if (pStage == GAMESTAGE_SELECT)
	//{
	//	//wiÌÀWÝè
	//	pVtx[0].pos = D3DXVECTOR3(100, 100, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(300, 100, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(100, 200, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(300, 200, 0.0f);

	//	//eNX`ÌÀWÝè
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//}
	//pVtx += 4;

	//¸_obt@ðAbN·é
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//wi`æ
//===============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//foCXÖÌ|C^
	int nCntBg;

	//foCXðæ¾·é
	pDevice = GetDevice();

	//¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//¸_tH[}bgÌÝè
	pDevice ->SetFVF(FVF_VERTEX_2D);	

	for (nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//eNX`ÌÝè
		pDevice->SetTexture(0, g_pTextureBG[nCntBg]);

		//|SÌ`æ
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBg, 2);
	}
}