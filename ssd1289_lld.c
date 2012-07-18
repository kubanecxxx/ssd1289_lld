/*
 * LCD_STM32F4.c
 *
 *  Created on: 11.4.2012
 *      Author: martin
 */

/* Includes ******************************************************************/

#include "ssd1289_lld.h"
#include "ssd1289_port.h"

/* Private Variables *********************************************************/
/* Functions *****************************************************************/

/*
 * Clear the screen.
 */
void Clear_Screen(uint16_t color)
{
	uint32_t i = 0;

	Set_Cursor(0, 0);

	i = 0x12C00;
	Write_GDDRAM_Prepare();
	while (i--)
	{
		Write_Data(color);
	}
}

/*
 * Set Cursor to Position [x, y].
 */
void Set_Cursor(uint16_t x, uint16_t y)
{
	/* Check if pixel position fits onto display. */
	if (x > LCD_X_SIZE)
		x = LCD_X_SIZE;
	if (y > LCD_Y_SIZE)
		y = LCD_Y_SIZE;

	Write_Command_Data(0x004E, x);
	Write_Command_Data(0x004F, y);
}

/*
 * Draw a Single Pixel on Position [x, y].
 */
void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
	Set_Cursor(x, y);
	Write_GDDRAM_Prepare();
	Write_Data(color);
}

/*
 * Draw an image in format GRB565.
 * x, y - position, where to start displaying.
 * x_res, y_res - resolution in pixels.
 * *ptr_image - pointer to image array.
 */
void Draw_Image(uint16_t x, uint16_t y, uint16_t x_res, uint16_t y_res,
		const uint16_t *ptr_image)
{
	uint16_t i = 0, j = 0;

	for (i = 0; i < x_res; i++)
	{
		Set_Cursor((x + i), y);
		Write_GDDRAM_Prepare();

		for (j = 0; j < y_res; j++)
		{
			Write_Data(*(ptr_image++));
		}
	}
}

/*
 * Reset and Initialize Display.
 */
void Init_LCD(void)
{

	ssd1289_low_level_init();

	/* Reset */CLR_RES();
	Delay_ms(30);
	SET_RES();
	Delay_ms(10);

#define martin

#ifdef martin
#define Write_Command Write_Command_Data
	Write_Command(0x0007, 0x0021);
	Write_Command(0x0000, 0x0001);
	Write_Command(0x0007, 0x0023);
	Write_Command(0x0010, 0x0000); /* Exit Sleep Mode */
	Delay_ms(30);
	Write_Command(0x0007, 0x0033);

	/*
	 * Entry Mode R11h = 6018h
	 *
	 * DFM1 = 1, DFM0 = 1 => 65k Color Mode
	 * ID0 = 1, AM = 1    => the way of automatic incrementing
	 *                       of address counter in RAM
	 */
	Write_Command(0x0011, 0x6018);
	Write_Command(0x0002, 0x0600); /* AC Settings */

	/* Initialize other Registers */

	/*
	 * Driver Output Control R01h = 2B3Fh
	 *
	 * REV = 1            => character and graphics are reversed
	 * BGR = 1            => BGR color is assigned from S0
	 * TB  = 1            => sets gate output sequence (see datasheet page 29)
	 * MUX[8, 5:0]        => specify number of lines for the LCD driver
	 */
	Write_Command(0x0001, 0x2B3F);
#else
	Write_Command_Data(0x0000, 0x0001);
	Write_Command_Data(0x0003, 0xA8A4);
	Write_Command_Data(0x000C, 0x0000);
	Write_Command_Data(0x000D, 0x800C);
	Write_Command_Data(0x000E, 0x2B00);
	Write_Command_Data(0x001E, 0x00B7);
	Write_Command_Data(0x0001, 0x2B3F);
	Write_Command_Data(0x0002, 0x0600);
	Write_Command_Data(0x0010, 0x0000);
	Write_Command_Data(0x0011, 0x6070);
	Write_Command_Data(0x0005, 0x0000);
	Write_Command_Data(0x0006, 0x0000);
	Write_Command_Data(0x0016, 0xEF1C);
	Write_Command_Data(0x0017, 0x0003);
	Write_Command_Data(0x0007, 0x0233);
	Write_Command_Data(0x000B, 0x0000);
	Write_Command_Data(0x000F, 0x0000);
	Write_Command_Data(0x0041, 0x0000);
	Write_Command_Data(0x0042, 0x0000);
	Write_Command_Data(0x0048, 0x0000);
	Write_Command_Data(0x0049, 0x013F);
	Write_Command_Data(0x004A, 0x0000);
	Write_Command_Data(0x004B, 0x0000);
	Write_Command_Data(0x0044, 0xEF95);
	Write_Command_Data(0x0045, 0x0000);
	Write_Command_Data(0x0046, 0x013F);
	Write_Command_Data(0x0030, 0x0707);
	Write_Command_Data(0x0031, 0x0204);
	Write_Command_Data(0x0032, 0x0204);
	Write_Command_Data(0x0033, 0x0502);
	Write_Command_Data(0x0034, 0x0507);
	Write_Command_Data(0x0035, 0x0204);
	Write_Command_Data(0x0036, 0x0204);
	Write_Command_Data(0x0037, 0x0502);
	Write_Command_Data(0x003A, 0x0302);
	Write_Command_Data(0x003B, 0x0302);
	Write_Command_Data(0x0023, 0x0000);
	Write_Command_Data(0x0024, 0x0000);
	Write_Command_Data(0x0025, 0x8000);
	Write_Command_Data(0x004f, 0x0000);
	Write_Command_Data(0x004e, 0x0000);
#endif
	Write_GDDRAM_Prepare();

}

/*
 * Write to LCD RAM.
 */
void Write_Command_Data(uint16_t reg, uint16_t data)
{
	ssd1289_low_level_output_address(reg);
	ssd1289_low_level_output_data(data);
}

/*
 * Prepares writing to GDDRAM.
 * Next coming data are directly displayed.
 */
void Write_GDDRAM_Prepare(void)
{
	ssd1289_low_level_output_address(GDDRAM_PREPARE);
}

/*
 * Writes data to last selected register.
 * Used with function Write_GDDRAM_Prepare().
 */
void Write_Data(uint16_t data)
{
	ssd1289_low_level_output_data(data);
}

