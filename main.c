#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calcfunc.h"

int isDigit(char input){
	if(input>='0'&&input<='9')
		return 1;
	if(input == '.')
		return 1;
	return 0;
}

//returns a dynamically sized line from the stdin
char *getLine(){
	int size = 0, allocated = 10;
	char *line = malloc(allocated), c;
	while((c=getchar())!='\n'&&c!=EOF){
		if(size+1>=allocated){
			allocated *= 2;
			line = realloc(line,allocated);
		}
		line[size++]=c;
	}
	line[size]='\0';
	return line;
}

//returns a dynamically sized RPN equation
char *parseLine(char *input){
	int pos = 0, allocated = strlen(input)+1;
	char *output = malloc(allocated), opstack[256]={0};
	char *op = opstack;
	while(*input){
		if(isDigit(*input)) { //puts a number directly into the string
			if(pos+2>=allocated){
				allocated *= 2;
				output = realloc(output,allocated);
			}
			output[pos++]=*input++;
			while(isDigit(*input)){
				if(pos+1>=allocated){
					allocated *= 2;
					output = realloc(output,allocated);
				}
				output[pos++]=*input++;
			}
			output[pos++]=' ';
		} else if(*input=='+'||*input=='-') { //Aunt Sally
			while(*op == '*' || *op == '/' || \
				  *op == '+' || *op == '-' || *op == '^') {
				if(pos+2>=allocated){
					allocated *= 2;
					output = realloc(output,allocated);
				}
				output[pos++]=*op;
				output[pos++]=' ';
				op--;
			}
			*++op=*input++;
		} else if(*input=='*'||*input=='/') { //My Dear
			while(*op == '*' || *op == '/' || *op == '^') {
				if(pos+2>=allocated){
					allocated *= 2;
					output = realloc(output,allocated);
				}
				output[pos++]=*op;
				output[pos++]=' ';
				op--;
			}
			*++op=*input++;
		} else if(*input=='^') { //Excuse
			while(0) { // this is just here as a placeholder
				if(pos+2>=allocated){
					allocated *= 2;
					output = realloc(output,allocated);
				}
				output[pos++]=*op;
				output[pos++]=' ';
				op--;
			}
			*++op=*input++;
		} else if(*input=='(') { //Please open
			*++op=*input++;
		} else if(*input==')') { //Please close
			while(*op!='(' && *op) {
				if(pos+2>=allocated){
					allocated *= 2;
					output = realloc(output,allocated);
				}
				output[pos++]=*op;
				output[pos++]=' ';
				op--;
			}
			if(!*op) {
				free(output);
				return NULL;
			}
			*op-- = '\0';
			input++;
		} else {
			input++;
		}
	}
	while(*op){ //drain the remaining stack
		if(pos+2>=allocated){
			allocated *= 2;
			output = realloc(output,allocated);
		}
		output[pos++]=*op--;
		output[pos++]=' ';
	}
	output[pos]='\0';
	return output;
}

double parseRPN(char *input){
	Number stack[100]={0,1};
	Number *pos = stack;
	for(char *token = strtok(input," \n");token;token=strtok(NULL," \n")){
		switch(*token){
			case '-':
				--pos;
				*pos = subtract(*pos,*(pos+1));
				break;
			case '+':
				--pos;
				*pos = add(*pos,*(pos+1));
				break;
			case '/':
				--pos;
				*pos = divide(*pos,*(pos+1));
				break;
			case '*':
				--pos;
				*pos = multiply(*pos,*(pos+1));
				break;
			case '^':
				--pos;
				*pos = exponent(*pos,*(pos+1));
				break;
			default:
				pos++;
				pos->top=atof(token);
				pos->bottom=1.0;
		}
	}
	return pos->top/pos->bottom;
}

int main(){
	puts("To quit enter a blank line.");
	while(1){
		printf(">>> ");
		char *input = getLine();
		if(!strlen(input)){
			free(input);
			break;
		}
		char *rpn = parseLine(input);
		free(input);
		if(rpn) {
			printf("%f\n",parseRPN(rpn));
			free(rpn);
		} else {
			puts("Error");
		}
	}
	return 0;
}
