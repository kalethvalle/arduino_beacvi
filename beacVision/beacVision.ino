#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

byte LecturaUID[4];
byte User1[4] = {0x4A, 0xA1, 0xC3, 0x9A}; // manilla
byte User2[4] = {0xE1, 0x85, 0x52, 0xD3}; // llavero
byte User3[4] = {0x55, 0x15, 0x58, 0xE2}; // tarjeta

void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("bien ...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID: ");

  for(byte i = 0; i < mfrc522.uid.size; i++){
    if(mfrc522.uid.uidByte[i] < 0x10){
      Serial.print(" 0");
    }else{
      Serial.print(" ");
    }
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    LecturaUID[i] = mfrc522.uid.uidByte[i];
  }

  Serial.print("\t");
  if(comparaUID(LecturaUID, User1)){
    Serial.println("Bienvenido User 1");
  }else if(comparaUID(LecturaUID, User2)){
    Serial.println("Bienvenido User 2");
  }else if(comparaUID(LecturaUID, User3)){
    Serial.println("Bienvenido User 3");
  }else{
    Serial.println("No te conozco");
  }
  //Serial.println();
  mfrc522.PICC_HaltA();
}

boolean comparaUID(byte lectura[], byte usuario[]){
  for(byte i = 0; i < mfrc522.uid.size; i++){
     if(lectura[i] != usuario[i]){
        return(false);
     }
     return(true);
  }
}
