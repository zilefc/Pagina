/* ==================================================================================================
                                     UNIVERSIDADE EDUARDO MONDLANE
                                        FACULDADE DE ENGENHARIA
                                DEPARTAMENTO DE ENGENHARIA ELECTROTÉCNICA
                                    CURSO DE ENGENHARIA ELECTRÓNICA
                                     Relatório do Projeto do Curso
                                Casa Inteligente controlada remotamente
                                   Autor: Mauro Miguel Dos Martins
                                 Supervisor: Luis Massango, Eng⁰.
                                             Maputo, Dezembro de 2021
   ==================================================================================================*/#include <ESP8266WiFi.h>
#include<FirebaseArduino.h>

#define FIREBASE_HOST "web-html-8cc81-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "wFhTUprtFn5w1eSoLTwcrI9LX4yE4fidzKNEVclo"
#define WIFI_SSID "Redmi Note 10S"
#define WIFI_PASSWORD "111333@5@5"
 
const int LED=1;
void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
if(Firebase.failed())
  {
    Serial.print(Firebase.error());
  }
  else{
    Serial.print("Firebase Connected");
  }
  
  Firebase.setInt("S1", 0);
}
void loop()
{
    String path = "/SALA/";
    FirebaseObject sala = Firebase.get(path);
    String LuzSala = sala.getString("estado");
    if(LuzSala == "LIGADA"){
      digitalWrite(LED, HIGH); 
    }
    else if (LuzSala == "DESLIGADA"){
      digitalWrite(LED, LOW);
    }
}
