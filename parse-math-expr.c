#include <stdio.h>
#include <math.h>
#include "parse-math-expr.h"

char parseOperand(char c, double* number){

	char hasFractionalPart = 0; /*False (default). 'hasFractionalPart' is set to True (hasFractionalPart = 1;) when we encounter the character '.' in the keyboard buffer*/
	double sign = 1;    /*Operand is Positive (default). 'sign' is used at the end of the function to determine the sign of the operand.*/
	*number = 0;

	if(c == '-')
		sign = -1;
	else if( c == '+')
		;
	else if( c >= '0' && c <= '9')
		*number = (double)(c-'0');  /*Computing the first significant digit.*/
	else if( c == '.')
		hasFractionalPart = 1;  /*The operand does not have an integer part. (Example: .1234 )*/
	else if( c == '*' || c == '/')
		return 's'; /*SyntaxError: Two operators cannot be consecutive. (Example: 34 + * 78 )*/
	else if(c == '(')
		return 'o'; /*return OpeningParenthesis status*/
	else
		return c;

	c = getchar();
	char exponent = 0;  /*Used for computing the fractional part of the operand.*/

	while( (c >= '0' && c<='9') || c == '.'  ){
		if (c >= '0' && c<='9'){
			if(hasFractionalPart == 1)
				*number += (double)(c-'0') / (double)pow(10, ++exponent);
			else
				*number = (double)((*number)*10+ (c-'0'));
		}
		else if( hasFractionalPart == 1)    //if (c == '.' && hasFractionalPart == 1) then something is wrong!
			return 's'; /*SyntaxError: We have two dots '.' in our operand. (Example: 12.8.9 or .90.8 ).*/
		else
			hasFractionalPart = 1;
		c = getchar();
	}
	*number *= sign;
	return c;
}

char parseMathExpression(double* operands, char* operators, char* load){

	char c;  // character from the buffer
	char parseOperand(char , double*);

	while( (*load) < 3){
		c = getchar();
		c = parseOperand(c, &operands[*load]);

		if(c == 's')
			return 's'; // syntaxError status

		while( c == ' ' || c == '\t') // we discard white spaces
			c = getchar();

		switch(c){

			case '+':
				operators[*load] = '+';
				break;
			case '-':
				operators[*load] = '-';
				break;
			case '*':
				operators[*load] = '*';
				break;
			case '/':
				operators[*load] = '/';
				break;
			case '(':
				operators[*load] = '(';
				return 'o'; //OpeningParenthesis status. (Example: 89(90+10) )
				break;
			case 'o':
				return 'o'; //OpeningParenthesis status. We have an operator before '('. (Example: 89 * (90+10) )
				break;
			case ')':
				return 'c'; //ClosingParenthesis status.
				break;
			case '\n':
				return 'n'; //End status.
			default:
				return 's'; //SyntaxError status.
				break;
		}
		*load += 1;
	}
	return '>'; //ContinuingWithExpression status
}
