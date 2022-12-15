#ifndef _H3_TYPECANTAKE_H_
#define _H3_TYPECANTAKE_H_
#include <h3.h>

#define TYPECANTAKE_TYPEID 0x1251510001

H3_CAPI_BEGIN_BLOCK
void TypeCanTake_Terminate(void* properties);
void* TypeCanTake_CreateProperties();


H3_CAPI_END_BLOCK

#define TYPECANTAKE_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeCanTake_Terminate,                                 \
		.isInitialized      = false,													   \
		.componentType      = TYPECANTAKE_TYPEID,                                    \
		.properties         = TypeCanTake_CreateProperties(),						   \
	}

#endif /* _H3_TYPECANTAKE_H_ */