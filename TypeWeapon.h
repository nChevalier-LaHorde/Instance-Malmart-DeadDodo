#ifndef _H3_TYPEWEAPON_H_
#define _H3_TYPEWEAPON_H_
#include <h3.h>

#define TYPEWEAPON_TYPEID 0x107800001

H3_CAPI_BEGIN_BLOCK
void TypeWeapon_Terminate(void* properties);
void* TypeWeapon_CreateProperties();
void NoneUpdate(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK

#define TYPEWEAPON_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeWeapon_Terminate,                                 \
		.isInitialized      = false,													   \
		.Update             = NoneUpdate,                                                      \
		.componentType      = TYPEWEAPON_TYPEID,                                    \
		.properties         = TypeWeapon_CreateProperties(),						   \
	}

#endif /* _H3_TYPEWEAPON_H_ */
