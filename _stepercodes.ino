#include <Stepper.h>
const int stepsPerRevolution = 2048;
// Initialize the stepper library on pins (change if needed)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
String inputString = "";   // store serial input
boolean inputComplete = false;
void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(10);  // set motor speed (RPM)
  Serial.println("Stepper Motor Control Ready!");
  Serial.println("Enter command: rotate <degrees>");
}
void loop() {
  // Check if input is available
  if (inputComplete) {
    processCommand(inputString);
    inputString = "";
    inputComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {   
      inputComplete = true;
    } else {
      inputString += inChar;
    }
  }
}
// Function to process commands
void processCommand(String command) {
  command.trim(); // remove spaces
  // Check if the command starts with "rotate"
  if (command.startsWith("rotate")) {
    // Extract degree value
    int spaceIndex = command.indexOf(' ');
    if (spaceIndex > 0) {
      String degreeStr = command.substring(spaceIndex + 1);
      int degrees = degreeStr.toInt();  // convert to integer
      // Convert degrees to steps
      long steps = mapDegreesToSteps(degrees);
      Serial.print("Rotating ");
      Serial.print(degrees);
      Serial.print(" degrees -> ");
      Serial.print(steps);
      Serial.println(" steps");
      // Rotate motor
      myStepper.step(steps);
    } else {
      Serial.println("Invalid format! Use: rotate <degrees>");
    }
  } else {
    Serial.println("Unknown command. Use: rotate <degrees>");
  }
}
// Function to convert degrees to steps
long mapDegreesToSteps(int degrees) {
  return (long)degrees * stepsPerRevolution / 360;
}









