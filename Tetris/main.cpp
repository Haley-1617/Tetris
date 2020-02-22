//
//  main.cpp
//  Tetris
//
//  Created by Haley Lai on 2/17/20.
//  Copyright © 2020 Haley Lai. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

static const int SCREEN_WIDTH = 300;
static const int SCREEN_HEIGHT = 640;
static const int GAME_WIDTH = 200;
SDL_Renderer *renderer;

class Game {
private:
   SDL_Window *window;
//   SDL_Renderer *renderer;
public:
   Game();
   ~Game();
   bool init();
   void error(const string &message, const string &type);
   void movement(SDL_Event &e);
   SDL_Renderer* getRenderer() { return renderer; }
};

Game::Game() {
   init();
}

Game::~Game() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   window = NULL;
   renderer = NULL;

   IMG_Quit();
   SDL_Quit();
}

bool Game::init() {
   bool success = true;

   if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      error("SDL couldn't initialize!", "SDL");
      success = false;
   }
   else {
      window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if (!window) {
         error("Window couldn't be created!", "SDL");
         success = false;
      }
      else {
         renderer = SDL_CreateRenderer(window, -1,
                                       SDL_RENDERER_ACCELERATED |
                                       SDL_RENDERER_PRESENTVSYNC);
         if (!renderer) {
            error("Renderer couldn't be created!", "SDL");
            success = false;
         }
         else {
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
         }
      }
   }
   return success;
}

void Game::error(const string &message, const string &type) {
   cout << message << endl;
   if (type == "SDL")
      cout << SDL_GetError() << endl;
   else if (type == "IMG")
      cout << IMG_GetError() << endl;
}

