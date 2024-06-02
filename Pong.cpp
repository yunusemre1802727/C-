#include <iostream>
#include <raylib.h>
using namespace std;
int player_score = 0;
int cpu_score = 0;
class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;
	void Draw() {
		DrawCircle(x, y, radius, WHITE);
}
	void Update() {
		x = x + speed_x;
		y = y + speed_y;

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speed_y = speed_y * -1;
		}
		if (x + radius >= GetScreenWidth()) {
			cpu_score++;
			ResetBall();
		}
		if (x - radius <= 0) {
			player_score++;
			ResetBall();
		}
	}
	void ResetBall() {
		x = GetScreenWidth() / 2;
		y = GetScreenHeight() / 2;
		int speed_choises[2] = { -1,1 };
		speed_x *= speed_choises[GetRandomValue(0, 1)];
		speed_y *= speed_choises[GetRandomValue(0, 1)];
	}
};

class Paddle{
protected:
	void LimitMovement() {
		if (y <= 0) {
			y = 0;
		}
		if (y >= GetScreenHeight() - height) {
			y = GetScreenHeight() - height;
		}
	}
public:
	float x, y;
	float width, height;
	int speed;
void Update(){
	if (IsKeyDown(KEY_UP)) {
		y = y - speed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		y = y + speed;
	}
	LimitMovement();
}
void Draw() {
	DrawRectangle(x,y,width,height,WHITE);
}

};

class CpuPaddle:public Paddle {
public:
	void Update(int ball_y_cor) {
		if (y + height / 2 > ball_y_cor) {
			y = y - speed;
		}
		if (y - height / 2 <= ball_y_cor) {
			y = y + speed;
		}
		LimitMovement();
	}
}; 
Ball ball;
Paddle player;
CpuPaddle cpu;

int main()
{
	cout << "Starting the game" << endl;
	const int screen_width = 1280;
	const int screen_height = 800;
	InitWindow(screen_width, screen_height, "My Pong Game!");
	SetTargetFPS(60);
	// Set ball
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 7;
	ball.speed_y = 7;

	// set player
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 6;
	// set cpu
	cpu.width = 25;
	cpu.height = 120;
	cpu.x =  10;
	cpu.y = screen_height / 2 - player.height / 2;
	cpu.speed = 6;

	

	while (WindowShouldClose() == false) {
		BeginDrawing();
		// Updating
		ball.Update();
		player.Update();
		cpu.Update(ball.y);
		// check collision
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height })) {
			ball.speed_x *= -1;
		}
		// Drawing
		ClearBackground(BLACK);
		DrawLine(screen_width/2, 0, screen_width / 2, screen_height, YELLOW);
		ball.Draw();
		player.Draw();
		cpu.Draw();
		DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player_score), 3* screen_width / 4 - 20, 20, 80, WHITE);
		EndDrawing();
	}
	CloseWindow();

	return 0;
}
