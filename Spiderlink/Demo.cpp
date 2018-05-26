#include "Demo.h"

Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::Init()
{
	
	BuildBackground();
	InitButton();
	BuildGameOver();
	InitButtonG();
	InitAudio();
	AddInputs();
	InputMapping("SelectButton", SDLK_RETURN);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);

	BuildStone();
	BuildThreat();	
	BuildSpider();

	//Play the music
	Mix_PlayMusic(music, -1);
	SDL_Delay(150);
	
}

void Demo::Update(float deltaTime)
{
	if (IsKeyDown("Quit")) {
		SDL_Quit();
		exit(0);
	}

	if (IsKeyDown("SelectButton")) {
		if (activeButtonIndex == 1) {
			SDL_Quit();
			exit(0);
		}

		if (activeButtonIndex == 0) {
			gameplay_window = true;
			Render();
		}
	}

	if (gameplay_window == true)
	{
		UpdateSpriteAnim(deltaTime);
		ControlSprite(deltaTime);
	}

	if (IsKeyUp("NextButton")) {
		if (activeButtonIndex < NUM_BUTTON - 1) {
			activeButtonIndex = activeButtonIndex + 1;
			SDL_Delay(150);
		}
	}

	if (IsKeyUp("PrevButton")) {
		if (activeButtonIndex > 0) {
			activeButtonIndex = activeButtonIndex - 1;
			SDL_Delay(150);
		}
	}

	if (Mix_Playing(sfx_channel) == 0 && IsKeyDown("SFX")) {
		sfx_channel = Mix_PlayChannel(-1, sound, 0);
		if (sfx_channel == -1) {
			
		}
	}
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program4, "projection"), 1, GL_FALSE, value_ptr(projection));

	if (gameplay_window == true) {

		DrawThreat();
		DrawStone();
		DrawSpider();

	}
	else if (gameover_window == false) {
		DrawBackground();
		RenderButton();
		/*DrawGameOver();
		RenderButtonG();*/
	}
	else
	{
		DrawGameOver();
		RenderButtonG();
		xpos = 0, ypos = 0;
		ypos = 0, ypos2 = 0;
	}
		
}

void Demo::AddInputs() {
	InputMapping("Quit", SDLK_ESCAPE);
	InputMapping("BGM", SDLK_m);
	InputMapping("SFX", SDLK_s);
}

void Demo::ControlSprite(float deltaTime)
{	

	if (IsKeyDown("Move Right")) {
		spider_idle = false;
		right_swing = true;
		if (direction == 2) {
		}
		else {
			direction = 1;
			if (onGround) {
				yVelocity = -0.2f;
				xVelocity = 7.0f;
				//yVelocity2 = -0.2f;
				//xVelocity2 = 7.0f;
				onGround = false;
			}		
		}
	}

	if (IsKeyUp("Move Right")) {
		if (xVelocity > 3.0f) {
			xVelocity  = 3.0f;
			//xVelocity2 = 3.0f;			
		}
	}
	
	if (IsKeyDown("Move Left")) {
		spider_idle = false;
		left_swing = true;
		if (direction == 1) {
		}
		else{
			direction = 2;
			if (onGround) {
				yVelocity = -0.2f;
				xVelocity = 7.0f;
				//yVelocity2 = -0.2f;
				//xVelocity2 = 7.0f;
				onGround = false;
			}		
		}
	}

	if (IsKeyUp("Move Left")) {
		if (xVelocity > 3.0f) {
			xVelocity = 3.0f;
			//xVelocity2 = 3.0f;
		}
	}

	if (IsKeyDown("Jump")) {
		left_swing = false;
		right_swing = false;
		shoot = true;
		xVelocity = 0;
		yVelocity = 0;
		
		xpos2 += xpos-xposGround;
		ypos2 += ypos-yposGround;
		
		if (checkCollision()) {

			shoot = false;
			spider_idle = true;
			direction = 0;
			
			xposGround = xpos;
			yDistance = ypos - yposGround;			
			ypos =ypos - yDistance;
			yposGround = ypos;
			xVelocity = 0;
			yVelocity = 0;
			onGround = true;
			
			xposGround2 = xpos2;
			yDistance = ypos2 - yposGround2;
			ypos2 = ypos2 - yDistance;
			yposGround2 = ypos2;
			//xVelocity2 = 0;
			//yVelocity2 = 0;

			UpdateStonePosition();
			
		}
		else {
			xVelocity = 0;
			yVelocity = 1.0f;
			xVelocity2 = 0;
			yVelocity2 = 1.0f;
		}
		
	}
	
	//yVelocity += gravity * (deltaTime / 5);
	//xVelocity += gravity * (deltaTime / 5);

	if (direction == 1) {		
		xpos += (deltaTime / 7.5) * xVelocity;
		//xpos2 += (deltaTime / 7.5) * xVelocity2;
		
	}
	if (direction == 2) {
		xpos -= (deltaTime / 7.5) * xVelocity;
		//xpos2 -= (deltaTime / 7.5) * xVelocity2;
	}
		
	if (left_fall ) {
		xpos -= deltaTime / 7.5  * xVelocity;
		ypos2 += deltaTime / 1.5  * yVelocity2;
	}
	if (right_fall) {
		xpos += deltaTime / 7.5  * xVelocity;
		ypos2 += deltaTime / 1.5  * yVelocity2;
	}
	if (shoot) {
		ypos2 += deltaTime/1.5  * yVelocity2;
		xpos2 -= (deltaTime / 7.5) * xVelocity2;
	}
	ypos += deltaTime / 1.5  * yVelocity;
	

	if (ypos > (GetScreenHeight() - frame_height)+400) {
		/*exit(0);*/
		gameplay_window = false;
		gameover_window = true;
		Render();
	}
		

	if ( xpos < (xposGround-200)) {
		direction = 0;
		//ypos = yposGround;
		//xpos = xposGround;
		yVelocity = 1.0f;
		xVelocity = -1.0f;
		//ypos2 = yposGround2;
		//xpos2 = xposGround2;
		//yVelocity2 = 0;
		//xVelocity2 = 0;
		left_swing = false;
		
		left_fall = true;
						
	}
	if (xpos > (xposGround + 200) ) {
		direction = 0;
		//ypos = yposGround;
		//xpos = xposGround;
		yVelocity = 1.0f;
		xVelocity = 1.0f;
		//ypos2 = yposGround2;
		//xpos2 = xposGround2;
		//yVelocity2 = 0;
		//xVelocity2 = 0;
		
		right_swing = false;
		left_fall = true;
		
		
	}


	glUniform1i(glGetUniformLocation(this->program, "flip"), flip);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));
}


int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start("Spiderlink", 800, 600, false, WindowFlag::EXCLUSIVE_FULLSCREEN, 60, 1);

	return 0;
}

