  /*-------------------------.   
  | :: Defining constants :: |
  '-------------------------*/

//These values are normally defined by the injector dlls, but not when analyzed by GPU Shaderanalyzer
//I need to ensure they always have a value to be able to compile them whenever I'm not using the injector.
#ifdef SMAA_PIXEL_SIZE
  #ifndef BUFFER_RCP_WIDTH
    #define BUFFER_RCP_WIDTH SMAA_PIXEL_SIZE.x
    #define BUFFER_RCP_HEIGHT SMAA_PIXEL_SIZE.y
    #define BUFFER_WIDTH (1.0 / SMAA_PIXEL_SIZE.x)
    #define BUFFER_HEIGHT (1.0 / SMAA_PIXEL_SIZE.y)
  #endif
#endif

#ifndef BUFFER_RCP_WIDTH
  #define BUFFER_RCP_WIDTH (1.0 / 1680)
  #define BUFFER_RCP_HEIGHT (1.0 / 1050)
  #define BUFFER_WIDTH 1680
  #define BUFFER_HEIGHT 1050
#endif

#define screen_size float2(BUFFER_WIDTH,BUFFER_HEIGHT)

#define px BUFFER_RCP_WIDTH
#define py BUFFER_RCP_HEIGHT

#define pixel float2(px,py)

// -- Define DirectX9 FXAA specific aliases --
#if FXAA_HLSL_3 == 1
  #define myTex2D(s,p) tex2D(s,p)
  
  #define s0 frameSampler
  #define s1 frameSampler
#endif

// -- Define DirectX10/11 specific aliases --
#if FXAA_HLSL_4 == 1 || FXAA_HLSL_5 == 1
  #define myTex2D(s,p) s.SampleLevel(LinearSampler, p, 0)
  
  #define s0 frameTex2D
  #define s1 frameTex2D
#endif

// -- Define DirectX9 specific aliases --
#if SMAA_HLSL_3 == 1
  #define myTex2D(s,p) tex2D(s,p)
  
  #define s0 colorTexG
  #define s1 colorTexG //TODO make a nearest sampler if needed
#endif

// -- Define DirectX10/11 specific aliases --
#if SMAA_HLSL_4 == 1 || SMAA_HLSL_4_1 == 1
  #define myTex2D(s,p) s.SampleLevel(LinearSampler, p, 0)

  #define s0 colorTexGamma
  #define s1 colorTexGamma //TODO make a nearest sampler if needed
#endif


  /*------------------------------.   
  | :: Include enabled shaders :: |
  '------------------------------*/
  
  
#if (USE_CUSTOM == 1)
  #include "SweetFX\Shaders\Custom.h"
  #define Need_sRGB 1
#endif
  
#if (USE_CARTOON == 1)
  #include "Cartoon.h"
#endif  

#if (USE_ADVANCED_CRT == 1)
  #include "AdvancedCRT.h"
#endif

#if (USE_EXPLOSION == 1)
  #include "SweetFX\Shaders\Explosion.h"
  #define Need_sRGB 1
#endif

#if (USE_CA == 1)
    #include "SweetFX\Shaders\ChromaticAberration.h"
#endif

#if (USE_BLOOM == 1)
  #include "Bloom.h"
#endif

#if (USE_HDR == 1)
  #include "HDR.h"
#endif

#if (USE_LUMASHARPEN == 1)
  #include "LumaSharpen.h"
#endif

#if (USE_LEVELS == 1)
  #include "SweetFX\Shaders\Levels.h"
  #define Need_sRGB 1
#endif

#if (USE_TECHNICOLOR == 1)
  #include "Technicolor.h"
#endif

#if (USE_DPX == 1)
  #include "DPX.h"
#endif

#if (USE_MONOCHROME == 1)
  #include "Monochrome.h"
#endif

#if (USE_LIFTGAMMAGAIN == 1)
  #include "LiftGammaGain.h"
#endif

#if (USE_TONEMAP == 1)
  #include "Tonemap.h"
#endif

#if (USE_SEPIA == 1)
  #include "Sepia.h"
#endif

#if (USE_VIBRANCE == 1)
  #include "Vibrance.h"
#endif

#if (USE_CURVES == 1)
  #include "Curves.h"
#endif

#if (USE_VIGNETTE == 1)
  #include "Vignette.h"
#endif

#if (USE_DITHER == 1)
  #include "Dither.h"
#endif

#if (USE_BORDER == 1)
  #include "Border.h"
#endif

#if (USE_SPLITSCREEN == 1)
  #include "Splitscreen.h"
#endif

  /*-------------------------------.   
  | :: Xbox360 Gamma correction :: |
  '-------------------------------*/

/*
  I suspect that some games that ported to PC are such terrible ports that the developers forgot (or didn't bother)
  to do correct gamma correction for PC but just copied the Xbox360 code.
  
  If that is the case then I can probably correct for it, but I need to find some terrible ports and check for this first.
  Until then this code is not used.
*/

