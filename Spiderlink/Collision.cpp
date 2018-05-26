#include "Demo.h"

bool Demo::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

bool Demo::checkCollision() {
	int coll = 0;
	for (int i = 0; i < 50; i++) {
		if (IsCollided(xpos2, ypos2, frame_width2, frame_height2, xposStone[i], yposStone[i], frame_width3, frame_height3)) {
			coll++;
		}
	}
	
	if (coll > 0) {
		return true;
	}
	else {
		return false;
	}
	
}