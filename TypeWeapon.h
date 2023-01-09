#ifndef _H3_TYPEWEAPON_H_
#define _H3_TYPEWEAPON_H_
#include <h3.h>

#define TYPEWEAPON_TYPEID 0x107800001

H3_CAPI_BEGIN_BLOCK
void TypeWeapon_Terminate(void* properties);
void* TypeWeapon_CreateProperties();

H3_CAPI_END_BLOCK

#define TYPEWEAPON_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeWeapon_Terminate,                                 \
		.isInitialized      = false,													   \
		.componentType      = TYPEWEAPON_TYPEID,                                    \
		.properties         = TypeWeapon_CreateProperties(),						   \
	}

#endif /* _H3_TYPEWEAPON_H_ */
