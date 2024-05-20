// #include "main.h"

// void init_serial() {
//     Serial.begin(SERIAL_BAUDRATE);
// }

// String buffer = "";

// void read_command() {
//     while (Serial.available()) {
//         char c = Serial.read();

//         if (c == '\n') {
//             if (buffer[0] == '0') {
//                 inner_shoulder.write(60);
//                 outer_shoulder.write(30);
//                 delay(3000);
//                 inner_shoulder.write(INNER_SHOULDER_DEFAULT);
//                 outer_shoulder.write(OUTER_SHOULDER_DEFAULT);

//             } else if (buffer[0] == '1') {
                
//             } else if (buffer[0] == '2') {

//             }

//             buffer = "";
//         } else {
//             buffer += c;
//         }
//     }
// }