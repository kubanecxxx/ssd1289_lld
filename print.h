/**
 * @file characters.h
 * @author kubanec
 * @date 24.7.2012
 *
 */

#ifndef CHARACTERS_H_
#define CHARACTERS_H_

#ifdef __cplusplus
extern "C"
{
#endif

void disp_Putchar(uint8_t znak, uint16_t x, uint16_t y, uint16_t color,
		uint8_t size);
void disp_PutString(const char * data, uint16_t x, uint16_t y, uint16_t color,
		uint8_t size);
void disp_PutsStringBackground(const char * data, uint16_t x, uint16_t y,
		uint16_t color, uint16_t background_color, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif /* CHARACTERS_H_ */
