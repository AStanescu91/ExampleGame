cbuffer cbVSPerFrame
{
	float4x4 worldViewProj;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	output.position = mul(position, worldViewProj);
	output.color = color;

	return output;
}