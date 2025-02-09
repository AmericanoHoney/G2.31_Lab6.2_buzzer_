#include <Arduino.h>

#define BUZZER_PIN  21  // Buzzer pin
#define BUTTON_PIN  35  // Button pin

hw_timer_t *My_timer = NULL;

int notes[] = {
  523, 587, 698, 784, 880, 698, 784, 880, 1047, 880,
  880, 1047, 1175, 1397, 1175, 0,
  1397, 1175, 1047, 880, 1047, 1175, 1047,
  1047, 880, 784, 698, 784, 880, 784, 523, 587, 698, 784, 880
};

int durations[] = { 
  250, 250, 250, 250, 1100, 250, 200, 350, 250, 1100,
  250, 250, 350, 250, 1300, 300,
  250, 250, 250, 250, 250, 250, 400,
  250, 250, 250, 250, 250, 250, 400, 250, 250, 250, 250, 1200 
};

int speedLevels[] = {900, 700, 500, 300, 100};
int speed = 2; // Start with normal speed (index 2)
int numNotes = sizeof(notes) / sizeof(notes[0]);


int noteIndex = 0;

// Button interrupt handler
void IRAM_ATTR onButtonPress() {
  speed = (speed + 1) % 5;
  Serial.println(speed);
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  // Setup the button interrupt
  attachInterrupt(BUTTON_PIN, onButtonPress, RISING);
  Serial.begin(115200);
}

void loop() {
  //delay(speedLevels[speed]);
  for(int i = 0;i < numNotes;i++){
    tone(BUZZER_PIN, notes[i], durations[i]);
    delay(durations[i] + speedLevels[speed]);
    noTone(BUZZER_PIN);
  }
  delay(3000);
}