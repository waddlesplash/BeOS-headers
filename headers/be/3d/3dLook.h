#ifndef _3D_LOOK_H
#define _3D_LOOK_H

#include <InterfaceDefs.h>

#ifndef _3D_MODEL_H
#include "3dModel.h"
#endif
#ifndef _RGBA_COLOR_H
#include "RGBAColor.h"
#endif

extern RGBAColor RGBADefaultColor;

class B3dRenderer;
class B3dLens;
class B3dLightProc;

enum {
	B_SMOOTH_SHADE = -2,
	B_EDGE_SHADE = -1
};

class B3dLook {
 public:
	long         referenceCount;
	B3dModel     *model;
	RGBAColor    color;
	B3dLook(char *name, B3dModel *model, RGBAColor *Color);
	virtual ~B3dLook();
	virtual void Draw(ulong         flags,
					  B3dMatrix     *rotation,
					  B3dVector     *translation,
					  B3dLens       *lens,
					  B3dRenderer   *renderer,
					  B3dLightProc  *lightProc);
	virtual void *ClipHook(void *look1, float rel1, void *look2, float rel2);
    inline const char   *Name();
 private:
	char         name[B_3D_NAME_LENGTH];
};

const char *B3dLook::Name() {
	return name;
}

#endif

 






