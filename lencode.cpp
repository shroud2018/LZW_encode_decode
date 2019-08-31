#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cstdint>
#include <string>
#include <cstdio>
#include <cstring>
#include <stdio.h>
using namespace std;

void error(bool condition, const string& msg)
{
	if (!condition) {
		cout << msg << endl;
		exit(1);
	}
}

class Dictionary {
	//insert and search
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

void lencode(char* text) {//do encode
	char current[1000];
	char next;
	int dict_num=0;
	Dictionary dict;
	int key = 256;
	int key_10 = 256;
	int pointer=0;
	next = text[pointer];
	sprintf(current, "%c", next);
	pointer++;
	next = text[pointer];
	while(pointer<strlen(text)-1){//read one char
		sprintf(current,"%s%c",current,next);
		if(!dict.exist(current)){//not exist in dict
			if(key<16384){//dict is full
				dict.insert(key,current);
				key++;
			}
			current[strlen(current)-1] = '\0';
			if(dict_num==0){//if not in dict, print itself, else print the key
				printf("%s ",current);
			}
			else{
				printf("%d ",dict_num);
			}
			dict_num = 0;
			sprintf(current,"%c",next);
		}
		else{
			dict_num = dict.get_num(current);
		}
		pointer++;
		next = text[pointer];
	}
	if(dict_num!=0){
		printf("%d\n",dict_num);
	}
	else{
		printf("%s\n",current);
	}

}
void llencode(char* text) {//do and print encode dictionary
	char current[1000];
	char output[1000];
	char next;
	int dict_num=0;
	Dictionary dict;
	int key = 256;
	int key_10 = 256;
	int pointer=0;
	next = text[pointer];
	sprintf(current, "%c", next);
	printf("NIL %s\n",current);
	pointer++;
	next = text[pointer];
	while(pointer<strlen(text)-1){
		printf("%s ",current);
		printf("%c",next);
		sprintf(current,"%s%c",current,next);
		if(!dict.exist(current)){//not exist in dict
			printf(" ");
			if(key<16384){//dict is full
				dict.insert(key,current);
				
			}
			strcpy(output,current);
			current[strlen(current)-1] = '\0';
			if(dict_num==0){//if not in dict, print itself, else print the key
				printf("%s ",current);
			}
			else{
				printf("%d ",dict_num);
			}
			dict_num = 0;
			sprintf(current,"%c",next);
			printf("%d ",key);
			printf("%s\n",output);
			key++;
		}
		else{
			printf("\n");
			dict_num = dict.get_num(current);
		}
		pointer++;
		next = text[pointer];
	}
	if(dict_num!=0){
		printf("%s ",current);
		printf("EOF ");
		printf("%d\n",dict_num);
	}
	else{
		printf("%c ",text[strlen(text)-2]);
		printf("EOF ");
		printf("%c\n",text[strlen(text)-2]);
	}

}

int main(int argc, char* argv[])
{
	char input[1000000];
	fgets(input,1000000,stdin);
	if(argc==2){//input "lencode -l to run the dict"
		llencode(input);
	}
	else{//do lzw compression
		lencode(input);
	}
}


