float4x4 gWorldViewProj;
Texture2D gTexture;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

/// Create Depth Stencil State (ENABLE DEPTH WRITING)
DepthStencilState EnableDepth
{
    DepthEnable = TRUE;
    DepthWriteMask = ALL;
};

/// Create Rasterizer State (Backface culling) 
RasterizerState backfaceCulling
{
    CullMode = BACK;
};


//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};

PS_INPUT SSAO_VS(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT)0;
	output.Position = float4(input.Position,1.0);
    output.TexCoord = input.TexCoord;


    return output;
}

float4 SSAO_PS(PS_INPUT input) : SV_Target
{
	uint width;
	uint height;
	gTexture.GetDimensions(width,height);
    
	float dx = 1.0 / width;
	float dy = 1.0 / height;

    return gTexture.Sample(samPoint, float2(input.TexCoord.x, input.TexCoord.y));
}

technique11 GenerateAmbientOcclusion
{
    pass P0
    {
        SetRasterizerState(backfaceCulling);
        SetDepthStencilState(EnableDepth, 0);
		SetVertexShader(CompileShader(vs_4_0, SSAO_VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, SSAO_PS()));
    }
}

