
#ifndef _INPUT_H_
#define _INPUT_H_

//キーボード入力管理クラスです
class CInputManager
{
public:
	/****************************************************/
	/*UpdateKeyboardState関数							*/
	/*	機能：キーボード状態を更新する関数				*/
	/*  必ず毎フレーム呼出してください					*/
	/*	引数：なし										*/
	/*	戻り値：なし									*/
	/****************************************************/
	void UpdateKeyboardState(void)
	{
		memcpy(this->m_prevKeyboardState, this->m_curKeyboardState, sizeof(this->m_prevKeyboardState));
		GetKeyboardState(this->m_curKeyboardState);
	}

	/****************************************************/
	/*isKeyDown関数										*/
	/*	機能：キー押下状態判定関数						*/
	/*	　　　キーが押下されているかを判定します		*/
	/*	引数：											*/
	/*	  key		：判定するキー						*/
	/*	戻り値：押下(true)　未押下(false)				*/
	/****************************************************/
	bool isKeyDown(const int& key)
	{
		return (this->m_curKeyboardState[key] & 0x80) != 0;
	}

	/****************************************************/
	/*isPressed関数										*/
	/*	機能：キー瞬間押下状態判定関数					*/
	/*	　　　キーが瞬間的に押下されているかを判定します*/
	/*	引数：											*/
	/*	  key		：判定するキー						*/
	/*	戻り値：押下(true)　未押下(false)				*/
	/****************************************************/
	bool isPressed(const int& key)
	{
		return ((this->isKeyDown(key)) && ((this->m_prevKeyboardState[key] & 0x80) == 0));
	}
private:
	BYTE m_prevKeyboardState[256];	//直前のキーボード状態
	BYTE m_curKeyboardState[256];	//現在のキーボード状態
};

#endif // _INPUT_H_