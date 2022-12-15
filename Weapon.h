#ifndef _H3_WEAPON_H_
#define _H3_WEAPON_H_
#include <h3.h>

#define WEAPON_TYPEID 0x107800001

H3_CAPI_BEGIN_BLOCK
void Weapon_Terminate(void* properties);
void Weapon_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* Weapon_CreateProperties(H3Handle cam, H3Handle scn);
void WeaponOnCollision(H3Handle object, SH3Collision collision);
void WeaponOnCollisionLeave(H3Handle object, SH3Collision collision);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Weapon, bool, displayWeapon);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Weapon, H3Handle, weaponObj);
H3_CAPI_END_BLOCK

#define WEAPON_CREATE(CAM, SCN)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = Weapon_Terminate,                                 \
		.Update             = Weapon_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = WEAPON_TYPEID,                                    \
		.properties         = Weapon_CreateProperties(CAM, SCN),						   \
		.OnTriggerEnter     = WeaponOnCollision,									\
								\
	}

#endif /* _H3_WEAPON_H_ */