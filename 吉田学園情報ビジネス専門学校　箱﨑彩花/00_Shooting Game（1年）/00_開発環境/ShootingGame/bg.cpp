//===============================================================================
//
// wi [bg.cpp]
// Author :  ú±ÊÔ
//
//===============================================================================
#include "main.h"
#include"bg.h"

//==============================================================================
//}Nè`
//===============================================================================
#define BG_TEXTURE		 "data/TEXTURE/bg100.png"						//ÇÝÞeNX`
#define BG_TEXTURE1	 "data/TEXTURE/bg101.png"						//ÇÝÞeNX`
#define BG_TEXTURE2	 "data/TEXTURE/bg102.png"						//ÇÝÞeNX`
#define MAX_BG_DATA				(3)													//eNX`Ì
#define BG_POS_X						(0)													//wiÌ¶ãXÀW
#define BG_POS_Y						(0)													//wiÌ¶ãYÀW
#define BG_WIDTH						(SCREEN_WIDTH)							//wiÌ
#define BG_HEIGHT					(SCREEN_HEIGHT)							//wiÌ³
#define VERTEX_NUMBER			(4)													//¸_

//===============================================================================
//O[oÏé¾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_BG_DATA] = {};				//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;						//¸_obt@ÖÌ|C^
int g_nCntBg = 0;																					//t[ðJEg

//===============================================================================
//wiú»
//===============================================================================
void InitBG(void)
{
	//Ïé¾
	VERTEX_2D * pVtx;						//¸_îñÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice;	//foCXÖÌ|C^
	int nCntBg;

	//foCXðæ¾
	pDevice = GetDevice();

	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE, &g_pTextureBG[0]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE1, &g_pTextureBG[1]);
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE2, &g_pTextureBG[2]);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUMBER * MAX_BG_DATA,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBg = 0; nCntBg < MAX_BG_DATA; nCntBg++)
	{
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
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//wieNX`ÌÝè
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f );
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffBG->Unlock();
}

//===============================================================================
//wiI¹
//===============================================================================
void UninitBG(void)
{
	int nCntTex;

	//eNX`Ìjü
	for (nCntTex = 0; nCntTex < MAX_BG_DATA; nCntTex++)
	{
		if (g_pTextureBG[nCntTex] != NULL)
		{
			g_pTextureBG[nCntTex]->Release();
			g_pTextureBG[nCntTex] = NULL;
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
	int nCntBg = 1;

	g_nCntBg++;

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//wieNX`ÌÝè
	for (nCntBg = 0; nCntBg < MAX_BG_DATA; nCntBg++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (- g_nCntBg * (0.002f * (nCntBg + 1))));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (- g_nCntBg * (0.002f * (nCntBg + 1))));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + (- g_nCntBg * (0.002f * (nCntBg + 1))));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + (- g_nCntBg * (0.002f * (nCntBg + 1))));

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªiß
	}

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

	for (nCntBg = 0; nCntBg < MAX_BG_DATA; nCntBg++)
	{
		//eNX`ÌÝè
		pDevice->SetTexture(0, g_pTextureBG[nCntBg]);
	
		//|SÌ`æ
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, VERTEX_NUMBER * nCntBg, 2);
	}
}