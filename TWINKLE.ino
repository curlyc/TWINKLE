// thanks crait for tochars
// thanks Mre64 for the star i stole from battle for zuthsrah
#include "Arduboy2.h" //includes arduboy2 library
Arduboy2 ab; //so i dont have to type asmuch
const unsigned char star[] PROGMEM  = {  //sprite for the star aka player
    0x00, 0x10, 0x10, 0x28, 0xC6, 0x28, 0x10, 0x10, 0x00, 0x00,
      
};
// GLOBAL variables, you can use these anywhere after this point
int gamestate = 0; //start the game on the title page
int locx = 50; //players starting location left to right  in pixels
int locy = 50; //players starting location up or down in pixels
int alocx = 60; //asteroid starting location left to right in pixels
int alocy = 0;// asterpod starting location up or down in pixels
int adir = 0;// direction asteroid is going 
int hp = 10; //players starting hp, currently does nothing
int points = 0; //number of asteroids that have fallen off the screen currently still counts even if it hits player
int VooKnew = 1;
int fast = 3;
int bottom = 48;
int top  = 0;
int left = 0;
int right = 120;
void VooDoo() { //this is a function to set the location of the adteroid after the previous one has fallen off the screen
   VooKnew = random(1, 4) ; //choses wich corner asteroid will come out of
      if (VooKnew == 1) {
      alocx = left; //left
      alocy = top; //top
      adir = 0; //down right
      }
      if (VooKnew == 2) {
       alocx = right; //right
       alocy = top; //top
       adir = 1; //down left
      }
      if (VooKnew == 3) {
       alocx = left; //left
       alocy = bottom; //bottom
       adir = 3; //up right
      }
      if (VooKnew == 3) {
       alocx = right; //right
       alocy = bottom; //bottom
       adir = 4; //up left
      }
      
}
void wiggle() { //makes the asteroid move
  // move the asteroid down
       if ((VooKnew == 1) && (alocy <= bottom)&& ab.everyXFrames(fast)) { 
        alocx += 2;
        alocy += 1; //to speed up asterid decrease the number in () or oncrease the number in this line
      }
      if ((VooKnew == 2) && (alocy <= bottom)&& ab.everyXFrames(fast)) { 
        alocx -= 2;
        alocy += 1; //to speed up asterid decrease the number in () or oncrease the number in this line
      }
      if ((VooKnew == 3) && (alocy >= top)&& ab.everyXFrames(fast)) { 
        alocx += 2;
        alocy -= 1; //to speed up asterid decrease the number in () or oncrease the number in this line
      }
      if ((VooKnew == 4) && (alocy >= top)&& ab.everyXFrames(fast)) { 
        alocx -= 2;
        alocy -= 1; //to speed up asterid decrease the number in () or oncrease the number in this line
      }
}
void setup() {
  ab.begin();
  ab.setFrameRate(30); //speed controll
  ab.initRandomSeed(); //makes the random more random
  ab.clear();  //clears the screen
  Serial.begin(9600); //opens conection to pc through micro usb
}

void loop() {
  if (!(ab.nextFrame()))
    return;
    ab.clear();

    if (gamestate == 0) { //title screen
      if (ab.pressed(A_BUTTON)){
          gamestate += 1;
      }
      
  // print  TITLE 
  ab.setCursor((30), (0)); 
  ab.print("TWINKLE");  
  // print VERSION
  ab.setCursor((30), (50)); 
  ab.print("TEAM STAR");
  ab.setCursor((30), (40)); 
  ab.print("VERSION 0.1 ");
    }
    if (gamestate == 1) {
      wiggle();
      //if asteroid falls off screen
      if ((alocy >= bottom) or (alocy < top)) { //if the old asteroid falls off screen execute the next two lines
        points += 1; //takes players current points and adds 1 to it
        VooDoo(); // calls the VooDoo function to reset a new asteroid
      }
      
     // move the player left one space
    if (ab.pressed(LEFT_BUTTON) && (locx > 1)){
    locx -= 1; //edited this to make the player move faster
  }

  // move player right one space
  if (ab.pressed(RIGHT_BUTTON) && (locx <= 119)){
    locx += 1; //dito edit
  }

  // move player up one space
    if (ab.pressed(UP_BUTTON) && (locy > 1)){
    locy -= 1;
  }

  //move player down one space
  if (ab.pressed(DOWN_BUTTON) && (locy < 48)){
    locy += 1;
  }
  ab.setCursor((0), (0)); 
  ab.print("points"); //prints the word points on the screen
  ab.setCursor((0), (10)); 
  ab.print(points);//prints the current value of the variable points on the screen
  ab.setCursor((0), (20)); 
  ab.print("hp"); //prints the word points on the screen
  ab.setCursor((0), (30)); 
  ab.print(hp);
  ab.setCursor((alocx), (alocy));  //sets the location of the asteroid
  ab.print("*");//puts the asteroid on the screen
  ab.drawBitmap(locx, locy, star, 8, 8, WHITE); //places the star (player) on the screen
  
    } 

    if (gamestate == 2) {
      //pause screen
    }
    if (gamestate == 3) {
      //win screen
    }
    if (gamestate == 4) {
      //lose screen
    }
    
Serial.write(ab.getBuffer(), 128 * 64 / 8); //sends the screen to the pc
ab.display();
}
