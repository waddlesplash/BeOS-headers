#ifndef _3D_RADIAL_LIGHT_H
#define _3D_RADIAL_LIGHT_H

#ifndef _3D_DEFS_H 
#include "3dDefs.h"
#endif
#ifndef _3D_LIGHT_H
#include "3dLight.h"
#endif

class B3dRadialLight : public B3dLight {
 public:
	B3dRadialLight(char *name, float power, RGBAColor *color, B3dVector *source);
	virtual ~B3dRadialLight();
};

#endif