class Block {
private:
//   TO DO: fix magic number
   const int blocks[7][4][5][5] = {
//      O
      {
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      I
      {
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      J
      {
         {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      L
      {
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      S
      {
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      T
      {
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         }
      },
//      Z
      {
         {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
         },
         {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
         }
      }
   };
   const int initPos[7][4][2] = {
   //      O
         {
            {-2, -3},
            {-2, -3},
            {-2, -3},
            {-2, -3}
         },
   //      I
         {
            {-2, -2},
            {-2, -3},
            {-2, -2},
            {-2, -3}
         },
   //      J
         {
            {-2, -2},
            {-2, -3},
            {-2, -3},
            {-2, -3}
         },
   //      L
         {
            {-2, -2},
            {-2, -3},
            {-2, -3},
            {-2, -3}
         },
   //      S
         {
            {-2, -3},
            {-2, -3},
            {-2, -3},
            {-2, -2}
         },
   //      T
         {
            {-2, -2},
            {-2, -3},
            {-2, -3},
            {-2, -3}
         },
   //      Z
         {
            {-2, -2},
            {-2, -3},
            {-2, -3},
            {-2, -3}
         }
      };

public:
//   block = this->blocks[type][rotate]; (isn't working somehow)
   void getBlocks(int &type, int &rotate, int (&block)[5][5])
   {memcpy(block, this->blocks[type][rotate], sizeof(block));}
   void getInitPos(int &type, int &rotate, int (&pos)[2])
   {memcpy(pos, this->initPos[type][rotate], sizeof(pos));}
};

class Board : public Block {
private:
   int curBlock[5][5], nextBlock[5][5];
   int initialPos[2], curPosY, curPosX;
   int board [SCREEN_HEIGHT][GAME_WIDTH];
public:
   Board();
   bool collision(int &posX, int &posY);
   void moveLR(char &LR);
   void init();
   void newBlock();
   void drawBoard(bool &drop);
   void drawBlocks(int (&block)[5][5], int &posX, int posY);
   void updateBoard(int &posX, int posY);
   void renderBlock(int (&block)[5][5], int &posX, int posY);
   void background();
   void render();
   void setPosY() {curPosY+=20;}
   void setPosX(char &LR);
};

Board::Board() {
   for (int y = 0; y < SCREEN_HEIGHT; y++)
      for (int x = 0; x < GAME_WIDTH; x++)
         board[y][x] = 0;
}

bool Board::collision(int &posX, int &posY) {
   for (int y0 = 0, y1 = posY; y0 < 5; y0++, y1+=20) {
      for (int x0 = 0, x1 = posX; x0 < 5; x0++, x1+=20) {
         if (curBlock[y0][x0] != 0 && board[y1][x1] != 0) {
            return true;
         }
         else if (curBlock[y0][x0] != 0 && y1 == SCREEN_HEIGHT)
            return true;
      }
   }
   return false;
}

void Board::moveLR(char &LR) {
   for (int y0 = 0, y1 = curPosY; y0 < 5; y0++, y1+=20) {
      for (int x0 = 0, x1 = curPosX; x0 < 5; x0++, x1+=20) {
         if (curBlock[y0][x0] != 0 && x1 < 0) curPosX+=20;
         else if (LR == 'L' && curBlock[y0][x0] != 0 && board[y1][x1] != 0) curPosX+=20;
         else if (curBlock[y0][x0] != 0 && x1 >= GAME_WIDTH) curPosX-=20;
         else if (LR == 'R' && curBlock[y0][x0] != 0 && board[y1][x1] != 0) curPosX-=20;
      }
   }
}

void Board::init() {
   background();
//   TO DO: draw initial block and next block on the screen
   int randBlock, randType;
   randBlock = rand() % 7;
   randType = rand() % 4;
   getBlocks(randBlock, randType, curBlock);
   getInitPos(randBlock, randType, initialPos);
   curPosX = (GAME_WIDTH / 2) + initialPos[0] * 20;
   renderBlock(curBlock, curPosX, initialPos[1] * 20);
   curPosY = 0;

   randBlock = rand() % 7;
   randType = rand() % 4;
   getBlocks(randBlock, randType, nextBlock);
   getInitPos(randBlock, randType, initialPos);
}

void Board::newBlock() {
   memcpy(curBlock, nextBlock, sizeof(curBlock));
   curPosX = (GAME_WIDTH / 2) + initialPos[0] * 20;
   renderBlock(curBlock, curPosX, initialPos[1] * 20);
   curPosY = 0;
   int randBlock, randType;
   randBlock = rand() % 7;
   randType = rand() % 4;
   getBlocks(randBlock, randType, nextBlock);
   getInitPos(randBlock, randType, initialPos);
}

void Board::drawBoard(bool &drop) {
//   TO DO: fix magic number 20(sizePerUnit), 1(regularBlock), and 2(pivot)
   background();
   if (drop) curPosY+=20;
   if (collision(curPosX, curPosY)) {
      updateBoard(curPosX, curPosY - 20);
      newBlock();
   }
   else renderBlock(curBlock, curPosX, curPosY);
}

void Board::drawBlocks(int (&block)[5][5], int &posX, int posY) {
   for (int y0 = 0, y1 = posY; y0 < 5; y0++, y1+=20) {
         for (int x0 = 0, x1 = posX; x0 < 5; x0++, x1+=20) {
            if (block[y0][x0] == 1) {
               board[y1][x1] = 1;
            }
            else if (block[y0][x0] == 2) {
               board[y1][x1] = 2;
            }
         }
   }
}

void Board::updateBoard(int &posX, int posY) {
   for (int y0 = 0, y1 = posY; y0 < 5; y0++, y1+=20)
      for (int x0 = 0, x1 = posX; x0 < 5; x0++, x1+=20)
         if (curBlock[y0][x0] != 0)
            board[y1][x1] = curBlock[y0][x0];
}

void Board::renderBlock(int (&block)[5][5], int &posX, int posY) {
   for (int y0 = 0, y1 = posY; y0 < 5; y0++, y1+=20) {
      for (int x0 = 0, x1 = posX; x0 < 5; x0++, x1+=20) {
         if (block[y0][x0] == 1) {
            SDL_Rect fillRect = {x1, y1, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
         else if (block[y0][x0] == 2) {
            SDL_Rect fillRect = {x1, y1, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
      }
   }
}

void Board::background() {
   for (int i = 0; i <= GAME_WIDTH; i+=20) {
      SDL_SetRenderDrawColor(renderer, 0xc1, 0xc5, 0xc9, 0xFF);
      SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
   }
   for (int i = 0; i < SCREEN_HEIGHT; i+=20) {
      SDL_SetRenderDrawColor(renderer, 0xc1, 0xc5, 0xc9, 0xFF);
      SDL_RenderDrawLine(renderer, 0, i, GAME_WIDTH, i);
   }
}

void Board::render() {
   for (int y = 0; y < SCREEN_HEIGHT; y+=20)
      for (int x = 0; x < GAME_WIDTH; x+=20) {
         if (board[y][x] == 1) {
            SDL_Rect fillRect = {x, y, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
         else if (board[y][x] == 2) {
            SDL_Rect fillRect = {x, y, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
      }
}

void Board::setPosX(char &LR) {
   if (LR == 'L') curPosX -= 20;
   else if (LR == 'R') curPosX += 20;
   moveLR(LR);
}

SDL_Renderer* draw(int (&block)[5][5], int posX, int posY, SDL_Renderer *renderer) {
   posY = posY % 10000;
   posY = posY / 1000 * 20;
   if (posY + 100 > SCREEN_HEIGHT) posY = SCREEN_HEIGHT - 100;
   for (int y0 = 0, y1 = posY; y0 < 5; y0++, y1+=20) {
      for (int x0 = 0, x1 = posX; x0 < 5; x0++, x1+=20) {
         if (block[y0][x0] == 1) {
            SDL_Rect fillRect = {x1, y1, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
         else if (block[y0][x0] == 2) {
            SDL_Rect fillRect = {x1, y1, 20, 20};
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &fillRect);
         }
      }
   }
   return renderer;
}

int main(int argc, const char * argv[]) {
   srand(time(NULL));
   cout << "True: " << true << endl;
   int z[2][5][5] = {
      {
         {0,0,0,0,0},
         {0,0,0,0,0},
         {0,1,1,0,0},
         {0,0,2,1,0},
         {0,0,0,0,0}

      },
      {
         {0,0,0,0,0},
         {0,0,0,0,0},
         {0,0,0,1,0},
         {0,0,2,1,0},
         {0,0,1,0,0}}};
   Game game;
   char LR = ' ';
   bool quit = false;
   SDL_Event e;
   int x = 0;
   int rotate = 1;
   Uint32 cur = SDL_GetTicks(), old = 0;
   Board board;
   Block sample;
   bool drop = false;
   int test[5][5] = {0};
   sample.getBlocks(x, rotate, test);
   for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++)
         cout << test[i][j] << ", ";
      cout << endl;
   }
//   SDL_Renderer *block = draw(z, game.SCREEN_WIDTH / 2, game.SCREEN_HEIGHT / 2, renderer);
   board.init();
   while (!quit) {
      drop = false;
      while (SDL_PollEvent(&e)) {
         if (e.type == SDL_QUIT)
            quit = true;
         else if (e.type == SDL_KEYDOWN)
            switch (e.key.keysym.sym) {
               case SDLK_LEFT:
                  LR = 'L';
                  board.setPosX(LR);
                  break;
               case SDLK_RIGHT:
                  LR = 'R';
                  board.setPosX(LR);
                  break;
               case SDLK_UP:
                  if (rotate == 1) rotate--;
                  else rotate++;
                  break;
               case SDLK_DOWN:
                  board.setPosY();
                  break;
            }
      }
      cur = SDL_GetTicks();
      if (cur - old >= 200) {
         old = cur;
         drop = true;
      }
      board.drawBoard(drop);
      board.render();
//      draw(z[rotate], x, (int)cur, renderer);


      SDL_RenderPresent(renderer);
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(renderer);
   }

   return 0;
}
