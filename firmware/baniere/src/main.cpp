/*
 Auteur : Kevin Boyer--Navarro
 Date   : 17 novembre 2024
 Version: 1.0
 Description :
 Ce programme contrôle l'ouverture et la fermeture d'une bannière utilisée pour la Coupe de France de Robotique 2025.
 Le système repose sur un moteur pas à pas 28BYJ-48 actionnant un mécanisme pignon-crémaillère via un driver ULN2003.
 Deux modes de contrôle sont implémentés : via des boutons physiques ou via Bluetooth.
 Suggestions :
 Il serait intéressant d'ajouter une carte pour calculer le courant consommé par le moteur, ce qui servirait de fin de course.
 Cette option est déjà prévue dans le code mais doit être testée.
*/
#include <Arduino.h>
#include <Stepper.h> // Bibliothèque pour contrôler le moteur pas à pas

// Nombre de pas par révolution pour le moteur 28BYJ-48
const int stepsPerRevolution = 2048;
// Initialisation de l'objet Stepper avec les broches IN1, IN3, IN2, IN4
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
// Broche du capteur de courant
const int currentSensorPin = A0;
// Seuil de courant pour détecter une fin de course (ajustable selon le système)
const int currentThreshold = 600;
// État du moteur (direction inverse)
bool reverseDirection = false;
bool estOuvert = false;
// Message reçu via Bluetooth
String message;
void setup() {
 // Configuration de la vitesse du moteur en tours par minute
 myStepper.setSpeed(15);
 // Initialisation de la communication série pour le Bluetooth et le débogage
 Serial.begin(9600);
 Serial.println("Connexion établie. Envoyez un message.");
 Serial.println("Moteur prêt !");
 // Configuration des broches pour les boutons
 pinMode(6, INPUT); // Bouton pour l'ouverture
 pinMode(7, INPUT); // Bouton pour la fermeture
}
void loop() {
 // Lecture de la valeur du capteur de courant
 int currentReading = analogRead(currentSensorPin);
 // Lecture de l'état des boutons
 int stateD6 = digitalRead(6); // Bouton d'ouverture
 int stateD7 = digitalRead(7); // Bouton de fermeture
 // Affichage des messages reçus via Bluetooth
 Serial.print("Message : ");
 Serial.println(message);
 // Affichage de la valeur du courant détecté (diagnostic)
 Serial.print("Courant détecté : ");
 Serial.println(currentReading);
 // Vérification du seuil de courant pour détecter une fin de course
 if (currentReading > currentThreshold) {
   Serial.println("Pic d'intensité détecté ! Fin de course atteinte.");
   reverseDirection = true; // Inversion de direction
 }
 // Affichage de l'état du bouton d'ouverture
 if (stateD6 == HIGH) {
   Serial.println("Ouverture : bouton activé (HIGH)");
 } else {
   Serial.println("Ouverture : bouton désactivé (LOW)");
 }
 // Affichage de l'état du bouton de fermeture
 if (stateD7 == HIGH) {
   Serial.println("Fermeture : bouton activé (HIGH)");
 } else {
   Serial.println("Fermeture : bouton désactivé (LOW)");
 }
 // Lecture et traitement des messages Bluetooth
 if (Serial.available() > 0) {
   message = Serial.readString(); // Lecture du message
   Serial.println("Message reçu :");
   Serial.println(message);
   message.trim(); // Suppression des espaces inutiles
   if (message == "A") {
     Serial.println("Test de communication : OK");
   }
 }
 // Commande d'ouverture de la bannière
 if ((stateD6 == HIGH || message.equals("show_time_baby")) && !estOuvert) {
   estOuvert = true;
   if (reverseDirection) {
     // Mouvement anti-horaire (correction après un pic de courant)
     Serial.println("Rotation anti-horaire");
     myStepper.step(-stepsPerRevolution / 10); // Un dixième de tour
     delay(500);
   } else {
     // Mouvement horaire
     Serial.println("Rotation horaire");
     myStepper.step(stepsPerRevolution * 1.7); // Une rotation complète
     delay(1000);
     message = ""; // Réinitialisation du message
   }
 }
 // Commande de fermeture de la bannière
 if ((stateD7 == HIGH || message.equals("retour")) && estOuvert) {
   estOuvert = false;
   if (reverseDirection) {
     // Mouvement horaire (correction après un pic de courant)
     Serial.println("Rotation horaire");
     myStepper.step(stepsPerRevolution / 10); // Un dixième de tour
     delay(500);
   } else {
     // Mouvement anti-horaire
     Serial.println("Rotation anti-horaire");
     myStepper.step(-stepsPerRevolution * 1.7); // Une rotation complète
     delay(1000);
     message = ""; // Réinitialisation du message
   }
 }
}