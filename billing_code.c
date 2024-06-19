//Author-Cybot95
#include <SPI.h>
#include <MFRC522.h>
#define RELAY 8
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int ctc;
int ctp1;
int ctp2;
int term;
double total;
int prod_ct;

void setup()
{


    pinMode (RELAY,OUTPUT);
    Serial.begin(9600);   // Initiate a serial communication
    SPI.begin();      // Initiate  SPI bus
    mfrc522.PCD_Init();   // Initiate MFRC522
    Serial.println("\n\nSMART SHOPPING TROLLEY");
    delay (1000);
    Serial.println("        WITH AUTOMATED BILLING");
    delay (1000);
    
    Serial.println("\n          ------PROJECT GROUP IPC 180------");
    delay(1000);
    Serial.println("\n          ------PRESIDENCY UNIVERSITY------");
    delay(1000);
    Serial.println("\n Scan Your Membership Card To Start...!");
    ctc=0;
    ctp1=0;
    ctp2=0;
    term=0;
    total=0;
    prod_ct=0;
       
  
}

// Card Registration and ID Allocation
void CardReg()
{
  if(ctc <= 0 && ctc < 1) 
             {
              Serial.print("\n");
              Serial.println("\nName: Amrutkumar");
              Serial.println("\nID: xxxxxxx01");
              delay(1000);
              ctc++;
             }
             else
             {
              Serial.print("\nTotal Price : ");
                Serial.print(total);
              delay(1000);
              Serial.print("\nTotal Products : ");
                 Serial.print(prod_ct);
              delay(1000);
              Serial.print("\n");
              Serial.println("\n Shopping Ended");
              Serial.println("\n Thank You For Visiting "); 
              delay(1000);
              term=1;
              setup();
             }
}


// Product Entry
void Prod1()
{if(term==0)
            { 
              if(ctp1 <= 0 && ctp1 < 1) 
             {
              Serial.print("\n");
              Serial.println("\n   >>>>>Product KEYCHAIN Added       ");
              Serial.println("\nPrice(RS):10.00      ");
              delay(1000);
              total = total + 10.00;
              prod_ct++;
              ctp1++;
             }
      
             else
             {
              Serial.print("\n");
              Serial.println("\n   >>>>>Product KEYCHAIN Removed!!!        "); 
              delay(1000);
              total = total - 10.00;
              prod_ct--;
              ctp1--;
             }
            }
  
}

void Prod2()
{
        if(term==0)
            { 
               if(ctp2 <= 0 && ctp2 < 1) 
               {
                Serial.print("\n");
                Serial.println("\n   >>>>>Product CLIP Added       ");
                Serial.println("\nPrice(Rm):20.00      ");
                delay(1000);
                total = total + 20.00;
                prod_ct++;
                ctp2++;
               }
        
               else

              {
                Serial.print("\n");
                Serial.println("\n   >>>>>Product CLIP Removed!!!        "); 
                delay(1000);
                total = total - 20.00;
                prod_ct--;
                ctp2--;
               }
            }
}

void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
  return;
  }
  // Select one of the cards
  
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
  return;
  }
  
  //Show UID on serial monitor
  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
  content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
  content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
      
      if (content.substring(1) == "09 E9 17 E9") //change here the UID of the card/cards that you want to give access
       {
            CardReg();
       }
        else if (content.substring(1) == "E9 82 16 C2") //change here the UID of the card/cards that you want to give access
        {
             Prod1();
        }
          else if (content.substring(1) == "07 1B D8 55") //change here the UID of the card/cards that you want to give access
          {
               Prod2();
          }
            else
            {
              Serial.println("Invalid Card Error");
            }
      
       Serial.print("\n\n");
}
