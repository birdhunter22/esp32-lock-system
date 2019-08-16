#include <FirebaseESP32.h>
#include <WiFi.h>


#define FIREBASE_HOST "************"             //firebase host
#define FIREBASE_AUTH "******************"       //firebase auth
 
const char* ssid = "mojo jojo";                  //ssid of wifi
const char* password =  "************";          // password of wifi

int lock = 23;                                   // esp 32 pin no. where lock is connected


// function for connecting to wifi
void connectToNetwork()                          
{
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }
 
  Serial.println("Connected to network");
 
}


    String path = "/Home/Unlock";                  //path to the firebase directory where string for mobile device is triggered
    String Data;
    String Data1;

FirebaseData firebaseData;                        // creating firebase object
 
void setup() 
{
 
  Serial.begin(115200);                           // setting the monitor value
 pinMode (lock, OUTPUT);                          // setting the pin np.23 defined as lock to be set as output

  connectToNetwork();
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
}
 
void loop() 
{
  Firebase.getString(firebaseData,path,Data1);
  digitalWrite(lock, HIGH);                     // the relay module works only with signal as low, so default it is set as high
  delay(1000);
    if (Data1 == "true")                        // if the string is triggered with mobile then the pin is set as low
    {  
      delay(1000);                       
    Serial.println("welcome ,Door is now open");                 
    Firebase.setString(firebaseData,path,"false");
    digitalWrite(lock, LOW);
    delay(1000);
    
    }
  }
