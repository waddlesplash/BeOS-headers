#ifndef _CONFIG_MGR_H
#define _CONFIG_MGR_H

#ifndef _ISAPNP_H
#include "isapnp.h" 
#endif


#ifdef __cplusplus
extern "C" {
#endif



enum
{
	CONFIG_MGR_CONFIGURE_ALL_DEVICES = B_DEVICE_OP_CODES_END+1,

	CONFIG_MGR_GET_NTH_ISA_DEVICE_CONFIG, 

	CONFIG_MGR_RESERVE_IRQ,
	CONFIG_MGR_RESERVE_DMA_CHANNEL,
	CONFIG_MGR_RESERVE_IO_PORT_RANGE,
	CONFIG_MGR_RESERVE_MEMORY_RANGE
};


#ifdef __cplusplus
}
#endif
#endif

