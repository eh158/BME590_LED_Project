// use preprocessor directives to define constants in the code
#define FLASH_RATE_HZ 2
#define BUTTON_IN D1
#define PWN_LED_OUT D11
#define PWM_MAX 255

// global variables representing "state" across all functions
// operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
int operating_mode = 0;
bool BUTTON_PUSHED = false;
int previous_button_state = 0;
int PWM_OUT = 0;

// executed one-time at device startup
void setup() {

   attachInterrupt(BUTTON_IN, button_pushed, FALLING);
   // define output (PWM) pin connected to LED

}

// continually-running loop
// calls functions that are named as "actions"
void loop(){

    check_for_button_press();

    shine_led();

}

void set_pwm_based_on_operating_mode() {

    switch (operating_mode) {
        case 0:
            PWM_OUT = 0;
        case 1:
            PWM_OUT = PWM_MAX;
        case 2:
            PWN_OUT = int(PWM_MAX/2);
        case 3:
            PWN_OUT = int(PWM_MAX/4);
        case 4:
            flash_the_light();
    }

}

void button_pushed() {
    BUTTON_PUSHED = true;
}

void flash_the_light() {
  //insert code for flashing the light
}

void shine_led() {
    analogWrite(PWM_LED_OUT, PWM_OUT);
}

void check_button_press() {
    if (BUTTON_PUSHED == true) {
        operating_mode = operating_mode + 1;
        if (operating_mode == 5) {
            operating_mode = 0;
        }
    }
    set_pwm_based_on_operating_mode();
    BUTTON_PUSHED = false
}
