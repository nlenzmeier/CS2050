/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * LAB F 
 * Lab 11
 * NALYV2
 * Created on December 2, 2015, 11:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <string.h>
#include <ctype.h>

void parseFile(char* filename);
void parseWord(char* word);
bool isAPhoneNumber(char* word);
bool isADate(char* word);
bool isATime(char* word);

int main(int argc, char** argv)
{
	parseFile(argv[1]);	
	return 0;
}

//not actually needed for the test input file, but a nice general parser
//with a few delimiters for general use. Can be used on other text files,
//such as memos, etc
void parseFile(char* filename)
{
	FILE* fp = fopen(filename, "r");
	char* word = malloc(sizeof(char)*255);
	char c;
	int i = 0;
	bool periodInWord = false;
	bool wasWordDone = false;
	//puts actual words together, instead of using strtok.
	//This way you can use strtok if you so choose in the 
	//check functions below.
	while((c = fgetc(fp)) != EOF)
	{
		//thought this would cause a corner case, will keep here anyway.
		if(c == '\n')
		{
			wasWordDone = true;
		}
		//these separate words from each other.
		else if(c == ' ' || c == ',' || c == '.')
		{
			wasWordDone = true;
		}
		//this is either a letter or character that is part of a word.
		else
		{
			//still on the same word.
			if(wasWordDone == false)
			{
				word[i] = c;
				i++;
			}
			//new word has been started. Process old word, then
			//start over.
			else
			{
				word[i] = '\0';
				i = 0;
				parseWord(word);
				free(word);
				word = malloc(sizeof(char)*255);
				word[i] = c;
				wasWordDone = false;
				i++;
			}
		}	
	}
	//leaves out the last word because the loop stops at EOF,
	//so process last word.
	parseWord(word);	
	fclose(fp);
	free(word);
}

void parseWord(char* word)
{
	if(isAPhoneNumber(word))
	{
		printf("Phone Number found: %s\n", word);
	}
	if(isADate(word))
	{
		printf("Date found: %s\n", word);
	}
	if(isATime(word))
	{
		printf("Time found: %s\n", word);
	}
}

//These are for you to do!
//I also changed it up last minute. You can use strtok() if you want, but
//you won't get the bonus!
bool isAPhoneNumber(char* word)
{     
    int i, count=0;
    for (i = 0; word[i] != '\0'; i++){
        count+=1;
    }
    if (count != 12){
        return false;
    }
    if (word[3] != '-' || word[7] != '-'){
        return false;
    }
    else{
        if (isdigit(word[0])){
            if (isdigit(word[1])){
                 if (isdigit(word[2])){
                      if (isdigit(word[4])){
                           if (isdigit(word[5])){
                                if (isdigit(word[6])){
                                     if (isdigit(word[8])){
                                         if (isdigit(word[9])){
                                             if (isdigit(word[10])){
                                                  if (isdigit(word[11])){
                                                        return true;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
        }
        
        return false;
    }
    
}	
bool isADate(char* word)
{
	int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //We'll say that the earliest readable date is 01/01/1970 (computer epoch).
    //Computers shouldn't be reading stuff from earlier than computers anyway.
    int earliestValidYear = 1970;
    int earliestValidDay = 1;
    int earliestValidMonth = 1;
    
    int i = 0, count = 0;
    for (i = 0; i < 10; i++){
        if(word[i]=='/'){
            count+=1;
        }
    }
    if(count > 2){
        return false;
    }
    
    if(word[1] == '/' && word[4] == '/'){
        int d=0, m=0, y=0;
        sscanf(word, "%d/%d/%d", &m, &d, &y);
        
        if(m > 12){
            return false;
        }
        if(m == 2 && d > 28){
            return false;
        }
        if(m == 4 && d > 30){
            return false;
        }
        if(y < 1970 || y > 2015){
            return false;
        }
        
        return true;
    }
    
    if(word[1] == '/' && word[3] == '/'){
        int da=0, mo=0, ye=0;
        sscanf(word, "%d/%d/%d", &mo, &da, &ye);
        
        if(mo == 2 && da > 28){
            return false;
        }
        if(mo == 4 && da > 30){
            return false;
        }
        if(ye < 1970 || ye > 2015){
            return false;
        }
        
        return true;
    }
    
    if(word[2] == '/' && word[4] == '/'){
        int days=0, months=0, years=0;
        sscanf(word, "%d/%d/%d", &months, &days, &years);
        
        if(months > 12){
            return false;
        }
        if(years < 1970 || years > 2015){
            return false;
        }
        if(months == 02 && days > 28){
            return false;
        }
        if(months == 04 && days > 30){
            return false;
        }
        return true;
    }
    
    if(word[2] == '/' && word[5] == '/'){
        int day=0, mon=0, yea=0;
        sscanf(word, "%d/%d/%d", &mon, &day, &yea);
        
        if(mon > 12){
            return false;
        }
        if(mon == 02 && day > 28){
            return false;
        }
        if(mon == 04 && day > 30){
            return false;
        }
        if(day > 31){
            return false;
        }
        if(yea < 1970 || yea > 2015){
            return false;
        }
        
        return true;
    }
}
bool isATime(char* word)
{
    int i=0;
    if(word[1] == ':' && word[5] == 'm'){
        if(word[6] == 'm'){
            return false;
        }
        int m = 0, h = 0;
        sscanf(word, "%d:%d%*cm", &h, &m);
        
        if(m > 59){
            return false;
        }
        return true;
    }
    if(word[2] == ':' && word[6] == 'm'){
        if(word[7] == 'm'){
            return false;
        }
        int min =0, hour=0;
        sscanf(word, "%d:%d%*cm", &hour, &min);
        
        if(hour < 1 || hour > 12){
               return false;
            }    
        if(min > 59){
            return false;
        }
        return true;
    }
    else{
        return false;        
    }
}

