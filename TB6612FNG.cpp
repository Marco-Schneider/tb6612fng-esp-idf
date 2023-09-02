#include "TB6612FNG.h"

#define DEFAULT_FREQUENCY 10000

Motor::Motor(gpio_num_t IN1, gpio_num_t IN2, gpio_num_t PWM, gpio_num_t STBY,
             mcpwm_unit_t unit, mcpwm_timer_t timer, mcpwm_io_signals_t iosig, mcpwm_operator_t op) {
  
  this->IN1 = IN1;
  this->IN2 = IN2;
  this->PWM = PWM;
  this->STBY = STBY;

  gpio_set_direction(IN1, GPIO_MODE_OUTPUT);
  gpio_set_direction(IN2, GPIO_MODE_OUTPUT);

  mcpwm_gpio_init(unit, iosig, PWM);

  mcpwm_config_t config;
  config.frequency = DEFAULT_FREQ;
  config.cmpr_a = 0;
  config.cmpr_b = 0;
  config.counter_mode = MCPWM_UP_COUNTER;
  config.duty_mode = MCPWM_DUTY_MODE_0;

  mcpwm_init(unit, timer, &config);
}

Motor::~Motor() {
  gpio_set_level(IN1, 0);
  gpio_set_level(IN2, 0);
  mcpwm_stop(unit, timer);
}

Motor::drive(float speed) {
  gpio_set_level(STBY, 1);
  if(speed >= 0) {
    gpio_set_level(IN1, 0);
    gpio_set_level(IN2, 1);
    mcpwm_set_duty(unit, timer, op, speed);
  } 
  else {
    gpio_set_level(IN1, 1);
    gpio_set_level(IN2, 0);
    mcpwm_set_duty(unit, timer, op, -speed);
  }
}