
struct VSO
{
	float4 p : SV_POSITION;
	float3 c : COLOR;
};

float4 PS(VSO i) : SV_Target
{
	return float4(i.c.r, i.c.g, i.c.b, 1.0f);
}

