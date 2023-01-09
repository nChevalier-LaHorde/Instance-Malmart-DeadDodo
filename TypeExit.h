#ifndef _H3_TYPEEXIT_H_
#define _H3_TYPEEXIT_H_
#include <h3.h>

#define TYPEEXIT_TYPEID 0x1255451501511

H3_CAPI_BEGIN_BLOCK
void TypeExit_Terminate(void* properties);
void* TypeExit_CreateProperties();

H3_CAPI_END_BLOCK

#define TYPEEXIT_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeExit_Terminate,                                 \
		.isInitialized      = false,													   \
		.componentType      = TYPEEXIT_TYPEID,                                    \
		.properties         = TypeExit_CreateProperties(),						   \
	}

#endif /* _H3_TYPEEXIT_H_ */