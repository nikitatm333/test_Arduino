const int mass_leds[3] = {9, 10, 11};
const int but1 = 6;
int currentMode = 0; // 0 - get_pwd_leds, 1 - leds_all_on

void get_pwd_leds(void) {
  for (int i = 0; i < 255; i = i + 10) {
    analogWrite(mass_leds[0], i);
    analogWrite(mass_leds[1], i);
    analogWrite(mass_leds[2], i);
    delay(100);
  }
  for (int i = 255; i > 0; i = i - 10) {
    analogWrite(mass_leds[0], i);
    analogWrite(mass_leds[1], i);
    analogWrite(mass_leds[2], i);
    delay(100);
  }
}

void leds_all_on(void) {
  // Включение всех светодиодов на максимальную яркость
  for (int i = 0; i < 3; i++) {
    analogWrite(mass_leds[i], 255);
  }
}

void setup() {
  // Инициализация пинов светодиодов
  for (int i = 0; i < 3; i++) {
    pinMode(mass_leds[i], OUTPUT);
  }
  // Инициализация пина кнопки
  pinMode(but1, INPUT);
}

void loop() {
  int lastButtonState = LOW;
  int buttonState = digitalRead(but1);

  // Проверка на изменение состояния кнопки
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Переключение режима
    currentMode = 1 - currentMode;
    delay(200); // Задержка для предотвращения дребезга
  }

  // Выполнение действия в зависимости от текущего режима
  if (currentMode == 0) {
    get_pwd_leds();
  } else {
    leds_all_on();
  }

  lastButtonState = buttonState;
}
