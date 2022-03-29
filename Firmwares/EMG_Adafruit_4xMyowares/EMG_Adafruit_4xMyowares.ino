// Connection to Myoware sensor
#define EMG_PIN_1 A0
#define EMG_PIN_2 A1
#define EMG_PIN_3 A2
#define EMG_PIN_4 A3
#define PHOTORES_PIN A5 // Photoresistor at Arduino analog pin A5
// Integer for sensor value
int EMG_val_1;
int EMG_val_2;
int EMG_val_3;
int EMG_val_4;
int photores_val;          // Store value from photoresistor (0-1023)

//Set Sampling rate
const int Fs = 1000; //Hz
int prev_time = 0;
int current_time = 0;

void setup() {
  // Set up serial port
  Serial.begin(115200);
  pinMode(PHOTORES_PIN, INPUT);// Set pResistor - A0 pin as an input (optional)
  pinMode(EMG_PIN_1, INPUT);
  pinMode(EMG_PIN_2, INPUT);
  pinMode(EMG_PIN_3, INPUT);
  pinMode(EMG_PIN_4, INPUT);
}

void loop() {
  current_time = micros();
  if (current_time - prev_time > pow(10, 6) / Fs)
  {
    // Read sensor value
    EMG_val_1 = analogRead(EMG_PIN_1);
    EMG_val_2 = analogRead(EMG_PIN_2);
    EMG_val_3 = analogRead(EMG_PIN_3);
    EMG_val_4 = analogRead(EMG_PIN_4);
    photores_val = analogRead(PHOTORES_PIN);

    // Print value to Serial Monitor

    Serial.print(EMG_val_1);
    Serial.print(",");
    Serial.print(EMG_val_2);
    Serial.print(",");
    Serial.print(EMG_val_3);
    Serial.print(",");
    Serial.print(EMG_val_4);
    Serial.print(",");
    Serial.print(photores_val);
    Serial.print(",");
    Serial.println(current_time);
    prev_time = current_time;
  }
}
