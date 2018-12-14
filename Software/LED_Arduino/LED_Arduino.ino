// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN 3
#define PWM_LED_OUT 10
#define PWM_MAX 255

// global variables representing "state" across all functions
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool BUTTON_PUSHED = false;
int previous_button_state = 0;
int PWM_OUT = 0;
int last_debounce = 0;

// executed one-time at device startup
void setup() {

   attachInterrupt(digitalPinToInterrupt(BUTTON_IN), button_pressed, FALLING);
   // define output (PWM) pin connected to LED
   Serial.begin(9600);

}

// continually-running loop
// calls functions that are named as "actions"
void loop(){
  //check_button_press();
  
  shine_led();
//  Serial.print(operating_mode);
  //Serial.print(PWM_OUT);
  set_pwm_based_on_operating_mode();
}

void set_pwm_based_on_operating_mode() {
    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
            break;
        case 1:
            PWM_OUT = PWM_MAX;
            break;
        case 2:
            PWM_OUT = int(PWM_MAX/2);
            Serial.println("HERE");
            break;
        case 3:
            PWM_OUT = int(PWM_MAX/4);
            break;
        case 4:
            flash_the_light();
            break;
        case 5:
            PWM_OUT = 0;
            break;
    }
    //Serial.println(operating_mode);
    //Serial.println(PWM_OUT);

}

void button_pressed() {
  if((millis()-last_debounce)>300){
    BUTTON_PUSHED = true;
//    Serial.print("PUSH");
    check_button_press();
  }
  last_debounce=millis();
}

void flash_the_light() {
  //insert code for flashing the light
  analogWrite(PWM_LED_OUT, PWM_MAX);
  delay(500/FLASH_RATE_HZ);
  analogWrite(PWM_LED_OUT, 0);
  delay(500/FLASH_RATE_HZ);
}

void shine_led() {
    if(operating_mode==4){
      flash_the_light();
    }
    else{
      analogWrite(PWM_LED_OUT, PWM_OUT);
    }
}

void check_button_press() {
  
    if (BUTTON_PUSHED == true) {
        operating_mode = operating_mode + 1;
        Serial.print("Changed");
        if (operating_mode == 5) {
            operating_mode = 0;
        }
    }
    set_pwm_based_on_operating_mode();
    BUTTON_PUSHED = false;
}
