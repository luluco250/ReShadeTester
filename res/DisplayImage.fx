#include "ReShade.fxh"

#ifndef DISPLAY_IMAGE_FILENAME
#define DISPLAY_IMAGE_FILENAME "DisplayImage.png"
#endif

#ifndef DISPLAY_IMAGE_WIDTH
#define DISPLAY_IMAGE_WIDTH BUFFER_WIDTH
#endif

#ifndef DISPLAY_IMAGE_HEIGHT
#define DISPLAY_IMAGE_HEIGHT BUFFER_HEIGHT
#endif

#ifndef DISPLAY_IMAGE_MINFILTER
#define DISPLAY_IMAGE_MINFILTER LINEAR
#endif

#ifndef DISPLAY_IMAGE_MAGFILTER
#define DISPLAY_IMAGE_MAGFILTER LINEAR
#endif

#ifndef DISPLAY_IMAGE_ADDRESSU
#define DISPLAY_IMAGE_ADDRESSU BORDER
#endif

#ifndef DISPLAY_IMAGE_ADDRESSV
#define DISPLAY_IMAGE_ADDRESSV BORDER
#endif

texture2D tDisplayImage_Image <
	source = DISPLAY_IMAGE_FILENAME;
> {
	Width = DISPLAY_IMAGE_WIDTH;
	Height = DISPLAY_IMAGE_HEIGHT;
};
sampler2D sImage {
	Texture = tDisplayImage_Image;

	AddressU = DISPLAY_IMAGE_ADDRESSU;
	AddressV = DISPLAY_IMAGE_ADDRESSV;

	MinFilter = DISPLAY_IMAGE_MINFILTER;
	MagFilter = DISPLAY_IMAGE_MAGFILTER;
};

float4 PS_DisplayImage(
	float4 position : SV_POSITION,
	float2 uv       : TEXCOORD
) : SV_TARGET {
	return float4(tex2D(sImage, uv).rgb, 1.0);
}

technique DisplayImage {
	pass {
		VertexShader = PostProcessVS;
		PixelShader  = PS_DisplayImage;
	}
}
