#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// defining button and led pins
#define P_BUTTON 11
#define LED_PIN 10

// variables for millis()
bool led_state = false;
unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 250;

// variables for keypad
const byte ROWS = 4;
const byte COLS = 4;

// 2d array for keypad
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// assigning pins to rows and coloumns of keypad
byte row_pins[ROWS] = {9, 8, 7, 6};
byte col_pins[COLS] = {5, 4, 3, 2};

// making map for keypad
Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, ROWS, COLS);

// Set the LCD address to 0x27 for a 20x4 display
LiquidCrystal_I2C lcd(0x27, 20, 4);

// string to store multiple values from keypad
String input = "";
int amount = 0;
char get_key;
char key;


void setup() {
    lcd.init();  // initializing lcd
    Serial.begin(9600); // Initializing Serial Communication
    pinMode(P_BUTTON, INPUT);  // defining pinMode for power button
    pinMode(LED_PIN, OUTPUT);  // defining pinMode for led
}

void loop() {
    // Reading Power Button
    int p_button_state = digitalRead(P_BUTTON);

    // Using millis to keep power button ON
    if (p_button_state == HIGH && (millis() - last_debounce_time) > debounce_delay) {
        p_button();
    }

    // checking led state to On lcd and enabling permission to keypad
    if (led_state == true && get_key == 0) {
        home_screen();
        getkey();
    }
}

void p_button() {
    led_state = !led_state;  // Toggle LED state
    digitalWrite(LED_PIN, led_state ? HIGH : LOW);
    last_debounce_time = millis();
    Serial.println(led_state ? "LED ON" : "LED OFF");
    Serial.println(led_state ? "LCD: ON" : "LCD: OFF");
    if (led_state == false) {
        lcd.noBacklight();
        lcd.clear();
    }
}

void home_screen() {
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("1. Withdraw");
    lcd.setCursor(0, 1);
    lcd.print("2. Deposit");
    lcd.setCursor(0, 2);
    lcd.print("3. Check Balance");
}

void getkey() {
    get_key = keypad.getKey();
    if (get_key == '1') {
        withdraw_screen();
    }
}

void withdraw_screen() {
    lcd.clear();
    key = 0;
    while(key != '1' && key != '2' && key != '3' && key != '4' && key != '5' && key != '6' && key != '7')
    {
        key = keypad.getKey();
        lcd.setCursor(0, 0);
        lcd.print("1. 5000");
        lcd.setCursor(9, 0);
        lcd.print("2. 3000");
        lcd.setCursor(0, 1);
        lcd.print("3. 2000");
        lcd.setCursor(9, 1);
        lcd.print("4. 1000");
        lcd.setCursor(0, 2);
        lcd.print("5. 550");
        lcd.setCursor(9, 2);
        lcd.print("6. 200");
        lcd.setCursor(5, 3);
        lcd.print("7. Custom");
    }
    withdraw_selection();
}

void withdraw_selection() {
    key = key;
    switch (key)
    {
        case '1':
            case_1();
            break;

        case '2':
            case_2();
            break;

        case '3':
            case_3();
            break;

        case '4':
            case_4();
            break;

        case '5':
            case_5();
            break;

        case '6':
            case_6();
            break;

        case '7':
            case_7();
            break;

        default:
            break;
    }
}


void case_1() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 5000rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;  // Initialize to 0

    while (true) {
        char check_key = keypad.getKey();  // Continuously check for key press
    
        if (check_key) {  // If a valid key is pressed (key != 0)
            confirm_cancel_key = check_key;
        
            if (confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;  // Exit the loop when 'C' or 'D' is pressed
            }
        }
    }

    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_2() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 3000rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;

    while (true) {
        char check_key = keypad.getKey();

        if (check_key) {
            confirm_cancel_key = check_key;

            if(confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;
            }
        }
    }


    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_3() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 2000rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;
    
    while (true) {
        char check_key = keypad.getKey();

        if(check_key) {
            confirm_cancel_key = check_key;

            if(confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;
            }
        }
    }


    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_4() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 1000rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;  // Initialize to 0

    while (true) {
        char check_key = keypad.getKey();  // Continuously check for key press
    
        if (check_key) {  // If a valid key is pressed (key != 0)
            confirm_cancel_key = check_key;
        
            if (confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;  // Exit the loop when 'C' or 'D' is pressed
            }
        }
    }


    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_5() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 550rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;  // Initialize to 0

    while (true) {
        char check_key = keypad.getKey();  // Continuously check for key press
    
        if (check_key) {  // If a valid key is pressed (key != 0)
            confirm_cancel_key = check_key;
        
            if (confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;  // Exit the loop when 'C' or 'D' is pressed
            }
        }
    }

    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_6() {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Extract 200rs");
    lcd.setCursor(1, 2);
    lcd.print("C.Cancel");
    lcd.setCursor(10, 2);
    lcd.print("D.Confirm");

    char confirm_cancel_key = 0;  // Initialize to 0

    while (true) {
        char check_key = keypad.getKey();  // Continuously check for key press
    
        if (check_key) {  // If a valid key is pressed (key != 0)
            confirm_cancel_key = check_key;
        
            if (confirm_cancel_key == 'C' || confirm_cancel_key == 'D') {
                break;  // Exit the loop when 'C' or 'D' is pressed
            }
        }
    }


    if(confirm_cancel_key == 'D') {
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Dispensing Cash!");
        delay(5000);
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("Cash Dispensed!");
        delay(5000);
        lcd.clear();
        lcd.noBacklight();
    }

    else if(confirm_cancel_key == 'C') {
        withdraw_screen();
    }
}

void case_7() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1. 10");
    lcd.setCursor(9, 0);
    lcd.print("2. 20");
    lcd.setCursor(0, 1);
    lcd.print("3. 50");
    lcd.setCursor(9, 1);
    lcd.print("4. 100");
    lcd.setCursor(0, 2);
    lcd.print("5. 500");
    lcd.setCursor(9, 2);
    lcd.print("6. 1000");
    lcd.setCursor(5, 3);
    lcd.print("7. 5000");
    custom_withdraw_selection();
}

void custom_withdraw_selection() {
    char custom_withdraw_test_key = 0;
    char custom_withdraw_key = 0;
    while (true)
    {
        custom_withdraw_test_key = keypad.getKey();
    if (custom_withdraw_test_key) {
        custom_withdraw_key = custom_withdraw_test_key;
    }
    if(custom_withdraw_key == 'D') {
        break;
    }
    Serial.println(custom_withdraw_key);
    case_selection();
    }
    
    
}

void case_selection() {

}