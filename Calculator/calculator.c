 /******************************************************************************
 *
 * Module: CALCULATOR
 *
 * File Name: calculator.c
 *
 * Description: Source file for the calculator driver
 *
 * Author: Ali Sadek
 *
 *******************************************************************************/

#include "calculator.h"

/****************************Variable Declarations******************************/

uint8 key;
uint8 mul=0, add=0, sub=0, divide=0, equal;
uint32 operand[2];
uint32 lastNum=0;

/**********************************************************************************
* 				Functions Definitions				  *
* ********************************************************************************/
void mult(uint32 x, uint32 y)
{
	mul=0;
	uint64 result;
	result= x*y;
	LCD_integerToString((unsigned long long) result);
}
void addition(uint32 x, uint32 y)
{
	add=0;
	LCD_integerToString(x+y);
}
void subtraction(uint32 x, uint32 y)
{
	sub=0;
	LCD_integerToString(x-y);
}
void division(uint32 x, uint32 y)
{
	divide=0;
	LCD_integerToString(x/y);
}
int main(void)
{

LCD_init();

uint32 *arrPtr = operand;

	while(1)
	{
		key=KeyPad_getPressedKey();
		/*New Button Every 500ms*/
		_delay_ms(500);

		if((key<=9) && (key>=0))
		{
			LCD_integerToString(key);
			*arrPtr= (uint32)key;
		}
		while ((key<=9) && (key>=0))
		{
			key=KeyPad_getPressedKey();
			_delay_ms(500);
			if (!((key<=9) && (key>=0)))
				break;
			LCD_integerToString(key);
			*arrPtr= (*arrPtr*10)+key;
		}

			switch(key)
			{
			lastNum =0;
			case '*':
				mul=1;
				LCD_displayCharacter(key);
				arrPtr++;
			break;
			case '/':
				divide=1;
				LCD_displayCharacter(key);
				arrPtr++;
			break;
			case '-':
				sub=1;
				LCD_displayCharacter(key);
				arrPtr++;
			break;
			case '+':
				add=1;
				LCD_displayCharacter(key);
				arrPtr++;
			break;
			default:break;
			}
			if (key=='=')
			{
				LCD_displayCharacter(key);
				if (mul==1)
				{
					mult(operand[0], operand[1]);
				}
				else if (add==1)
				{
					addition(operand[0], operand[1]);
				}
				else if (sub==1)
				{
					subtraction(operand[0], operand[1]);
				}
				else if (divide==1)
				{
					division(operand[0], operand[1]);
				}
			}
		}
	}

