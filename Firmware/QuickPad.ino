// QuickPad firmware (Arduino IDE)
// Seeed XIAO RP2040 + 6 keys + 0.91" SSD1306 OLED + DS3231 clock + EC11 encoder
//
// Board package: "Raspberry Pi Pico/RP2040" by Earle F. Philhower
//   Tools > Board > Raspberry Pi Pico/RP2040 > Seeed XIAO RP2040
// Libraries (Library Manager): Adafruit SSD1306, Adafruit GFX Library, RTClib
//
// Pins below are RP2040 GPIO numbers, matched to the XIAO's D-pin labels.

#include <Wire.h>
#include <Keyboard.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

// ---------------- Pins (from the QuickPad schematic) ----------------
const uint8_t KEY_PINS[6] = {
  26,  // D0  -> SW1
  27,  // D1  -> SW2
  28,  // D2  -> SW3
  29,  // D3  -> SW4
  2,   // D8  -> SW5
  4    // D9  -> SW6
};
const uint8_t PIN_SDA = 6;  // D4
const uint8_t PIN_SCL = 7;  // D5
const uint8_t ENC_A   = 0;  // D6
const uint8_t ENC_B   = 1;  // D7
const uint8_t ENC_BTN = 3;  // D10

// ---------------- Settings you can change ----------------
// What each key sends, in order SW1..SW6. F13-F18 don't clash with anything.
const uint8_t KEYMAP[6] = { KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18 };

const bool    SCREEN_UPSIDE_DOWN = true;   // OLED is mounted upside down
const bool    USE_24_HOUR        = false;  // true shows 15:09 instead of 3:09 PM
const uint8_t OLED_ADDRESS       = 0x3C;   // a few OLEDs use 0x3D
const bool    REVERSE_KNOB       = false;  // flip if the knob turns the wrong way

// USB media codes (HID consumer page)
const uint16_t MEDIA_VOL_UP   = 0xE9;
const uint16_t MEDIA_VOL_DOWN = 0xEA;
const uint16_t MEDIA_MUTE     = 0xE2;

// ---------------- Hardware objects ----------------
Adafruit_SSD1306 display(128, 32, &Wire, -1);
RTC_DS3231 rtc;
bool rtcFound = false;

// ---------------- Rotary encoder (read with interrupts) ----------------
// Tracks every A/B transition; an EC11 makes 4 transitions per click.
volatile int32_t encCount = 0;
volatile uint8_t encState = 0;
const int8_t QUAD_TABLE[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void encoderISR() {
  encState = ((encState << 2) | (digitalRead(ENC_A) << 1) | digitalRead(ENC_B)) & 0x0F;
  encCount += QUAD_TABLE[encState];
}

int32_t lastDetent = 0;

// ---------------- Buttons (6 keys + encoder button) ----------------
const uint8_t NUM_BUTTONS = 7;
const uint8_t ENCODER_BUTTON = 6;
uint8_t buttonPins[NUM_BUTTONS];
bool buttonPressed[NUM_BUTTONS];
unsigned long lastChange[NUM_BUTTONS];
const unsigned long DEBOUNCE_MS = 5;

// ---------------- Screen ----------------
const char* DAYS[7]    = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const char* MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int lastMinuteShown = -1;

void printCentered(const char* text, uint8_t size, int16_t y) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(size);
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, y);
  display.print(text);
}

void updateScreen(bool force) {
  if (!rtcFound) {
    display.clearDisplay();
    printCentered("Clock not found", 1, 12);
    display.display();
    return;
  }
  DateTime now = rtc.now();
  if (!force && now.minute() == lastMinuteShown) return;  // redraw once a minute
  lastMinuteShown = now.minute();

  char dateText[24];
  snprintf(dateText, sizeof(dateText), "%s %s %d, %d",
           DAYS[now.dayOfTheWeek()], MONTHS[now.month() - 1], now.day(), now.year());

  char timeText[12];
  if (USE_24_HOUR) {
    snprintf(timeText, sizeof(timeText), "%02d:%02d", now.hour(), now.minute());
  } else {
    int hour12 = now.hour() % 12;
    if (hour12 == 0) hour12 = 12;
    snprintf(timeText, sizeof(timeText), "%d:%02d %s", hour12, now.minute(),
             now.hour() < 12 ? "AM" : "PM");
  }

  display.clearDisplay();
  printCentered(dateText, 1, 1);    // small line on top
  printCentered(timeText, 2, 15);   // big line underneath
  display.display();
}

void sendMedia(uint16_t code) {
  Keyboard.consumerPress(code);
  delay(5);
  Keyboard.consumerRelease();
}

// ---------------- Setup ----------------
void setup() {
  // Buttons: internal pull-ups, so a press reads LOW
  for (uint8_t i = 0; i < 6; i++) buttonPins[i] = KEY_PINS[i];
  buttonPins[ENCODER_BUTTON] = ENC_BTN;
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    buttonPressed[i] = false;
    lastChange[i] = 0;
  }

  // Encoder
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_A), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), encoderISR, CHANGE);

  // I2C bus shared by the OLED and the clock
  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.begin();
  Wire.setClock(400000);

  // Screen
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.setRotation(SCREEN_UPSIDE_DOWN ? 2 : 0);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  printCentered("QuickPad", 2, 8);
  display.display();

  // Clock: if it has never been set (or lost power), set it to the time
  // this sketch was compiled, which is accurate to within a few seconds.
  rtcFound = rtc.begin(&Wire);
  if (rtcFound && rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // USB keyboard + media keys
  Keyboard.begin();

  delay(1000);
  updateScreen(true);
}

// ---------------- Main loop ----------------
void loop() {
  unsigned long nowMs = millis();

  // Keys and encoder button
  for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
    bool pressed = (digitalRead(buttonPins[i]) == LOW);
    if (pressed != buttonPressed[i] && nowMs - lastChange[i] > DEBOUNCE_MS) {
      buttonPressed[i] = pressed;
      lastChange[i] = nowMs;

      if (i == ENCODER_BUTTON) {
        if (pressed) sendMedia(MEDIA_MUTE);
      } else if (pressed) {
        Keyboard.press(KEYMAP[i]);
      } else {
        Keyboard.release(KEYMAP[i]);
      }
    }
  }

  // Volume knob: one volume step per click
  noInterrupts();
  int32_t count = encCount;
  interrupts();
  int32_t detent = count / 4;
  if (detent != lastDetent) {
    int32_t steps = detent - lastDetent;
    lastDetent = detent;
    if (REVERSE_KNOB) steps = -steps;
    uint16_t code = steps > 0 ? MEDIA_VOL_UP : MEDIA_VOL_DOWN;
    for (int32_t s = 0; s < abs(steps); s++) sendMedia(code);
  }

  // Clock: check once per second, redraw only when the minute changes
  static unsigned long lastCheck = 0;
  if (nowMs - lastCheck >= 1000) {
    lastCheck = nowMs;
    updateScreen(false);
  }
}
