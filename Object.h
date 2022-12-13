#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <h3.h>

#define OBJECTCOMPONENT_TYPEID 0x000002221

H3_CAPI_BEGIN_BLOCK
void ObjectComponent_Terminate(void* properties);
void* ObjectComponent_CreateProperties(H3Handle scn, H3Handle h3, H3Handle cam, int* scnLunch);
void UpObject(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ObjectComponent, int, monstereEffect);

H3_CAPI_END_BLOCK


#define OBJECTCOMPONENT_CREATE(SCN,H3, CAM, SCNLUNCH)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = ObjectComponent_Terminate,                                 \
		.Update             = UpObject,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = OBJECTCOMPONENT_TYPEID,									 \
		.properties         = ObjectComponent_CreateProperties(SCN, H3, CAM, SCNLUNCH) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */
