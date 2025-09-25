// main.cpp

#include "coconut.hpp"
#include <raylib.h>

int main(int argc, char **argv)
{
   InitWindow(920, 920, "coconut");
   InitAudioDevice();
   SetExitKey(KEY_NULL);

   // note: stack warning, lets live on the edge!
   coconut::Application *app = new coconut::Application;
   if (app == nullptr || 
       !app->initialize(GetScreenWidth(), GetScreenHeight())) 
   {
      return 0;
   }

   while (!WindowShouldClose()) {
      if (!app->update()) {
         break;
      }

      ClearBackground(Color{ 0x11, 0x22, 0x33, 0xFF });
      BeginDrawing();
      
      app->render();

      DrawFPS(GetScreenWidth() - 100, 2);
      EndDrawing();
   }

   app->shutdown();
   delete app;

   CloseAudioDevice();
   CloseWindow();

   return 0;
}
