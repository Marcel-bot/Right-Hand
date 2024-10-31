#include <main.h>

#define MAX_SIZE 20

struct motionMove {
    uint8_t part, degree;
};

struct motion {
    float duration;
    float x1, y1, x2, y2;
    uint8_t len;
    motionMove motion_moves[8];
};

motion processMotion;

class Queue {
    motion items[MAX_SIZE]{};
    int front;
    int rear;

public:
    Queue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return front == -1;
    }

    bool push(const motion element) {
        if (isEmpty()) {
            front = 0;
        }
        rear = (rear + 1) % MAX_SIZE;
        items[rear] = element;
        return true;
    }

    void pop() {
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }
    }

    motion first() const {
        return items[front];
    }
};

Queue motions;

double cubic_bezier(float p0, float p1, float p2, float p3, float t) {
    double one_minus_t = 1 - t;
    return one_minus_t * one_minus_t * one_minus_t * p0 +
           3 * one_minus_t * one_minus_t * t * p1 +
           3 * one_minus_t * t * t * p2 +
           t * t * t * p3;
}

void onReceive(const int size) {
    const uint8_t type = Wire.read();

    Serial.print("received: ");
    Serial.print(size);
    Serial.print("; type: ");
    Serial.println(type);

    if (type == MOTION_METADATA) {
        float receivedFloats[5];

        for (int i = 0; i < 5; i++) {
            byte floatBytes[4];

            for (int b = 0; b < 4; b++) {
                if (Wire.available()) {
                    floatBytes[b] = Wire.read();
                }
            }

            receivedFloats[i] = *reinterpret_cast<float *>(floatBytes);
        }

        for (int i = 0; i < 5; i++) {
            processMotion.duration = receivedFloats[0];
            processMotion.x1 = receivedFloats[1];
            processMotion.y1 = receivedFloats[2];
            processMotion.x2 = receivedFloats[3];
            processMotion.y2 = receivedFloats[4];
        }
    } else if (type == MOTION_DATA) {
        for (int i = 0; i < size - 1; i += 2) {
            processMotion.motion_moves[processMotion.len].part = Wire.read();
            processMotion.motion_moves[processMotion.len++].degree = Wire.read();
        }

        motions.push(processMotion);

        processMotion.len = 0;
    }
}

void setup() {
    Serial.begin(BAUDRATE);
    Wire.begin(I2C_ADDRESS);

    delay(100);
    Serial.println("Booted");

    Wire.onReceive(onReceive);
}

void loop() {
    if (!motions.isEmpty()) {
        Serial.println("Processing motion");
        for (float t = 0; t <= 1.0; t += .1) {
            Serial.println(cubic_bezier(motions.first().x1, motions.first().y1, motions.first().x2, motions.first().y2,
                                        t));
        }
        Serial.println("Processed");

        motions.pop();
    }
}
