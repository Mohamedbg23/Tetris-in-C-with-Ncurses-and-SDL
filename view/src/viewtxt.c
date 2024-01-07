//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include <stdio.h>
#include <stdlib.h>

#include "viewtxt.h"
#include "viewer.h"
#include <time.h>



#define H 22
#define W 42

WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *local_win;
  local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);
  wrefresh(local_win);
  return local_win;
}

/**
 * @brief textViewer::initTextViewer implementation.
 */
viewer *initTextViewer() {
  viewer *ret = (viewer *)malloc(sizeof(viewer));
  if (!ret) {
    perror("initTextViewer viewer");
    return NULL;
  }

  dataTextViewer *data = (dataTextViewer *)malloc(sizeof(dataTextViewer));
  if (!data) {
    perror("initTextViewer data");
    free(ret);
    return NULL;
  }
  ret->data = data;

  // prepare ncurses stuff.
  initscr();

  // init the color mode.
  if (has_colors() == FALSE) {
    endwin();
    fprintf(stderr, "Life is SAD without color :'(\n");
    exit(EXIT_FAILURE);
  }

  start_color();
  init_pair(9, COLOR_CYAN, COLOR_WHITE);
  
  //CYAN
  init_pair(1,COLOR_CYAN,COLOR_CYAN);

  //BLUE
  init_pair(2,COLOR_BLUE,COLOR_BLUE);

  //orange
  init_color(31, 1000, 500, 0);
  init_pair(3, 31, 31);

  //RED
  init_pair(4,COLOR_RED,COLOR_RED);

  //GREEN
  init_pair(5,COLOR_BLUE,COLOR_BLUE);

  //YELLOW
  init_pair(6,COLOR_YELLOW,COLOR_YELLOW);

  //PINK 
  init_color(71, 1000, 500, 800); 
  init_pair(7,71,71);

  //BLACK for 8 ombre
  init_pair(8,COLOR_BLACK,COLOR_BLACK);


  cbreak();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);

  data->height = H;
  data->width = W;
  data->starty = 7;
  data->startx = 30;
  curs_set(0);
  refresh();
  data->win =
      create_newwin(data->height, data->width, data->starty, data->startx);

  ret->destroy = destroyTextViewer;
  

  return ret;
}  // initTextViewer


/**
 * @brief textViewer::stop implementation.
 *
 */
void stopTextPlayer(viewer *v) { endwin(); }  // stop

/**
 * @brief textViewer::display implementation.
 */
