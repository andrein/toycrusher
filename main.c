#include "global.h"

#include "motor.h"
#include "usart.h"
#include "button.h"
#include "sensors.h"

#define SONAR_RANGE 120

void setup(void){
  motor_setup();
  usart_setup();
  button_setup();
  sensors_setup();
}

robot_state state = STOP;

int main(void){
  setup();

  line_sensor line_sensors;
  line_sensor last_sensor = FRONT_LEFT;
  
  while (1){
    if ((line_sensors = read_line_sensors())){
	state = (state == STOP) ? STOP : EVADE;
    }
    
    switch(state){
      case SEEK:
	printf("STATE: seek\n");

	while(read_sonar() > SONAR_RANGE){
	  if (last_sensor == FRONT_RIGHT){
	    spin_left(255);
	  } else {
	    spin_right(255);
	  }
	}
	state = TARGET;
	break;
      
      case TARGET:
	printf("STATE: target\n");
	
	switch (read_front_sensors()){
	  case FRONT_TARGET_LEFT:
	    steer_left(255);
	    break;
	  case FRONT_TARGET_RIGHT:
	    steer_right(255);
	    break;
	  case FRONT_TARGET_LEFT | FRONT_TARGET_RIGHT:
	    go_forward(255);
	    break;
	  default:
	    go_forward(255);
	    if (read_sonar() > SONAR_RANGE)
	      state = SEEK;
	}
	break;
      
      case ATTACK:
	printf("STATE: attack\n");
	go_forward(255);
	break;
      
      case EVADE:
	printf("STATE: evade\n");
	
	do{
	  switch(line_sensors){
	    case FRONT_LEFT:
	      printf("EVADE: FRONT_LEFT\n");
	      spin_right(255);
	      last_sensor = FRONT_LEFT;
	      _delay_ms(500);
	    break;
	    
	    case FRONT_RIGHT:
	      printf("EVADE: FRONT_RIGHT\n");
	      last_sensor = FRONT_RIGHT;
	      spin_left(255);
	      _delay_ms(500);
	    break;
	    
	    case FRONT_LEFT | FRONT_RIGHT:
	      printf("EVADE: FRONT\n");
	      go_reverse(255);
	      _delay_ms(1000);
	      brake();
	      spin_left(255);
	      _delay_ms(1000);
	      brake();
	      go_forward(255);
	    break;
	  }
	} while((line_sensors = read_line_sensors()));
	state = SEEK;
	
	break;
      case STOP:
	printf("STATE: stopped\n");
	break;
    }
  }
  return 0;
}
