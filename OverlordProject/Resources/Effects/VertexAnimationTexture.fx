// https://www.youtube.com/watch?v=NQ5Dllbxbz4
float4x4 gWorld : WORLD;
float4x4 gWorldViewProj : WORLDVIEWPROJECTION; 
float3 gLightDirection = float3(-0.577f, -0.577f, 0.577f);

Texture2D gDiffuseMap;
Texture2D gPositionMap;
Texture2D gNormalMap;

float gTextureWidth;
float gNumberOfFrames= 30;
float gCurrentFrame = 0;

struct VS_INPUT{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};
struct VS_OUTPUT{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};

DepthStencilState EnableDepth
{
	DepthEnable = TRUE;
	DepthWriteMask = ALL;
};

RasterizerState NoCulling
{
	CullMode = NONE;
};

BlendState NoBlending
{
	BlendEnable[0] = FALSE;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    float pixel = 1.0 / gTextureWidth;
    float halfPixel = pixel * 0.5;
    float framePixelSize = 1 / gNumberOfFrames;

    float2 samplePosition = float2(halfPixel, ((gCurrentFrame + 0.5) * framePixelSize));
    float4 PositionSample = gPositionMap[int2(samplePosition.x, samplePosition.y)];

    float3 position = input.pos + PositionSample.xyz;
    output.pos = float4(position, 1.0);
    output.pos = mul(output.pos, gWorldViewProj);

    output.normal = input.normal; //+ gNormalMap.Sample(samLinear, float2(halfPixel, -((gCurrentFrame + 0.5) * framePixelSize))).xyz;
    output.texCoord = input.texCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET{

	float4 diffuseColor = gDiffuseMap.Sample( samLinear,input.texCoord );
	float3 color_rgb= diffuseColor.rgb;
	float color_a = diffuseColor.a;
	
	//HalfLambert Diffuse :)
	float diffuseStrength = dot(input.normal, -gLightDirection);
	diffuseStrength = diffuseStrength * 0.5 + 0.5;
	diffuseStrength = saturate(diffuseStrength);
	color_rgb = color_rgb * diffuseStrength;

	return float4( color_rgb , color_a );
}

technique11 Default
{
    pass P0
    {
		SetRasterizerState(NoCulling);
		SetDepthStencilState(EnableDepth, 0);
		SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader( CompileShader( vs_4_0, VS() ) );
		SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}