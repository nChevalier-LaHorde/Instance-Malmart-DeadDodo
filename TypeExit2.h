#ifndef _H3_TYPEEXIT2_H_
#define _H3_TYPEEXIT2_H_
#include <h3.h>

#define TYPEEXIT2_TYPEID 0x1255451501511

H3_CAPI_BEGIN_BLOCK
void TypeExit2_Terminate(void* properties);
void* TypeExit2_CreateProperties();

H3_CAPI_END_BLOCK

#define TYPEEXIT2_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeExit2_Terminate,                                 \
		.isInitialized      = false,													   \
		.componentType      = TYPEEXIT2_TYPEID,                                    \
		.properties         = TypeExit2_CreateProperties(),						   \
	}

#endif /* _H3_TYPEEXIT2_H_ */