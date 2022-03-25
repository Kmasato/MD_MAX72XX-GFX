#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <Adafruit_GFX.h>

/* LED Matrix settings */
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5

#define ROW_SIZE 16
#define COLUMN_SIZE 16

class MD_GFX:public MD_MAX72XX{
  private:
    
  public:
    using MD_MAX72XX::MD_MAX72XX;

    void drawCanvas(GFXcanvas1 canvas){
      for(int i = 0; i < ROW_SIZE; i++){
        for(int j = 0; j < COLUMN_SIZE; j++){
          drawPoint(i,j,canvas.getPixel(i,j));
        }
      }
    }

    /* transform the coordinate for square display*/
    void drawPoint(int x, int y, bool state){
      if(0 <= y && y < COLUMN_SIZE/2){
        setPoint(COLUMN_SIZE/2 - y - 1, x, state);
        }
      if(COLUMN_SIZE/2 <= y && y < COLUMN_SIZE){
        setPoint(COLUMN_SIZE - y - 1, x + ROW_SIZE, state);
        }
    }
};

MD_GFX mx = MD_GFX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
GFXcanvas1 myCanvas = GFXcanvas1(ROW_SIZE, COLUMN_SIZE);

void setup() {
  mx.begin();
}

void loop() {

  mx.clear();

  /* Draw Text */
  myCanvas.setTextSize(1);
  myCanvas.drawChar(0,0,'A',0x01,0,1);
  myCanvas.drawChar(6,0,'B',0x01,0,1);
  myCanvas.drawChar(12,0,'C',0x01,0,1);
  myCanvas.drawChar(0,9,'D',0x01,0,1);
  myCanvas.drawChar(6,9,'E',0x01,0,1);
  myCanvas.drawChar(12,9,'F',0x01,0,1);

  /* Draw some figures
  myCanvas.fillRect(1,1,3,3,0x01);
  myCanvas.fillRect(2,7,5,8,0x01);
  myCanvas.fillCircle(10,4,3,0x01);
  myCanvas.fillTriangle(9,9,15,9,12,15,0x01);
  */

  mx.drawCanvas(myCanvas);
  delay(200);
}
