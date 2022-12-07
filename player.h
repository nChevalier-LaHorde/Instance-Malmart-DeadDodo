#ifndef _H3_PLAYER_H_
#define _H3_PLAYER_H_
#include <h3.h>

#define PLAYER_TYPEID 0x10000001

H3_CAPI_BEGIN_BLOCK
void Player_Terminate(void* properties);
void Player_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* Player_CreateProperties(H3Handle cam);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO(Player, float, player_x);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(Player, float, player_y);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(Player, float, player_x);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Player, float, player_y);
H3_CAPI_END_BLOCK

#define PLAYER_CREATE(CAM)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = Player_Terminate,                                 \
		.Update             = Player_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = PLAYER_TYPEID,                                    \
		.properties         = Player_CreateProperties(CAM),						   \
	}

#endif /* _H3_PLAYER_H_ */