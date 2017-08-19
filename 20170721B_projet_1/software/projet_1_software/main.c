/*
 * main.c
 *
 *  Created on: 2017-06-30
 *      Author: VINCENT GOSSELIN
 */


/* C Library */
#include <stdio.h>		// printf()
#include <string.h> 	// sprintf()

#include "io.h"
#include "alt_types.h"
#include "system.h"

//for 7-segments
#include "sseg_driver.h"

//for buttons
#include "button_reader.h"
#define BUTTONS_BASE 0x101020

//for audio
#include "audio_driver.h"


//There are 4 different state : 0 -> no-effect, 1 -> distortion, 2 -> delay, 3 -> octave
//default is no effect
int state = 0;
//State selection
void state_select(void);

int main(void)
{
	//FALLING Edge selected in Qsys.
	clear_all_edge_capture;

	//Configure audio chip. By default, Line IN is connected to Line OUT by the BYPASS scheme.
	audio_init();

	while(1)
	{

		//Guitar Pedal.

		display_int_to_sseg(state); //0 for no-effect
		state_select();
		switch (state){
		case 0 :
			audio_no_effect();
			break;

		case 1 :
			audio_distortion();
			break;

		case 2 :
			audio_delay();
			break;

		case 3 :
			audio_octave();
			break;

		}
	}
	return 0;
}

void state_select(void){
	if(edge_capture & key0_pressed){
		state = 0;
		//clear_key0;
	} else if(edge_capture & key1_pressed){
		state = 1;
		//clear_key1;
	} else if(edge_capture & key2_pressed){
		state = 2;
		//clear_key2;
	} else if(edge_capture & key3_pressed){
		state = 3;
		//clear_key3;
	}

	clear_all_edge_capture;
}




