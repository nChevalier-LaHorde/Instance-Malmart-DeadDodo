#ifndef _MC_H_
#define _MC_H_

#include <h3.h>

#define MCCOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void MCComponent_Terminate(void* properties);
void* MCComponent_CreateProperties(H3Handle scn, H3Handle h3);
void UpMC(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);




H3_CAPI_END_BLOCK


#define MCCOMPONENT_CREATE(SCN, H3)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = MCComponent_Terminate,                                 \
		.Update             = UpMC,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = MCCOMPONENT_TYPEID,									 \
		.properties         = MCComponent_CreateProperties(SCN, H3) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */