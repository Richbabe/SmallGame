cbuffer DataBuffer : register(b0)
{
	float4 sizeCoord;
};
struct VertexInputType
{
	float4 position : POSITION;
	float2 color : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

PixelInputType main( VertexInputType input) 
{
	PixelInputType output=(PixelInputType)0;

	input.position.xy *= sizeCoord.xy;
	input.position.xy += sizeCoord.zw;

	output.position = input.position;
	output.tex = input.color.xy;

	return output;
}