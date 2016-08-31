/*!
 * @brief	スキンモデルシェーダー。(4ボーンスキニング)
 */

bool Texflg;

//スキン行列。
#define MAX_MATRICES  50
float4x3    g_mWorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;

float4x4 g_worldMatrix;					//ワールド行列。
float4x4 g_viewMatrix;					//ビュー行列。
float4x4 g_projectionMatrix;			//プロジェクション行列。
float4x4 g_rotationMatrix;				//回転行列。法線を回転させるために必要になる。ライティングするなら必須。

float		g_numBone;			//骨の数。

#define DIFFUSE_LIGHT_NUM	4		//ディフューズライトの数。
float4	g_diffuseLightDirection[DIFFUSE_LIGHT_NUM];	//ディフューズライトの方向。
float4	g_diffuseLightColor[DIFFUSE_LIGHT_NUM];		//ディフューズライトのカラー。
float4	g_ambientLight;								//環境光。
float4  g_diffuseMaterial : COLOR0;					//マテリアルカラー

texture g_diffuseTexture;		//ディフューズテクスチャ。
sampler g_diffuseTextureSampler = 
sampler_state
{
	Texture = <g_diffuseTexture>;
    MipFilter = NONE;
    MinFilter = NONE;
    MagFilter = NONE;
    AddressU = Wrap;
	AddressV = Wrap;
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


/*!
 * @brief	入力頂点
 */
struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float3  Normal          : NORMAL;
    float3  Tex0            : TEXCOORD0;
	float4	color	: COLOR0;
};

/*!
 * @brief	出力頂点。
 */
struct VS_OUTPUT
{
	float4  Pos     : POSITION;
    float3  Normal	: NORMAL;
    float2  Tex0    : TEXCOORD0;
	float4	color	: COLOR0;
	float4  PosWVP	: TEXCOORD5;
};

VS_OUTPUT VSMain( VS_INPUT In )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	
	//ブレンドするボーンのインデックス。
	int4 IndexVector = D3DCOLORtoUBYTE4(In.BlendIndices);
	
	//ブレンドレート。
	float BlendWeightsArray[4] = (float[4])In.BlendWeights;
    int   IndexArray[4]        = (int[4])IndexVector;
    float LastWeight = 0.0f;
    float3 Pos = 0.0f;
    float3 Normal = 0.0f;
	//ボーン数ループ?
    for (int iBone = 0; iBone < g_numBone-1; iBone++)
    {
        LastWeight = LastWeight + BlendWeightsArray[iBone];
        
        Pos += mul(In.Pos, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        Normal += mul(In.Normal, g_mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
    }
    LastWeight = 1.0f - LastWeight; 

    //？？
	Pos += (mul(In.Pos, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);
    Normal += (mul(In.Normal, g_mWorldMatrixArray[IndexArray[g_numBone-1]]) * LastWeight);

	//ワールド行列
	//Pos = mul(float4(Pos.xyz, 1.0f), g_worldMatrix);
	//ビュー行列
	Pos = mul(float4(Pos.xyz, 1.0f), g_viewMatrix);
	//プロジェクション行列
	o.Pos = mul(float4(Pos.xyz, 1.0f), g_projectionMatrix);
	o.PosWVP = o.Pos;

	//法線ベクトル正規化
	Normal = normalize(Normal);
	o.Normal = mul(Normal, g_rotationMatrix);	//法線を回す。

    o.Tex0 = In.Tex0;
	o.color = In.color;

	return o;
}

struct PS_OUTPUT
{
	float4 color0 : COLOR0;		//色
	float4 color1 : COLOR1;		//深度
	float4 color2 : COLOR2;		//深度(調整)
};

/*!
 * @brief	ピクセルシェーダー。
 */
PS_OUTPUT PSMain( VS_OUTPUT In )
{
	PS_OUTPUT output = (PS_OUTPUT)0;
	//カラー
	if (Texflg)
	{
		output.color0 = tex2D(g_diffuseTextureSampler, In.Tex0);
	}
	else
	{
		output.color0 = g_diffuseMaterial;
	}

	//デフューズライトを計算。
	{
		float4 dif = 0.0f;

		for (int i = 0; i < DIFFUSE_LIGHT_NUM; i++){
			//0.0f未満なら0.0fを返す
			dif.xyz += max(0.0f, dot(In.Normal.xyz, -g_diffuseLightDirection[i].xyz))
				* g_diffuseLightColor[i].xyz;
		}
		dif += g_ambientLight;

		output.color0.xyz *= dif.xyz;
	}

	//深度計算
	float Depth = (In.PosWVP.z / In.PosWVP.w);

	output.color1 = Depth;

	if (0.0f <= Depth && Depth < 0.25f)
	{
		output.color2.a = 4 * Depth;
	}
	else if (0.25f < Depth && Depth < 0.75f)
	{
		output.color2.a = 1.0f;
	}
	else if (0.75f < Depth && Depth <= 1.0f)
	{
		output.color2.a = 4 * (1 - Depth);
	}

	return output;
}

technique NormalRender
{
    pass p0
    {
        VertexShader = compile vs_3_0 VSMain();
        PixelShader = compile ps_3_0 PSMain();
    }
}
