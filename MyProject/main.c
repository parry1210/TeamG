#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
#include <main.h>

#include "motors.h"

#include "sensors/proximity.h"

#include "epuck1x/uart/e_uart_char.h"
#include "stdio.h"
#include "serial_comm.h"



messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);


int main(void)
{
	    halInit();
		chSysInit();
		mpu_init();
		messagebus_init(&bus,&bus_lock,&bus_condvar);//proximity

		motors_init();

		proximity_start();
		calibrate_ir();

		serial_start();
		void e_send_uart1_char(const char * buff, int buff_len);

		/* Infinite loop. */
		while (1) {
	    	//waits 1 second
	    	chThdSleepMilliseconds(50);
	    	left_motor_set_speed(500);
	    	right_motor_set_speed(500);

	    	int str_length;
	    	char str[100];
	    	int prox_values[8];

	    	for(int i=0;i<8;i++)
	    	{
	          	prox_values[i]=get_calibrated_prox(i);
	          	str_length=sprintf(str,"prox_values %d is %d\n",i,prox_values[i]);
	          	e_send_uart1_char(str,str_length);
	          	chThdSleepMilliseconds(50);
	    	}

	    	if (prox_values[0]>50&&prox_values[7]>50){
	    		bool turn_left=(prox_values[1]+prox_values[2])>(prox_values[6]+prox_values[5]);
	    	    bool turn_right=(prox_values[1]+prox_values[2])<(prox_values[6]+prox_values[5]);
	    	    if(turn_left){
	    	    	left_motor_set_speed(-1000);
	        	    right_motor_set_speed(1000);
	        	    chThdSleepMilliseconds(500);
	    	    }
	    	    if(turn_right){
	    	    	left_motor_set_speed(1000);
	        	    right_motor_set_speed(-1000);
	        	    chThdSleepMilliseconds(500);
	    	    }
	        }

		 }

}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
