#include <Servo.h>

Servo bottom;
Servo top;

void setup() {
	pinMode(52, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);

	bottom.attach(8);
	top.attach(10);
}

bool canRun = true;
int num = 0;

int lastState;

void loop() {
	int buttonState = digitalRead(52);

	if (lastState == LOW && buttonState == HIGH) {
		top.write(180);
		delay(500);
		bottom.write(60);
		delay(500);
		top.write(90);
	} else {
		bottom.write(90);
		top.write(90);
	}

	lastState = buttonState;
}
