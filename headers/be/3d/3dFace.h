#ifndef _3D_FACE_H
#define _3D_FACE_H

#include <unistd.h>

#ifndef _3D_BODY_H 
#include "3dBody.h"
#endif
#ifndef _3D_FACE_MODEL_H 
#include "3dFaceModel.h"
#endif
#ifndef _3D_FACE_LOOK_H 
#include "3dFaceLook.h"
#endif

class B3dFace : public B3dBody {
 public:
	B3dFace(char *name);
	virtual ~B3dFace();
	virtual bool GetTouch(B3dVector *origin, B3dVector *axis, B3dVector *touch);
	virtual long SetFlatLook(char *name,
							 long mode,
							 RGBAColor *color,
							 RGBAColor *colorList = 0L,
							 ulong status = B_SMOOTH_SHADE);
};

#endif







