// https://www.gamedeveloper.com/programming/shader-tutorial-crt-emulation
// https://babylonjs.medium.com/retro-crt-shader-a-post-processing-effect-study-1cb3f783afbc

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

Texture2D gTexture;
float gLineOpacity1 = 1.25f;
float gLineOpacity2 = 0.1f;

float gBrightness = 1.f;
float gVignetteRoundness = 10.f;
float gVignetteOpacity = 3.5f;

float2 gCurvature = float2(15.0f, 15.0f);

float gPI = 3.141592f;

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

//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	// Set the Position
	output.Position = float4(input.Position,1.0);
	// Set the TexCoord
	output.TexCoord = input.TexCoord;
	
	return output;
}

float2 curveUV(float2 uv)
{
    uv = uv * 2.0f - 1.0f;
    float2 offset = abs(uv.yx) / gCurvature;
    uv = uv + uv * offset * offset;
    uv = uv * 0.5 + 0.5;
    return uv;
}

float4 scanlineIntensity(float uv, float resolution, float opacity)
{
    float intensity = sin(uv * resolution * gPI * 2.0f);
    intensity = ((0.5 * intensity) + 0.5) * 0.9 + 0.1;

    float power = pow(intensity, opacity);
    return float4(power, power, power, 1.0);
}

float4 vignetteIntensity(float2 uv, float2 resolution, float opacity, float roundness)
{
    float intensity = uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y);
    float power = saturate(pow((resolution.x / roundness) * intensity, opacity));
    return float4(power, power, power, 1.0);
}

//PIXEL SHADER
//------------
float4 PS(PS_INPUT input): SV_Target
{
    uint width;
    uint height;
    gTexture.GetDimensions(width, height);

    float2 remappedUv = curveUV(input.TexCoord);
    if(remappedUv.x < 0.0f || remappedUv.y < 0.0f || remappedUv.x > 1.0f || remappedUv.y > 1.0f)
        return float4(0.0f, 0.0f, 0.0f, 1.0f);

    float4 baseColor = gTexture.Sample(samPoint, remappedUv);

    baseColor *= vignetteIntensity(remappedUv, float2(width, height), gVignetteOpacity, gVignetteRoundness);

    baseColor *= scanlineIntensity(remappedUv.x, (float)height,gLineOpacity1);
    baseColor *= scanlineIntensity(remappedUv.y, (float)width, gLineOpacity2);
    baseColor *= float4(gBrightness, gBrightness, gBrightness, 1.0f);

    return baseColor;

    //float2 screenPosition = float2(input.TexCoord.x * width, input.TexCoord.y * height);
//
    //float2 newUVs = curveUV(input.TexCoord);
    //if(newUVs.x < 0.0f || newUVs.y < 0.0f || newUVs.x > 1.0f || newUVs.y > 1.0f)
    //    return float4(0.0f, 0.0f, 0.0f, 1.0f);
//
    //float3 color = gTexture.Sample(samPoint, newUVs).rgb;
    //float3 finalColor = float3(0,0,0);
    //float3 muls = float3(0,0,0);
//
    //int pp = (int)screenPosition.x % 3;
    //if(pp == 1) 
    //{
    //    muls.r = color.r;
    //    muls.g = gFillColor2;
//
    //}
    //else if(pp == 2)
    //{
    //    muls.g = color.g;
    //    muls.b = gFillColor2;
    //} 
    //else 
    //{
    //    muls.b = color.b;
    //    muls.r = gFillColor2;
    //}
    //if((int)screenPosition.y % 3 == 0) muls *= float4(gScansColor, gScansColor, gScansColor, 1);
//
    //color = color * muls;
    //color += (gBrightness / 255);
    //color = color - gContrast * (color - 1.0) * color * (color - 0.5);
//
//
    //return float4(color, 1.0);
}


//TECHNIQUE
//---------
technique11 Blur
{
    pass P0
    {
        SetRasterizerState(backfaceCulling);
        SetDepthStencilState(EnableDepth, 0);
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    }
}