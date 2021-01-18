#include <LiquidCrystal.h>
bool isArrayEqual(char [], char []);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int ARRAY_SIZE = 6;
int NOTA_START = 350;
int NOTA1 = 440;
int NOTA2 = 494;
int NOTA3 = 420;
int NOTA_ERROR = 600;
int BUZZER_PIN = 8;
int BUTTON1_PIN = 6;
int BUTTON2_PIN = 7;
char morsCodes[ARRAY_SIZE];
int codeCounter = 0;
int letterCounter = 0;
int HC_ECHO = 9;
int HC_TRG = 10;
int MORS_CODE_LENGTH = 26;
char words[] = "                ";
char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890.,? ";
char *letterMorsCodes[] = {
    "._    ", // A
    "_...  ", // B
    "_._.  ", // C
    "_..   ", // D
    ".     ", // E
    ".._.  ", // F
    "__.   ", // G
    "....  ", // H
    "..    ", // I
    ".___  ", // J
    "_._   ", // K
    "._..  ", // L
    "__    ", // M
    "_.    ", // N
    "___   ", // O
    ".__.  ", // P
    "__._  ", // Q
    "._.   ", // R
    "...   ", // S
    "_     ", // T
    ".._   ", // U
    "..._  ", // V
    ".__   ", // W
    "_.._  ", // X
    "_.__  ", // Y
    "__..  ", // Z
    ".____ ", // 1
    "..___ ", // 2
    "...__ ", // 3
    "...._ ", // 4
    "..... ", // 5
    "_.... ", // 6
    "__... ", // 7
    "___.. ", // 8
    "____. ", // 9
    "_____ ", // 0
    "._._._", // .
    "__..__", // ,
    "..__..", // ?
    "      ", //  
};

void setup() {
  lcd.begin(16, 2);
  lcd.print("write something!");
  pinMode(BUTTON1_PIN, INPUT);
  pinMode(BUTTON2_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(HC_ECHO, INPUT);
  pinMode(HC_TRG, OUTPUT);
  Serial.begin(9600);
  tone(BUZZER_PIN, NOTA_START);
  delay(500);
  noTone(BUZZER_PIN);
}

void loop() {
  bool isEqual = false;
  if(digitalRead(BUTTON1_PIN) == HIGH) {
    morsCodes[codeCounter] = '.';
    codeCounter++;
    lcd.setCursor(0, 1);
    lcd.print(morsCodes);
    tone(BUZZER_PIN, NOTA1);
    delay(500);
    noTone(BUZZER_PIN);
  }
  if(digitalRead(BUTTON2_PIN) == HIGH) {
    morsCodes[codeCounter] = '_';
    codeCounter++;
    lcd.setCursor(0, 1);
    lcd.print(morsCodes);
    tone(BUZZER_PIN, NOTA2);
    delay(500);
    noTone(BUZZER_PIN);
  }

  long duration;
  digitalWrite(HC_TRG, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(HC_TRG, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(HC_TRG, LOW);
  duration = pulseIn(HC_ECHO, HIGH);
  if(duration < 600) {
    for(int i = codeCounter; i<ARRAY_SIZE; i++) {
      morsCodes[i] = ' ';
    }
    for(int i = 0; i<40; i++) {
      isEqual = isArrayEqual(letterMorsCodes[i], morsCodes);
      if(isEqual) {
        words[letterCounter] = letters[i];
        lcd.setCursor(0, 0);
        lcd.print(words);
        tone(BUZZER_PIN, NOTA3);
        delay(200);
        noTone(BUZZER_PIN);
        letterCounter++;
        break;
      }
    }
    if(isEqual == false) {
      tone(BUZZER_PIN, NOTA_ERROR);
      delay(500);
      noTone(BUZZER_PIN);
    }
    for(int i=0; i<ARRAY_SIZE; i++) {
      morsCodes[i] = ' '; 
    }
    lcd.setCursor(0, 1);
    lcd.print(morsCodes);
    codeCounter = 0;
    delay(500);
  }
}

bool isArrayEqual(char arr1[], char arr2[]) {
  for(int i = 0; i<ARRAY_SIZE; i++) {
    if(arr1[i] != arr2[i]) return 0;
  }
  return 1;
}
