
#include "Middleware.h"



class MazdaLED : 
Middleware
{

private:
  static QueueArray<Message>* mainQueue;
  static unsigned long updateCounter;
  static void pushNewMessage();
  static int fastUpdateDelay;
public:
  static void init( QueueArray<Message> *q );
  static void tick();
  static boolean enabled;
  static void showStatusMessage(char* str, int time);
  static char lcdString[13];
  static char lcdStockString[13];
  static char lcdStatusString[13];
  static char gaugePage;
  static unsigned long stockOverrideTimer;
  static unsigned long statusOverrideTimer;
  static void setOverrideTime( int n );
  static void setStatusTime( int n );
  static unsigned long animationCounter;
  static Message process( Message msg );
  static char* currentLcdString();
  static void knockServiceCall();
  static void egtServiceCall();
  static void afrServiceCall();
  static void boostServiceCall();
  static void batServiceCall();
  static void fpServiceCall();
  static void advanceServiceCall();


};

boolean MazdaLED::enabled = EEPROM.read(0);
unsigned long MazdaLED::updateCounter = 0;
int MazdaLED::fastUpdateDelay = 500;
QueueArray<Message>* MazdaLED::mainQueue;
char MazdaLED::lcdString[13] = "CANBusTriple";
char MazdaLED::lcdStockString[13] = "            ";
char MazdaLED::lcdStatusString[13] = "            ";
char MazdaLED::gaugePage = 0;

int boost, boostWhole, boostRemainder = 0;
int afr, afrWhole, afrRemainder = 0;
int krd, krdWhole, krdRemainder = 0;
int krdMax, krdMaxWhole, krdMaxRemainder = 0;
int bat = 0;
int fp = 0;

unsigned long MazdaLED::animationCounter = 0;
unsigned long MazdaLED::stockOverrideTimer = 4000;
unsigned long MazdaLED::statusOverrideTimer = 0;





void MazdaLED::init( QueueArray<Message> *q )
{
  mainQueue = q;
}

void MazdaLED::tick()
{
  if(!enabled) return;

  // New LED update CAN message for fast updates
  // check stockOverrideTimer, no need to do fast updates while stock override is active
  if( (updateCounter+fastUpdateDelay) < millis() && stockOverrideTimer < millis() ){
    pushNewMessage();
    updateCounter = millis();
  }

  // Send knock retard query
  // if( (millis() % 100) < 1 ) MazdaLED::knockServiceCall();
  //if( (millis() % 100) < 1 ) MazdaLED::egtServiceCall();
  // if( (millis() % 100) < 1 ) MazdaLED::advanceServiceCall();

  if( (millis() % 100) < 1 ) MazdaLED::knockServiceCall();  
  if( (millis() % 203) < 1 ) MazdaLED::afrServiceCall();
  if( (millis() % 206) < 1 ) MazdaLED::boostServiceCall();
  if( (millis() % 503) < 1 ) MazdaLED::batServiceCall();
  if( (millis() % 209) < 1 ) MazdaLED::fpServiceCall();


}


void MazdaLED::showStatusMessage(char* str, int time){
  sprintf( MazdaLED::lcdStatusString , str);
  MazdaLED::setStatusTime(time);
}


void MazdaLED::knockServiceCall(){

  // NOT WORKING

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;     // 02 01 0D 00 00 00 00 00
  msg.frame_data[0] = 0x03;
  msg.frame_data[1] = 0x22;
  msg.frame_data[2] = 0x03;
  msg.frame_data[3] = 0xEC;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);

}

void MazdaLED::advanceServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;     // 02 01 0D 00 00 00 00 00
  msg.frame_data[0] = 0x03;
  msg.frame_data[1] = 0x22;
  msg.frame_data[2] = 0x11;
  msg.frame_data[3] = 0x6B;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);

}

void MazdaLED::egtServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;
  msg.frame_data[0] = 0x02;
  msg.frame_data[1] = 0x01;
  msg.frame_data[2] = 0x3c;
  msg.frame_data[3] = 0x00;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);

}

void MazdaLED::afrServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;
  msg.frame_data[0] = 0x03;
  msg.frame_data[1] = 0x22;
  msg.frame_data[2] = 0xDA;
  msg.frame_data[3] = 0x85;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);
}

void MazdaLED::boostServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;
  msg.frame_data[0] = 0x02;
  msg.frame_data[1] = 0x01;
  msg.frame_data[2] = 0x0B;
  msg.frame_data[3] = 0x00;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);
}

void MazdaLED::batServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;
  msg.frame_data[0] = 0x03;
  msg.frame_data[1] = 0x22;
  msg.frame_data[2] = 0x03;
  msg.frame_data[3] = 0xCA;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);
}

