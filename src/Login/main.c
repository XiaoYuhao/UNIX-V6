/*
 * main.c
 *
 *  Created on: 2019-4-12
 *      Author: Xiao  Yuhao
 */
#include "stdio.h"
#include "stdlib.h"
#include "sys.h"

#include "string.h"

#define MAX_LEN 28

int main1(){
	char username[MAX_LEN];
	char password[MAX_LEN];

	while(1){
		printf("Login:");
		gets(username);
		printf("Password:");
		get_password(password);
		if( strcmp( "root", username ) == 0 ){
			if( strcmp( "123456", password ) == 0){
				if( fork()){
					int temp;
					wait(&temp);
				}
				else{
					char* argv[3];
					argv[0]="/Shell";
					argv[1]=username;
					argv[2]= 0;
					execv("/Shell.exe",argv);
				}
			}
			else{
				printf("Login incorrect\n");
			}
		}
		else if( strcmp( "user", username ) == 0 ){
			if( strcmp( "654321", password ) == 0){
				if( fork()){
					int temp;
					wait(&temp);
				}
				else{
					char* argv[3];
					argv[0]="/Shell";
					argv[1]=username;
					argv[2]= 0;
					execv("/Shell.exe",argv);
				}
			}
			else{
				printf("Login incorrect\n");
			}
		}
	}
	return 0;
}

