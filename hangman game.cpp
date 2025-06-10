#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
//system(CLEAR_COMMAND)
#else 
#define CLEAR_COMMAND "clear"
#endif

#define MAX_TRIES_EASY 10
#define MAX_TRIES_MODERATE 8
#define MAX_TRIES_HARD 6
#define WORD_LIST_SIZE 5
#define LEADERBOARD_SIZE 5

typedef struct {
	char name[50];
	int score;
	int level;
}player;

const char* easyWords[WORD_LIST_SIZE]={
"apple" , "ball" , " cat" , "dog" , "fish"};
const char* easyHints[WORD_LIST_SIZE]={
"a fruit" , "it bounces" , "a pet " , "barks" , "lives in water "};
const char*moderateWords[WORD_LIST_SIZE]={
"planet" , "butter ", " school" , "garden" , "rocket"};
const char*moderateHints[WORD_LIST_SIZE]={
"orbits the sun" , "used on toast" ,"place to study" , "has flowers" , "goes to space "};
const char*hardWords[WORD_LIST_SIZE]={
"computer" , "hangman" ,"electric" , "triangle" , "magnet"};
const char* hardHints[WORD_LIST_SIZE]={"electronic device" , "this game" , "power type " , "3 sided shape " , "attracts metal" };

void clearScreen(){
	system(CLEAR_COMMAND); //clear , cls 
}


void printHeader(char *name , int score , int level){
	printf("=============================================\n\n");
	printf("player: %s\tScore:%d\tLevel:%s\n " name , score ,(level==1 ? "EASY" :level ==2? "MODERATE": "HARD");
	printf("=============================================\n\n");
}

void printHangman(int tries){
	switch (tries){
		case 1:printf("\O\n"); break;
		case 2: printf("\n O\n | \n") ; break ;
		case 3: printf("\n O\n |/ \n ") ; break ;
		case 4: printf("\n O\n /|\ \n ") ; break ;
		case 5: printf("\n O\n/|\\\n/\n"); break;
		case 6: printf("\n O\n/|\\\n/ \\\n"); break;
		case 7: printf("\n O\n/|\\\n/ \\\n\nGame Over!\n"); break;
	}
}



























