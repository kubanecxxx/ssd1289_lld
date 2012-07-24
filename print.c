/**
 * @file characters.c
 * @author kubanec
 * @date 24.7.2012
 *
 */

#include "inttypes.h"
#include "fonts/fonts.h"
#include "string.h"
#include "ssd1289_lld.h"

#define lcdDrawPixel tft_DrawPixel
#define lcdDrawRectangle tft_DrawRectangle

/*************************************************/
/**
 * @brief dierect put char to display
 * @param character to be sent to display
 * @param x coordinate
 * @param y coordinate
 * @param color 16-bit
 * @param size of font
 */
void disp_Putchar(uint8_t znak, uint16_t x, uint16_t y, uint16_t color,
		uint8_t size)
{

	uint8_t i, j;
	uint32_t temp;
	const uint8_t * temp2 = Fonts_GetChar(znak, size);

	if (size == 8)
		for (i = 0; i < size; i++)
		{
			temp = temp2[i];
			for (j = 0; j < size; j++)
			{
				if (temp & (1 << j))
				{
					lcdDrawPixel(x + i, y + j, color);
				}
			}
		}
	if (size == 16)
		for (i = 0; i < size; i++)
		{
			temp = temp2[i];
			temp |= (temp2[i + 16] << 8);
			//endian conversion
			//temp = (temp1 << 8) | (temp1 >> 8);
			for (j = 0; j < size; j++)
			{
				if (temp & (1 << j))
				{
					lcdDrawPixel(x + i, y + j, color);
				}
			}
		}
}

/**
 * @brief direct put string to display, using lcdPutchar
 * @param data - null terminated string of characters
 * @param x  coordinate of the first char
 * @param y  coordinate of the first char
 * @param color 16-bit
 * @param size of font
 */
void disp_PutString(const char * data, uint16_t x, uint16_t y, uint16_t color,
		uint8_t size)
{
	while (*data != 0)
	{
		disp_Putchar((uint8_t) *(data++), x, y, color, size);
		x += size;
	}
}

/**
 * @brief put string on display with background
 * @param data - null terminated string of characters
 * @param x  coordinate of the first char
 * @param y  coordinate of the first char
 * @param color 16-bit text color
 * @param backgroud_color
 * @param size of font
 */
void disp_PutsStringBackground(const char * data, uint16_t x, uint16_t y,
		uint16_t color, uint16_t background_color, uint8_t size)
{
	uint16_t x2 = size * strlen(data);

	lcdDrawRectangle(x, y, x + x2, y + size, background_color);

	disp_PutString(data, x, y, color, size);

}
