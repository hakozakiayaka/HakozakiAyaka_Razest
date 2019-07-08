//===============================================================================
//
// SæÊ [logo.cpp]
// Author :  ú±ÊÔ
//
//===============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"
#include "logo.h"

//==============================================================================
//}Nè`
//===============================================================================
#define LOGO_TEX	"data/TEXTURE/mio.jpg"	//ÇÝÞeNX`

//===============================================================================
//O[oÏé¾
//===============================================================================
LPDIRECT3DTEXTURE9 g_pTextureLogo = NULL;					//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLogo = NULL;		//¸_obt@ÖÌ|C^
Logo g_Logo;

//===============================================================================
//SæÊú»
//===============================================================================
void InitLogo(void)
{
	//Ïé¾
	VERTEX_2D * pVtx;							//¸_îñÖÌ|C^
	LPDIRECT3DDEVICE9 pDevice;		//foCXÖÌ|C^

	//\¢ÌÌú»
	g_Logo.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//Êu
	g_Logo.state = LOGOSTATE_NONE;						//S
	g_Logo.bUse = false;

	//foCXðæ¾
	pDevice = GetDevice();

	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice, LOGO_TEX, &g_pTextureLogo);

	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLogo,
		NULL);

	//¸_obt@ðbNµA¸_f[^ÖÌ|C^ðæ¾
	g_pVtxBuffLogo->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Logo.state == LOGOSTATE_LOGO)
	{
		//wiÌÀWÝè
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(500.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffLogo->Unlock();
}

//===============================================================================
//SæÊI¹
//===============================================================================
void UninitLogo(void)
{
	//eNX`Ìjü
	if (g_pTextureLogo != NULL)
	{
		g_pTextureLogo->Release();
		g_pTextureLogo = NULL;
	}
	
	//¸_obt@Ìjü
	if (g_pVtxBuffLogo != NULL)
	{
		g_pVtxBuffLogo->Release();
		g_pVtxBuffLogo = NULL;
	}
}

//===============================================================================
//SæÊXV
//===============================================================================
void UpdateLogo(void)
{
}

//===============================================================================
//SæÊ`æ
//===============================================================================
void DrawLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//foCXÖÌ|C^

	//foCXðæ¾·é
	pDevice = GetDevice();

	//¸_obt@ðfoCXÌf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffLogo, 0, sizeof(VERTEX_2D));

	//¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);

	//eNX`ÌÝè
	pDevice->SetTexture(0, g_pTextureLogo);

	//|SÌ`æ
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//===============================================================================
//SÌÝè
//===============================================================================
void SetLogo(D3DXVECTOR3 pos, int nTexType, LogoState state)
{
	g_Logo.pos = pos;
	g_Logo.nTexType = nTexType;
	g_Logo.state = LOGOSTATE_LOGO;
	g_Logo.bUse = true;
}