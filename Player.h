#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <h3.h>

#define PLAYERCOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void PlayerComponent_Terminate(void* properties);
void* PlayerComponent_CreateProperties();
void UpPlayer(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void PlayerCol(H3Handle obj, SH3Collision col);
void PlayerColLeave(H3Handle obj, SH3Collision col);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, int, playerOnCollision);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, H3Handle, objTouch);

H3_CAPI_END_BLOCK


#define PLAYERCOMPONENT_CREATE()                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = PlayerComponent_Terminate,                                 \
		.Update             = UpPlayer,                                                      \
		.isInitialized      = false,                                                     \
		.OnTriggerEnter = PlayerCol, \
		.OnTriggerLeave = PlayerColLeave, \
		.componentType      = PLAYERCOMPONENT_TYPEID,									 \
		.properties         = PlayerComponent_CreateProperties() \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */

