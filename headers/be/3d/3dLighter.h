#ifndef _3D_LIGHTER_H
#define _3D_LIGHTER_H

#include <InterfaceDefs.h>

#ifndef _3D_DEFS_H 
#include "3dDefs.h"
#endif
#ifndef _3D_AMBIENT_LIGHT_H 
#include "3dAmbientLight.h"
#endif
#ifndef _3D_PARALLEL_LIGHT_H 
#include "3dParallelLight.h"
#endif
#ifndef _3D_RADIAL_LIGHT_H 
#include "3dRadialLight.h"
#endif
#ifndef _3D_LIGHT_PROC_H 
#include "3dLightProc.h"
#endif

enum {
	B_MAX_PARALLEL_LIGHT_COUNT = 4,
	B_MAX_RADIAL_LIGHT_COUNT =   4
};

class B3dLightProcDesc {
 public:
	RGBAColor   color;
	B3dVector   vector;

	void AdjustColor(B3dLightProcDesc *dup, RGBAColor *color);
};

class B3dLightProc_1_32;
class B3dLightProc_1_8;

class B3dLightProc_1 : public B3dLightProc {
 public:
	long             parallelLightCount;
	long             radialLightCount;
	RGBAColor        ambientColor;

	B3dLightProcDesc parallelProcs[B_MAX_PARALLEL_LIGHT_COUNT];
	B3dLightProcDesc radialProcs[B_MAX_RADIAL_LIGHT_COUNT];

	virtual void   CalcRGBA(B3dVector *point, B3dVector *norm, RGBAColor *color);
	void           SetHighlightColor32(B3dLightProc_1_32 *dup, RGBAColor *color);
	void           SetHighlightColor8(B3dLightProc_1_8 *dup, RGBAColor *color, ulong *map);
};

class B3dLightProc_1_32 : public B3dLightProc_1 {
 public:
	virtual ulong  Calc32(B3dVector *point, B3dVector *norm, RGBAColor *src);
	virtual ulong  RGBATo32(RGBAColor *color, RGBAColor *color2);
};

class B3dLightProc_1_8 : public B3dLightProc_1 {
 public:
	ulong          *IndexMap;
	
	virtual ulong  Calc32(B3dVector *point, B3dVector *norm, RGBAColor *src);
	virtual ulong  RGBATo32(RGBAColor *color, RGBAColor *color2);
};

class B3dWorld;

class B3dLighter {
	friend long lighter_thread(void *data);
 public:
	B3dLighter();
	virtual ~B3dLighter();

	virtual void CollectLight(B3dWorld *world, B3dMatrix *rotation, B3dVector *origin);
	virtual B3dLightProc *SelectLight(B3dThing *thing);
	virtual void GetOptions(void *options);
	virtual void SetOptions(void *options);
	virtual ulong *SetColorMap(uchar *map, rgb_color *color_list);
	virtual void SetColorSpace(color_space cs_mode);
 private:
	B3dLightProc_1    LP;
	B3dLightProc_1_32 LP32;
	B3dLightProc_1_8  LP8;
	color_space       cs;
	rgb_color         *ColorMap;
	ulong             *IndexMap;
};

#endif















