/* Author: Danielle Carter
 * ID: 800850014
 * Date: September 7, 2015
 * Course: ITCS 3146-001
 * Professor: Cukic
 */

#include<stdio.h>


int main() {
    char field[200][200] = {'1'};
    FILE *fptr;
    char c;
    char file_name[20];
    int i, j, m, n;
    
    //Get dimensions of maze 
    printf("Enter the dimensions of the array. \n");
    printf("Rows: ");
    scanf("%d", &m);  //Enter rows
    printf("Columns: ");
    scanf("%d", &n);  //Enter columns
    
    //Read maze from text file into 2D array named field
    printf("Type in the name of the file containing the field:\n");
    scanf("%s",file_name);
    fptr = fopen(file_name,"r");
    for (i=0; i < m; i++)
     for (j=0; j < n; j++){
       c = fgetc(fptr); 
       while ( !((c == '1')||(c == '0')) ) c = fgetc(fptr);
       field[i][j] = c;
    }
    fclose(fptr);
    
  int count = 0;                    //counts number of zeroes found
  int row, col;                     //Track row and column indices
  int entRow, entCol, exRow, exCol; //store entrance and exit idices

  //Starts tracing border at [0][0] and goes down first column
  for(row = 0; row < m; row++) {
	  if(field[row][0] == '0') {
		  count++;
		  if(count == 1){  //If this is the first zero, store as entrance
			  entRow = row;
			  entCol = 0;
		  }else if (count == 2) {  //If this is the second zero, store as exit
			  exRow = row;
			  exCol = 0;
			  break; //Once exit is found, stop looping
		  }
	  }
  }

  //As long as entrance and exit are not both found, continue checking border
  if (count != 2) {
	  for(col = 0; col < n; col++) {
		  if(field[m-1][col] == '0') {
			  count++;
			  if(count == 1){
				  entRow = m-1;
				  entCol = col;
			  }else if (count == 2) {
				  exRow = m-1;
				  exCol = col;
				  break;
			  }
		  }
	  }
  }

  if (count != 2) {
	  for(row = m-1; row >= 0; row--) {
		  if(field[row][n-1] == '0') {
			  count++;
			  if(count == 1){
				  entRow = row;
				  entCol = n-1;
			  }else if (count == 2) {
				  exRow = row;
				  exCol = n-1;
				  break;
			  }
		  }
	  }
  }

  if (count != 2) {
 	  for(col = n-1; col >= 0; col--) {
		  if(field[0][col] == '0') {
			  count++;
			  if(count == 1){
				  entRow = 0;
				  entCol = col;
			  }else if (count == 2) {
				  exRow = 0;
				  exCol = col;
				  break;
			  }
		  }
	  }
  }
  
   char surr[4] = {'1'};  //array to hold surrounding points
   row = entRow;          //initialize starting row to entrance row coordinate
   col = entCol;          //initialize starting column to entrance column coordinate
   int dir;               //holds direction number (0, 1, 2, or 3)
   int entrance = 0;      //for while condition
   int end = 0;           //for while condition
   
   //Determines what dir will be initialized to
   if(entCol == 0){              //If entrance is on left wall
       dir = 3;                  //Begin facing right
   }else if(entRow == (m - 1)){  //If entrance is on bottom wall
       dir = 0;                  //Begin facing up
   }else if(entCol == (n - 1)){  //If entrance is on right wall
       dir = 1;                  //Begin facing left
   }else{                        //Entrance is on top wall
       dir = 2;                  //Begin facing down
   }
   
   //Begin mapping path
   do{
       //Assign surrounding map coordinates to surr array
        if(!((row - 1) < 0)){                          //Make sure it exists first
           surr[(4 - dir) % 4] = field[row - 1][col];  //Store the point above
        }else{
           surr[(4 - dir) % 4] = '1';                  //Otherwise, assign to '1' 
        }
        
        if(!((col - 1) < 0)){
           surr[(5 - dir) % 4] = field[row][col - 1];   //Store the point to the left
        }else{
           surr[(5 - dir) % 4] = '1';
        }
        
        if(!((row + 1) > (m - 1))){
           surr[(6 - dir) % 4] = field[row + 1][col];   //Store the point below
        }else{
           surr[(6 - dir) % 4] = '1';
        }
        
        if(!((col + 1) > (n - 1))){
           surr[(3 - dir) % 4] = field[row][col + 1];   //Store the point to the right
        }else{
           surr[(3 - dir) % 4] = '1';
        }
     
       //Change current 'position'0' to 'X'
       field[row][col] = 'X';
       
       //Determine WHERE to move based on contents of surr array, or the surrounding points
       if(surr[0] != '1' && surr[3] == '1'){ //go forward one space
           switch (dir) { //Determine HOW to move based on dir
           case 0:
              if(!((row - 1) < 0)){
                row--;
                dir = 0;
              }
              break;
            case 1:
               if(!((col - 1) < 0)){
                  col--;
                  dir = 1;
               }
               break;
            case 2:
              if(!((row + 1) > (m - 1))){
                 row++;
                 dir = 2;
               }
               break;
            case 3:
               if(!((col + 1) > (n - 1))){
                  col++;
                  dir = 3;
               }
               break;
         default:
            printf("Error!");
         }
       }else if(surr[3] != '1'){ //go right one space
           switch (dir) {
            case 0:
                if(!((col + 1) > (n - 1))){
                   col++;
                  dir = 3;
                }
                break;
            case 1:
                if(!((row - 1) < 0)){
                   row--;
                   dir = 0;
                }
                break;
            case 2:
                if(!((col - 1) < 0)){
                   col--;
                   dir = 1;
                }
                break;
            case 3:
                if(!((row + 1) > (m - 1))){
                   row++;
                   dir = 2;
                }
                break;
            default:
                printf("Error!");
            }
       }else if(surr[1] != '1'){ //go left one space
           switch (dir) {
            case 0:
                if(!((col - 1) < 0)){
                   col--;
                   dir = 1;
                }
                break;
            case 1:
                if(!((row + 1) > (m - 1))){
                   row++;
                   dir = 2;
                }
               break;
            case 2:
                if(!((col + 1) > (n - 1))){
                   col++;
                   dir = 3;
                }
                break;
            case 3:
                if(!((row - 1) < 0)){
                   row--;
                   dir = 0;
                }
                break;
            default:
                printf("Error!");
            } 
       }else{ //turn around and go forward one space
           switch (dir) {
            case 0:
                if(!((row + 1) > (m - 1))){
                   row++;
                   dir = 2;
               }
                break;
            case 1:
                if(!((col + 1) > (n - 1))){
                   col++;
                   dir = 3;
               }
               break;
            case 2:
            if(!((row - 1) < 0)){
                   row--;
                   dir = 0;
               }
                break;
            case 3:
                if(!((col - 1) < 0)){
                   col--;
                   dir = 1;
               }
                break;
            default:
                printf("Error!");
            }
       }
       
       field[row][col] = 'X'; //Replace current '0' with an 'X'
       
       //Check whether returned to entrance or exit has been found
        if((row == entRow && col == entCol)){
            entrance = 1;
        }
        
        if(row == exRow && col == exCol){
            end = 1;
        }
       
    }while(((!entrance) && (!end)));  //end loop when you reach entrance or exit 
   
    //Print the maze with path marked
    for (i=0; i < m; i++)
    for (j=0; j < n; j++)  {
      if (j == 0) printf("\n");                
      printf("%c  ", field[i][j]);
    }
    printf("\n");
    
    //Determine whether a path to the exit was found
    if (row == entRow && col == entCol) {
        printf("No path was found.\n");
    }else if (row == exRow && col == exCol) {
        printf("A path was found.\n");
    }else{
        printf("Error.\n");
    }
}