
byte heat[LED_COUNT];
byte heating[LED_COUNT];
void fireSetup() {
  for (int i = 0; i < LED_COUNT; i++) {
    heat[i] = 255;
  }
  for (int i = 0; i < LED_COUNT; i++) {
    heating[i] = 0;
  }
}

uint32_t heatToRGB(byte heat) {
  int r = 0;
  int g = 0;
  int b = 0;
  if (heat < 220) {
    r = heat;
  } else{
    r = heat;
    g = heat - 220;
  }
  return strip.gamma32(strip.ColorHSV(heat*24,255,(128+heat/2))) ;
 // return strip.Color(r, g, b);
}

void fireLoop() {

  
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    //lower all leds by a factor of 1;
    if(heat[i]>1){
      heat[i]-=2;
    }
    if(random(600)==0){
      heating[i]=min(heating[i]+random(4,10),10);
    }
    if(heating[i]>0){
      int heatf = 25;
      heat[i] = min(heat[i]+heatf,255);
      for(int k=1;k<10;k++){
        heat[(i-k+LED_COUNT)%LED_COUNT]=min(heat[(i-k+LED_COUNT)%LED_COUNT]+(heatf/(1+(k/5))),255);
        heat[(i+k)%LED_COUNT]=min(heat[(i+k)%LED_COUNT]+(heatf/(1+(k/5)) ),255);
      }
      
      heating[i]--;
    }
    
    strip.setPixelColor(i, heatToRGB(heat[i]));
  }
  strip.show(); // Update strip with new contents

  delay(40);
}
