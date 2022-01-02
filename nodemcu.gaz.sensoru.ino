#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "GQgx0nGCCCJ68wPX10jPRS1q9YSOy5KK"; //Mail Adresinize Gelen tokeni Buraya yapistirin
char ssid[] = "FiberHGW_TPFC5E_2.4GHz"; //Wifi Isminizi buraya yazin
char pass[] = "cbkpjpXL"; //Wifi sifrenizi buraya yazin

String MakerIFTTT_Key ;
;String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;

BlynkTimer timer;
WiFiClient client;

int GazSensoru = A0; // A0 pinine
int data = 0;

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);

  
}

void loop()
{
  timer.run();
  Blynk.run();
}

void getSendData()
{
  data = analogRead(GazSensoru);
  Blynk.virtualWrite(V2, data);

  if (data > 490)
  {
    Blynk.notify("Dikkat !!! Gaz Sensörünüz Çalıştı");
    digitalWrite(YesilLed, LOW);
    digitalWrite(KirmiziLed, HIGH);
    tone(buzzer, 1000, 200);
    delay(6000);
    if (client.connect("maker.ifttt.com",80)) {
      MakerIFTTT_Key ="he8OcY1twZAkb8tl3ALvO";
      MakerIFTTT_Event ="ESP_CALL";
      p = post_rqst;
      p = append_str(p, "POST /trigger/");
      p = append_str(p, MakerIFTTT_Event);
      p = append_str(p, "/with/key/");
      p = append_str(p, MakerIFTTT_Key);
      p = append_str(p, " HTTP/1.1\r\n");
      p = append_str(p, "Host: maker.ifttt.com\r\n");
      p = append_str(p, "Content-Type: application/json\r\n");
      p = append_str(p, "Content-Length: ");
      content_length_here = p;
      p = append_str(p, "NN\r\n");
      p = append_str(p, "\r\n");
      json_start = p;
      p = append_str(p, "{\"value1\":\"");
      p = append_str(p, "DUMAN DUMAN UYANN DUMANN VARR");
      p = append_str(p, "\",\"value2\":\"");
      p = append_str(p, "");
      p = append_str(p, "\",\"value3\":\"");
      p = append_str(p, "");
      p = append_str(p, "\"}");
  
      compi= strlen(json_start);
      content_length_here[0] = '0' + (compi/10);
      content_length_here[1] = '0' + (compi%10);
      client.print(post_rqst);
    }
    
  }

}
