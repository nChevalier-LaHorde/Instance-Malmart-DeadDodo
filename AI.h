#ifndef _H3_AI_H_
#define _H3_AI_H_

#include <h3.h>

#define AI_TYPEID 0x60000001

H3_CAPI_BEGIN_BLOCK
void AI_Terminate(void* properties);
void AI_Collision(H3Handle obj, SH3Collision col);
void AI_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* AI_CreateProperties(H3Handle scn, H3Handle player, H3Handle watchman);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(AI, int, chase);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(AI, int, chase);

H3_CAPI_END_BLOCK


#define AI_CREATE(SCN, PLAYER, WATCHMAN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = AI_Terminate,                                 \
		.Update             = AI_Update,                                                      \
		.isInitialized      = false,                                                     \
		.OnCollisionEnter   = AI_Collision,														\
		.componentType      = AI_TYPEID,									 \
		.properties         = AI_CreateProperties(SCN, PLAYER, WATCHMAN) \
	}

#endif /* _H3_AI_H_ */