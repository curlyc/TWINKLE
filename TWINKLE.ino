// thanks crait for tochars
// thanks Mre64 for the star i stole from battle for zuthsrah
#include "Arduboy2.h" //includes arduboy2 library
Arduboy2 ab; //so i dont have to type asmuch
const unsigned char star[] PROGMEM  = {  //sprite for the star aka player
    0x00, 0x10, 0x10, 0x28, 0xC6, 0x28, 0x10, 0x10, 0x00, 0x00,
      
};
int gamestate = 0; //start the game on the title page
int locx = 50; //players starting location left to right  in pixels
int locy = 50; //players starting location up or down in pixels
int alocx = 60; //asteroid starting location left to right in pixels
int alocy = 0;  // asterpod starting location up or down in pixels
int hp = 10; //players starting hp, currently does nothing
int points = 0; //number of asteroids that have fallen off the screen currently still counts even if it hits player

void VooDoo() { //this is a function to set the location of the adteroid after the previous one has fallen off the screen
   alocx = random(1, 120) ; //sets asteroid locationx to a random place between 1 and 120 left to right
   alocy = 0; //sets asteroids starting location to zero on the y axis up and down
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
      // move the asteroid down
       if ((alocy <= 50)&& ab.everyXFrames(3)) { //makes the asteroid move 1 pixel every x frame
        alocy += 1; //to speed up asterid decrease the number in () or oncrease the number in this line
      }
      //if asteroid falls off screen
      if (alocy >= 50) { //if the old asteroid falls off screen execute the next two lines
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
