//=============================================================================
//
// wi [BG.cpp]
// Author :  ú±ÊÔ
//
//=============================================================================
#include "BG.h"
#include "main.h"

//=============================================================================
// }Nè`
//=============================================================================
#define MAX_TEX	(4)		//ÇÝ±ÞeNX`ÌÅå
#define MAX_BG		(5)		//wiÌÅå

//=============================================================================
// O[oÏ
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBG[MAX_TEX] = {};	//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//¸_obt@ÖÌ|C^
BG g_BG[MAX_BG];																//îñÝè

//=============================================================================
// X^[g{^ú»
//=============================================================================
void InitBG(void)
{
	//Ïé¾
	char	BGName[MAX_TEX][48];		//t@C¼ði[·é
	int	nCntTex;
	int    nCntBG;

	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ÏÌú»
	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		g_BG[nCntBG].nTexNum = 0;				//eNX`ÌÔ
		g_BG[nCntBG].bUse = false;				//gpµÄ¢È¢óÔÉ·é
	}

	//eNX`t@C¼ði[·é
	wsprintf(&BGName[0][0], "data\\TEXTURE\\ranking2.png");			//LOÌwi
	wsprintf(&BGName[1][0], "data\\TEXTURE\\gameclear.png");			//Q[NA
	wsprintf(&BGName[2][0], "data\\TEXTURE\\gameover.png");			//Q[I[o[
	wsprintf(&BGName[3][0], "data\\TEXTURE\\kabegami.jpg");			//LOA^CgÌwi

	//eNX`ÌÇÝÝ
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &BGName[nCntTex][0],
								  &g_pTextureBG[nCntTex]);
	}

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffBG,
								NULL);

	VERTEX_2D*pVtx;		//¸_îñÖÌ|C^

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_BG; nCntTex++)
	{
		//¸_ÀWÌÝè
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhwÌÝè
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//¸_J[ÌÝè
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//eNX`ÀWÌÝè
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//YÌÊuÜÅißé
		pVtx += 4;
	}

	//¸_obt@ðAbN·é
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// ^CgI¹
//=============================================================================
void UninitBG(void)
{
	//Ïé¾
	int nCntTex;

	//eNX`Ìjü
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
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

//=============================================================================
// ^CgXV
//=============================================================================
void UpdateBG(void)
{
}

//=============================================================================
// ^Cg`æ
//=============================================================================
void DrawBG(void)
{
	//Ïé¾
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;		//foCXÖÌ|C^

	//foCXÌæ¾
	pDevice = GetDevice();

	//¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == true)
		{
			//eNX`ÌÝè
			pDevice->SetTexture(0, g_pTextureBG[g_BG[nCntBG].nTexNum]);

			//|SÌ`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//v~eBuÌíÞ
								   nCntBG * 4,												//Jn·é¸_ÌCfbNX
								   2);																//v~eBuÌ
		}
	}
}

//=============================================================================
// îñÝè
//=============================================================================
void SetBG(int nTexNum)
{
	//Ïé¾
	int nCntBG;

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == false)
		{
			g_BG[nCntBG].nTexNum = nTexNum;		//eNX`ÌÔ
			g_BG[nCntBG].bUse = true;			//gpµÄ¢éóÔÉ·é
			break;
		}
	}
}

//=============================================================================
// wiðÁ·
//=============================================================================
void DeleteBG()
{
	//Ïé¾
	int nCntBG;

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == true)
		{
			g_BG[nCntBG].bUse = false;		//gpµÄ¢È¢óÔÉ·é
		}
	}
}