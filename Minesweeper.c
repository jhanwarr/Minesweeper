#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//libraries needed by the program

//function to find the number of mines near the given grid

int convert (int n, int m, int r, int c, int arr[n][m])
{
  //-1 = bomb; 0 = blank; +ve = no. of mines around it...arr[][]
  // 1 = open; 0 = closed...open[][]
  
  int start_row, end_row, start_col, end_col;
  int mines_count = 0;
  
  //initialization for rows
  
  if (r == 0)
    {
      start_row = 0;
      end_row = 1;
    }
  
  else if ( r == (n - 1) )
    {
    
      start_row = r - 1;
      end_row = r;
    }
  
  else
    {
      start_row = r - 1;
      end_row = r + 1;
    }
  
  //initialization for coloumns
  
  if (c == 0)
    {
      start_col = 0;
      end_col = 1;
    }
  
  else if ( c == (m - 1) )
    {
      start_col = c - 1;
      end_col = c;
    }
  
  else
    {
      start_col = c - 1;
      end_col = c + 1;
    }
  
  //extracting the grids around the given grid and seing the mines around it
  
  for (int i = start_row; i <= end_row; i++)
    {
      for (int j = start_col; j <= end_col; j++)
        {
          if (arr[i][j] == -1)
            {
              mines_count++;
            }
        }
    }
  
  return mines_count;
}

//function to print the mine at the end
void display_end (int n, int m, int r, int c, int arr[n][m], int open[n][m])
{
  
  printf("      ");
  
  //printing the coloumns guide
  
  for (int j = 0; j < m; j++)
    {
      printf (" %2dC", j + 1);
    }
  
  printf ("\n\n");
  
  //printing the mine
  
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        {
          //printing the Rows guide
          
          if (j == 0)
            {
              printf ("   %2dL", i + 1);
            }
          
          if (arr[i][j] == -1)
            {
              if( (i == r) && (j == c))
                printf ("   #");
                //if user explodes the mine
              
              else
                printf ("   M");
                
            }
          
          else if (open[i][j])
            {
              printf (" %3d", arr[i][j]);
            }
          
          else
            {
              arr[i][j] = convert (n, m, i, j, arr);
              printf (" %3d", arr[i][j]);
            }
        }
      
      printf ("\n\n");
    }
}

//function to print the mine after each turn

void display (int n, int m, int arr[n][m], int open[n][m])
{
  
  printf ("      ");
  
  //printing the coloumns guide

  for (int j = 0; j < m; j++)
    {
      printf (" %2dC", j + 1);
    }
  
  printf ("\n\n");
  
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
        {
          //printing the coloumns guide
            
          if (j == 0)
            {
              printf ("   %2dR", i + 1);
            }
          
          if (open[i][j] == 0)
            {
              printf ("   *");
              //if unopened, prints asterisk
            }
          
          else
            {
              printf (" %3d", arr[i][j]);
            }
        }
      
      printf ("\n\n");
    }
}

