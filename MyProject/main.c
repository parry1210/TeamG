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

messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);


int main(void)
{

    halInit();
    chSysInit();
    mpu_init();
    
    messagebus_init(&bus,&bus_lock,&bus_condvar);
    
    motors_init();
    
    proximity_start();
    calibrate_ir();


    /* Infinite loop. */
    while (1) {
    	//waits 1 second
        chThdSleepMilliseconds(100);
        
        left_motor_set_speed(500);
        right_motor_set_speed(500);
        
        if
        get_prox(0);
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
