#define PIN 15 // not sure what this is for...
ESP8266WebServer server(80);

WiFiClient wifiClient;
//PubSubClient mqttclient(mqttserver, 1883, callback, wifiClient);
 //     IPAddress testserver(192, 168, 1, 24);
// int* testserver[4] = {192,168,1,24};


PubSubClient mqttclient ; 

//WiFiUDP listener;


// multicast DNS responder
MDNSResponder mdns;

 /// set timer....
SimpleTimer timer;

const String version = "WS2812";


  //NeoPixelBus strip = NeoPixelBus(120, 2);

  NeoPixelBus* strip = NULL; // dynamic
 uint8_t* pixelsPOINT = NULL;



WiFiUDP Udp;
