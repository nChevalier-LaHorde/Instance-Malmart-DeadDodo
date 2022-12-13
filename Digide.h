#ifndef _H3_DIGIDE_H_
#define _H3_DIGIDE_H_
#include <h3.h>

#define DIGIDE_TYPEID 0x20000001

H3_CAPI_BEGIN_BLOCK
void Digide_Terminate(void* properties);
void Digide_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* Digide_CreateProperties(H3Handle scene, int nbcode1, int nbcode2, int nbcode3, int nbcode4);
H3_CAPI_END_BLOCK

#define DIGIDE_CREATE(SCENE, NBCODE1, NBCODE2, NBCODE3, NBCODE4)														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = Digide_Terminate,                                 \
		.Update             = Digide_Update,                                    \
		.isInitialized      = false,													   \
		.componentType      = DIGIDE_TYPEID,                                    \
		.properties         = Digide_CreateProperties(SCENE, NBCODE1, NBCODE2, NBCODE3, NBCODE4),						   \
	}

#endif /* _H3_DIGIDE_H_ */