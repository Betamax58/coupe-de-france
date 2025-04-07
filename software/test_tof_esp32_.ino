#include <SPI.h>
#include <Wire.h>
#include <Adafruit_VL53L1X.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <ArduinoJson.h> // Librairie JSON adaptée à Arduino
#include "SparkFun_Qwiic_OTOS_Arduino_Library.h"
 
// Capteur OTOS
QwiicOTOS myOtos;
 
// Création du noeud ROS
ros::NodeHandle nh;
 
// Adresse du multiplexeur TCA9548A
#define TCA9548A_ADDR 0x70
#define VL53L1X_ADDR 0x29
#define NUM_SENSORS 6  // Nombre de capteurs connectés
#define RESET_PIN 5     // Broche de reset du multiplexeur
 
Adafruit_VL53L1X lox[NUM_SENSORS];
bool sensorConnected[NUM_SENSORS];  // État des capteurs
 
// Déclaration des Publishers ROS pour TOF et OTOS
std_msgs::String str_msg_tof;
std_msgs::String str_msg_otos;
ros::Publisher chatter_tof("tof_data", &str_msg_tof);
ros::Publisher chatter_otos("otos_data", &str_msg_otos);
 
// Prototypes
void enableChannels(uint8_t channel);
bool checkSensorConnection(uint8_t channel);
void resetMultiplexeur();
String generateJSON_tof();
String generateJSON_otos();
 
void setup() {
    // Initialisation du noeud ROS
    nh.initNode();
    nh.advertise(chatter_tof);
    nh.advertise(chatter_otos);
 
    Serial.begin(115200);
    Wire.begin(8, 9);
    Wire.setClock(100000);  // Réduction de la vitesse I²C
 
    // Timeout pour éviter blocage si OTOS non détecté
    unsigned long startAttemptTime = millis();
    while (!myOtos.begin()) {
        Serial.println("OTOS non connecté !");
        delay(1000);
        if (millis() - startAttemptTime > 5000) {
            Serial.println("Impossible de détecter OTOS. Redémarrage annulé.");
            break;
        }
    }
 
    // Initialisation OTOS avec coefficients de correction
    Serial.println("OTOS connecté !");
    myOtos.calibrateImu();
    myOtos.setLinearScalar(0.598802395);
    myOtos.setAngularScalar(0.7783);
    myOtos.resetTracking();
    Serial.println("OTOS prêt.");
 
    // Configuration de la broche RESET du multiplexeur
    pinMode(RESET_PIN, OUTPUT);
    resetMultiplexeur();
 
    // Configuration des GPIO pour l'adresse I2C du TCA9548A
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
 
    Serial.println("I2C initialisé.");
 
    // Vérification et initialisation des capteurs TOF
    for (int i = 0; i < NUM_SENSORS; i++) {
        enableChannels(i);
        Serial.print("Vérification de la connexion I2C pour le capteur ");
        Serial.println(i + 1);
 
        if (!checkSensorConnection(i)) {
            Serial.print("Capteur ");
            Serial.print(i + 1);
            Serial.println(" non détecté.");
            sensorConnected[i] = false;
            continue;
        }
 
        if (!lox[i].begin(VL53L1X_ADDR, &Wire)) {
            Serial.print("Erreur d'initialisation pour le capteur ");
            Serial.println(i + 1);
            sensorConnected[i] = false;
        } else {
            Serial.print("Capteur ");
            Serial.print(i + 1);
            Serial.println(" initialisé avec succès !");
            sensorConnected[i] = true;
            lox[i].startRanging();
        }
    }
}
 
void loop() {
    // Génération des JSON
    String jsonString_tof = generateJSON_tof();
    String jsonString_otos = generateJSON_otos();
 
    // Affichage dans le moniteur série
    Serial.println(jsonString_tof);
    Serial.println(jsonString_otos);
    Serial.println("");
    Serial.println("");
 
    // Publication sur ROS
    str_msg_tof.data = jsonString_tof.c_str();
    str_msg_otos.data = jsonString_otos.c_str();
    chatter_tof.publish(&str_msg_tof);
    chatter_otos.publish(&str_msg_otos);
 
    nh.spinOnce();
    delay(50);
}
 
// Fonction pour effectuer un reset du multiplexeur
void resetMultiplexeur() {
    digitalWrite(RESET_PIN, LOW);
    delay(10);
    digitalWrite(RESET_PIN, HIGH);
    delay(10);
}
 
// Fonction pour activer un canal du multiplexeur
void enableChannels(uint8_t channel) {
    resetMultiplexeur();
    Wire.beginTransmission(TCA9548A_ADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
    delay(2);
}
 
// Fonction pour vérifier la connexion d'un capteur via I2C
bool checkSensorConnection(uint8_t channel) {
    enableChannels(channel);
    Wire.beginTransmission(VL53L1X_ADDR);
    uint8_t error = Wire.endTransmission();
    return (error == 0);
}
 
// Génération du JSON pour les capteurs TOF
String generateJSON_tof() {
    DynamicJsonDocument doc(256);
 
    for (int i = 0; i < NUM_SENSORS; i++) {
        enableChannels(i);
        if (sensorConnected[i] && lox[i].dataReady()) {
            float distance = lox[i].distance() / 1000.0;
            doc["tof" + String(i + 1)] = distance;
        } else {
            doc["tof" + String(i + 1)] = "déconnecté";
        }
    }
 
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}
 
// Génération du JSON pour le capteur OTOS
String generateJSON_otos() {
    DynamicJsonDocument doc(256);
 
    // Récupération des données OTOS
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);
 
    doc["x"] = myPosition.x * 2.54;  // Conversion pouces → cm
    doc["y"] = myPosition.y * 2.54;
    doc["heading"] = myPosition.h;
 
    String jsonString;
    serializeJson(doc, jsonString);
    return jsonString;
}
