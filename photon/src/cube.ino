/*
 * Project cube
 * Description:
 * Author:
 * Date:
 */

#include "ssd1331.h"
#include "gfx.h"

int _button_pin = D0;

int _led_r_pin = D1;
int _led_g_pin = D2;
int _led_b_pin = A7;

// Setup timer for LED animation
void timerCallback();
Timer timer(10, timerCallback);

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing OLED monitor..");
  SSD1331_begin();
  SSD1331_clear();
  Serial.println(" Done!");

  SSD1331_clear();
  SSD1331_mono_bitmap(0, 0, waveshare_logo, 96, 64, BLUE);

  delay(3000);

  SSD1331_clear();

  draw(1                                              ); delay(200);
  draw(1 | 2                                          ); delay(200);
  draw(1 | 2 | 4                                      ); delay(200);
  draw(1 | 2 | 4 | 8                                  ); delay(200);
  draw(1 | 2 | 4 | 8 | 16                             ); delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32                        ); delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64                   ); delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64 | 128             ); delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 512       ); delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 512 | 1024); delay(200);
  SSD1331_clear();                                       delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 512 | 1024); delay(200);
  SSD1331_clear();                                       delay(200);
  draw(1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 512 | 1024); delay(200);
  SSD1331_clear();                                       delay(200);

#if 0
  GFX_drawLine(5, 5, 10, 10, BLUE);
  delay(5000);
  SSD1331_clear();
#endif

  Serial.print("Initializing button..");
  pinMode(_button_pin, INPUT_PULLDOWN);
  Serial.println(" Done!");

  Serial.print("Initializing LED: R..");
  pinMode(_led_r_pin, OUTPUT);
  Serial.print("G..");
  pinMode(_led_g_pin, OUTPUT);
  Serial.print("B..");
  pinMode(_led_b_pin, OUTPUT);
  Serial.println(" Done!");

  // start LED timer
  timer.start();
}

void draw(int b)
{
  if (b & 1) SSD1331_mono_bitmap(0, 2, Signal816, 16, 8, GRAY);
  if (b & 2) SSD1331_mono_bitmap(19, 2, Msg816, 16, 8, WHITE);
  if (b & 4) SSD1331_mono_bitmap(38, 2, Bluetooth88, 8, 8, RED);
  if (b & 8) SSD1331_mono_bitmap(52, 2, GPRS88, 8, 8, PINK);
  if (b & 16) SSD1331_mono_bitmap(66, 2, Alarm88, 8, 8, YELLOW);
  if (b & 32) SSD1331_mono_bitmap(80, 2, Bat816, 16, 8, GOLDEN);

  if (b & 64) SSD1331_mono_bitmap(0, 22, Signal816, 16, 8, BROWN);
  if (b & 128) SSD1331_mono_bitmap(38, 22, Bluetooth88, 8, 8, CYAN);
  if (b & 256) SSD1331_mono_bitmap(19, 22, Msg816, 16, 8, BLUE);
  if (b & 512) SSD1331_mono_bitmap(52, 22, GPRS88, 8, 8, GREEN);
  if (b & 1024) SSD1331_mono_bitmap(66, 22, Alarm88, 8, 8, PURPLE);
}

int val = 0;
int pin[] = { _led_r_pin, _led_g_pin, _led_b_pin };

// timer callback for LED animation
int pins = 1; int color = 0; int delta = 1;
void timerCallback()
{
  // if button is not pressed - return
  if (digitalRead(_button_pin) == 0)
  {
    Serial.println("- - -"); setColor(0, 0, 0);
    SSD1331_mono_bitmap(0, 2, Signal816, 16, 8, BLACK);
    return;
  }

  int rgb = RGB(pins & 1 ? color : 0,
      pins & 2 ? color : 0,
      pins & 4 ? color : 0);
      SSD1331_mono_bitmap(0, 2, Signal816, 16, 8, BLACK);
  SSD1331_mono_bitmap(0, 2, Signal816, 16, 8, rgb);

  // reverse operation if needed
  if (delta == -1 && color == 0)
  {
    delta = 1;
    pins++;
    if (pins == 8) pins = 1;
  }

  if (delta == 1 && color == 255)
  {
    delta = -1;
  }

  color += delta;

  setColor(
    pins & 1 ? color : 0,
    pins & 2 ? color : 0,
    pins & 4 ? color : 0
  );
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  //SSD1331_string(2, 52, "MUSIC", 12, 0, WHITE);
  delay(1000);
  //SSD1331_clear();
  delay(1000);
}

void setColor(int red, int green, int blue)
{
  analogWrite(_led_r_pin, 255 - red);
  analogWrite(_led_g_pin, 255 - green);
  analogWrite(_led_b_pin, 255 - blue);
}
