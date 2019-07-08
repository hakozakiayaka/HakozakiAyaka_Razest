//=============================================================================
//
// シーン処理 [scene.h]
// Author : 箱﨑彩花
//
//=============================================================================
#ifndef _SCENE_H_		//二重インクルード防止
#define _SCENE_H_

#include	"main.h"		//メイン

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DATA				(10000)			//データの最大数
#define PRIORITY				(8)					//優先順位の最大数

//*****************************************************************************
// オブジェクトクラス
//*****************************************************************************
class CScene
{
public:
	//オブジェクトの種類
	typedef enum
	{
		OBJTYPE_NONE = 0,									//初期化
		OBJTYPE_BG,												//背景
		OBJTYPE_PLAYER,										//プレイヤー
		OBJTYPE_ANIMAL,										//おとも
		OBJTYPE_ENEMY,										//エネミー
		OBJTYPE_BULLET,										//弾
		OBJTYPE_EFFECT,										//エフェクト
		OBJTYPE_FADE,											//フェード
		OBJTYPE_PAUSE,										//ポーズ
		OBJTYPE_LIFE,											//ライフ
		OBJTYPE_MAX											//種類の最大値
	} OBJTYPE;

	CScene(int nPriority = 3);								//オーバーロードされたコンストラクタ
	virtual ~CScene();											//デストラクタ
	virtual HRESULT Init(void) = 0;						//初期化処理
	virtual void Uninit(void) = 0;							//終了処理
	virtual void Update(void) = 0;							//更新処理
	virtual void Draw(void) = 0;							//描画処理

	//静的メンバ関数
	void SetObjType(OBJTYPE objType);				//オブジェクトの設定
	OBJTYPE GetObjType(void);							//オブジェクトの種類を取得する処理

	//静的メンバ関数
	static CScene * GetScene(int nPriority, int nIdx);				//シーンの取得
	static void ReleaseAll(void);												//全ての終了処理
	static void ReleaseFadeAll(void);										//フェード以外終了処理
	static void UpdateAll(void);													//全ての更新処理
	static void DrawAll(void);													//全ての描画処理
	static void SetPause(bool bPause);

private:
	//静的メンバ変数宣言
	static int			m_nNumAll;													//ポリゴンの総数
	static CScene *m_apScene[PRIORITY][MAX_DATA];		//ポリゴンの生成
	static bool		 m_bPause;

	int					m_nPriority;								//優先順位の番号
	int					m_nID;										//自分自身の番号
	OBJTYPE			m_objType;								//オブジェクトの種類

protected:
	void Release(void);											//オブジェクトを破棄する処理
};

#endif