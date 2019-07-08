//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 箱�ｱ彩花
//
//=============================================================================
#ifndef _TUTORIAL_H_		//二重インクルード防止
#define _TUTORIAL_H_

#include	"main.h"				//メイン

//*****************************************************************************
// チュートリアルクラス
//*****************************************************************************
class CTutorial
{
public:
	CTutorial();																	//コンストラクタ
	~CTutorial();																//デストラクタ
	HRESULT Init(void);													//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);														//更新処理
	void Draw(void);															//描画処理
};
#endif