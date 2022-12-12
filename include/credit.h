#ifndef _H3_COMPONENTS_CREDITCOMPONENT_H_
#define _H3_COMPONENTS_CREDITCOMPONENT_H_

#include <h3.h>

//COMPOSANT JOUEUR
#define CREDITCOMPONENT_TYPEID 0x0000201

H3_CAPI_BEGIN_BLOCK

void CreditComponent_Terminate(void* properties);
void CreditComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* CreditComponent_CreateProperties(H3Handle h3, int stateMenu);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(CreditComponent, int, wayPoint);

H3_CAPI_END_BLOCK

#define CREDITCOMPONENT_CREATE(H3, STATEMENU)							\
	(SH3Component) {													\
		.Terminate          = CreditComponent_Terminate,				\
		.Update             = CreditComponent_Update,					\
		.isInitialized      = false,									\
		.componentType      = CREDITCOMPONENT_TYPEID,					\
		.properties         = CreditComponent_CreateProperties(H3, STATEMENU)		\
	}

//ajouter en haut collisionenter / collisionleave = 
#endif /* _H3_COMPONENTS_CREDITCOMPONENT_H_ */