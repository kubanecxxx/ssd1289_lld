/*
 * LCD_STM32F4.h
 *
 *  Created on: 11.4.2012
 *      Author: martin
 */

/*
 *
 * Display coordinates:
 *  [x,y]
 *     [0,319]                                 [0,0]
 *       -----------------------------------------
 *       |                                       |
 *       |                                       |
 *       |                                       |
 *       |                                       |
 *       |             TOUCH DISPLAY             |
 *       |                                       |
 *       |                                       |
 *       |                                       |
 *       |                                       |
 *       -----------------------------------------
 *   [239,319]                               [239,0]
 */

#ifndef _SSD1289_LLD_H_
#define _SSD1289_LLD_H_

/* Includes ******************************************************************/

#include "inttypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Display size in x and y axis in pixels */
#define LCD_X_SIZE          239
#define LCD_Y_SIZE          319

#define GDDRAM_PREPARE      0x0022  /* Graphic Display Data RAM Register. */

#define LCD_WHITE           0xFFFF
#define LCD_BLACK           0x0000
#define LCD_GREEN           0x07E0
#define LCD_RED             0xF800
#define LCD_BLUE            0x001F
#define LCD_GREY            0xF7DE
#define LCD_ORANGE          0xFA20
#define LCD_YELLOW          0xFFE0

/* Public Function Prototypes *******************************************************/
void tft_ClearScreen(uint16_t color);
void tft_SetCursor(uint16_t x, uint16_t y);
void tft_DrawImage(uint16_t x, uint16_t y, uint16_t x_res, uint16_t y_res,
		const uint16_t *ptr_image);
void tft_InitLCD(void);
void tft_Write_Command(uint16_t address, uint16_t data);
void tft_Write_GDDRAM_Prepare(void);
void tft_Write_Data(uint16_t data);
void tft_Write_Command_Data(uint16_t address, uint16_t data);
void tft_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void tft_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t color);

//user should implement this function in port file
void Delay_ms(uint32_t nTime);

#ifdef __cplusplus
}
#endif

#endif //_SSD1289_LLD_H_