int main(void)
{
  srand (time (NULL));
  //for generating random numbers
  
  printf ("\n\nWelcome to Minesweeper!\n");
  printf ("                        ~ Â© by Raj Vardhann Jhanwar!\n\n");
  //just for fun :-)
  
  int n, m, z;
  //variables needed to declare the function
  
  printf ("Please enter the number of rows : ");
  scanf ("%d", &n);
  //the number of rows
  
  //validation
  while (n <= 0)
    {
      printf ("The rows must be greater than 0. Please enter the rows again : ");
      scanf ("%d", &n);
    }
    
  printf ("Enter the number of coloumns : ");
  scanf ("%d", &m);
  //the number of coloumnns
  
  //validation
  while (m <= 0)
    {
      printf ("The number of coloumns must be greater than 0. Please enter the number of coloumns again : ");
      scanf ("%d", &m);
    }
  
  printf ("Enter the number of mines to be placed randomly, which should be less than %d : ", (n * m));
  scanf ("%d", &z);
  //the number of mines
  
  //validation
  while ((z >= (n * m)) && (z < 0))
    {
        printf ("Invalid Entry of the number of mines. Please enter the value again : ");
        scanf ("%d", &z);
    }
  
  int arr[n][m];
  int open[n][m];

  int mine_index_unprocessed[z];
  
  //TAKING AN ARRAY FOR MINES AND THEN FILLING IT WITH RANDOM ASSIGNMENTS    

  while (1)
    {
      int conseq = 0;
      //filling the array made for mines index
      
      for (int i = 0; i < z; i++)
        {
          int random_num = (rand () % (n * m)) + m;
          int check = 0;
          
          //checking for repitition
          
          for (int j = 0; j < i; j++)
            {
              if (mine_index_unprocessed[j] == random_num)
                {
                  i--;
                  check = 1;
                  break;
                }
            } 
          
          if (check)
            continue;
          
          mine_index_unprocessed[i] = random_num; 
          //when processing this array into 2D, the '+ 5' is needed for first iteration
        }
      
      int count = 0;
      
      // checking for 9 mines placed in a 3*3 grid in the main array, since it is not allowed 
      
      for (int i = 1; i < (n - 1); i++)
        {
              for (int j = 1; j < (m - 1); j++)
            {
              if (arr[i][j] == -1)
                {
                  count++;
                }
            }
        }

      if (count == 9)
        conseq = 1;
        
      //checking for a 4*4 grid mine in the corners, which is not allowed
      
      if ((m > 2) && (n > 2))
        {
          if ( (arr[0][0] == -1)  && (arr[0][1] == -1) && (arr[1][0] == -1) && (arr[1][1] == -1))
            conseq = 1;
            
          if ( (arr[0][m-1] == -1) && (arr[0][m-2] == -1) && (arr[1][m-1] == -1) && (arr[1][m-2] == -1) )
            conseq = 1;
            
          if ( (arr[n-1][0] == -1) && (arr[n-2][0] == -1) && (arr[n-1][1] == -1) && (arr[n-2][1] == -1) )
            conseq = 1;
            
          if ( (arr[n-2][m-2] == -1) && (arr[n-2][m-1] == -1) && (arr[n-1][m-1] == -1) && (arr[n-1][m-2] == -1) )
            conseq = 1;
        }
        
        if (conseq == 0)
          break;
    }
  
  //PROCESSING THE 1D ARRAY INTO 2D
  int k = 0;
  
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < z; j++)
        {
          mine_index_unprocessed[j] -= m;
        }
      
      for (int j = 0; j < m; j++)
        {
          open[i][j] = 0;
          arr[i][j] = 0;
	  
          for (int k = 0; k < z; k++)
            {
              if (mine_index_unprocessed[k] == j)
                {
                  arr[i][j] = -1;
                  break;
                }
            }
        }   
    }
  
  
  display (n, m, arr, open);
  //calling thr method display to show the minesweeper
  
  int r, c;
  
  for (int a = 0; a < (m*n); a++)
    {
      printf ("\nCurrent situation : there are %d positions and %d mines left\n", ((m * n) - z) - a, z);
      
      //Won
      if ( ( ( (m * n) - z) - a) == 0 )
        {
          printf ("\nHurrah! You have won this game.\n");
          display_end (n, m, r, c, arr, open);

          printf ("I hope you had fun and that you play the game again.\n");
          printf ("Thank You!\n\n");
          
          break;    
        }
      
      //Input
      printf ("What row and column would you guess?\n");
      printf ("Enter the row between 1 and %d : ", n);
      scanf ("%d", &r);
      
      //validation
      
      while ( (r > n) || (r < 1) )
      {
        printf ("Invalid input...please enter again\n\n");
          
        printf ("Enter the row between 1 and %d : ", n);
        scanf ("%d", &r);  
      }
      
      printf ("Enter the coloumn between 1 and %d : ", m);
      scanf ("%d", &c);

      //validation
      
      while ( (c > m) || (c < 1) )
        {
          printf ("Invalid input...please enter again\n\n");
          
          printf ("Enter the coloumn between 1 and %d : ", m);
          scanf ("%d", &c);
        }
      
      r--;
      c--;
      //removing 1 from the row and coloumn to figure out the index in the grid
      
      //checking if the index was already opened by the user or is it unopened
      if (open[r][c] == 0)
        {
          open[r][c] = 1;
        }
      
      else
        {
          a--;
          display (n, m, arr, open);
          printf ("\nThe grid has already been filled. Please enter another grid.\n");
          continue;
        }
      
      //Lost
      if (arr[r][c] == -1)
        {
          printf("\n\n\nOops! A mine exploded at your location ### !\n\n\n");

          display_end (n, m, r, c, arr, open);
          
          printf("I would love to see you try again and win...Hope you had fun\n\n");
          
          break;
        }
      
      arr[r][c] = convert (n, m, r, c, arr);
      //finding the number of mines around the given grid at (r,c)
      
      
      if (arr[r][c] == 0)
        {
          int zero[n * m * 2];
          //array to contain the indexes of grids with 0 mines around it
          
          zero[0] = r;
          zero[1] = c;
          
          int check = 2;
          //check = (the number of indexes found with 0) * 2, for row and coloumns are considered 2 elements in zero[][]
          
          while ( check != 0)
            {
              check--;
              int c1 = zero[check];
              //extracting the coloumn 
              
              check--;
              int r1 = zero[check];
              //extracting the row
              
              int start_row, end_row, start_col, end_col;
              //variables required
              
              //initialization of start_row and end_row
              
              if (r1 == 0)
                {
                  start_row = 0;
                  end_row = 1;
                }
              
              else if ( r1 == (n - 1) )
                {
                  start_row = r1 - 1;
                  end_row = r1;
                }
              
              else
                {
                  start_row = r1 - 1;
                  end_row = r1 + 1;
                }
              
              //initialization of start_col and end_col
              
              if (c1 == 0)
                {
                  start_col = 0;
                  end_col = 1;
                }
              
              else if ( c1 == (m - 1) )
                {
                  start_col = c1 - 1;
                  end_col = c1;
                }
              
              else
                {
                    start_col = c1 - 1;
                    end_col = c1 + 1;
                }
              
              //running a loop around all the grids of (r,c)
              
              for (int i = start_row; i <= end_row; i++)
                {
                  for (int j = start_col; j <= end_col; j++)
                    {
                      //opening the grid at (i,j) if it's unopened
                      
                      if (open[i][j] == 0)
                        {
                          a++;
                          open[i][j] = 1;
                          arr[i][j] = convert (n, m, i, j, arr);
                          
                          //adding the indexes of any grid around (r,c) if it's value is 0
                          if (arr[i][j] == 0)
                            {
                              zero[check] = i;
                              check++;
                              
                              zero[check] = j;
                              check++;
                            }
                        }  
                    }
                }
            }
        }
      
      display (n, m, arr, open);
      //displaying the mine at the end of the move
    }
    
  return 0;
  //returning 0 and exiting the code
}
