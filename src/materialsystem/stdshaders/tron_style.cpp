#include "BaseVSShader.h" 
#include "tron_style_ps20.inc"
#include "tron_style_vs20.inc"
 
BEGIN_VS_SHADER( Tron_Style, "Help for Tron_Style" )
 
BEGIN_SHADER_PARAMS
   SHADER_PARAM( FBTEXTURE, SHADER_PARAM_TYPE_TEXTURE, "_rt_FullFrameFB", "" )
END_SHADER_PARAMS
 
// Set up anything that is necessary to make decisions in SHADER_FALLBACK.
SHADER_INIT_PARAMS()
{
}
 
SHADER_FALLBACK
{
  return 0;
}
 
SHADER_INIT
{
  if( params[FBTEXTURE]->IsDefined() )
  {
   LoadTexture( FBTEXTURE );
  }
}
 
SHADER_DRAW
{
  SHADOW_STATE
  {
   pShaderShadow->EnableDepthWrites( false );
 
   pShaderShadow->EnableTexture( SHADER_SAMPLER0, true );
   int fmt = VERTEX_POSITION;
   pShaderShadow->VertexShaderVertexFormat( fmt, 1, 0, 0 );
 
   DECLARE_STATIC_PIXEL_SHADER( tron_style_ps20 );
   SET_STATIC_PIXEL_SHADER( tron_style_ps20 );
 
   DECLARE_STATIC_VERTEX_SHADER( tron_style_vs20 );
   SET_STATIC_VERTEX_SHADER( tron_style_vs20 );
 
  }
  DYNAMIC_STATE
  {
   BindTexture( SHADER_SAMPLER0, FBTEXTURE, -1 );
   DECLARE_DYNAMIC_PIXEL_SHADER( tron_style_ps20 );
   SET_DYNAMIC_PIXEL_SHADER( tron_style_ps20 );
 
   DECLARE_DYNAMIC_VERTEX_SHADER( tron_style_vs20 );
   SET_DYNAMIC_VERTEX_SHADER( tron_style_vs20 );
  }
  Draw();
}

END_SHADER