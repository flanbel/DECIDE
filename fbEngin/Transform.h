
//前方定義
class CGameObject;

//_TRANSFORM_H_がdefine定義されていなければ実行される。
#ifndef _TRANSFORM_H_
//ここで定義することで二回目以降読み込まれない。
#define _TRANSFORM_H_

//トランスフォームクラス
class CTransform
{
public:
	CTransform();
	~CTransform();

	//CGameObject(自分)を返す(使う時があるのか・・・？)
	//戻り値：CGameObject* 自分
	CGameObject* GameObject();

	void GameObject(CGameObject* object);

	//親を返す関数
	//戻り値：CTransform* 親のアドレス
	CTransform* Parent();

	//自分の親に登録する
	//戻り値：bool 登録できたか否か
	//第一引数：CTransform
	bool SetParent(CTransform* parent);

	//子供を検索する関数
	//戻り値：CTransform* ヒットした子のアドレス
	//第一引数：string 子供の名前
	CTransform* FindChild(string childname);

	//子の数を返す関数
	//戻り値：int 子の数
	int ChildCnt();

	//子供たち取得
	map<string, CTransform*> Children();

	//ローカルからトランスフォームを更新
	//戻り値：なし
	//引数：なし
	void UpdateTransform();

	//トランスフォームからワールド行列更新
	//戻り値：なし
	//引数：なし
	void UpdateWolrdMatrix();

	//解放
	void Release();

	//ゲッター
	D3DXMATRIX WorldMatrix();

	//ゲッター
	D3DXMATRIX RotateMatrix();

	//クォータニオンを設定する関数
	//第一引数：float x回転,第二引数：float y回転,第三引数：float z回転
	//void SetLocalRotation(float x,float y,float z)
	//{
	//	D3DXQUATERNION q = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//	D3DXMATRIX rot;
	//	//回転行列生成
	//	D3DXMatrixRotationYawPitchRoll(&rot, y, x, z);
	//	//回転行列からクォータニオン生成
	//	D3DXMatrixRotationQuaternion(&rot, &q);

	//	LocalRotation = q;
	//}

	D3DXVECTOR3					Position;			//最終ポジション
	D3DXVECTOR3					LocalPosition;		//ローカルポジション
	D3DXVECTOR3					Scale;				//最終スケール
	D3DXVECTOR3					LocalScale;			//ローカルスケール
	D3DXVECTOR3					Rotation;			//回転
	D3DXVECTOR3					LocalRotation;		//ローカル回転
private:
	CGameObject*				m_GameObject;	//自分のアドレス
	CTransform*					m_Parent;		//親のアドレス
	map<string, CTransform*>	m_Children;		//子供達のアドレスを格納したmap
	
	D3DXMATRIX					m_RotateMatrix;	//回転行列
	D3DXMATRIX					m_WorldMatrix;	//ワールド行列
};
//#ifndefの終わりを示す。
#endif //_TRANSFORM_H_