#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cstdint>
#include <string>
#include <cstdio>
#include <cstring>
#include "stdio.h"
#include <algorithm>
#include <cstdlib>
#include <string>
using namespace std;

void error(bool condition, const string& msg)
{
	if (!condition) {
		cout << msg << endl;
		exit(1);
	}
}

class Dictionary {
	//insert and search in dict
public:
	void insert(int i, const string& str) {
		hash_.insert(make_pair(i, str));
		hash2_.insert(make_pair(str, i));
	}

	bool exist(int i) {
		return end(hash_) != hash_.find(i);
	}

	bool exist(const string& str) {
		return end(hash2_) != hash2_.find(str);
	}

	uint16_t get_num(const string& str) {
		auto found = hash2_.find(str);
		error(end(hash2_) != found, "get_num error");
		return found->second;
	}

	string get_str(int i) {
		auto found = hash_.find(i);
		error(end(hash_) != found, "get_str error");
		return found->second;
	}
	Dictionary() {
		for (int i = 0; i < 256; ++i) {
			char c = i;
			hash_.insert(make_pair(i, string() + c));
			hash2_.insert(make_pair(string() + c, i));
		}
	}
	void print() {
		for (auto& p : hash_) {
			if (p.first >= 256)
				cout << "[" << p.first << ", " << p.second << "]\n";
		}
	}

private:
	unordered_map<uint16_t, string> hash_;
	unordered_map<string, uint16_t> hash2_;
};

void ldecode(char* text) {//just compressed
	char current[1000];
	char current_next[1000];
	char *next;
	Dictionary dict;
	int key = 256;
	int check = 0;
	int dict_num = 0;
	int pointer = 1;
	while(pointer<strlen(text)-1){//replace the second space bewtween two space with '*'
		if(text[pointer]==' '){
			if(text[pointer-1]==' '&&text[pointer+1]==' '){
				text[pointer] = '*';
			}
			else{
				text[pointer] = ' ';
			}		
		}
		pointer++;
	}
	next = strtok(text," ");
	printf("%s",next);
	sprintf(current,"%s",next);
	next = strtok(NULL," ");
	while(next!=NULL){
		check = atoi(next);
		if(check<256){//check if the string is a dict key or just a string
			//output the string
			for(int i=0;i<strlen(next);i++){
				if(next[i] == '*'){
					printf(" ");
				}
				else{
					printf("%c",next[i]);
				}			
			}
			sprintf(current,"%s%s",current,next);
			dict.insert(key,current);
			key++;
			sprintf(current,"%s",next);
		}
		else{
			if(check>=key){//if the dict key did not exist
				sprintf(current,"%s%c",current,current[0]);
				dict.insert(key,current);
				key++;
				//print the string
				for(int i=0;i<strlen(current);i++){
					if(current[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current[i]);
					}			
				}				
			}
			else{//the dict key can be find in it
				string output = dict.get_str(check);
				output.copy(current_next,output.length(),0);
				*(current_next+output.length()) = '\0';
				//print the string
				for(int i=0;i<strlen(current_next);i++){
					if(current_next[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current_next[i]);
					}			
				}	
				sprintf(current,"%s%c",current,current_next[0]);
				dict.insert(key,current);
				sprintf(current,"%s",current_next);
				key++;
			}
		}
		check = 0;
		next = strtok(NULL," ");
	}
	printf("\n");
}

void lldecode(char* text) {//compressed and show dict
	char current[1000];
	char current_next[1000];
	char current_1[1000];
	char *next;
	Dictionary dict;
	int key = 256;
	int check = 0;
	int dict_num = 0;
	int pointer = 1;
	while(pointer<strlen(text)-1){//replace the second space bewtween two space with '*'
		if(text[pointer]==' '){
			if(text[pointer-1]==' '&&text[pointer+1]==' '){
				text[pointer] = '*';
			}
			else{
				text[pointer] = ' ';
			}		
		}
		pointer++;
	}
	next = strtok(text," ");
	printf("NIL %s %s\n",next,next);
	
	sprintf(current,"%s",next);
	sprintf(current_1,"%s",next);
	next = strtok(NULL," ");
	
	while(next!=NULL){	
		//print current string
		for(int i=0;i<strlen(current_1);i++){
			if(current_1[i] == '*'){
				printf(" ");
			}
			else{
				printf("%c",current_1[i]);
			}			
		}
		printf(" ");
		check = atoi(next);
		if(check<256){//check if the string is a dict key or just a string
			//print next string
			for(int i=0;i<strlen(next);i++){
				if(next[i] == '*'){
					printf(" ");
				}
				else{
					printf("%c",next[i]);
				}			
			}
			printf(" ");
			//print output
			for(int i=0;i<strlen(next);i++){
				if(next[i] == '*'){
					printf(" ");
				}
				else{
					printf("%c",next[i]);
				}			
			}
			sprintf(current,"%s%s",current,next);
			dict.insert(key,current);
			//print dict key
			printf(" %d ",key);
			//print dict string
			for(int i=0;i<strlen(current);i++){
				if(current[i] == '*'){
					printf(" ");
				}
				else{
					printf("%c",current[i]);
				}			
			}
			key++;
			sprintf(current,"%s",next);
			printf("\n");
		}
		else{
			//print next string
			printf("%d ",check);
			if(check>=key){
				sprintf(current,"%s%c",current,current[0]);
				dict.insert(key,current);
				//print output string
				for(int i=0;i<strlen(current);i++){
					if(current[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current[i]);
					}			
				}
				//print dict key
				printf(" %d ",key);
				//print dict string
				for(int i=0;i<strlen(current);i++){
					if(current[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current[i]);
					}			
				}
				key++;
				printf("\n");				
			}
			else{
				
				string output = dict.get_str(check);
				output.copy(current_next,output.length(),0);
				*(current_next+output.length()) = '\0';
				//print output string
				for(int i=0;i<strlen(current_next);i++){
					if(current_next[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current_next[i]);
					}			
				}	
				sprintf(current,"%s%c",current,current_next[0]);
				//print dict key
				dict.insert(key,current);
				printf(" %d ",key);
				//print dict string
				for(int i=0;i<strlen(current);i++){
					if(current[i] == '*'){
						printf(" ");
					}
					else{
						printf("%c",current[i]);
					}			
				}
				sprintf(current,"%s",current_next);
				key++;
				printf("\n");
			}
		}
		check = 0;
		sprintf(current_1,"%s",next);
		next = strtok(NULL," ");
		
		
	}

}
int main(int argc, char* argv[])
{
	char input[1000000];
	fgets(input,1000000,stdin);
	input[strlen(input)-1] = '\0';
	if(argc==2){//if input "ldecode -l" then dict
		lldecode(input);
	}
	else{
		ldecode(input);
	}
}


