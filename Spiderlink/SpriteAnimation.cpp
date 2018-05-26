#include "Demo.h"

void Demo::UpdateSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime / 5;

	if (spider_idle &&  frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx >= 2) frame_idx = 1;  else frame_idx++;

		// Pass frameIndex to shader
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
	}

	if (right_swing &&  frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx >= 6) frame_idx = 5;  else frame_idx++;

		// Pass frameIndex to shader
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);

	}
	if (left_swing &&  frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx >= 4) frame_idx = 3;  else frame_idx++;

		// Pass frameIndex to shader
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);

	}

	if ((left_fall || right_fall ||shoot) && frame_dur > FRAME_DUR) {
		frame_dur = 0;
		frame_idx = 0;

		// Pass frameIndex to shader
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
	}
}