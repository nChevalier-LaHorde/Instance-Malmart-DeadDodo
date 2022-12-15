#ifndef _H3_CHECKPOINTIA_H_
#define _H3_CHECKPOINTIA_H_
#include <h3.h>

#define CHECKPOINTIA_TYPEID 0x30000001

H3_CAPI_BEGIN_BLOCK
void CheckPointIA_Terminate(void* properties);
void CheckPointIA_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* CheckPointIA_CreateProperties(H3Handle scene);
void CheckPointIAOnCollision(H3Handle object, SH3Collision collision);
void CheckPointIAOnCollisionLeave(H3Handle object, SH3Collision collision);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(CheckPointIA, float, checkPointIA_x);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(CheckPointIA, float, checkPointIA_y);
H3_CAPI_END_BLOCK

#define CHECKPOINTIA_CREATE(SCENE)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = CheckPointIA_Terminate,                                 \
		.Update             = CheckPointIA_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = CHECKPOINTIA_TYPEID,                                    \
		.properties         = CheckPointIA_CreateProperties(SCENE),						   \
	}

#endif /* _H3_CHECKPOINTIA_H_ */