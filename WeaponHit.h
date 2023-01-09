#ifndef _H3_HIT_H_
#define _H3_HIT_H_
#include <h3.h>

#define HIT_TYPEID 0x1054655552541

H3_CAPI_BEGIN_BLOCK
void Hit_Terminate(void* properties);
void* Hit_CreateProperties();
void hitOnCollision(H3Handle obj, SH3Collision col);
void hitOnCollisionLeave(H3Handle obj, SH3Collision col);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(Hit, bool, iAmOnCollisionWithAI);
H3_CAPI_END_BLOCK

#define HIT_CREATE()														   \
	(SH3Component) {                                                                       \
		.Init               = NULL,                                                        \
		.Terminate          = Hit_Terminate,                                 \
		.isInitialized      = false,													   \
		.OnCollisionEnter	= hitOnCollision, \
		.OnCollisionLeave	= hitOnCollisionLeave, \
		.componentType      = HIT_TYPEID,                                    \
		.properties         = Hit_CreateProperties(),						   \
	}

#endif /* _H3_HIT_H_ */