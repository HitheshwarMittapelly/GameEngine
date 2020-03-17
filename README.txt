How to run 
- Open the solution using Visual Studio
- Build the solution
- If using Visual Studio Debugger, the game starts automatically
- Locate the temp folder, the game will be at temp/(platform)/(configuration)/_MyGame/MonsterChase.exe
- Double click the exe file
Gameplay
- This game is the good old Breakout.
- Ball destroys the block upon hit
- Use the platform to control the ball trajectory
- Two ways to control the ball trajectory
  1. If the platform is stationary, ball goes left if it hit to the left of the platform center and the velocity is based on how far it hit from the center
  2. Just before the ball hits the platform, if the platform has any velocity this is imparted to the ball. So moving left when the ball is about to hit, makes the ball to go left.
- Finish all the blocks to win.
- Missing the ball means defeat

Key notes:

- SSE implementation for Matrix and Vector4 classes.
- Collision detection using Swept Axis checks.
- Multiple collision resolution functions - Collision resolution between two static objects, one static and one non static and both non static. Can be seen in Engine/Physics/PhysicsSystem.cpp
- All the standard coding conventions followed - Pass by reference return by value, inline methods, const correctness, Initializer values in constructors - Can be seen in any of the Engine/Input or Engine/Physics or Engine/Renderer or Engine/Utils/Matrix4x4.cpp
- Implemented delegates - Engine/Delegates/Delegates.cpp and Engine/Input/InputSystem.cpp (But not used in the game)