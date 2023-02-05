#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>


#define RST_PIN         9            
#define SS_PIN          10    // data pin  
#define LED_G 5 
#define LED_R 4 
Servo myServo; 


MFRC522 mfrc522(SS_PIN,   RST_PIN);   //function inbuilt in library 

String read_rfid;  //read in string                 
String ok_rfid_1="e199312d"; // rfid number showed in serial monitor        
String ok_rfid_2="fbecb673";  //2nd rfid number      


void setup() {
    Serial.begin(9600);// form a connection between arduino aur arduino id            
    while (!Serial);         
    SPI.begin();                
    mfrc522.PCD_Init();         //pin that provide card data to arduino
    myServo.attach(3); //servo pin
    myServo.write(0); //servo start position
    pinMode(LED_G, OUTPUT);
    pinMode(LED_R, OUTPUT);

   
}

void dump_byte_array(byte   *buffer, byte bufferSize) { //card's number will dump on screen  
    read_rfid="";
    for (byte i = 0; i < bufferSize;   i++) {
        read_rfid=read_rfid + String(buffer[i], HEX);
    }
}

void   open_lock() {
  
   digitalWrite(LED_G, HIGH);
   delay(300);
   myServo.write(180);
   delay(5000);
   digitalWrite(LED_G, LOW);
  
}


void   close_lock2() {          
   
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_R, LOW);
  
}


void   loop() {

      
    if ( ! mfrc522.PICC_IsNewCardPresent())// it's a predefine lib fuction that will check whether its new card or not 
                            
         return;

    
    if ( ! mfrc522.PICC_ReadCardSerial())// read card serial number
         return;

    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);// function call
     Serial.println(read_rfid);
    if (read_rfid==ok_rfid_1) {
      
      open_lock();
    }

    Serial.println(read_rfid);
     if (read_rfid==ok_rfid_2) {
      
      close_lock2();
     }
    //Add below as many "keys" as you want
    //if (read_rfid==ok_rfid_2)   {
      //also ok, op en the door
    //  open_lock();
    //}
    //   else not needed. Anything else is not ok, and will not open the door...
}

