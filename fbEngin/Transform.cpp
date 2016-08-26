#include "Transform.h"
#include "GameObject.h"

CTransform::CTransform()
{
	m_GameObject = nullptr;
	m_Parent = nullptr;
	m_Children.clear();

	Position = VECTOR3_ZERO;
	LocalPosition = VECTOR3_ZERO;
	//Rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//LocalRotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	Rotation = VECTOR3_ZERO;
	LocalRotation = VECTOR3_ZERO;
	Scale = VECTOR3_ONE;
	LocalScale = VECTOR3_ONE;

	D3DXMatrixIdentity(&m_WorldMatrix);
}

CTransform::~CTransform()
{
	
}

CGameObject* CTransform::GameObject()
{
	return m_GameObject;
}

void CTransform::GameObject(CGameObject* object)
{
	m_GameObject = object;
}

//親を返す関数
//戻り値：CTransform* 親のアドレス
CTransform* CTransform::Parent()
{
	return m_Parent;
};

//引数のトランスフォームを自分の親に登録する
//戻り値：bool 登録できたか否か
//第一引数：CTransform
bool CTransform::SetParent(CTransform* parent)
{
	//子に同じ名前がいないか検索
	auto child = parent->m_Children.find(this->m_GameObject->name());
	//ヒットしなかった。
	if (child == parent->m_Children.end())
	{
		//親に登録
		this->m_Parent = parent;
		//親の子に自分を登録
		parent->m_Children.insert(make_pair(this->m_GameObject->name(), this));

		return true;
	}
	//ヒットしてしまった。
	else
	{
		//登録できなかった旨を表示
		//場所
		string place;
		//行数
		string line;
		Support::IntToString(&line, __LINE__);
		//ファイル名
		string file = __FILE__;
		place = "ファイル名："+ file + '\n' +"行数：" + line + "行"+ "でエラーが発生しました。\n";
		string log = this->m_GameObject->name() + "は同じ名前の子が既に登録されていたので" + parent->m_GameObject->name() + "に登録できませんでした。";
		log = place + log;
		MessageBox(NULL, log.c_str(), TEXT("エラー"), MB_OK);
		return false;
	}
}

//子供を検索する関数
//戻り値：CTransform* ヒットした子のアドレス
//第一引数：string 子供の名前
CTransform* CTransform::FindChild(string childname)
{
	//子の検索
	auto child = m_Children.find(childname);
	//ヒットした
	if (child != m_Children.end())
	{
		//子を返す
		return child->second;
	}
	//ヒットしなかった
	else
	{
		return nullptr;
	}
};

//子の数を返す関数
//戻り値：int 子の数
int CTransform::ChildCnt()
{
	return m_Children.size();
};

//子供たち取得
map<string, CTransform*> CTransform::Children()
{
	return m_Children;
};

//ローカルからトランスフォームを更新
//親から更新していくべき
//戻り値：なし
//引数：なし
void CTransform::UpdateTransform()
{
	//親が居るなら
	if (m_Parent) {
		//親がいる。
		D3DXMATRIX mParentWorld = m_Parent->WorldMatrix();
		D3DXVECTOR3 qParentRot = m_Parent->Rotation;
		D3DXVECTOR3 pscale = m_Parent->Scale;
		//親のワールド行列を乗算して、ローカル座標をワールド座標に変換する。
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &LocalPosition, &mParentWorld);
		//ポジション
		Position.x = pos.x;
		Position.y = pos.y;
		Position.z = pos.z;
		//スケール値
		Scale.x = LocalScale.x * pscale.x;
		Scale.y = LocalScale.y * pscale.y;
		Scale.z = LocalScale.z * pscale.z;
		//クォータニオン　未実装
		Rotation.x = LocalRotation.x;
		Rotation.y = LocalRotation.y;
		Rotation.z = LocalRotation.z;
		//Rotation = LocalRotation * qParentRot;
	}
	else {
		//ローカルをそのまま
		Position = LocalPosition;
		Scale = LocalScale;
		Rotation = LocalRotation;
	}

	UpdateWolrdMatrix();
}

//トランスフォームからワールド行列更新
//戻り値：なし
//引数：なし
void CTransform::UpdateWolrdMatrix()
{
	//ワールド行列を求める。
	D3DXMATRIX scale, pos;
	//サイズ
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	//回転
	D3DXMatrixRotationYawPitchRoll(&m_RotateMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
	//D3DXMatrixRotationQuaternion(&rotate, &Rotation);
	//ポジション
	D3DXMatrixTranslation(&pos, Position.x, Position.y, Position.z);
	m_WorldMatrix = scale * m_RotateMatrix * pos;
}

//トランスフォーム解放
void CTransform::Release()
{
	map<string, CTransform*>::iterator it = m_Children.begin();
	while (it != m_Children.end())
	{
		//親を削除
		it->second->m_Parent = nullptr;
		it++;
	}
	m_Children.clear();
}

//////以下セッター・ゲッター


//ゲッター
D3DXMATRIX CTransform::WorldMatrix()
{
	return m_WorldMatrix;
}

//ゲッター
D3DXMATRIX CTransform::RotateMatrix()
{
	return m_RotateMatrix;
}