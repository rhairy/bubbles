/* vgatm.c
 * VGA Text Mode driver.
 */

#include "vgatm.h"

size_t vgatm_x = 0;
size_t vgatm_y = 0;
uint8_t vgatm_color = 0x2a;
uint16_t *vgatm_cursor = (uint16_t*) VGATM_BASE_PTR;

void vgatm_cls() {
	for (size_t y = 0; y < VGATM_HEIGHT; y++) {
		for (size_t x = 0; x < VGATM_WIDTH; x++) {
			vgatm_nav(x, y);
			vgatm_write(' ',vgatm_color);
		}
	}
	vgatm_x = 0;
	vgatm_y = 0;
	vgatm_cursor = (uint16_t*) VGATM_BASE_PTR;
}

void vgatm_nav(const size_t x, const size_t y) {
	vgatm_cursor = (uint16_t*) VGATM_BASE_PTR;
	vgatm_cursor += (VGATM_WIDTH * y) + x;
}

void vgatm_putchar(uint8_t c) {
	if (c == '\n') {
		vgatm_x = 0;
		vgatm_y++;
		vgatm_nav(vgatm_x, vgatm_y);
		vgatm_write(c, vgatm_color);
	} else if (vgatm_x < VGATM_WIDTH - 1) {
		vgatm_nav(vgatm_x++, vgatm_y);
		vgatm_write(c, vgatm_color);
	} else if (vgatm_y < VGATM_HEIGHT - 1) {
		vgatm_x = 0;
		vgatm_nav(vgatm_x, vgatm_y++);
		vgatm_write(c, vgatm_color);
	}
}

void vgatm_write(uint8_t c, uint8_t color) {
	uint16_t payload = (uint16_t) c | (uint16_t) color << 8;
	*vgatm_cursor = payload;
}
