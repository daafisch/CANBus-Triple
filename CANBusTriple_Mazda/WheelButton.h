

int arrowButtonIn = A0;
int infoButtonIn = A1;

// Button states
#define ARROW_BUTTON_NONE 9
#define ARROW_BUTTON_ENTER 7
#define ARROW_BUTTON_UP 1
#define ARROW_BUTTON_DOWN 2
#define ARROW_BUTTON_LEFT 3
#define ARROW_BUTTON_RIGHT 5
#define INFO_BUTTON_NONE 10
#define INFO_BUTTON_NAV 1
#define INFO_BUTTON_BACK 2
#define INFO_BUTTON_INFO 3

//Button codes
#define B_ARROW_NONE   B00000000
#define B_ARROW_LEFT   B10000000
#define B_ARROW_RIGHT  B01000000
#define B_ARROW_UP     B00100000
#define B_ARROW_DOWN   B00010000
#define B_ARROW_ENTER  B00001000
#define B_INFO_NONE    B00000000
#define B_INFO_NAV     B00000100
#define B_INFO_BACK    B00000010
#define B_INFO_INFO    B00000001

/*
*  Returns a byte indicating wheel buttons that are down
*  
*/

class WheelButton {
  public:
    static byte getButtonDown();
    static boolean arrowButtonIsDown;
    static boolean infoButtonIsDown;
  private:
  
};


boolean WheelButton::arrowButtonIsDown = false;
boolean WheelButton::infoButtonIsDown = false;



byte WheelButton::getButtonDown(){
  
  int aBtn = analogRead(arrowButtonIn) / 100;
  byte out = 0;
  
  switch(aBtn){
    case ARROW_BUTTON_NONE:
      
    break;
    case ARROW_BUTTON_LEFT:
      out += B10000000;
    break;
    case ARROW_BUTTON_RIGHT:
      out += B01000000;
    break;
    case ARROW_BUTTON_UP:
      out += B00100000;
    break;
    case ARROW_BUTTON_DOWN:
      out += B00010000;
    break;
    case ARROW_BUTTON_ENTER:
      out += B00001000;
    break;
  }
  
  int iBtn = analogRead(infoButtonIn) / 100;
  switch( iBtn ){
    case INFO_BUTTON_NONE:
      
    break;
    case INFO_BUTTON_NAV:
      out += B00000100;
    break;
    case INFO_BUTTON_BACK:
      out += B00000010;
    break;
    case INFO_BUTTON_INFO:
      out += B0000001;
    break;
  }
  
  
  return out;
}



