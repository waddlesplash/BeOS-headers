#ifndef _ISAPNP_H
#define _ISAPNP_H

#ifdef __cplusplus
extern "C" {
#endif


typedef union
{
	uint32	id;
	uint8	b[4];
	
} EISA_PRODUCT_ID; /* in little-endian format */


/* uint32 MAKE_EISA_PRODUCT_ID(EISA_PRODUCT_ID* ptr, char ch0, char ch1, char ch2, uint12 prod_num, uint4 rev) */
/* example: MAKE_EISA_PRODUCT_ID(&foo_id, 'F','O','O', 0xdb1, 3); */
/* makes correct little-endian format */
#define	MAKE_EISA_PRODUCT_ID(ptr, ch0, ch1, ch2, prod_num, rev) \
	do																						\
	{ 																						\
		(ptr)->b[0] = (uint8)(((((ch0) - 'A' + 1) & 0x1f) << 2) | ((((ch1) - 'A' + 1) & 0x18) >> 3));  	\
		(ptr)->b[1] = (uint8)(((((ch1) - 'A' + 1) & 0x07) << 5) | ((((ch2) - 'A' + 1) & 0x1f)     ));  	\
		(ptr)->b[2] = (uint8)((((prod_num) & 0xff0) >> 4));												\
		(ptr)->b[3] = (uint8)((((prod_num) & 0x00f) << 4) | ((rev) & 0xf) );							\
	}	while(0)


/* Compare IDs without revision */
/* bool EQUAL_EISA_PRODUCT_ID(EISA_PRODUCT_ID id1, EISA_PRODUCT_ID id2); */
#define	EQUAL_EISA_PRODUCT_ID(id1, id2) \
	(((id1).b[0] == (id2).b[0]) && ((id1).b[1] == (id2).b[1]) && ((id1).b[2] == (id2).b[2]) && (((id1).b[3] & 0xf0) == ((id2).b[3] & 0xf0)))


#define MAX_COMPATIBLE_DEVICE_ID	8
#define MAX_ISA_PNP_IRQS			2
#define MAX_ISA_PNP_DMAS			2
#define MAX_ISA_PNP_IO_PORT_RANGES	8
#define MAX_ISA_PNP_MEMORY_RANGES	4
#define MAX_ISA_PNP_NAME_LEN		32 


typedef enum
{
	HTES	= 1, /* high true edge sensitive */ /* default & ISA */
	LTES	= 2,
	HTLS	= 4,
	LTLS	= 8
} IRQ_TYPE;

typedef struct
{
	uint8		irq;
	IRQ_TYPE	irq_type;
}	irq_descriptor;

typedef struct
{
	uint8	channel;
	uint8	flags;
} dma_channel_descriptor;


#define DMA_TYPE_MASK			0x03
#define DMA_TYPE_8_BIT			0x00
#define DMA_TYPE_8_AND_16_BIT	0x01
#define DMA_TYPE_16_BIT			0x02

#define DMA_TYPE_BUS_MASTER		0x04
#define DMA_TYPE_BYTE_MODE		0x08
#define DMA_TYPE_WORD_MODE		0x10

#define DMA_TYPE_SPEED_MASK		0x60
#define DMA_TYPE_SPEED_COMPAT	0x00
#define DMA_TYPE_SPEED_TYPE_A	0x20
#define DMA_TYPE_SPEED_TYPE_B	0x40
#define DMA_TYPE_SPEED_TYPE_F	0x60

typedef struct
{
	uint16	base;
	uint16	len;
} io_port_range_descriptor;


typedef struct
{
	uint32	base;
	uint32	len;
	uint8	flags;
} memory_range_descriptor;


/* The current configuration. Goes to the "normal" drivers */ 
typedef struct
{
	EISA_PRODUCT_ID				card_id;
	EISA_PRODUCT_ID				logical_device_id;
	EISA_PRODUCT_ID				compatible_device_ids[MAX_COMPATIBLE_DEVICE_ID];

	char						card_name[MAX_ISA_PNP_NAME_LEN];
	char						logical_device_name[MAX_ISA_PNP_NAME_LEN];

	ushort						num_compatible_device_ids;
	ushort						num_irqs;
	ushort						num_dma_channels;
	ushort						num_io_port_ranges;
	ushort						num_memory_ranges;

	irq_descriptor				irqs[MAX_ISA_PNP_IRQS];
	dma_channel_descriptor		dma_channels[MAX_ISA_PNP_DMAS];
	io_port_range_descriptor	io_port_ranges[MAX_ISA_PNP_IO_PORT_RANGES];
	memory_range_descriptor		memory_ranges[MAX_ISA_PNP_MEMORY_RANGES];

} isa_device_config;


#ifdef __cplusplus
}
#endif
#endif

