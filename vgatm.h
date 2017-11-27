/* vgatm.h
 * VGA Text Mode driver.
 */

#include <stddef.h>
#include <stdint.h>

#define VGATM_BASE_PTR 0xb8000
#define VGATM_WIDTH 80
#define VGATM_HEIGHT 25

extern size_t vgatm_x;
extern size_t vgatm_y;
extern uint8_t vgatm_color;
extern uint16_t *vgatm_cursor;

void vgatm_cls();
void vgatm_nav(const size_t x, const size_t y);
void vgatm_putchar(const uint8_t c);
void vgatm_write(const uint8_t c, const uint8_t color);