void MazdaLED::fpServiceCall(){

  Message msg;
  msg.busId = 2;
  msg.frame_id = 0x7E0;
  msg.frame_data[0] = 0x03;
  msg.frame_data[1] = 0x22;
  msg.frame_data[2] = 0xF4;
  msg.frame_data[3] = 0x23;
  msg.frame_data[4] = 0x00;
  msg.frame_data[5] = 0x00;
  msg.frame_data[6] = 0x00;
  msg.frame_data[7] = 0x00;
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);
}


void MazdaLED::pushNewMessage(){

  char* lcd = currentLcdString();

  Message msg;
  msg.busId = 3;
  msg.frame_id = 0x290;
  msg.frame_data[0] = 0xC0;  // Look this up from log
  msg.frame_data[1] = lcd[0];
  msg.frame_data[2] = lcd[1];
  msg.frame_data[3] = lcd[2];
  msg.frame_data[4] = lcd[3];
  msg.frame_data[5] = lcd[4];
  msg.frame_data[6] = lcd[5];
  msg.frame_data[7] = lcd[6];
  msg.length = 8;
  msg.dispatch = true;
  mainQueue->push(msg);

  Message msg2;
  msg2.busId = 3;
  msg2.frame_id = 0x291;
  msg2.frame_data[0] = 0x87;  // Look this up from log
  msg2.frame_data[1] = lcd[7];
  msg2.frame_data[2] = lcd[8];
  msg2.frame_data[3] = lcd[9];
  msg2.frame_data[4] = lcd[10];
  msg2.frame_data[5] = lcd[11];
  msg2.length = 8;
  msg2.dispatch = true;
  mainQueue->push(msg2);

  // Turn off extras and periods on screen
  // 02 03 02 8F C0 00 00 00 01 27 10 40 08

  Message msg3;
  msg3.busId = 1;
  msg3.frame_id = 0x28F;
  msg3.frame_data[0] = 0xC0;
  msg3.frame_data[1] = 0x0;
  msg3.frame_data[2] = 0x0;
  msg3.frame_data[3] = 0x0;
  msg3.frame_data[4] = 0x1;
  msg3.frame_data[5] = 0x27;
  msg3.frame_data[6] = 0x10;
  msg3.frame_data[7] = 0x40;
  msg3.length = 8;
  msg3.dispatch = true;
  mainQueue->push(msg3);


}


char* MazdaLED::currentLcdString(){
  if( stockOverrideTimer > millis() )
    return lcdStockString;
  else if( statusOverrideTimer > millis() )
    return lcdStatusString;
  else
    return lcdString;
}


void MazdaLED::setOverrideTime( int n ){
  stockOverrideTimer = millis() + n;
}

void MazdaLED::setStatusTime( int n ){
  statusOverrideTimer = millis() + n;
}


