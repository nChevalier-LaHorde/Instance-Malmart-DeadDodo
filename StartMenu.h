#ifndef _SM_H_
#define _SM_H_

#include <h3.h>

#define SMCOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void SMComponent_Terminate(void* properties);
void ColSM(H3Handle obj, SH3Collision col, void* properties);
void* SMComponent_CreateProperties(H3Handle h3, H3Handle scn);
void UpSM(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK


#define SMCOMPONENT_CREATE(H3, SCN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = SMComponent_Terminate,                                 \
		.Update             = UpSM,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = SMCOMPONENT_TYPEID,									 \
		.properties         = SMComponent_CreateProperties(H3, SCN) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */