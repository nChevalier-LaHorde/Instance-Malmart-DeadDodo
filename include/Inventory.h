#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <h3.h>

#define INVENTORYCOMPONENT_TYPEID 0x0054002221

H3_CAPI_BEGIN_BLOCK
void InventoryComponent_Terminate(void* properties);
void* InventoryComponent_CreateProperties(H3Handle player, H3Handle cam, H3Handle scn);
void UpInventory(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(InventoryComponent, H3Handle, stockSelected);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, H3Handle, stock1);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, H3Handle, stock2);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, H3Handle, stock3);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(InventoryComponent, int, selected);



H3_CAPI_END_BLOCK


#define INVENTORYCOMPONENT_CREATE(PLAYER, CAM, SCN)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = InventoryComponent_Terminate,                                 \
		.Update             = UpInventory,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = INVENTORYCOMPONENT_TYPEID,									 \
		.properties         = InventoryComponent_CreateProperties(PLAYER, CAM, SCN) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */