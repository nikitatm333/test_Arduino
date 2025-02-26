const int mass_leds[3] = {9, 10, 11};
const int but1 = 6;
int currentMode = 0; // 0 - get_pwd_leds, 1 - leds_all_on
unsigned long previousMillis = 0;
const long interval = 100; // Интервал в миллисекундах для обновления яркости

void get_pwd_leds(void) {
  static int brightness = 0;
  static int fadeAmount = 10;

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }

    for (int i = 0; i < 3; i++) {
      analogWrite(mass_leds[i], brightness);
    }
  }
}

void leds_all_on(void) {
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
  static int lastButtonState = LOW;
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
