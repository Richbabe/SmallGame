Texture2D gTex;
SamplerState gSampler;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


float4 main(PixelInputType input) : SV_TARGET
{
	return gTex.Sample(gSampler, input.tex);
}