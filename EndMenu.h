#ifndef _H3_COMPONENTS_ENDMENUCOMPONENT_H_
#define _H3_COMPONENTS_ENDMENUCOMPONENT_H_

#include <h3.h>

//COMPOSANT JOUEUR
#define ENDMENUCOMPONENT_TYPEID 0x0589934

H3_CAPI_BEGIN_BLOCK

void EndMenuComponent_Init(SH3Transform*, void**);
void EndMenuComponent_Terminate(void* properties);
void EndMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* EndMenuComponent_CreateProperties(H3Handle h3, H3Handle camera);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EndMenuComponent,  bool, playerAlive);

H3_CAPI_END_BLOCK

#define ENDMENUCOMPONENT_CREATE(H3, CAMERA)                                 \
	(SH3Component) {                                                 \
		.Init				= EndMenuComponent_Init,								\
		.Terminate          = EndMenuComponent_Terminate, \
		.Update             = EndMenuComponent_Update,                \
		.isInitialized      = false,                                 \
		.componentType      = ENDMENUCOMPONENT_TYPEID,                \
		.properties         = EndMenuComponent_CreateProperties(H3, CAMERA) \
	}

#endif 