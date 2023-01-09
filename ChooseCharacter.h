#ifndef _H3_COMPONENTS_CHARACTERCOMPONENT_H_
#define _H3_COMPONENTS_CHARACTERCOMPONENT_H_

#include <h3.h>

#define CHARACTERCOMPONENT_TYPEID 0x0000301

H3_CAPI_BEGIN_BLOCK

void CharacterComponent_Terminate(void* properties);
void CharacterComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* CharacterComponent_CreateProperties(H3Handle h3, H3Handle player);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(CharacterComponent, int, wayPoint);


H3_CAPI_END_BLOCK

#define CHARACTERCOMPONENT_CREATE(H3, PLAYER)							\
	(SH3Component) {													\
		.Terminate          = CharacterComponent_Terminate,				\
		.Update             = CharacterComponent_Update,					\
		.isInitialized      = false,									\
		.componentType      = CHARACTERCOMPONENT_TYPEID,					\
		.properties         = CharacterComponent_CreateProperties(H3, PLAYER)		\
	}

#endif /* _H3_COMPONENTS_CHARACTERCOMPONENT_H_ */