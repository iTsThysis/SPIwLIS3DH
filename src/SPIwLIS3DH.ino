SYSTEM_MODE(MANUAL)
SYSTEM_THREAD(ENABLED)

#include "oled-wing-adafruit.h"
#include "LIS3DH.h"


OledWingAdafruit display;
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHSPI accel(SPI, D3, WKP);
unsigned long lastPrintSample = 0;


void displaySetup() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);

}
void setup() {
  display.setup();
	displaySetup();
  display.setTextSize(1);
	display.setTextColor(WHITE);
	display.println("DISPLAY CONNECTED");
	display.display();
  delay(2000);
  LIS3DHConfig config;
  config.setAccelMode(LIS3DH::RATE_100_HZ);
  accel.setup(config);
}

void loop() {
  display.loop();
  if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
			float gx = sample.x / 1600.0;
      float gy = sample.y / 1600.0;
      float gz = sample.z / 1600.0;
      displaySetup();
      display.println("Acc.:");
      display.setCursor(64, 0);
      display.print("G Force:");
      display.setCursor(0, 8);
      display.print("X:");
      display.println(sample.x);
      
      display.setCursor(64, 8);
      display.print(gx);
      display.setCursor(0, 16);
      
      display.print("Y:");
      display.println(sample.y);
      
      display.setCursor(64, 16);
      display.print(gy);
      display.setCursor(0, 24);
      
      display.print("Z:");
      display.print(sample.z);

      display.setCursor(64, 24);
      display.print(gz);
      display.setCursor(0, 32);

      display.display();
      delay(200);
		}
		else {
			displaySetup();
      display.println("no sample");
      display.display();
		}
	}
}