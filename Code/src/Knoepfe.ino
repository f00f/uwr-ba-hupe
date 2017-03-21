#include "config.h"
#include "display.h"

void Knoepfe ()
{
        if (digitalRead(PinButtonReset) == 0 && Knopf1Timer < millis() - 1000) // Reset initalisieren
        {
                Knopf1Timer = millis();
                Reset = 1;
        }
        if (Knopf1Timer + 2000 < millis())    // nach 2 Sekunden ResetModus beenden
        {
                if (Reset==1)
                {
                        zeigSpielzeit(TimerSpielzeit);
                        clearDigit5();
                }
                Reset = 0;
        }

        if (Reset == 1)
        {
                zeigReset();
        }



        if (digitalRead(PinButtonSetup) == 0 && Knopf2Timer < millis() - 1000) // Reset / Strafwurf
        {
                Knopf2Timer = millis();

                if (Reset == 1)                             // Reset tatsächlich auslösen
                {
                        Setup = SetupStateHome;
                }

                if (Stop != 0 || DurchlaufendeSpielzeit == 1)                           //Strafwurf
                {
                        if (istStrafwurf == 1)
                        {
                                StrafwurfTimer = 0;
                                istStrafwurf = 0;
                                clearDigits78();
                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                                {
                                        zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                                }
                        }
                        else
                        {
                                if (DurchlaufendeSpielzeit == 1)
                                {
                                        StrafwurfStop = 1;
                                }
                                istStrafwurf = 1;
                                StrafwurfTimer = Strafwurf;
                                zeigSekundenAn78(StrafwurfTimer);
                        }
                }
        }

        if (digitalRead(PinButtonPlus) == 0 && Knopf3Timer < millis() - 1000) //Strafzeit
        {
                Knopf3Timer = millis();
                for (int i = 0; i < 6; i++)
                {
                        if (Strafzeiten[i] == 0)
                        {
                                Strafzeiten[i] = Strafzeit;
                                i = 6;
                        }
                }

                AnzahlStrafzeiten = 0;
                for (int i = 0; i < 6; i++)
                {
                        if (Strafzeiten[i] != 0)
                        {
                                AnzahlStrafzeiten++;
                        }
                        zeigAnzahlStrafzeiten(AnzahlStrafzeiten);
                }
        }

        if (digitalRead(PinButtonMinus) == 0 && Knopf4Timer < millis() - 800)
        {
                Knopf4Timer = millis();

                if (Stop != 0)               //Zeit umschalten läuft - LÄUFT NICHT
                {
                        if (DurchlaufendeSpielzeit == 0)
                        {
                                Start = Start + millis() - Stop;
                                Stop = 0;
                        }
                        else                 //durchlaufende Zeit
                        {
                                if (durchlaufendeZeitStop == 1) // Spiel am Anfang Starten
                                {
                                        durchlaufendeZeitStop = 0;
                                        Start = Start + millis() - Stop;
                                        Stop = 0;
                                }
                        }
                }
                else                       //Zeit umschalten LÄUFT - läuft nicht
                {
                        if (DurchlaufendeSpielzeit == 0)
                        {
                                Stop = millis(); //Zeit wird angehalten wenn keine durchlaufende Spielzeit
                        }

                        if (istStrafwurf == 1 && StrafwurfStop == 0) //durchlaufende Zeit - Strafwurf beenden
                        {
                                istStrafwurf = 0;
                                StrafwurfTimer = 0;

                                clearDigits78();
                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                                {
                                        zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                                }
                        }

                        if (StrafwurfStop == 1 && istStrafwurf == 1) //durchlaufende Zeit - Strafwurf ausführen
                        {
                                StrafwurfStop = 0;
                        }

                }
        } //Ende ButtonMinus
}
