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
        
        for(int i=0;i<8;i++){
            prox_values[i]=get_prox(i);
        }
        
        if(prox_values[0]==106||prox_values[1]==151||prox_values[2]==2147){
            chThdSleepMilliseconds(100);
            left_motor_set_speed(300);
            right_motor_set_speed(-300);
        else if(prox_values[7]==330||prox_values[6]==3658||prox_values[5]==59){
            chThdSleepMilliseconds(100);
            left_motor_set_speed(-300);
            right_motor_set_speed(300);
        else if(prox_values[3]==1||prox_values[4]==1{
            chThdSleepMilliseconds(100);
            left_motor_set_speed(500);
            right_motor_set_speed(500);
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
