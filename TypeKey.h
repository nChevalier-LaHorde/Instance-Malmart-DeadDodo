#ifndef _H3_TYPEKEY_H_
#define _H3_TYPEKEY_H_
#include <h3.h>

#define TYPEKEY_TYPEID 0x1251651511

H3_CAPI_BEGIN_BLOCK
void TypeKey_Terminate(void* properties);
void* TypeKey_CreateProperties();
void UpKey(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK

#define TYPEKEY_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeKey_Terminate,                                 \
		.Update				= UpKey, \
		.isInitialized      = false,													   \
		.componentType      = TYPEKEY_TYPEID,                                    \
		.properties         = TypeKey_CreateProperties(),						   \
	}

#endif /* _H3_TYPEKEY_H_ */
