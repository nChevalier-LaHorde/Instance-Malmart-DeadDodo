#ifndef _H3_TYPEMONSTERE_H_
#define _H3_TYPEMONSTERE_H_
#include <h3.h>

#define TYPEMONSTERE_TYPEID 0x10546510001

H3_CAPI_BEGIN_BLOCK
void TypeMonstere_Terminate(void* properties);
void* TypeMonstere_CreateProperties();

H3_CAPI_END_BLOCK

#define TYPEMONSTERE_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeMonstere_Terminate,                                 \
		.isInitialized      = false,													   \
		.componentType      = TYPEMONSTERE_TYPEID,                                    \
		.properties         = TypeMonstere_CreateProperties(),						   \
	}

#endif /* _H3_TYPEMONSTERE_H_ */