Message MazdaLED::process(Message msg)
{
  if(!enabled) return msg;

  if( msg.frame_id == 0x28F && stockOverrideTimer < millis() ){
    // Block extras
    msg.frame_data[0] = 0xC0;
    msg.frame_data[1] = 0x0;
    msg.frame_data[2] = 0x0;
    msg.frame_data[3] = 0x0;
    // msg.frame_data[4] = 0x01; // Looks like phone light
    msg.frame_data[5] = 0x27;
    msg.frame_data[6] = 0x10;
    // msg.frame_data[7] = 0x40; looks like music note light
    msg.dispatch = true;
  }

  if( msg.frame_id == 0x290 ){

    if( msg.frame_data[1] != lcdStockString[0] ||
      msg.frame_data[2] != lcdStockString[1] || 
      msg.frame_data[3] != lcdStockString[2] || 
      msg.frame_data[4] != lcdStockString[3] || 
      msg.frame_data[5] != lcdStockString[4] || 
      msg.frame_data[6] != lcdStockString[5] || 
      msg.frame_data[7] != lcdStockString[6] ){

      lcdStockString[0] = msg.frame_data[1];
      lcdStockString[1] = msg.frame_data[2];
      lcdStockString[2] = msg.frame_data[3];
      lcdStockString[3] = msg.frame_data[4];
      lcdStockString[4] = msg.frame_data[5];
      lcdStockString[5] = msg.frame_data[6];
      lcdStockString[6] = msg.frame_data[7];

      /*
        Serial.print( "lcdStockString: ");
       Serial.println( lcdStockString );
       */

    }

    char* lcd = currentLcdString();

    msg.frame_data[1] = lcd[0];
    msg.frame_data[2] = lcd[1];
    msg.frame_data[3] = lcd[2];
    msg.frame_data[4] = lcd[3];
    msg.frame_data[5] = lcd[4];
    msg.frame_data[6] = lcd[5];
    msg.frame_data[7] = lcd[6];
    msg.dispatch = true;

  }

  if( msg.frame_id == 0x291 ){

    if( msg.frame_data[1] != lcdStockString[7] ||
      msg.frame_data[2] != lcdStockString[8] || 
      msg.frame_data[3] != lcdStockString[9] || 
      msg.frame_data[4] != lcdStockString[10] || 
      msg.frame_data[5] != lcdStockString[11] ){

      lcdStockString[7] = msg.frame_data[1];
      lcdStockString[8] = msg.frame_data[2];
      lcdStockString[9] = msg.frame_data[3];
      lcdStockString[10] = msg.frame_data[4];
      lcdStockString[11] = msg.frame_data[5];

      setOverrideTime(1500);

    }

    char* lcd = currentLcdString();

    msg.frame_data[1] = lcd[7];
    msg.frame_data[2] = lcd[8];
    msg.frame_data[3] = lcd[9];
    msg.frame_data[4] = lcd[10];
    msg.frame_data[5] = lcd[11];
    msg.dispatch = true;

  }




  /*if( msg.frame_id == 0x7E8  ){
   knockRetard = (msg.frame_data[3]*7)/2;
   }
   
   if( msg.frame_id == 0x7E8 && msg.frame_data[2] == 0x3C ){
   egt = (( msg.frame_data[3] *256)+ msg.frame_data[4] )/10 - 40;
   }
   
   if( msg.frame_id == 0x7E8 && msg.frame_data[2] == 0x11 && msg.frame_data[3] == 0x6B ){
   sparkAdvance = (msg.frame_data[5]*0x0A)/4;
   // sparkAdvance = msg.frame_data[5];
   }
   
   if( msg.frame_id == 0x73F && msg.frame_data[2] == 0x59 && msg.frame_data[3] == 0x6A ){
   pWeight = (((msg.frame_data[4]*256) + msg.frame_data[5]) * 0xB)/0x64 ;
   }*/

  if(msg.frame_id == 0x7E8 || msg.frame_id == 0x7E0)
  {
    //Serial.println(msg.frame_id);
    //Serial.println(msg.frame_data[0]);
    //Serial.println(msg.frame_data[1]);
    //Serial.println(msg.frame_data[2]);
    //Serial.println(msg.frame_data[3]);
    //Serial.println(msg.frame_data[4]);
    //Serial.println(msg.frame_data[5]);
    //Serial.println(msg.frame_data[6]);
    //Serial.println(msg.frame_data[7]);
    if(msg.frame_data[1] == 0x62)
    {
      if(msg.frame_data[2] == 0xDA && msg.frame_data[3] == 0x85) //Air to Fuel
      {
        afr = ((msg.frame_data[4] *23)/20);
        afrWhole = afr/10;
        afrRemainder = (afr % 10); 

      }
      else if(msg.frame_data[2] == 0x03 && msg.frame_data[3] == 0xCA) //Boost air temps
      {
        bat = ((msg.frame_data[4] * 0x09)/0x05)-0x26;
      }
      else if(msg.frame_data[2] == 0x03 && msg.frame_data[3] == 0xEC) //Knock retard degrees
      {
        krd = ((msg.frame_data[4]*256)+msg.frame_data[5])/5;
        krdWhole = krd / 100;
        krdRemainder = krd % 100;  
        if(krd > krdMax)
        {
          krdMax = krd;
          krdMaxWhole = krdMax / 100;
          krdMaxRemainder = krdMax % 100;
        }
      }
      else if(msg.frame_data[2] == 0xF4 && msg.frame_data[3] == 0x23) //FP in PSI 
      {
        fp = ((((msg.frame_data[4]*256)+msg.frame_data[5])*0x1D) / 0x14);  
      }
    }
    else if(msg.frame_data[1] == 0x41)
    {
      if(msg.frame_data[2] == 0x0B) //Boost
      {
        boost = ((msg.frame_data[3] * 0x91)/0x64)-0x91;
        boostWhole = boost/10;
        boostRemainder = abs((boost % 10)); 
      } 
    }   
  }
  // sprintf(lcdString, "A:%d.%d K:%d", afrWhole, afrRemainder, knockRetard );
  switch(MazdaLED::gaugePage)
  {
  case 0:
    sprintf(lcdString, "B%3d.%d A%2d.%d", boostWhole, boostRemainder, afrWhole, afrRemainder );
    break;
  case 1:
    sprintf(lcdString,  "F%4d B%3d  ", fp, bat );
    break;
  case 2:
    sprintf(lcdString,  "KR%2d.%d %2d.%d", krdWhole, krdRemainder, krdMaxWhole, krdMaxRemainder );
    break;
  }


  // Turn off extras like decimal point. Needs verification!
  if( msg.frame_id == 0x201 ){
    msg.dispatch = false;
  }


  // Animation
  // strcpy( MazdaLED::lcdString, "CANBusTriple" );
  // animationCounter++;


  return msg;
}







