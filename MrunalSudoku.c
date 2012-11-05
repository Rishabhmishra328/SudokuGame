#include <stdio.h>
typedef struct{
	int filled[10];
}possibility;

void displaymatrix (int s[9][9]);
void setmatrix (int s[9][9]);
void initupdatepossibility(int s[9][9] , possibility p[81]);
void initpossibility(possibility p[81]);
void printpossibility(possibility p[81]);
void eliminate_from_row(int s[9][9],int mapper, possibility p[81], int row_id);
void eliminate_from_col(int s[9][9],int mapper, possibility p[81], int col_id);
int findandfillvalue(int s[9][9], possibility p[81], int row, int col);
int processmatrix(int s[9][9], possibility p[81]);




int main(){
int s[9][9]={0};
int result;
possibility p[81];
printf("\nThis is my sodoku trial\n");
initpossibility(p);
setmatrix(s);
displaymatrix(s);
initupdatepossibility(s,p);
result=processmatrix(s,p);
printpossibility(p);
displaymatrix(s);


}
void initpossibility(possibility p[81])
{
	int i,j,k,count;
	printf("\n This is my init possibility func\n");
	for(i=0;i<81;i++)
		{
		    for(j=0;j<9;j++){
		    p[i].filled[j]=(j+1); // init p to sequence 1,2,3,4...9
		                         // later will be updated as per digits in containing row and colown
			}
	}
	for(i=0;i<9;i++)
	{		
		for(j=0;j<9;j++)
		{
			p[(i*9)+j].filled[9]=(i*9+j);
			
		}
	}

}

void printpossibility(possibility p[81])
{
	int i,j;
	for(i=0;i<81;i++){
		for(j=0;j<10;j++)
		{
			printf(" %d " , p[i].filled[j]);
		}
		printf("\n");
	}
}
void displaymatrix (int s[9][9]){
	int i,j;
    for(i=0;i<9;i++){
		for(j=0;j<9;j++)
		{
			printf("%d\t", s[i][j]);
		}
		if(i%3 == 2)
		    printf("\n\n");
		printf("\n");
	}
}

void setmatrix (int s[9][9]){
        int i,j;

	
	
   
        // VERY easy level sudoku contains 45 elements out of 81 elements in a 3*3 matrix
	s[0][0] = 7;
	s[0][4] = 3;
	s[0][5] = 8;
	s[0][7] = 9;
	s[0][8] = 1;
	
	s[1][1] = 5;
	s[1][2] = 1;
	s[1][3] = 9;
	s[1][4] = 4;
	s[1][7] = 7;
	s[1][8] = 3;
	
	s[2][0] = 3;
	s[2][1] = 4;
	s[2][4] = 7;
	s[2][5] = 1;
	s[2][6] = 6;
	s[2][7] = 8;
	
	s[3][2] = 8;
	s[3][3] = 1;
	s[3][5] = 9;
	s[3][6] = 5;
	s[3][7] = 3;
	
	s[4][2] = 7;
	s[4][5] = 5;
	s[4][6] = 1;
	
	s[5][0] = 5;
	s[5][2] = 3;
	s[5][3] = 7; 
	s[5][5] = 4;
	s[5][6] = 9;
	
	s[6][0] = 1;
	s[6][1] = 3;
	s[6][4] = 9;
	s[6][7] = 6;
	s[6][8] = 4; 
	
	s[7][0] = 2;
	s[7][3] = 6; 
	s[7][4] = 1;
	s[7][6] = 3;
	
	s[8][1] = 7;
	s[8][2] = 6;
	s[8][3] = 4;
	s[8][4] = 5; 
	s[8][7] = 1;
	s[8][8] = 2;
}

void initupdatepossibility(int s[9][9], possibility p[81])
{
    int i,j,mapper,k,t;
	for(i=0;i<9;i++)                          // i is the coloumn iterator
	{
		for(j=0;j<9;j++)                     //j is the row iterator
		{ 
			mapper = (i*9) +j;               // mapper is the index that is maps matrix index to possibility array of [81][9]
	 		if(s[i][j])                      // if the block in matrix contains value then set value on filled array to 0
			{
				for(k=0;k<9;k++) 
				{
					p[mapper].filled[k]=0; //now this value cannot be filled hence setting its possibility to null
				}
			}
		}
	}
}

void eliminate_from_row(int s[9][9],int mapper, possibility p[81], int row_id){
	int i;
	for(i=0;i<9;i++)
	{
	   if(s[row_id][i]!= 0 )
       {
		   p[mapper].filled[ (s[row_id][i] ) - 1] =0;
	   }
	}
}

void eliminate_from_col(int s[9][9],int mapper, possibility p[81], int col_id){
	int i;
	for(i=0;i<9;i++)
	{
	   if(s[i][col_id]!= 0 )
           p[mapper].filled[ (s[i][col_id] ) - 1] =0;
	}
}

void eliminate_from_square(int s[9][9],possibility p[81] ,int row, int col){
	int i,j,k,rel_row_position,rel_col_position,mapper, index;
	rel_row_position = row - (row % 3);                          // is the relative row position of block in 3 * 3 matrix
	rel_col_position = col - (col % 3);         	             // is the relative col position of block in 3 * 3 matrix
	for(i = rel_row_position; i < (rel_row_position+3);  i++)		// run the for loop from i till 3 elements to its left
	{
        for(j = rel_col_position ; j < (rel_col_position + 3); j++)
		{
			if(s[i][j])                                         // scrolling  3*3 to find block will contains value 
				                                                // so that it can me eliminated from possibility
			    p[(row*9) +col].filled[(s[i][j] - 1)] = 0;         
				//now this value cannot be filled hence setting its possibility to null
		}
	}
}

int processmatrix(int s[9][9], possibility p[81]){
	int i,j,k,reset = -1;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(s[i][j] == 0)                 
			/* if the s[i][j] th block is filled then  */
			/* we have set possibility of it as 0 in initupdatepossibility*/
			{
				eliminate_from_row(s,((i*9)+j),p,i);
				eliminate_from_col(s,((i*9)+j),p,j);
				eliminate_from_square(s,p,i,j);
				reset = findandfillvalue(s,p,i,j);
				if(reset==1)
				{
					i=0;
					j=-1;
					reset = 0;
				}
				
		        }
			
		}
	}
	return 0;
}

int findandfillvalue(int s[9][9], possibility p[81], int row, int col)
{
	int i,j,value=0, curr_mapper;
	curr_mapper = row * 9 + col;	
	/* scan position matrix to find a 1D array which has single value */
	for(j=0;j<9;j++){
		if(p[curr_mapper].filled[j])
		{
			if(value == 0){
			    value = p[curr_mapper].filled[j];
			}
			else{
				value = 0; // reset the value showing single valued filled array wasnt found and hence breaked from the loop
				           // if a single valued filled array is present 
				           //then value variable will not come in else and will retain the number in it. 
				           //This number can be fill in the arrary
				break;
			}
		}
				
	}
	
	if(value)
	{
		s[row][col] = value;
		return 1;
	}
    return 0;
}
