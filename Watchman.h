/*#ifndef _H3_WATCHMAN_H_
#define _H3_WATCHMAN_H_
#include <h3.h>

#define WATCHMAN_TYPEID 0x40000001

H3_CAPI_BEGIN_BLOCK
void Watchman_Terminate(void* properties);
void Watchman_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* Watchman_CreateProperties(H3Handle scene);
void Watchman_Collision(H3Handle object, SH3Collision collision);
void Watchman_Trigger(H3Handle object, SH3Collision collision);
bool Watchman_RayCast(H3Handle scene, float vx, float vy, uint32_t id);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(Watchman, float, watchman_x);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Watchman, float, watchman_y);
H3_CAPI_END_BLOCK

#define WATCHMAN_CREATE(SCENE)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = Watchman_Terminate,                                 \
		.Update             = Watchman_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = WATCHMAN_TYPEID,                                    \
		.properties         = Watchman_CreateProperties(SCENE),						   \
		.OnCollisionEnter	= Watchman_Collision								   \
	}
*/
//#endif /* _H3_WATCHMAN_H_ */

#ifndef _H3_WATCHMAN_H_
#define _H3_WATCHMAN_H_

#include <h3.h>

#define WATCHMAN_TYPEID 0x40000001

H3_CAPI_BEGIN_BLOCK
void Watchman_Terminate(void* properties);
void* Watchman_CreateProperties(H3Handle Player, H3Handle scn);
void Watchman_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Watchman, bool, wave);

H3_CAPI_END_BLOCK


#define WATCHMAN_CREATE(PLAYER, SCN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = Watchman_Terminate,                                 \
		.Update             = Watchman_Update,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = WATCHMAN_TYPEID,									 \
		.properties         = Watchman_CreateProperties(PLAYER, SCN) \
	}

#endif /* _H3_WATCHMAN_H_ */