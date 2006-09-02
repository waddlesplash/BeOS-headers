/*
 * This file is part of the CAPI library
 *
 * Copyright (c) 2001, 2002 Marcus Overhagen <marcus@overhagen.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal 
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 */

#include "little_endian.h"

#define READ_API_MESSAGE_LENGTH(Msg)		read16(Msg,0)
#define READ_API_COMMAND(Msg)				read16(Msg,4)
#define READ_DATA_B3_REQ_DATA(Msg)			read32(Msg,12)
#define READ_DATA_B3_REQ_DATA_LENGTH(Msg)	read16(Msg,16)
#define READ_DATA_B3_REQ_DATA_HANDLE(Msg)	read16(Msg,18)
#define READ_DATA_B3_REQ_DATA64(Msg)		read64(Msg,22)

#define WRITE_DATA_B3_REQ_DATA(Msg,val)			write32(Msg,12,val)
#define WRITE_DATA_B3_REQ_DATA_LENGTH(Msg,val)	write16(Msg,16,val)
#define WRITE_DATA_B3_REQ_DATA_HANDLE(Msg,val)	write16(Msg,18,val)
#define WRITE_DATA_B3_REQ_DATA64(Msg,val)		write64(Msg,22,val)

#define CONNECT_REQ					0x8002 
#define CONNECT_CONF				0x8102
#define CONNECT_IND					0x8202
#define CONNECT_RESP				0x8302
#define CONNECT_ACTIVE_IND			0x8203
#define CONNECT_ACTIVE_RESP			0x8303
#define DISCONNECT_REQ				0x8004
#define DISCONNECT_CONF				0x8104
#define DISCONNECT_IND				0x8204
#define DISCONNECT_RESP				0x8304
#define ALERT_REQ					0x8001
#define ALERT_CONF					0x8101
#define INFO_REQ					0x8008
#define INFO_CONF					0x8108
#define INFO_IND					0x8208
#define INFO_RESP					0x8308
#define CONNECT_B3_REQ				0x8082
#define CONNECT_B3_CONF				0x8182
#define CONNECT_B3_IND				0x8282
#define CONNECT_B3_RESP				0x8382
#define CONNECT_B3_ACTIVE_IND		0x8283
#define CONNECT_B3_ACTIVE_RESP		0x8383
#define CONNECT_B3_T90_ACTIVE_IND	0x8288
#define CONNECT_B3_T90_ACTIVE_RESP	0x8388
#define DISCONNECT_B3_REQ			0x8084
#define DISCONNECT_B3_CONF			0x8184
#define DISCONNECT_B3_IND			0x8284
#define DISCONNECT_B3_RESP			0x8384
#define DATA_B3_REQ					0x8086
#define DATA_B3_CONF				0x8186
#define DATA_B3_IND					0x8286
#define DATA_B3_RESP				0x8386
#define RESET_B3_REQ				0x8087
#define RESET_B3_CONF				0x8187
#define RESET_B3_IND				0x8287
#define RESET_B3_RESP				0x8387
#define LISTEN_REQ					0x8005
#define LISTEN_CONF					0x8105
#define FACILITY_REQ				0x8080
#define FACILITY_CONF				0x8180
#define FACILITY_IND				0x8280
#define FACILITY_RESP				0x8380
#define SELECT_B_PROTOCOL_REQ		0x8041
#define SELECT_B_PROTOCOL_CONF		0x8141
#define MANUFACTURER_REQ			0x80FF
#define MANUFACTURER_CONF			0x81FF
#define MANUFACTURER_IND			0x82FF
#define MANUFACTURER_RESP			0x83FF
