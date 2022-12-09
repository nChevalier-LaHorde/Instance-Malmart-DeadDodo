#ifndef _MONSTERE_H_
#define _MONSTERE_H_

#include <h3.h>

#define MONSTERECOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void MonstereComponent_Terminate(void* properties);
void* MonstereComponent_CreateProperties(H3Handle obj);
void UpMonstere(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK


#define MONSTERECOMPONENT_CREATE(OBJ)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = MonstereComponent_Terminate,                                 \
		.Update             = UpMonstere,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = MONSTERECOMPONENT_TYPEID,									 \
		.properties         = MonstereComponent_CreateProperties(OBJ) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */
