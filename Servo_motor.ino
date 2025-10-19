#include <Servo.h>  // Include the Servo library

Servo servos[5];  // Array to hold 5 servo objects
const int servoPins[5] = {2, 3, 4, 5, 6};  // Pins to which servos are connected
int servoStates[5] = {0, 0, 0, 0, 0};      // Array to store servo states (0 or 1)

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  for (int i = 0; i < 5; i++) {
    servos[i].attach(servoPins[i]);  // Attach each servo to its pin
    servos[i].write(0);  // Initialize all servos to 0 degrees
  }
  Serial.println("Servos initialized to 0 degrees. Ready to receive data.");
}

void loop() {
  if (Serial.available()) {  // Check if data is available
    String receivedData = Serial.readStringUntil('\n');  // Read data until newline
    Serial.println("Received: " + receivedData);

    // Parse the received data
    int index = 0;
    char *token = strtok(receivedData.c_str(), ",");
    while (token != NULL && index < 5) {
      servoStates[index] = atoi(token);  // Convert to integer and store in servoStates
      token = strtok(NULL, ",");
      index++;
    }

    // Control servos based on the array
    for (int i = 0; i < 5; i++) {
      if (servoStates[i] == 1) {
        servos[i].write(180);  // Turn servo to 180 degrees
      } else {
        servos[i].write(0);  // Turn servo back to 0 degrees
      }
    }

    // Debug: Print the servo states
    Serial.print("Servo States: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(servoStates[i]);
      Serial.print(" ");
    }
    Serial.println();
  }
}