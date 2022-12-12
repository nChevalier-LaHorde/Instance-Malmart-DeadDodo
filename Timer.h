#ifndef _TIMER_H_
#define _TIMER_H_

#include <h3.h>

#define TIMERCOMPONENT_TYPEID 0x00165512221

H3_CAPI_BEGIN_BLOCK
void TimerComponent_Terminate(void* properties);
void* TimerComponent_CreateProperties(H3Handle scn, H3Handle cam, H3Handle objectc);
void UpTimer(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

H3_CAPI_END_BLOCK


#define TIMERCOMPONENT_CREATE(SCN, CAM, OBJECTC)                                          \
	(SH3Component) {                                                            \
		.Init               = NULL,                                                      \
		.Terminate          = TimerComponent_Terminate,                                 \
		.Update             = UpTimer,                                                      \
		.isInitialized      = false,                                                     \
		.componentType      = TIMERCOMPONENT_TYPEID,									 \
		.properties         = TimerComponent_CreateProperties(SCN, CAM, OBJECTC) \
	}

#endif /* _H3_COMPONENTS_SPRITECOMPONENT_H_ */
