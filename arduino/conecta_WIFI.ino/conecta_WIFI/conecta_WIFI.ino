#include <Arduino.h>
#include <ESPAsyncWebSrv.h>
#include "DHTesp.h"
#define DHTpin 15
DHTesp dht;

const char* ssid="afabri";
const char* password= "capacitacion";

AsyncWebServer server(80);

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  conectarse();
   dht.setup(DHTpin, DHTesp::DHT11);

  server.on("/",HTTP_GET,[](AsyncWebServerRequest * request){    
    int numParametros=request->params();
    Serial.print(numParametros);
    if(numParametros==0){
        request->send(200,"text/html","<H1> hola mundo </H1>");
    }
    else{
      AsyncWebParameter *p=request->getParam(0);
      String html="<H1>hola"+p->value()+"desde esp32</H1>";
      request->send(200,"text/html",html);
    }
    });

    server.on("/adios",HTTP_GET,[](AsyncWebServerRequest * r){
    r->send(200,"text/html","<h1>adios</h1>");
    });

    server.on("/on",HTTP_GET,[](AsyncWebServerRequest * r){
    digitalWrite(2, HIGH);
    r->send(200,"text/html","<h1>Led Prendido</h1>");
    });
    server.on("/off",HTTP_GET,[](AsyncWebServerRequest * r){
    digitalWrite(2, LOW);
    r->send(200,"text/html","<h1>Led Apagado</h1>");
    });
    server.on("/estadoSensor",HTTP_GET,[](AsyncWebServerRequest * r){
    String estado=dht.getStatusString();
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.on("/humedad",HTTP_GET,[](AsyncWebServerRequest * r){
    float humedad =  dht.getHumidity();
    String estado=String(humedad,1);
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.on("/temperaturaC",HTTP_GET,[](AsyncWebServerRequest * r){
      float temperatura = dht.getTemperature(); 
    String estado=String(temperatura,1);
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.on("/temperaturaF",HTTP_GET,[](AsyncWebServerRequest * r){
      float temperatura = dht.getTemperature(); 
    String estado=String(dht.toFahrenheit(temperatura), 1);
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.on("/indCalorC",HTTP_GET,[](AsyncWebServerRequest * r){
       float humedad =  dht.getHumidity();
    float temperatura = dht.getTemperature();   
    String estado=String(dht.computeHeatIndex(temperatura, humedad, false),1);
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.on("/indCalorF",HTTP_GET,[](AsyncWebServerRequest * r){
       float humedad =  dht.getHumidity();
    float temperatura = dht.getTemperature();   
    String estado=String(dht.computeHeatIndex(dht.toFahrenheit(temperatura), humedad, true),1);
    r->send(200,"text/html","<h1>"+estado+"</h1>");
    });
    server.begin();    
 
//lograda la conexion se muestra la informacion
}

void loop() {
  // put your main code here, to run repeatedly:
                          

 
}


  void conectarse(){
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid,password);
    while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }    
    Serial.println(WiFi.localIP());
      
    }
