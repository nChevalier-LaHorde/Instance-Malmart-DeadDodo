#ifndef _H3_TYPEDIGIDE_H_
#define _H3_TYPEDIGIDE_H_
#include <h3.h>

#define TYPEDIGIDE_TYPEID 0x12554321511

H3_CAPI_BEGIN_BLOCK
void TypeDigide_Terminate(void* properties);
void* TypeDigide_CreateProperties();
void UpDigide(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK

#define TYPEDIGIDE_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = TypeDigide_Terminate,                                 \
		.Update				= UpDigide, \
		.isInitialized      = false,													   \
		.componentType      = TYPEDIGIDE_TYPEID,                                    \
		.properties         = TypeDigide_CreateProperties(),						   \
	}

#endif /* _H3_TYPEDIGIDE_H_ */