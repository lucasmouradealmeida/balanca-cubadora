#include <usbhid.h>
#include <hiduniversal.h>
#include <Usb.h>
#include <usbhub.h>
#include <hidboot.h>
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);

String data = "";

class KbdRptParser : public KeyboardReportParser {
    void PrintKey(uint8_t mod, uint8_t key);
  protected:
    virtual void OnKeyDown  (uint8_t mod, uint8_t key);
    virtual void OnKeyPressed(uint8_t key);
};

KbdRptParser Prs;

void setup() {
  Serial.begin(115200);
  Usb.Init();
  delay(200);
  Hid.SetReportParser(0, (HIDReportParser*)&Prs);
}
void loop(){
  Usb.Task();
}


void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key) {
  uint8_t c = OemToAscii(mod, key);

  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnKeyPressed(uint8_t key) {
  char c = (char)key;

  if (key == 19) {
    String ret = data;
    data = "";
    barcodeCallback(ret);
  } else {
    data += c;
  }
}

void barcodeCallback(String data){
  Serial.println(data);
}
