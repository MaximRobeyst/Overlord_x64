float4x4 gWorldViewProj : WORLDVIEWPROJECTION;
TextureCube gCubeTexture;

struct VS_INPUT {
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
};
struct VS_OUTPUT {
	float4 pos : SV_POSITION;
	float3 uv : TEXCOORD;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;// or Mirror or Clamp or Border
    AddressV = Wrap;// or Mirror or Clamp or Border
};


RasterizerState NoCulling
{
	CullMode = NONE;
};

DepthStencilState DepthState
{
    DepthFunc = LESS_EQUAL;
};

VS_OUTPUT VS(VS_INPUT input) {
	VS_OUTPUT output;
	output.pos = mul(float4(input.pos, 1.0f), gWorldViewProj).xyww;
	output.uv = input.pos;

	return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET{

    return gCubeTexture.Sample(samLinear, input.uv);
}

technique11 Default
{
	pass P0
	{
		SetRasterizerState(NoCulling);
		SetDepthStencilState(DepthState, 0);

		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}