//float XenonGammaToLinear(float val)
//{
//   float ret;
//   saturate(val);
//   if (val < 0.25f)
//      ret = 0.25f * val;
//   else if (val < 0.375f)
//      ret = (1.0f/16.0f) + 0.5f*(val-0.25f);
//   else if (val < 0.75f)
//      ret = 0.125f + 1.0f*(val-0.375f);
//   else
//      ret = 0.5f + 2.0f*(val-0.75f);
//   return ret;
//}
//
//float LinearToXenonGamma(float val)
//{
//   float ret;
//   saturate(val);
//   if (val < (1.0f/16.0f))
//      ret = 4.0f * val;
//   else if (val < (1.0f/8.0f))
//      ret = (1.0f/4.0f) + 2.0f*(val-(1.0f/16.0f));
//   else if (val < 0.5f)
//      ret = 0.375f + 1.0f*(val-0.125f);
//   else
//      ret = 0.75f + 0.5f*(val-0.50f);
//   return ret;
//}

  /*--------------------.   
  | :: Effect passes :: |
  '--------------------*/

float4 main(float2 tex, float4 FinalColor)
{

 // #if (Xbox360gamma == 1)
 //   FinalColor.r = LinearToXenonGamma(FinalColor.r); // Linear to Xbox360 Gamma space (R)
 //   FinalColor.g = LinearToXenonGamma(FinalColor.g); // Linear to Xbox360 Gamma space (G)
 //   FinalColor.b = LinearToXenonGamma(FinalColor.b); // Linear to Xbox360 Gamma space (B)
	//#endif

  /*--------------------.   
  | :: Effect passes :: |
  '--------------------*/
    
  // Custom
  #if (USE_CUSTOM == 1)
    FinalColor = CustomPass(FinalColor,tex);
  #endif
  
  // Explosion
  #if (USE_EXPLOSION == 1)
    FinalColor = ExplosionPass(FinalColor,tex);
  #endif

  // Chromatic Aberration	
  #if (USE_CA == 1)
	FinalColor = CAPass(FinalColor,tex);
  #endif
  
  // Cartoon
  #if (USE_CARTOON == 1)
	FinalColor = CartoonPass(FinalColor,tex);
  #endif

  // Advanced CRT
  #if (USE_ADVANCED_CRT == 1)
	FinalColor = AdvancedCRTPass(FinalColor,tex);
  #endif

  // SweetCRT
  #if (USE_SWEETCRT == 1)
    FinalColor = SweetCRTPass(FinalColor,tex);
  #endif  
  
  // Bloom
  #if (USE_BLOOM == 1)
	FinalColor = BloomPass (FinalColor,tex);
  #endif
	
  // HDR
  #if (USE_HDR == 1)
	FinalColor = HDRPass (FinalColor,tex);
  #endif
	
  // LumaSharpen
  #if (USE_LUMASHARPEN == 1)
	FinalColor = LumaSharpenPass(FinalColor,tex);
  #endif

  // Levels
  #if (USE_LEVELS == 1)
	FinalColor = LevelsPass(FinalColor);
  #endif
  
  // Technicolor
  #if (USE_TECHNICOLOR == 1)
	FinalColor = TechnicolorPass(FinalColor);
  #endif
	
  // DPX
  #if (USE_DPX == 1)
	FinalColor = DPXPass(FinalColor);
  #endif
  
  // Monochrome
  #if (USE_MONOCHROME == 1)
	FinalColor = MonochromePass(FinalColor);
  #endif
	
  // Lift Gamma Gain
  #if (USE_LIFTGAMMAGAIN == 1)
	FinalColor = LiftGammaGainPass(FinalColor);
  #endif
	
  // Tonemap
  #if (USE_TONEMAP == 1)
	FinalColor = TonemapPass(FinalColor);
  #endif
	
  // Vibrance
  #if (USE_VIBRANCE == 1)
	FinalColor = VibrancePass(FinalColor);
  #endif

  // Curves
  #if (USE_CURVES == 1)
	FinalColor = CurvesPass(FinalColor);
  #endif
		
  // Sepia
  #if (USE_SEPIA == 1)
    FinalColor = SepiaPass(FinalColor);
  #endif
	
  // Vignette
  #if (USE_VIGNETTE == 1)
	FinalColor = VignettePass(FinalColor,tex);
  #endif
	
  // Dither (should go near the end as it only dithers what went before it)
  #if (USE_DITHER == 1)
	FinalColor = DitherPass(FinalColor,tex);
  #endif
	
  // Border
  #if (USE_BORDER == 1)
    FinalColor = BorderPass(FinalColor,tex);
  #endif
	
  // Splitscreen
  #if (USE_SPLITSCREEN == 1)
	FinalColor = SplitscreenPass(FinalColor,tex);
  #endif

  // Return FinalColor
  FinalColor.a = 1.0; //Clear alpha channel to reduce filesize of screenshots that are converted to png and avoid problems when viewing the screenshots.
  return FinalColor;
}