/*
 * button_app.h
 *
 *  Created on: Apr 11, 2014
 *      Author: adjikharisma
 */

#ifndef BUTTON_APP_H_
#define BUTTON_APP_H_

#include <DAVE3.h>

#define UP_BTN	11 	//PB4 P5.11
#define DWN_BTN	10 	//PB3 P5.10
#define ESC_BTN	9 	//PB2 P5.9
#define SET_BTN	8 	//PB1 P5.8

#define _UP_PRESSED 	!(RD_REG(PORT5->IN,PORT5_IN_P11_Msk,PORT5_IN_P11_Pos))
#define _DWN_PRESSED	!(RD_REG(PORT5->IN,PORT5_IN_P10_Msk,PORT5_IN_P10_Pos))
#define	_ESC_PRESSED	!(RD_REG(PORT5->IN,PORT5_IN_P9_Msk,PORT5_IN_P9_Pos))
#define	_SET_PRESSED	!(RD_REG(PORT5->IN,PORT5_IN_P8_Msk,PORT5_IN_P8_Pos))
#define	_NOT_PRESSED	(!_UP_PRESSED) && (!_DWN_PRESSED) && (!_ESC_PRESSED) && (!_SET_PRESSED)

void Button_Init(void);
void Button_Read(char *button, char *flag_push);


#endif /* BUTTON_APP_H_ */
