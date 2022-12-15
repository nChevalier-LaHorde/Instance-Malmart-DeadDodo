#ifndef _AI_H_
#define _AI_H_

#include <h3.h>

#define AICOMPONENT_TYPEID 0x0028402221

H3_CAPI_BEGIN_BLOCK
void AIComponent_Terminate(void* properties);
void ColAI(H3Handle obj, SH3Collision col);
void UpAI(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* AIComponent_CreateProperties(H3Handle scn, H3Handle player, H3Handle zombie);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(AIComponent, int, chase);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(AIComponent, int, chase);

H3_CAPI_END_BLOCK


#define AICOMPONENT_CREATE(SCN, PLAYER, ZOMBIE)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = AIComponent_Terminate,                                 \
		.Update             = UpAI,                                                      \
		.isInitialized      = false,                                                     \
		.OnCollisionEnter   = ColAI,														\
		.componentType      = AICOMPONENT_TYPEID,									 \
		.properties         = AIComponent_CreateProperties(SCN, PLAYER, ZOMBIE) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */