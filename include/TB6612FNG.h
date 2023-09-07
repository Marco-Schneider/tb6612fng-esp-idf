#pragma once

#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"

#define MOTOR0  MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0A, MCPWM_OPR_A
#define MOTOR1  MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM1A, MCPWM_OPR_A
#define MOTOR2  MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM2A, MCPWM_OPR_A
#define MOTOR3  MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM0A, MCPWM_OPR_A
#define MOTOR4  MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM1A, MCPWM_OPR_A
#define MOTOR5  MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM2A, MCPWM_OPR_A
#define MOTOR6  MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM0B, MCPWM_OPR_B
#define MOTOR7  MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM1B, MCPWM_OPR_B
#define MOTOR8  MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM2B, MCPWM_OPR_B
#define MOTOR9  MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM0B, MCPWM_OPR_B
#define MOTOR10 MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM1B, MCPWM_OPR_B
#define MOTOR11 MCPWM_UNIT_1, MCPWM_TIMER_2, MCPWM2B, MCPWM_OPR_B

class Motor 
{
  public:
    Motor(gpio_num_t IN1, gpio_num_t IN2, gpio_num_t PWM, gpio_num_t STBY, int offset,
      mcpwm_unit_t unit, mcpwm_timer_t timer, mcpwm_io_signals_t iosig, mcpwm_operator_t op);

    ~Motor();

    // Drives the motors, the direction is given by the sign
    // Expects one value between -100 <= 0 <= 100 (% of duty cycle)
    void drive(float speed);

    // Sets the STBY pin to low, thus stopping the motors
    void standby();
    
  private:
    gpio_num_t IN1, IN2, PWM, STBY;
    int offset;
    mcpwm_unit_t unit;
    mcpwm_timer_t timer;
    mcpwm_io_signals_t iosig;
    mcpwm_operator_t op;
};