#include "main.h"

void init_servos()
{
    inner_shoulder.attach(INNER_SHOULDER_PIN);
    outer_shoulder.attach(OUTER_SHOULDER_PIN);
    under_shoulder.attach(UNDER_SHOULDER_PIN);
    elbow.attach(ELBOW_PIN);

    inner_shoulder.write(INNER_SHOULDER_DEFAULT);
    outer_shoulder.write(OUTER_SHOULDER_DEFAULT);
    under_shoulder.write(UNDER_SHOULDER_DEFAULT);
    elbow.write(ELBOW_DEFAULT);
}

void init_serial()
{
    Serial.begin(SERIAL_BAUDRATE);
}

String buffer = "";

void read_command()
{
    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\n')
        {
            if (buffer[0] == '0')
            {
                for (int i = 0; i < 100; i++)
                {
                    inner_shoulder.write(int(i * .6));
                    elbow.write(int(i * .45));
                    delay(5);
                }
                delay(3000);
                for (int i = 99; i >= 0; i--)
                {
                    inner_shoulder.write(int(i * .6));
                    elbow.write(int(i * .45));
                    delay(5);
                }
            }
            else if (buffer[0] == '1')
            {
                for (int i = 10; i < 100; i++)
                {
                    outer_shoulder.write(20 + i * (180 - 30) / 100);
                    under_shoulder.write(90 + i * (180 - 90) / 100);
                    delay(22);
                }
                delay(2000);
                for (int i = 0; i < 2; i++)
                {
                    elbow.write(30);
                    delay(500);
                    elbow.write(0);
                    delay(500);
                }

                for (int i = 10; i < 100; i++)
                {
                    outer_shoulder.write(1.7 * i);
                    under_shoulder.write(1.8 * i);
                    delay(22);
                }

                outer_shoulder.write(20);
                under_shoulder.write(90);
            }
            else if (buffer[0] == '2')
            {
            }

            buffer = "";
        }
        else
        {
            buffer += c;
        }
    }
}

void setup()
{
    init_servos();
    init_serial();
}

void loop()
{
    read_command();
}
