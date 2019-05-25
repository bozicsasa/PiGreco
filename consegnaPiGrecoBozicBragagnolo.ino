//REALIZZATO DA BOZIC SASA E BRAGAGNOLO RICCARDO 3BI

#include <LiquidCrystal.h>
LiquidCrystal lcd (13, 12, 11, 10, 9, 8);

int pulsante1;
int pulsante2;
int pulsante3;
int pulsante4;
int pulsante5;
int pulsanteInizio;
int pi;
int bomba;
int record;
int posvita;
int vita;
int punteggio;
int tempo;


void setup() {
 lcd.begin(16,2);
 pulsante1 = 2;
 pulsante2 = 3;
 pulsante3 = 4;
 pulsante4 = 5;
 pulsante5 = 6; 
 pulsanteInizio = 7;
 pinMode(pulsante1, INPUT);
 pinMode(pulsante2, INPUT);
 pinMode(pulsante3, INPUT);
 pinMode(pulsante4, INPUT);
 pinMode(pulsante5, INPUT);
 pinMode(pulsanteInizio, INPUT);
}

void loop() {
  tempo = 5000;
  punteggio = 0;
  HomeScreen();
  pulsante(pulsanteInizio);
  Gioco(3);
}

void pulsante (int pulsantino)
{
  bool fine = false;
  while (!fine)
  {
    if(digitalRead(pulsantino)==HIGH)
    {
      fine = true;
    }
  }
}

void resultControl ()
{
  int tempoInizio = millis();
  int tempoSecondario;
  bool fine = false;
  bool piPressed = false;
  while (!fine)
  {
    if(posvita!= -1 && digitalRead(posvita ==HIGH))
    {
      vita++;
      fine = true;
    }
    else if(bomba!= -1 && digitalRead(bomba)==HIGH)    
    {
      vita--;
      fine = true;
    }
    else if(pi != -1 && digitalRead(pi)==HIGH)
    {
      punteggio++;
      fine = true;
      piPressed = true;
    }
    tempoSecondario = millis();
    if(tempoSecondario-tempoInizio>tempo)
    {
      fine = true;
      if(piPressed == false && pi !=-1)
      {
        vita--;
      }
    }
    if (tempo>2000)
      {
        tempo - 200;
      }
  }
  RefreshScreen();
}

void Gioco (int numVite)
{
  vita = numVite;
  bool fine = false;
  int valoreRandom;
  RefreshScreen();
  while(!fine)
  {
    posvita= -1;
    bomba = -1;
    pi = -1;
    valoreRandom = random(1,11);
    if(valoreRandom >= 1 && valoreRandom <= 6)
    {
      pi = random (2,7);
      lcd.setCursor((pi-1)*3,1);
      lcd.print("Pi");
    }
    else if(valoreRandom>= 7 && valoreRandom<= 9)
    {
      bomba = random (2,7);
      lcd.setCursor((bomba-1)*3,1);
      lcd.print("*");
    }
    else
    {
      posvita = random (2,7);
      lcd.setCursor((posvita-1)*3,1);
      lcd.print("♥");
    }
    resultControl();
    if(punteggio > record)
    {
      record = punteggio;
    }
    if(vita==0)
    {
      fine = true;
    }
  }
}

void RefreshScreen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("V"+String(vita));
  lcd.setCursor(5,0);
  lcd.print("Punti:" + String(punteggio));
}

void HomeScreen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("premere start");
  lcd.setCursor(0,1);
  lcd.print("record:"+ String(record));
}
