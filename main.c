#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/startimage.h"
#include "images/loseimage.h"
#include "images/winimage.h"
#include "images/dartpic.h"
#include "images/balloonpic.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

  Dart d;


/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  STARTNEXT,
  PLAYSETUP,
  PLAY,
  WIN,
  WINNEXT,

  LOSE,
  LOSECONDITION,
};

int main(void) {

  //balloon b;
  //Dart d;
  char buffer[50];
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;


  while (1) {

    currentButtons = BUTTONS; // Load the current state of the buttons
   waitForVBlank();
    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw


    switch (state) {
      case START:
      drawFullScreenImageDMA(startimage);
  //drawString(100, 100, "START", MAGENTA);
    int timer=1800;
    int start=1800;
        // state = ?
        //if(KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = STARTNEXT;

      //}
        break;
        case STARTNEXT:
        drawString(100, 100, "START", MAGENTA);
        //drawFullScreenImageDMA(startimage);
        if(KEY_DOWN(BUTTON_START, currentButtons)){
            state = PLAYSETUP;
        }
        //if(KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
        //  state = PLAYSETUP;
        //}
        if(KEY_DOWN(BUTTON_SELECT, currentButtons)){
          state=START;
        }
      break;
      case PLAYSETUP:
       fillScreenDMA(BLACK);
       //sprintf(buffer, "TOTAL TIME: %d", timer / 60);
       //drawString(100, 50, buffer, GREEN);
      //drawImageDMA(100,175, 50, 50, balloonpic);
      //drawImageDMA(50,20, 50, 50, dartpic);
       //drawImageDMA(balloonposRow,balloonposCol, 50, 50, balloonpic);

       d.row = 5;
       d.col = 5;
       drawImageDMA(d.row, d.col, 20, 20, dartpic);
       drawImageDMA(110, 180, 50, 50, balloonpic);
       state = PLAY;

       break;

       case PLAY:


      //  drawImageDMA(50,20, 50, 50, dartpic);
      //drawImageDMA(d.row, d.col, 50, 50, dartpic);
       sprintf(buffer, "TIME REMAINING: %d", start / 60);
       //drawString(100, 50, buffer, GREEN);
       drawRectDMA(150,100, 20,20, BLACK);
       drawString(150, 10, buffer, GREEN);

        //timer++;
       start--;
            if (KEY_DOWN(BUTTON_UP, currentButtons)){
     					move(&d, -4, 0);

             }
     				 if (KEY_DOWN(BUTTON_DOWN, currentButtons)){
     					move(&d, 4, 0);
             }
     				 if (KEY_DOWN(BUTTON_LEFT, currentButtons)){
     					move(&d, 0, -4);
             }
     				 if (KEY_DOWN(BUTTON_RIGHT, currentButtons)){
     					move(&d, 0, 4);
             }


               int val=collision(d);

               if(KEY_DOWN(BUTTON_SELECT, currentButtons)){
                 state=START;
               }

        // state = ?

        if(val == 1){
          timer-=start;
          state=WIN;
        }
        if(start == 0){
         state=LOSE;
       }

        break;
      case WIN:
      drawFullScreenImageDMA(winimage);


      state=WINNEXT;
        break;

      case WINNEXT:
      sprintf(buffer, "TOTAL TIME TAKEN: %d", timer/60);
      drawString(120, 100, buffer, WHITE);
      if(KEY_DOWN(BUTTON_SELECT, currentButtons)){
        state=START;
      }



        // state = ?
        break;
      case LOSE:
      drawFullScreenImageDMA(loseimage);
    
      state= LOSECONDITION;
      break;
      case LOSECONDITION:
      if(KEY_DOWN(BUTTON_SELECT, currentButtons)){
        state=START;
      }
        // state = ?

        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

 UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}


int collision(Dart d) {
  int isPopped=0;
  if( d.row > 90 && d.row<160 && d.col>160 && d.col<250) {
    isPopped=1;
  }
return isPopped;

}

void move(Dart *d, int directionLR, int directionUD){
  int r=(*d).row;
  int c=(*d).col;
  drawRectDMA(r,c, 20, 20, BLACK);
  if( (d->row)+directionLR <0){
    d->row=0;
  }
 else{
   d->row += directionLR;
 }
 if((d->col)+directionUD < 0){
     d->col=0;
 }
 else{
   d->col += directionUD;
 }
 if((d->col)+directionUD > (WIDTH-20) ) {
     d->col=(WIDTH -20);
 }
 else{
   d->col += directionUD;
 }
  if((d->row)+directionLR > (HEIGHT-20) ){
       d->row=(HEIGHT -20);
  }
  else{
    d->row += directionLR;
  }



  drawImageDMA((*d).row, (*d).col, 20, 20, dartpic);

}