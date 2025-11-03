#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <RadioLib.h>

//---------------------------------------------------------------------------
// General configuration
//---------------------------------------------------------------------------
#define OLED_RESET RST_OLED //21
#define OLED_SDA SDA_OLED //17
#define OLED_SCL SCL_OLED //18

#define USE_DSPMSG 1  // Allows disabling OLED at compile time

//---------------------------------------------------------------------------
// U8g2 library instance
//---------------------------------------------------------------------------
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);

//---------------------------------------------------------------------------
// Auxiliary functions
//---------------------------------------------------------------------------
#if USE_DSPMSG
void displayMessage(const char *line1 = "",
                    const char *line2 = "",
                    const char *line3 = "",
                    const char *line4 = "",
                    const char *line5 = "")
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_profont12_mf);

    const uint8_t lineHeight = 12;
    const uint8_t startY = 12;

    u8g2.drawStr(0, startY + lineHeight * 0, line1);
    u8g2.drawStr(0, startY + lineHeight * 1, line2);
    u8g2.drawStr(0, startY + lineHeight * 2, line3);
    u8g2.drawStr(0, startY + lineHeight * 3, line4);
    u8g2.drawStr(0, startY + lineHeight * 4, line5);

    u8g2.sendBuffer();
}
#endif

void enableDisplayPower()
{
#if USE_DSPMSG
     pinMode(36, OUTPUT); 
    digitalWrite(36, LOW);  // Vext ON
#endif
}

void disableDisplayPower()
{
#if USE_DSPMSG
    digitalWrite(36, HIGH); // Vext OFF
#endif
}

//---------------------------------------------------------------------------
// Arduino setup/loop
//---------------------------------------------------------------------------
void setup()
{
#if USE_DSPMSG
    enableDisplayPower();
    delay(10);              // Time to stabilize Vext
    u8g2.begin();
    u8g2.setContrast(255);  // Maximum contrast

    displayMessage("Dispositivo listo",
                   "Metodología OLED",
                   "Vext controlado",
                   "", "");
#else
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
#endif
}

void loop()
{
#if USE_DSPMSG
    static uint32_t lastToggle = 0;
    static bool showAlt = false;

    if (millis() - lastToggle > 1500) {
        lastToggle = millis();
        showAlt = !showAlt;

        if (showAlt) {
            displayMessage("Modo A",
                           "Lectura sensores",
                           "Pendiente...",
                           "", "");
        } else {
            displayMessage("Modo B",
                           "Actualiza OLED",
                           "Cada 1.5 s",
                           "", "");
        }
    }
#else
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
#endif
}