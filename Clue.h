#ifndef _CLUE_H_
#define _CLUE_H_

#include <h3.h>

#define CLUECOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void ClueComponent_Terminate(void* properties);
void* ClueComponent_CreateProperties(H3Handle scn, H3Handle h3);
void UpClue(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK


#define CLUECOMPONENT_CREATE(SCN, H3)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = ClueComponent_Terminate,                                 \
		.Update             = UpClue,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = CLUECOMPONENT_TYPEID,									 \
		.properties         = ClueComponent_CreateProperties(SCN, H3) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */

