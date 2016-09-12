/*!
 *@brief	3Dモデルの描画
 */
bool g_Texflg;							//テクスチャ
bool Toonflg;							//トゥーンシェーダ
bool Specflg;							//スペキュラーライト
bool Fresnelflg;						//フレネル反射
bool Shadowflg;							//シャドウフラグ

float4x4 g_rotationMatrix;				//回転行列。法線を回転させるために必要になる。ライティングするなら必須。
float4x4 g_worldMatrix;					//ワールド行列。
float4x4 g_viewMatrix;					//ビュー行列。
float4x4 g_projectionMatrix;			//プロジェクション行列。

float4x4 g_viewMatrixRotInv;			 //カメラの回転行列の逆行列

float4	 g_eyePos;						//視点。
float4x4 g_LVP;							//ライトのビュープロジェクション行列

texture g_LVPTex;				//テクスチャ。
sampler g_LVPTexSampler =
sampler_state
{
	Texture = <g_LVPTex>;
	MipFilter = NONE;
	MinFilter = NONE;
	MagFilter = NONE;
	AddressU = Clamp;			//繰り返さないようにする
	AddressV = Wrap;
};


#define DIFFUSE_LIGHT_NUM	4			//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;								//環境光。

float4  g_blendColor;			//混ぜる色(倍率)

float4  g_diffuseMaterial;		//マテリアルカラー

texture g_Texture;				//テクスチャ。
sampler g_TextureSampler = 
sampler_state
{
	Texture = <g_Texture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

float4 g_toonLight;				//toonライト
texture g_toonTexture;			//toonテクスチャ
sampler g_toonTextureSampler =
sampler_state
{
	Texture = <g_toonTexture>;
	AddressU = Wrap;
	AddressV = Wrap;
};

//頂点情報構造体

struct VS_INPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float3	normal	: NORMAL0;
	float2	uv		: TEXCOORD0;
};

struct VS_OUTPUT{
	float4	pos		: POSITION;
	float4	color	: COLOR0;
	float2	uv		: TEXCOORD0;
	float3	normal	: TEXCOORD1;
	float4	worldPos: TEXCOORD2;	//ワールド空間での頂点座標。
	float4  posWVP	: TEXCOORD3;	//深度出すためのポジション,posを使うと怒られたため仕方なく作った
	float4  ZCalcTex : TEXCOORD4;	// Z値算出用テクスチャ
};

/*!
 *@brief	頂点シェーダー。
 */
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	float4 pos;
	//モデルのローカル空間からワールド空間に変換。
	pos = mul( In.pos, g_worldMatrix );

	//ワールド座標の時のポジション保持
	Out.worldPos = pos;

	pos = mul( pos, g_viewMatrix );			//ワールド空間からビュー空間に変換。
	pos = mul( pos, g_projectionMatrix );	//ビュー空間から射影空間に変換。

	if (Shadowflg)
	{
		Out.ZCalcTex = mul(In.pos, g_worldMatrix);	 // ライトの目線によるワールドビュー射影変換をする
		Out.ZCalcTex = mul(Out.ZCalcTex, g_LVP);	 // ライトの目線によるワールドビュー射影変換をする
	}
	
	Out.pos = pos;
	Out.posWVP = Out.pos;
	Out.color = In.color;
	Out.uv = In.uv;
	Out.normal = mul( In.normal, g_rotationMatrix );	//法線を回す。
	
	return Out;
}

struct PS_OUTPUT
{
	float4 color0 : COLOR0;		//色
	float4 color1 : COLOR1;		//深度
	float4 color2 : COLOR2;		//深度(調整)
};
/*!
 *@brief	ピクセルシェーダー。
 */
PS_OUTPUT PSMain(VS_OUTPUT In)
{
	PS_OUTPUT color = (PS_OUTPUT)0;
	//テクスチャの有無
	if (g_Texflg){
		//uvに張り付け
		color.color0 = tex2D(g_TextureSampler, In.uv);
	}
	else
	{
		//マテリアルのカラーにする。
		color.color0 = g_diffuseMaterial;
	}

	//デフューズライトを計算。
	{
		float4 dif = 0.0f;
		{
			for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
				//0.0f未満なら0.0fを返す
				dif.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
					* g_diffuseLightColor[i].xyz;
			}
			dif += g_ambientLight;
		}
		color.color0.xyz *= dif.xyz;
	}

	//スペキュラーライト
	if (Specflg)
	{
		float3 spec = 0.0f;
			float3 toEyeDir = normalize(g_eyePos.xyz - In.worldPos);
			float3 R = -toEyeDir + 2.0f * dot(In.normal, toEyeDir) * In.normal;
		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			//スペキュラ成分を計算する。
			//反射ベクトルを計算。
			float3 L = -g_diffuseLightDirection[i].xyz;
				spec += g_diffuseLightColor[i] * pow(max(0.0f, dot(L, R)), 10) * g_diffuseLightColor[i].w;	//スペキュラ強度。
		}
		color.color0.xyz += spec.xyz;
	}

	//フレネル反射
	if (Fresnelflg)
	{
		//ファーライティングを計算。
		//法線をカメラ座標系に変換する。
		float3 normalInCamera = mul(In.normal, g_viewMatrixRotInv);
			float f = 1.0f - abs(dot(normalInCamera, float3(0.0f, 0.0f, 1.0f)));
		//数値が小さいほど反射する
		f = pow(f, 2.0f);
		color.color0 += f;
	}

	//トゥーンレンダリング
	if (Toonflg)
	{
		//ハーフランバート拡散照明によるライティング計算
		float p = dot(In.normal.xyz, -g_toonLight.xyz);
		p = p * 0.5f + 0.5f;
		p = p * p;

		//****************************************************************
		//トゥーンシェーダー処理
		//****************************************************************
		//色情報をテクセルのＵ成分とし、トゥーンマップテクスチャーから光の反射率を取得する
		float4 toon = tex2D(g_toonTextureSampler, float2(p, 0.0f));

			//色情報を格納する
			color.color0 *= toon;
	}

	color.color0 *= g_blendColor;

	//デプスシャドウ
	if (Shadowflg)
	{

		// ライト目線によるZ値の再算出
		float ZValue = In.ZCalcTex.z / In.ZCalcTex.w;

		// 射影空間のXY座標をテクスチャ座標に変換
		float2 TransTexCoord;
		TransTexCoord.x = (1.0f + In.ZCalcTex.x / In.ZCalcTex.w)*0.5f;
		TransTexCoord.y = (1.0f + (-In.ZCalcTex.y) / In.ZCalcTex.w)*0.5f;

		if (TransTexCoord.x <= 1.0f && TransTexCoord.y <= 1.0f)
		{
			// リアルZ値抽出
			float SM_Z = tex2D(g_LVPTexSampler, TransTexCoord).x;

			// 算出点がシャドウマップのZ値よりも大きければ影と判断
			if (ZValue > SM_Z + 0.005f){
				color.color0.rgb = color.color0.rgb * 0.5f;
			}
		}
	}

	//深度計算(RenderTarget1に出力される)
	float Depth = In.posWVP.z / In.posWVP.w;

	color.color1 = Depth;
	color.color1.a = 1.0f;
	//調整した深度
	if (0.0f <= Depth && Depth < 0.25f)
	{
		color.color2.a = 4 *  Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		color.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		color.color2.a = 4 * (1 - Depth);
	}
	
	//if (true){

	//	//αに輝度を埋め込む。
	//	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//	if (luminance > 1.0f){
	//		luminance = 1.0f / luminance;
	//	}
	//	else{
	//		luminance = 1.0f;
	//	}

	//	color.a = luminance;
	//}
	//else{
	//	color.a = 1.0f;
	//}


	//半透明合成
	return color;
}

PS_OUTPUT PSMainMini(VS_OUTPUT In)
{
	PS_OUTPUT color = (PS_OUTPUT)0;
	//テクスチャの有無
	if (g_Texflg){
		//uvに張り付け
		color.color0 = tex2D(g_TextureSampler, In.uv);
	}
	else
	{
		//マテリアルのカラーにする。
		color.color0 = g_diffuseMaterial;
	}

	//デフューズライトを計算。
	{
		float4 dif = 0.0f;
		{
			for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
				//0.0f未満なら0.0fを返す
				dif.xyz += max(0.0f, dot(In.normal.xyz, -g_diffuseLightDirection[i].xyz))
					* g_diffuseLightColor[i].xyz;
			}
			dif += g_ambientLight;
		}
		color.color0.xyz *= dif.xyz;
	}

	//深度計算(RenderTarget1に出力される)
	float Depth = In.posWVP.z / In.posWVP.w;

	color.color1 = Depth;
	color.color1.a = 1.0f;
	//調整した深度
	if (0.0f <= Depth && Depth < 0.25f)
	{
		color.color2.a = 4 * Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		color.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		color.color2.a = 4 * (1 - Depth);
	}

	//if (true){

	//	//αに輝度を埋め込む。
	//	float luminance = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	//	if (luminance > 1.0f){
	//		luminance = 1.0f / luminance;
	//	}
	//	else{
	//		luminance = 1.0f;
	//	}

	//	color.a = luminance;
	//}
	//else{
	//	color.a = 1.0f;
	//}


	//半透明合成
	return color;
}

/*!
*@brief	エッジ用頂点シェーダー。
*/
float4 VSEdge(VS_INPUT In) : POSITION
{
	float4 pos = In.pos;
	//法線の方向に広げる(エッジの幅となる)


	In.normal = mul(In.normal, g_rotationMatrix);	//法線を回す。
	pos.xyz += In.normal.xyz * 1.0f;			//法線方向に大きく

	pos = mul(pos, g_worldMatrix);		//モデルのローカル空間からワールド空間に変換。
	pos = mul(pos, g_viewMatrix);			//ワールド空間からビュー空間に変換。
	pos = mul(pos, g_projectionMatrix);	//ビュー空間から射影空間に変換。

	return pos;
}
/*!
*@brief	エッジ用ピクセルシェーダー。
*/
float4 PSEdge() : COLOR0
{
	//真っ黒
	return float4(0.0f, 0.0f, 0.0f, 1.0f);
}

////////////////////////////
//テクニック

//普通に描画する用
technique NormalRender
{
	pass p0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}

	pass p1
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMainMini();
	}
}

//エッジ用
technique EdgeRender
{
	pass p0
	{
		VertexShader = compile vs_2_0 VSEdge();
		PixelShader = compile ps_2_0 PSEdge();
	}
}