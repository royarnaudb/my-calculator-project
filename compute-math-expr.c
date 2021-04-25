#include <stdio.h>
#include "parse-math-expr.h"
#include "compute-math-expr.h"

double calculate(char* status){

	char load = 0;  /*The maximum load(number of operands that can be stored) is 3.*/
	double operands[3] = {0,0,0};
	char operators[3] = {'+','+','+'};

	char parseMathExpression(double* operands, char* operators, char* load);
	char find(char c, char* operators);
	void compute(char* operators, double* operands, char* load);

	do{
		*status = parseMathExpression(operands, operators, &load);

		if(*status == '>'){
			compute(operators, operands, &load);
		}
		else if(*status == 'n' || *status == 'c'){
			compute(operators, operands, &load);
			break; /*Break the loop, then return operands[0] as our result.*/
		}
		else if(*status == 'o'){
			if(find('(', operators)){
				operators[load] = '*';
				if(load < 2)
					operands[load+1] = calculate(status);
				else{
					compute(operators, operands, &load);
					operands[load] = calculate(status);
				}
			}
			else
				operands[load] = calculate(status);
			compute(operators, operands, &load);

			if(*status == '\n')
				break; /*Break the loop, then return operands[0] as our result.*/
		}

	}while(*status != 's');

	return operands[0];
}

char find(char c, char* operators){

	if(operators[0] == c || operators[1] == c || operators[2] == c)
		return 1;
	return 0;
}

int highestOperator(char* operators){

	if( operators[0] == '*' || operators[0] == '/')
        return 0;
	else if( operators[1] == '*' || operators[1] == '/')
		return 1;
	return 0;
}

void arithmeticOperation(char operator, double* a, double* b, double* result){

	switch(operator){
		case '+':
			*result = *a + *b;
			break;
		case '-':
			*result = *a - *b;
			break;
		case '*':
			*result = *a * *b;
			break;
		case '/':
			*result = *a / *b;
			break;
		default:
			printf("Error: Unexpected operator '%c'!", operator);
			break;
	}
}

void updateData(char mode, char* load, char* operators, double* operands){

	switch(mode){
		case 1:
			operands[1]=0;
			operators[0]=operators[2];
			operators[1]='+';
			*load = 1;
			break;
		case 2:
			operands[1]=operands[2];
			operators[0]=operators[1];
			operators[1]=operators[2];
			*load = 2;
			break;
		case 3:
			operators[1]=operators[2];
			*load = 2;
			break;
		default:
			printf("Something went Wrong! The updateData mode '%i' is not defined!", mode);
			break;
	}
	operands[2]=0;
	operators[2]='+';
}

void compute(char* operators, double* operands, char* load){
	int highestOperator(char* operators), firstOperator;
	/*firstOperator is the first operator that we will arithmeticOperation with. And the function highestOperator return its position.*/
	void arithmeticOperation(char operator, double* a, double* b, double* result);
	void updateData(char mode, char* load, char* operators, double* operands);

	firstOperator = highestOperator(operators);
	if(operators[2] == '+' || operators[2] == '-'){ // if the last operator input is '+' or '-'.
				if(firstOperator == 0){
					arithmeticOperation(operators[firstOperator], &operands[0], &operands[1], &operands[0]);
					arithmeticOperation(operators[1], &operands[0], &operands[2], &operands[0]);
					updateData(1, load, operators, operands);
				}
				else if(firstOperator == 1){
					arithmeticOperation(operators[firstOperator], &operands[1], &operands[2], &operands[1]);
					arithmeticOperation(operators[0], &operands[0], &operands[1], &operands[0]);
					updateData(1, load, operators, operands);
				}
			}
			else if(operators[2] == '*' || operators[2] == '/'){ // if the last operator input is '*' or '/'.
				if(firstOperator == 0 && (operators[0] == '*' || operators[0] == '/')){
					arithmeticOperation(operators[firstOperator], &operands[0], &operands[1], &operands[0]);
					if(operators[1] == '*' || operators[1] == '/'){
						arithmeticOperation(operators[1], &operands[0], &operands[2], &operands[0]);
						updateData(1, load, operators, operands);
					}
					else
						updateData(2, load, operators, operands);
				}
				else if(firstOperator == 1 && (operators[1] == '*' || operators[1] == '/')){
					arithmeticOperation(operators[firstOperator], &operands[1], &operands[2], &operands[1]);
					updateData(3, load, operators, operands);
				}
				else{
					arithmeticOperation(operators[firstOperator], &operands[0], &operands[1], &operands[0]);
					updateData(2, load, operators, operands);
				}
			}
}