void display(dataTextViewer *data,grille *g) {
  // Clear the window before updating
  werase(data->win);
 

  // Iterate through the Tetris board and display each cell
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      // Calculate the screen coordinates for each cell in the board
      int row = i  + 1  ;  // Add 1 to avoid overwriting the border of the window
      int col =  j * 4  ;  // Adjust the column position based on your layout

      // Print the value of the board cell at position (i, j)
     int cellValue = g->tab[i * LARGEUR + j];

    switch(cellValue){

      case 1:
        wattron(data->win, COLOR_PAIR(1));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(1));
        break;
      
      case 2:
        wattron(data->win, COLOR_PAIR(2));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(2));
        break;
      case 3:
        wattron(data->win, COLOR_PAIR(3));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(3));
        break;
      case 4:
        wattron(data->win, COLOR_PAIR(4));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(4));
        break;
      case 5:
        wattron(data->win, COLOR_PAIR(5));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(5));
        break;
      case 6:
        wattron(data->win, COLOR_PAIR(6));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(6));
        break;
      
      case 7:
        wattron(data->win, COLOR_PAIR(7));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(7));
        break;

      case 8:
        wattron(data->win, COLOR_PAIR(8));
        mvwprintw(data->win, row, col, "%4s", "");
        wattroff(data->win, COLOR_PAIR(8));
        break;
    }
      
    }
  }


  // Refresh the window to reflect the changes
  mvprintw(2, 40, " SCORE ");
    mvprintw(3, 40, "+-----+");
    attron(COLOR_PAIR(9));
    mvprintw(4, 40, "|%5d|", g->score);
    attroff( COLOR_PAIR(9));
    mvprintw(5, 40, "+-----+");

    mvprintw(2, 55, " LEVEL ");
    mvprintw(3, 55, "+-----+");
    mvprintw(4, 55, "|%5d|", (g->niveau / 10) + 1);
    mvprintw(5, 55, "+-----+");

    // print the reserved piece 
    for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
        // Calculate the screen coordinates for each cell in the matrix
        int row = i + 9;    // Starting from row 9
        int col = j * 4 + 12;  // Starting from column 15

        // print the reserved piece based on the reserve
        switch(g->reserve){
          case 1:
            if(i==0&&j==0){attron(COLOR_PAIR(1));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(1));}
            else if(i==0&&j==1){attron(COLOR_PAIR(1));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(1));}
            else if(i==0&&j==2){attron(COLOR_PAIR(1));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(1));}
            else if(i==0&&j==3){attron(COLOR_PAIR(1));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(1));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

            case 2:
            if(i==0&&j==0){attron(COLOR_PAIR(2));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(2));}
            else if(i==1&&j==0){attron(COLOR_PAIR(2));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(2));}
            else if(i==1&&j==1){attron(COLOR_PAIR(2));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(2));}
            else if(i==1&&j==2){attron(COLOR_PAIR(2));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(2));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

            case 3:
            if(i==0&&j==2){
              attron(COLOR_PAIR(3));
              mvprintw(row, col, "%4d", 0);
              attroff(COLOR_PAIR(3));
            }
            else if(i==1&&j==2){attron(COLOR_PAIR(3));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(3));}
            else if(i==1&&j==1){attron(COLOR_PAIR(3));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(3));}
            else if(i==1&&j==0){attron(COLOR_PAIR(3));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(3));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            
            break;

            case 4:
            if(i==0&&j==0){attron(COLOR_PAIR(4));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(4));}
            else if(i==0&&j==1){attron(COLOR_PAIR(4));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(4));}
            else if(i==1&&j==1){attron(COLOR_PAIR(4));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(4));}
            else if(i==1&&j==2){attron(COLOR_PAIR(4));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(4));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

            case 5:
            if(i==0&&j==1){attron(COLOR_PAIR(5));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(5));}
            else if(i==0&&j==2){attron(COLOR_PAIR(5));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(5));}
            else if(i==1&&j==0){attron(COLOR_PAIR(5));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(5));}
            else if(i==1&&j==1){attron(COLOR_PAIR(5));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(5));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

            case 6:
            if(i==0&&j==1){attron(COLOR_PAIR(6));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(6));}
            else if(i==0&&j==2){attron(COLOR_PAIR(6));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(6));}
            else if(i==1&&j==1){attron(COLOR_PAIR(6));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(6));}
            else if(i==1&&j==2){attron(COLOR_PAIR(6));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(6));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

          case 7:
            if(i==0&&j==1){attron(COLOR_PAIR(7));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(7));}
            else if(i==1&&j==0){attron(COLOR_PAIR(7));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(7));}
            else if(i==1&&j==1){attron(COLOR_PAIR(7));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(7));}
            else if(i==1&&j==2){attron(COLOR_PAIR(7));mvprintw(row, col, "%4d", 0);attroff(COLOR_PAIR(7));}
            else{attron(COLOR_PAIR(8));mvprintw(row, col,"%4d", 1);attroff(COLOR_PAIR(8));}
            break;

        }
        
    }
}
  mvprintw(7, 15, "%s","RESERVE");
  mvprintw(15, 15, "%s","ENJOY");
  box(data->win, 0, 0);
  wbkgd(data->win, COLOR_PAIR(9));
  wrefresh(data->win);
}  // display

/**
 * @brief textViewer::destroyTextViewer implementation.
 */
void destroyTextViewer(viewer *v) {
  delwin(((dataTextViewer *)v->data)->win);
  free(v->data);
  free(v);
}  // destroyTextViewer