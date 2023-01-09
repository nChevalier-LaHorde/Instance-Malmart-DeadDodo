/*#ifndef _H3_RAYCAST_H_
#define _H3_RAYCAST_H_
#include <h3.h>

#define RAYCAST_TYPEID 0x50000001

H3_CAPI_BEGIN_BLOCK
void RayCast_Terminate(void* properties);
void RayCast_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* RayCast_CreateProperties(H3Handle scene);
void RayCastOnCollision(H3Handle object, SH3Collision collision);
void RayCastOnCollisionLeave(H3Handle object, SH3Collision collision);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(RayCast, float, rayCast_x);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(RayCast, float, rayCast_y);
H3_CAPI_END_BLOCK

#define RAYCAST_CREATE(SCENE)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = RayCast_Terminate,                                 \
		.Update             = RayCast_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = RAYCAST_TYPEID,                                    \
		.properties         = RayCast_CreateProperties(SCENE),						   \
	}
*/
//#endif /* _H3_RAYCAST_H_ */

/*#ifndef _H3_RAYCAST_H_
#define _H3_RAYCAST_H_
#include <h3.h>

#define RAYCAST_TYPEID 0x50000001

H3_CAPI_BEGIN_BLOCK
void RayCast_Terminate(void* properties);
void RayCast_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* RayCast_CreateProperties(H3Handle scene, float vx, float vy, uint32_t id);
void RayCast_Trigger(H3Handle object, SH3Collision collision);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(RayCast, int, way);
H3_CAPI_END_BLOCK

#define RAYCAST_CREATE(SCENE, VX, VY, ID)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = RayCast_Terminate,                                 \
		.Update             = RayCast_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = RAYCAST_TYPEID,                                    \
		.properties         = RayCast_CreateProperties(SCENE, VX, VY, ID),						   \
		.OnTriggerEnter		= RayCast_Trigger								   \
	}
*/
//#endif /* _H3_RAYCAST_H_ */

/*#ifndef _RAYCAST_H_
#define _RAYCAST_H_

#include <h3.h>

#define RAYCASTCOMPONENT_TYPEID 0x50000001

H3_CAPI_BEGIN_BLOCK
void RayCastComponent_Terminate(void* properties);
void RayCastComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* RayCastComponent_CreateProperties(H3Handle watchman);
void RayCastComponent_Collision(H3Handle object, SH3Collision collision);


H3_CAPI_END_BLOCK


#define RAYCASTCOMPONENT_CREATE(WATCHMAN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = RayCastComponent_Terminate,                                 \
		.Update             = RayCastComponent_Update,                                                      \
		.isInitialized      = false,                                                     \
		.OnCollisionEnter   = RayCastComponent_Collision,														\
		.componentType      = RAYCASTCOMPONENT_TYPEID,									 \
		.properties         = RayCastComponent_CreateProperties(WATCHMAN) \
	}
*/
//#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */

#ifndef _H3_RAYCAST_H_
#define _H3_RAYCAST_H_

#include <h3.h>

#define RAYCAST_TYPEID 0x50000001

H3_CAPI_BEGIN_BLOCK
void RayCast_Terminate(void* properties);
void RayCast_Collision(H3Handle obj, SH3Collision col);
void RayCast_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* RayCast_CreateProperties(H3Handle watchman);


H3_CAPI_END_BLOCK


#define RAYCAST_CREATE(WATCHMAN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = RayCast_Terminate,                                 \
		.Update             = RayCast_Update,                                                      \
		.isInitialized      = false,                                                     \
		.OnCollisionEnter   = RayCast_Collision,														\
		.componentType      = RAYCAST_TYPEID,									 \
		.properties         = RayCast_CreateProperties(WATCHMAN) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */