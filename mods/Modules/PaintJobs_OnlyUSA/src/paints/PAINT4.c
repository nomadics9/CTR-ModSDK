#include <common.h>
#include "../tex.h"

short brown_coco[16] __attribute__ ((section (".data"))) = {
0x380e,0x340d,0x300c,0x280a,0x1c07,0x1405,0x214d,0x190b,0x2d8f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
short motortop_coco[16] __attribute__ ((section (".data"))) = {
0x6018,0x781e,0x5014,0x24c2,0x1462,0x1846,0x380e,0x2d03,0x2429,0x783e,0x795e,0x7a3e,0x3d88,0x4e2d,0x3545,0x41a9,};
short floor_coco[16] __attribute__ ((section (".data"))) = {
0x2008,0x340d,0x5816,0x3c0f,0x5c17,0x681a,0x6419,0x5c17,0x380e,0x4c13,0x5014,0x2409,0x4812,0x2409,0x1806,0x2c0b,};
short motorside_coco[16] __attribute__ ((section (".data"))) = {
0x4812,0x6018,0x681a,0x2409,0xc42,0x1ca2,0x2905,0x781e,0x4186,0x49ea,0x524f,0x820,0x701c,0x78be,0x795e,0x79fe,};
short front_coco[16] __attribute__ ((section (".data"))) = {
0x1ce6,0x35ee,0x4737,0x677c,0x3c0f,0x4812,0x6419,0x741d,0x78fe,0x797e,0x785e,0x7a1e,0x280a,0x1405,0x3ab3,0x4f38,};
short back_coco[16] __attribute__ ((section (".data"))) = {
0x1cc5,0x39ac,0x3651,0x4b37,0x5b7a,0x46d5,0x340d,0x4812,0x5c17,0x741d,0x791e,0x79fe,0x785e,0x727c,0x2409,0x1004,};
short bridge_coco[16] __attribute__ ((section (".data"))) = {
0x18a3,0x2926,0x2008,0x6018,0x78be,0x2c0b,0x741d,0x791e,0x3dca,0x4411,0x79de,0x7a3e,0x4a2e,0x5ed3,0x5271,0x6f57,};
short exhaust_coco[16] __attribute__ ((section (".data"))) = {
0x2409,0x340d,0x5c17,0x781e,0x4630,0x56b3,0x5ed6,0x4a52,0x6b37,0x779c,0x6f59,0x41ec,0x318a,0x18c5,0x2528,0xc63,};

Texture PAINT4[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.front = (char*)front_coco,
		.back = (char*)back_coco,
		.floor = (char*)floor_coco,
		.brown = (char*)brown_coco,
		.motorside = (char*)motorside_coco,
		.motortop = (char*)motortop_coco,
		.bridge = (char*)bridge_coco,
		.exhaust = (char*)exhaust_coco,
	},
};