#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define SPIDER_FRAMES 7
#define NUM_BUTTON 2
#define FRAME_DUR 80

using namespace glm;
struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void InitAudio();
	void AddInputs();
	float frame_width = 0, frame_height = 0, frame_width2 = 0, frame_height2 = 0, frame_width3 = 0, frame_height3 = 0;
private:
	float frame_dur = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, xposGround = 0, yposGround = 0,
		xVelocity2 = 0, yVelocity2 = 0, xposGround2 = 0, yposGround2 = 0, xpos2 = 0, ypos2 = 0,
		xInterval = 0, yInterval = 0, xpos3 = 0, ypos3 = 0;
		
	float yDistance = 0;

	float xposStone[50];
	float yposStone[50];

	float xposMenu = 0, yposMenu = 0;
	
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2, VBO3, VAO3, EBO3, texture3, program3;

	GLuint sVBO[50];
	GLuint sVAO[50];
	GLuint sEBO[50];
	
	bool spider_idle = true, right_swing = false, left_swing = false,
		right_fall = false, left_fall = false, shoot = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0, direction=0;
	void InitButton();
	void RenderButton();
	void InitButtonG();
	void RenderButtonG();
	void BuildBackground();
	void DrawBackground();
	void BuildGameOver();
	void DrawGameOver();
	void BuildSpider();
	void DrawSpider();
	void BuildThreat();
	void DrawThreat();
	void UpdateSpriteAnim(float deltaTime);
	void ControlSprite(float deltaTime);
	void BuildStone();
	void DrawStone();
	void UpdateStonePosition();
	void ReGenerate();

	void BuildStone(int i);
	void DrawStone(int i);

	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	bool checkCollision();
	bool gameplay_window = false;
	bool gameover_window = false;

	Mix_Chunk *sound = NULL;
	Mix_Music *music = NULL;
	int sfx_channel = -1;
	map<GLchar, Character> Characters;
	GLuint texture4[NUM_BUTTON], hover_texture4[NUM_BUTTON], VBO5, VAO5, program4;
	GLuint textureG[NUM_BUTTON], hover_textureG[NUM_BUTTON], VBO4, VAO4, program5;
	GLuint VBO6, VAO6, EBO6, program6, texture6;
	GLuint VBO7, VAO7, EBO7, program7, texture7;

	float button_width[NUM_BUTTON], button_height[NUM_BUTTON], hover_button_width[NUM_BUTTON], hover_button_height[NUM_BUTTON];
	float button_widthG[NUM_BUTTON], button_heightG[NUM_BUTTON], hover_button_widthG[NUM_BUTTON], hover_button_heightG[NUM_BUTTON];
	int activeButtonIndex = 0;
	

};
#endif

