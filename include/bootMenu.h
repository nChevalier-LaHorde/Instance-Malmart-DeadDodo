#ifndef _H3_COMPONENTS_BOOTMENUCOMPONENT_H_
#define _H3_COMPONENTS_BOOTMENUCOMPONENT_H_

#include <h3.h>

//COMPOSANT JOUEUR
#define BOOTMENUCOMPONENT_TYPEID 0x0000101

H3_CAPI_BEGIN_BLOCK

void BootMenuComponent_Init(SH3Transform*, void**);
void BootMenuComponent_Terminate(void* properties);
void BootMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* BootMenuComponent_CreateProperties(H3Handle h3, int stateMenu);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(BootMenuComponent, int, stateMenu);

H3_CAPI_END_BLOCK

#define BOOTMENUCOMPONENT_CREATE(H3, STATEMENU)                                 \
	(SH3Component) {                                                 \
		.Init				= BootMenuComponent_Init,								\
		.Terminate          = BootMenuComponent_Terminate, \
		.Update             = BootMenuComponent_Update,                \
		.isInitialized      = false,                                 \
		.componentType      = BOOTMENUCOMPONENT_TYPEID,                \
		.properties         = BootMenuComponent_CreateProperties(H3, STATEMENU) \
	}

//ajouter en haut collisionenter / collisionleave = 
#endif /* _H3_COMPONENTS_BOOTMENUCOMPONENT_H_ */