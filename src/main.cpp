#include <M5StickCPlus.h>
#include <BleCombo.h>
#include <Arduino.h>

// Button A and B last pressed time in millis 
unsigned long btnALastOnMs = 0;
unsigned long btnBLastOnMs = 0; 

void beginBluetooth() {
  Serial.println("Starting BLE HID!");
  Mouse.begin();
  Keyboard.begin();
}

void setup(){
  // Initialize the M5StickCPlus object. Initialize the M5StickCPlus object
  M5.begin();

  M5.Lcd.setTextWrap(true);
  M5.Lcd.setTextSize(2);

  beginBluetooth();

  // M5.BtnA = Button(BUTTON_A_PIN, true, 100);
  // M5.BtnB = Button(BUTTON_B_PIN, true, 100);

  // LCD display. LCd display
  M5.Lcd.print("READY");

  
}

void clearLcd(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
}
  
void loop() {
  M5.update();

  if (!Keyboard.isConnected()){
      return;
  }

  auto now = millis();
  
  if (M5.BtnA.isPressed()){
    // use this to reduce sensitivity
    if (now - btnALastOnMs > 100){
      clearLcd();
      M5.Lcd.print("PageUp");
      Keyboard.press(KEY_PAGE_UP);
      Keyboard.releaseAll();      
    }
    btnALastOnMs = now;
  }

  if (M5.BtnB.isPressed()){
    if (now - btnBLastOnMs > 100){
      clearLcd();
      M5.Lcd.print("PageDown");
      Keyboard.press(KEY_PAGE_DOWN);
      Keyboard.releaseAll();
    }
    btnBLastOnMs = now;
  }
}
