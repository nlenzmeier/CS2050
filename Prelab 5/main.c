/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on September 24, 2015, 12:37 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef struct MA
{
    char name[30];
    char artist[30];
    int numberSold;
    int ID;
} music_album;

/*
 * 
 */
music_album* readFromFile(char* filename);
void printAlbums(music_album* list, long long time, long long t1, long long t2);
void mergeSortByArtist(music_album* list, int start, int end);
void merge(music_album* list, int start, int middle, int end);
void selectionSortOnNumberSold(music_album* list);
void insertionSortOnID(music_album* list);

int main(int argc, char** argv) {

    //User's choice on sort
    int choice;
    //Here are the time variables. They will hold the following:
    //  time: the final time that the algorithm took.
    //  t1: the first timestamp recorded, before the algorithm runs
    //  t2: the second timestamp recorded, after the algorithm runs
    long long time = -1;
    long long t1, t2;
    
    music_album* list = readFromFile(argv[1]);
    if(list == NULL)
    {
        printf("No array! Did something happen to the file?\n");
        return 1;
    }
    printAlbums(list, time, t1, t2);
    
    //Prints a menu. Each menu selection will do a different sort, and then print out the newly sorted array. 
    //Repeats until user put in 4, then the program will end. 
    while(1)
    {
        printf("Choose a selection:\n1: Selection sort on numberSold\n2: Insertion sort on ID\n3: Merge sort on artist\n");
        printf("4: exit\n");
        printf("\n>");
        scanf("%d", &choice);
        //Appropriate error checking
        while(choice > 4 || choice < 1)
        {
            printf("Invalid selection.\n");
            printf("\n>");
            scanf("%d", &choice);
        }
        
        //****************First thing to do************************
        //start the timing. Get the first timestamp here.
        
        switch (choice)
        {
            //****************Second thing to do************************
            case 1: 
                selectionSortOnNumberSold(list);
                //get the last timestamp right here. 
                printAlbums(list, time, t1, t2);
                break;
            case 2:
                insertionSortOnID(list);
                //or here for this sort. 
                printAlbums(list, time, t1, t2);
                break;
            case 3:
                mergeSortByArtist(list, 0, 9);
                //or here for this sort. 
                printAlbums(list, time, t1, t2);
                break;
            case 4:
                //not needed here
                free(list);
                return 0;
        }
        
        
    }
    
}

music_album* readFromFile(char* filename)
{
    FILE* fp = fopen(filename, "rb");
    
    if(!fp)
    {
        return NULL;
    }
    
    music_album* list = malloc(sizeof(music_album)*10);
    fread(list, sizeof(struct MA), 10, fp);
    fclose(fp);
    return list;
}

void printAlbums(music_album* list, long long time, long long t1, long long t2)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("------\nArtist: %s\nAlbum: %s\nNumber Sold: %d copies\nID: %d\n------\n", 
                list[i].artist, list[i].name, list[i].numberSold, list[i].ID);
    }
    if(time == -1)
    {
        printf("\nTime has not been recorded yet.\n\n");
    }
    else if(time == 0)
    {
        printf("\nTotal time: Less than 1 microsecond\n");
        printf("\nt1: %e\n", t1);
        printf("\nt2: %e\n\n", t2);
    }
    else 
    {
        printf("\nTotal time: %e\n", time);
        printf("\nt1: %e\n", t1);
        printf("\nt2: %e\n\n", t2);
    }
    
}


/*
 * Inputs:
 *      list: the pointer to the malloced array
 *      low: the lowest index of the scoped array
 *      high: the highest index of the scoped array
 * 
 * Returns: nothing
 */
void mergeSortByArtist(music_album* list, int low, int high)
{
    int middle1, middle2;
    
    if((high - low)>= 1){
        middle1 = (low + high)/2;
        middle2 = middle1 + 1;
        
        mergeSortByArtist( list, low, middle1);
        mergeSortByArtist( list, middle2, high);
        
        merge(list, low, middle1, high);
    }
//****************Third thing to do************************  
    
    /*
     * Fill in this function. Remember your base case.
     * 
     * Remember, the sort goes down the left side, then the right side, 
     * then merges the two sides. The breaking down parts are recursive calls,
     * and then you just do merge. 
     * 
     * Make sure you figure out how the left and right sides are represented
     * using low and high! 
     
     */
}


/*
 * Inputs:
 *      list: the pointer to the malloced array
 *      low: the lowest index of the scoped array
 *      mid: the middle index of the scoped array
 *      high: the highest index of the scoped array
 * 
 * Returns: nothing
 * 
 * DON'T TOUCH
 */
void merge(music_album* list, int low, int mid, int high)
{
    music_album *temp;
	int left, right, current;
	
	temp = malloc((high + 1)*sizeof(music_album));
	
	left = low;
	right = mid + 1;
	current = low;
	
	while((left <= mid) && (right <= high))
	{
		if (strcmp(list[left].artist, list[right].artist) > 0)
		{
			temp[current] = list[right];
			current++;
			right++;
		}
		else
		{
			temp[current] = list[left];
			current++;
			left++;
		}
	}
	
	while(left <= mid)
	{
		temp[current] = list[left];
		current++;
		left++;
	}
	
	while(right <= high)
	{
		temp[current] = list[right];
		current++;
		right++;
	}
	
	for(left = low; left < current; left++)
	{
		list[left] = temp[left];
	}
	
	free(temp);
        return;
}

/*
 * Inputs:
 *      list: the pointer to the malloced array
 * 
 * Returns: nothing
 */
void selectionSortOnNumberSold(music_album* list)
{
 int smallest;
    int i, j;
    
    for(i=0; i < 10-1; i++){
        smallest = i;
        
        for(j = i + 1; j < 10; j++){
            if(list[j].numberSold < list[smallest].numberSold){
               smallest = j; 
            }
        }
                music_album temp = list[i];
                list[i] = list[smallest];
                list[smallest] = temp;
            }
    return;
    //printAlbums(list);   
//****************Fourth thing to do************************      
    

/*
 * Take the malloced array, and do selection sort using the given
 * criteria. There's nothing else you have to do.
 */
}

/*
 * Inputs:
 *      list: the pointer to the malloced array
 * 
 * Returns: nothing
 */
void insertionSortOnID(music_album* list)
{
    int c, move, i;
    for (c = 0; c < 10; c++){
        move = c;
        music_album insert = list[c];
        
        while (move > 0 && list[move -1].ID > insert.ID){
             list[move] = list[move -1];
                --move;
        }
        list[move]= insert;
    }
    return;
    //printAlbums(list);
//****************Last thing to do************************        
 
 /*
 * Take the malloced array, and do insertion sort using the given
 * criteria. There's nothing else you have to do.
 */
}

