struct VS_INPUT
{
        float4 pos : POSITION
        float4 color : COLOR
};

float4 vsmain(VS_INPUT input ) : SV_POSITION
{
        return pos;
}

 float4 psmain(VS_INPUT input ) : SV_Target
 {
        return float4(0.8f,0.9f, 0.4f, 1.0f );   
 }