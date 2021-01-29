
/*
This program is a simple guessing number text game for the NES. 
*/

#include "neslib.h"
#include "stdio.h"

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// main function, run after console reset
int max = 1000;
int min = 1;
int guess = 500; 
char str[12]; 
//Function to handle guesses
void myGuess()
{
  char str[12];
  // Turn off PPU to erase and rewrite text
  ppu_off();
  vram_adr(NAMETABLE_A);
  vram_fill(0,1024);
  
  sprintf(str, "%d", guess);
  // MY GUESS IS:
  vram_adr(NTADR_A(2,2));
  vram_write("MY GUESS IS ",11);
  // print out current guess
  vram_adr(NTADR_A(5,5));
  vram_write(str,5);
  
  //Prompt User
  vram_adr(NTADR_A(2,10));
  vram_write("PRESS A IF NUMBER IS HIGHER!",28);
  
  vram_adr(NTADR_A(2,15));
  vram_write("PRESS START IF CORRECT GUESS!",29);
  
  vram_adr(NTADR_A(2,20));
  vram_write("PRESS B IF NUMBER IS LOWER!",27);
  
  //Turn screen back on
  ppu_on_all();
  
}

//function to determine what current guess should be
void getGuess(){
  guess = (max + min) /2;
  
}

//function to declare computer the winner. 
void winner()
{
  ppu_off();
  vram_adr(NAMETABLE_A);
  vram_fill(0,1024);
  // I AM THE GREATEST
  vram_adr(NTADR_A(5,10));
  vram_write("HAHA I AM THE GREATEST!", 22);
  
  vram_adr(NTADR_A(12,15));
  vram_write("I WIN!", 6);
  
  //vram_adr(NTADR_A(4,20));
  //vram_write("PRESS START TO PLAY AGAIN!", 26);
  ppu_on_all(); 
}


//function to enter into the gamestate, where our game loop occurs. 
void GameState(void)
{
  //Set Variables
  
  char pad1;
  int bool = 1;
  guess = 500; 

  
  myGuess(); 
  while(bool)
  {
  pad1 = pad_trigger(0);
    if (pad1 & PAD_A) 
    {
      min = guess;
      getGuess(); 
      myGuess();
    }
    else if (pad1 & PAD_B) 
    {
      max = guess;
      guess = (max + min) /2; 
      myGuess();
    }
    else if (pad1 & PAD_START) 
    {
      bool = 0;
      winner(); 
    }
  }
}




void main(void) 
{
  int bool1 = 1;
  char pad1; 
  
  
  
 
  // set palette colors
  pal_col(0,0x02);	// set screen to dark blue
  pal_col(1,0x14);	// fuchsia
  pal_col(2,0x20);	// grey
  pal_col(3,0x30);	// white

  // write text to name table
  
  
  vram_adr(NTADR_A(2,6));
  vram_write("I WILL GUESS YOUR NUMBER!",25);// write bytes to video RAM
  
  vram_adr(NTADR_A(2,20));
  vram_write("PRESS START TO BEGIN!",21);// write bytes to video RAM

  // enable PPU rendering (turn on screen)
  ppu_on_all();

  // Loop until user hits Start, then enters game state. 
 
  while (bool1) {
    pad1 = pad_trigger(0);
    if (pad1 & PAD_START) 
    {
      
      GameState();
      bool1 = 0; 
    }
  }
  
}

