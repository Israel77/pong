#include <raylib.h>

typedef struct {
	int x;
	int y;
	float radius;
	int speedX;
	int speedY;
	Color color;
} Ball;

void drawBall(Ball *ball)
{
	DrawCircle((int)ball->x, (int)ball->y, ball->radius, ball->color);
}

void updateBall(Ball *ball, int screenWidth, int screenHeight)
{
	ball->x += ball->speedX;
	ball->y += ball->speedY;

	// Check for screen boundaries and reverse direction if necessary
	if (ball->x - ball->radius <= 0 ||
	    ball->x + ball->radius >= screenWidth) {
		ball->speedX *= -1;
	}
	if (ball->y - ball->radius <= 0 ||
	    ball->y + ball->radius >= screenHeight) {
		ball->speedY *= -1;
	}
}

typedef struct {
	int x;
	int y;
	int width;
	int height;
	int speed;
} Paddle;

void drawPaddle(Paddle *paddle)
{
	DrawRectangle(paddle->x, paddle->y, paddle->width, paddle->height,
		      WHITE);
}

void updatePlayerPaddle(Paddle *paddle, int screenHeight)
{
	if (IsKeyDown(KEY_UP)) {
		paddle->y -= paddle->speed;
		if (paddle->y < 0)
			paddle->y = 0;
	}
	if (IsKeyDown(KEY_DOWN)) {
		paddle->y += paddle->speed;
		if (paddle->y + paddle->height > screenHeight)
			paddle->y = screenHeight - paddle->height;
	}
}

int main()
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 900;

	const int PADDLE_WIDTH = 15;
	const int PADDLE_HEIGHT = SCREEN_HEIGHT / 10;

	const int FPS = 60;

	const float BALL_SPEED = 7.0f;
	const int PADDLE_SPEED = 10;

	Ball ball = { .x = SCREEN_WIDTH / 2,
		      .y = SCREEN_HEIGHT / 2,
		      .radius = 20.0f,
		      .speedX = BALL_SPEED,
		      .speedY = BALL_SPEED,
		      .color = WHITE };

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
	SetTargetFPS(FPS);

	Paddle leftPaddle = { .x = 30,
			      .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			      .width = PADDLE_WIDTH,
			      .height = PADDLE_HEIGHT,
			      .speed = PADDLE_SPEED };

	Paddle rightPaddle = { .x = SCREEN_WIDTH - 30 - PADDLE_WIDTH,
			       .y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,
			       .width = PADDLE_WIDTH,
			       .height = PADDLE_HEIGHT,
			       .speed = PADDLE_SPEED };

	while (!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();

		updatePlayerPaddle(&rightPaddle, SCREEN_HEIGHT);
		updateBall(&ball, SCREEN_WIDTH, SCREEN_HEIGHT);

		drawPaddle(&leftPaddle);
		drawPaddle(&rightPaddle);
		drawBall(&ball);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}