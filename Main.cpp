#include "raylib.h"


struct Ball

{
    float x, y;
    float speedX, speedY;
    float radius;

    void Draw()
    {
        DrawCircle((int)x, (int)y, radius, WHITE);

    }
        
};


struct Paddle
{
    float x, y;
    float speed;
    float width, height;


    Rectangle GetRect()
    {
        return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
    }


    void Draw()

    {
        DrawRectangleRec(GetRect(), WHITE);

    }


};


int main(void)
{
    InitWindow(800, 600, "Pong");
    SetWindowState(FLAG_VSYNC_HINT);

    Ball ball;
    ball.x = GetScreenWidth() / 2.0f;
    ball.y = GetScreenHeight() / 2.0f;
    ball.radius = 5;
    ball.speedX = 300;
    ball.speedY= 300;
    
    Paddle leftPaddle;
    leftPaddle.x = 50;
    leftPaddle.y = GetScreenHeight() / 2;
    leftPaddle.width = 10;
    leftPaddle.height = 150;
    leftPaddle.speed = 500;

    Paddle rightPaddle;
    rightPaddle.x = GetScreenWidth() - 50;
    rightPaddle.y = GetScreenHeight() /2;
    rightPaddle.width = 10;
    rightPaddle.height = 150;
    rightPaddle.speed = 500;

    const char* winnerText = nullptr;

    while (!WindowShouldClose())

    {
       ball.x += ball.speedX * GetFrameTime();
       ball.y  += ball.speedY * GetFrameTime();



        if (ball.y < 0)
        {
            ball.y = 0;
            ball.speedY *= -1;

        }


        if (ball.y   > GetScreenHeight())
        {
           ball.y= GetScreenHeight();
            ball.speedY *= -1;
        }

        if (leftPaddle.y < 0)
        {
            leftPaddle.y = 0;
            leftPaddle.speed *= -1;

        }

        if (rightPaddle.y < 0)
        {
            rightPaddle.y - 0;
            rightPaddle.speed *= -1;

        }

        if (leftPaddle.y > GetScreenHeight())
        {
            leftPaddle.y = GetScreenHeight();
            leftPaddle.speed *= -1;
            
        }

        if (rightPaddle.y > GetScreenHeight())
        {
            rightPaddle.y = GetScreenHeight();
            rightPaddle.speed *= -1;
            
        }

        




        if (IsKeyDown(KEY_W ))
        {

            leftPaddle.y -= leftPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_D))
        {

            leftPaddle.y += leftPaddle.speed * GetFrameTime();
        }


        if (IsKeyDown(KEY_UP))
        {

            rightPaddle.y -= rightPaddle.speed * GetFrameTime();
        }

        if (IsKeyDown(KEY_DOWN))
        {

            rightPaddle.y += rightPaddle.speed * GetFrameTime();


        }

 


        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, leftPaddle.GetRect()))
        {
           
            if (ball.speedX < 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
            }
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, rightPaddle.GetRect()))
        {
            if (ball.speedX > 0)
            {
                ball.speedX *= -1.1f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * - ball.speedX;
            }
        }

        if (ball.x < 0)
        {
            winnerText = "Jogador Direito Ganhou !";
        }
        
        if (ball.x > GetScreenWidth())
        {

            winnerText = "Jogador Esquerdo Ganhou !";
        }

        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            ball.x = GetScreenWidth() / 2;
            ball.y = GetScreenHeight() / 2;
            ball.speedX = 300;
            ball.speedY = 300; 
            winnerText = nullptr;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        ball.Draw();
        leftPaddle.Draw();
        rightPaddle.Draw();

        if (winnerText)
        {
            int textWidth = MeasureText(winnerText, 30);
            DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 30, YELLOW);
        }

        DrawFPS(20,20);
        EndDrawing();
    }

    CloseWindow();
    
    
    return 0;
}