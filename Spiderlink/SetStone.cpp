#include "Demo.h"

void Demo::BuildStone() {
	for (int i = 0; i < 10; i++) {
	
		BuildStone(i);
		yInterval -= 250;
	}

	xInterval = 120;
	yInterval = -55;

	for (int i = 10; i < 20; i++) {
		BuildStone(i);
		yInterval -= 150;
	}

	xInterval = -120;
	yInterval = -30;
	
	for (int i = 20; i < 30; i++) {
		
		BuildStone(i);
		yInterval -= 200;
	}

	xInterval = -240;
	yInterval = -100;

	for (int i = 30; i < 40; i++) {

		BuildStone(i);
		yInterval -= 210;
	}

	xInterval = 250;
	yInterval = -140;

	for (int i = 40; i < 50; i++) {

		BuildStone(i);
		yInterval -= 280;
	}
}

void Demo::DrawStone() {
	for (int i = 0; i < 50; i++) {		
		DrawStone(i);
	}
}

void Demo::UpdateStonePosition() {
	for (int i = 0; i < 50; i++) {
		yposStone[i] = yposStone[i] - (yDistance);
	}

}

void Demo::ReGenerate() {

}