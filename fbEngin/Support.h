


#ifndef _SUPPORT_H_
#define _SUPPORT_H_

//メモリーリーク自動検出
//#if _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

//便利な関数を定義
class Support
{
public:
	//整数をstring型の文字列に変換
	//戻り値：文字列のポインタ(配列)
	//第一引数：string* 格納先ポインタ,第二引数：int 変換したい整数
	static void IntToString(string* s, int dnum)
	{
		vector<char> wst;
		//文字コード変換
		do
		{
			//1桁目
			short n = dnum % 10;
			//文字コード変換
			char wc = n + '0';
			//登録
			wst.push_back(wc);
			//次の桁へ
			dnum /= 10;
		} while (dnum != 0);

		//文字全消し
		s->clear();

		//順番が逆のなので、正しくする
		short i, j;
		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			s->push_back(wst[i]);
		}
		//終端文字
		//s = s + '\0';

	}
	//整数をWCHAR型の文字列に変換
	//戻り値：文字列のポインタ(配列)
	//第一引数：WCHAR* 格納先ポインタ,第二引数：int 変換したい整数
	static void IntToWchar(WCHAR* ws, int dnum)
	{
		vector<WCHAR> wst;
		//文字コード変換
		do
		{
			//1桁目
			short n = dnum % 10;
			//文字コード変換
			WCHAR wc = n + '0';
			//登録
			wst.push_back(wc);
			//次の桁へ
			dnum /= 10;
		} while (dnum != 0);

		//順番が逆のなので、正しくする
		short i, j;
		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			ws[i] = wst[j];
		}
		//終端文字
		ws[i] = '\0';
	}

	//実数をWCHAR型の文字列に変換
	//第一引数：WCHAR* 文字列を格納する配列,第二引数：double 変換したい実数,第三引数：short 小数点のどこまで表示するか = 1
	static void FloatToWchar(WCHAR* ws,double fnum,short n = 1)
	{

		for (short l = 0; l < n; l++)
		{
			fnum *= 10;
		}
		//整数化 + 四捨五入
		UINT64 s = (UINT64)(fnum + 0.5f);

		vector<WCHAR> wst;
		//文字コード変換
		do
		{
			//1桁目
			short n = s % 10;
			//文字コード変換
			WCHAR wc = n + '0';
			//登録
			wst.push_back(wc);
			//次の桁へ
			s /= 10;
		} while (s != 0);
		
		//順番が逆のなので、正しくする
		short i, j;

		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			//小数点の位置に来たら
			if (i == wst.size() - n)
			{
				//ドットを入れる
				ws[i] = '.';
				//添え字を進める
				i++;
			}
			ws[i] = wst[j];
		}
		wst.clear();
		//終端文字
		ws[i] = '\0';
	}

	//第一引数に第二引数の文字列を結合しする
	//文字列のポインタ
	static void LinkingWchar(WCHAR* w1, WCHAR* w2)
	{
		short n1 = 0, n2 = 0;
		//文字数を調べる
		while (w1[++n1] != '\0');
		while (w2[++n2] != '\0');
		short i;
		for (i = 0; i < n2; i++)
		{
			w1[n1 + i] = w2[i];
		}
		//終端文字
		w1[n1 + i] = '\0';
	}


	//ハッシュ生成
	//元は37
#define HASH_NUM 12

	//文字列からハッシュ値を作成
	//引数:const char* 文字列
	//戻り値：UINT64 ハッシュ値(32bit)
	static UINT64 MakeHash(const char* string)
	{
		UINT64 hash = 0;
		int l = strlen(string);
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + string[i];
		}
		return hash;
	}

	//文字列からハッシュ値を作成
	//引数:const WCHAR* 文字列
	//戻り値：UINT64 ハッシュ値(32bit)
	static UINT64 MakeHash(const WCHAR* string)
	{
		UINT64 hash = 0;
		int l = 0;
		while (string[++l] != '\0');
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + string[i];
		}
		return hash;
	}

	//文字列からハッシュ値を作成
	//引数:string 文字列
	//戻り値：UINT64 ハッシュ値
	static UINT64 MakeHash(string st)
	{
		UINT64 hash = 0;
		int l = st.size();
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + st[i];
		}
		return hash;
	}
};

#endif //_SUPPORT_H_