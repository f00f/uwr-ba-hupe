#ifndef display_h
#define display_h

#include "Arduino.h" // provides Serial
#include "config.h"

#if OUTPUT_LCD
#include "LiquidCrystal.h"
LiquidCrystal lcd(PinLcdRs, PinLcdEnable, PinLcdD4, PinLcdD5, PinLcdD6, PinLcdD7);
#endif
#if OUTPUT_LED
#include "LedControl.h"
LedControl lc = LedControl(PinLedDout, PinLedClk, PinLedCs, LedNumDevices);
#endif

// Loescht die Zeichen 2 bis 4
void clearDigits234()
{
  #if OUTPUT_LED
  lc.setChar(0, 6, ' ', false); //2. Led
  lc.setChar(0, 5, ' ', false); //3. Led
  lc.setChar(0, 4, ' ', false); //4. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(1, 1);
  lcd.print("   ");
  #endif
}

// Loescht das 5. Zeichen
void clearDigit5()
{
  #if OUTPUT_LED
  lc.setChar(0, 3, ' ', false); //5. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(5, 1);
  lcd.print(" ");
  #endif
}

// Loescht die Zeichen 5 bis 8
void clearDigits5678()
{
  #if OUTPUT_LED
  lc.setChar(0, 3, ' ', false); //5. Led
  lc.setChar(0, 2, ' ', false); //6. Led
  lc.setChar(0, 1, ' ', false); //7. Led
  lc.setChar(0, 0, ' ', false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(5, 1);
  lcd.print("    ");
  #endif
}

// Loescht die Zeichen 5, 7 und 8
void clearDigits578()
{
  #if OUTPUT_LED
  lc.setChar(0, 3, ' ', false); //5. Led
  lc.setChar(0, 1, ' ', false); //7. Led
  lc.setChar(0, 0, ' ', false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(5, 1);
  lcd.print(" ");
  lcd.setCursor(7, 1);
  lcd.print("  ");
  #endif
}

// Loescht die Zeichen 7 und 8
void clearDigits78()
{
  #if OUTPUT_LED
  lc.setChar(0, 1, ' ', false); //7. Led
  lc.setChar(0, 0, ' ', false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(7, 1);
  lcd.print("  ");
  #endif
}

void zeigReset()
{
  #if OUTPUT_LED
  lc.setRow(0, 7, B00000101); //  Punkt dann beginntend oben im Uhrzeigersinn
  lc.setChar(0, 6, 'e', false); //2. Led
  lc.setRow(0, 5, B01011011); //3. Led
  lc.setChar(0, 4, 'e', false); //4. Led
  lc.setRow(0, 3, B00001111); //5. Led
  lc.setChar(0, 2, ' ', false); //6. Led
  lc.setChar(0, 1, ' ', false); //7. Led
  lc.setChar(0, 0, ' ', false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(0, 1);
  lcd.print("Reset?   <ENTER>");
  #endif
}

void zeigSetup()
{
  #if OUTPUT_LED
  lc.setRow(0, 7, B01011011); //  Punkt dann beginntend oben im Uhrzeigersinn
  lc.setChar(0, 6, 'e', false); //2. Led
  lc.setRow(0, 5, B00001111); //3. Led
  lc.setRow(0, 4, B00111110); //4. Led
  lc.setChar(0, 3, 'p', false); //5. Led
  lc.setChar(0, 2, ' ', false); //6. Led
  lc.setChar(0, 1, ' ', false); //7. Led
  lc.setChar(0, 0, ' ', false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(0, 1);
  lcd.print("Setup    <ENTER>");
  #endif
  #if OUTPUT_SERIAL
  Serial.write("Setup");
  #endif
}

void zeigSetupIndikator(char c)
{
  #if OUTPUT_LED
  lc.setChar(0, 3, c, false); //5. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(5, 1);
  lcd.print(c);
  #endif
}

void zeigSetupDurchlaufendeSpielzeit(bool isDurchlaufend)
{
  #if OUTPUT_LED
  lc.setChar(0, 7, isDurchlaufend, false); //1. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(0, 1);
  lcd.print(isDurchlaufend ? "Ja" : "Nein");
  #endif
}


void zeigSekundenAn78(int sekunden)
{
  #if OUTPUT_LED
  lc.setChar(0, 1, sekunden / 10, false); //7. Led
  lc.setChar(0, 0, sekunden % 10, false); //8. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(7, 1);
  lcd.print(sekunden / 10);
  lcd.print(sekunden % 10);
  #endif
}

void zeigAnzahlStrafzeiten(int anzahl)
{
  #if OUTPUT_LED
  lc.setChar(0, 3, anzahl, false); //5. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(5, 1);
  lcd.print(anzahl);
  #endif
}

void zeigStrafzeiten(int anzahl, int kleinsteStrafzeit)
{
  zeigAnzahlStrafzeiten(anzahl);
  zeigSekundenAn78(kleinsteStrafzeit);
}

void zeigSpielzeit(int spielzeit)
{
  #if OUTPUT_LED
  lc.setChar(0, 7, (spielzeit / 60) / 10, false); //1. Led
  lc.setChar(0, 6, (spielzeit / 60) % 10, false); //2. Led
  lc.setChar(0, 5, (spielzeit % 60) / 10, false); //3. Led
  lc.setChar(0, 4, (spielzeit % 60) % 10, false); //4. Led
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(0, 1);
  lcd.print((spielzeit / 60) / 10);
  lcd.print((spielzeit / 60) % 10);
  lcd.print((spielzeit % 60) / 10);
  lcd.print((spielzeit % 60) % 10);
  #endif
}

// Zeigt an, wer gehupt hat
// @param c: Zeichen, das angezeigt werden soll (a-c)
void zeigWerGehuptHat(char c)
{
  #if OUTPUT_LED
  lc.setChar(0, 2, c, false);
  #endif
  #if OUTPUT_LCD
  lcd.setCursor(6, 1);
  lcd.print(c);
  #endif
}

#endif
