float4 vsmain(float4 pos : POSITION) : SV_POSITION
{
        return pos;
}

 float4 psmain(float4 pos : SV_POSITION) : SV_Target
 {
        return float4(0.5f, 0.2f, 0.3f, 1.0f );   
 }