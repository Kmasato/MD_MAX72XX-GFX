#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <Adafruit_GFX.h>

/* LED Matrix settings */
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define LED_NUM 8
#define ROW_MODULE_NUM 2
#define COL_MODULE_NUM 2
#define MAX_DEVICES 4

#define CLK_PIN 18
#define DATA_PIN 23
#define CS_PIN 5

class MD_GFX:public MD_MAX72XX{
  private:
    
  public:
    using MD_MAX72XX::MD_MAX72XX;

    void drawCanvas(GFXcanvas1 canvas){
      for(int i = 0; i < ROW_MODULE_NUM * LED_NUM; i++){
        for(int j = 0; j < COL_MODULE_NUM * LED_NUM; j++){
          drawPoint(i,j,canvas.getPixel(i,j));
        }
      }
    }
    
    /* transform the coordinate for square display*/
    void drawPoint(int x, int y, bool state){
      setPoint(LED_NUM - int(y % LED_NUM) - 1, x + int(y / LED_NUM) * (ROW_MODULE_NUM * LED_NUM), state);
    }
};

MD_GFX mx = MD_GFX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
GFXcanvas1 myCanvas = GFXcanvas1(ROW_MODULE_NUM * LED_NUM, COL_MODULE_NUM * LED_NUM);

void setup() {
  mx.begin();
}

void loop() {

  mx.clear();

  /* Draw Text
  myCanvas.setTextSize(1);
  myCanvas.drawChar(2,1,'1',0x01,0,1);
  myCanvas.drawChar(8,1,'2',0x01,0,1);
  myCanvas.drawChar(2,9,'3',0x01,0,1);
  myCanvas.drawChar(8,9,'4',0x01,0,1);
  */

  /* Draw some figures */
  myCanvas.fillRect(1,1,3,3,0x01);
  myCanvas.drawRect(2,5,5,7,0x01);
  myCanvas.fillCircle(11,4,3,0x01);
  myCanvas.drawTriangle(9,9,15,9,12,15,0x01);

  mx.drawCanvas(myCanvas);
  delay(200);
}
