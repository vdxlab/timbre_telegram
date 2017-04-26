#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "";     // your network SSID (name)
char password[] = ""; // your network key

// Initialize Telegram BOT
#define BOTtoken ""  // Bot Token (Get from Botfather)
#define chatID "" // https://stackoverflow.com/questions/32423837/telegram-bot-how-to-get-a-group-chat-id-ruby-gem-telegram-bot
#define relay 5
#define button 14
#define led 4

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

bool Start = false;

void sendMessage() {
      bot.sendMessage(chatID, "Sona el timbre!");
}

void dingDong() {
    digitalWrite(led,HIGH);
    digitalWrite(relay,HIGH);
    delay(200);
    digitalWrite(led,LOW);
    digitalWrite(relay,LOW);
    delay(200);
}
void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(relay, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  delay(10);
  digitalWrite(led, LOW); // initialize pin as off
}

int sw = 0;
int status_led = 0;

void loop() {
  sw = digitalRead(button);
  if ( sw == 0 ) {
    Serial.println("RING");
    sendMessage();
    dingDong();
    dingDong();
    delay(3000);
  }
  delay(100);
}
