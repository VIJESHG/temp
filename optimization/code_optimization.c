#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char result[8];
	char op[4];
	char op1[8];
	char op2[8];
	int isNum;
	int flag;	
} node;

node n[50];

//check if operand is a number
int isNumber(char *tmp) {
	int isDigit = 1;
	int j = 0;

	while(j < strlen(tmp) && isDigit == 1){
		if(tmp[j] <= 57 && tmp[j] >= 48 || tmp[j] == '.')
			isDigit = 1;
		else
			isDigit = 0;
		j++;
	}
	return isDigit;

}

//store intermediate code in a structure
void insert_result(char *s, int index) {
	//Result
	char * token = strtok(s, " \t");
	strcpy(n[index].result, token);

	//Operator
	token = strtok(NULL, " \t");
	strcpy(n[index].op, token);

	//Operand 1
	token = strtok(NULL, " \t");
	strcpy(n[index].op1, token);

	//Operand 2
	token = strtok(NULL, " \t");
	strcpy(n[index].op2, token);
	if(!strcmp(n[index].op2, "-"))
		n[index].isNum = isNumber(n[index].op1);	//if second operand is NULL, check if first operand is a number
	else {
		n[index].isNum = isNumber(n[index].op1);	//check if both the operands are number
		n[index].isNum += isNumber(n[index].op2);
	}
	n[index].flag = 1;
	printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", index + 1, n[index].result, n[index].op, n[index].op1, n[index].op2); 
}

//if a variable is initialized, substitute its value in RHS
void substitute_value(int index) {
	int i, j, num1, num2;
	for(i = 0; i <= index; i++) {
		//if both the operands are number, evaluate the expression
		if(n[i].isNum == 2) {
			num1 = atoi(n[i].op1);
			num2 = atoi(n[i].op2);
			
			if(!strcmp(n[i].op, "+"))
				num1 += num2;
			if(!strcmp(n[i].op, "-"))
				num1 -= num2;
			if(!strcmp(n[i].op, "*"))
				num1 *= num2;
			if(!strcmp(n[i].op, "/"))
				num1 /= num2;
			
			strcpy(n[i].op, "=");
			
			sprintf(n[i].op1, "%d", num1);
			strcpy(n[i].op2, "-");
			n[i].isNum -= 1;
		}
		/*if one of the operand is number, substitute value of other operand
		 *After substitution, if both the operands are number, evaluate the expression
		 */
		if(n[i].isNum == 1 && strcmp(n[i].op2, "-")) {
			for(j = 0; j < i; j++) {
				if(n[j].isNum == 1 && !strcmp(n[j].op2, "-") && !strcmp(n[i].op1, n[j].result)) {
					strcpy(n[i].op1, n[j].op1);
					n[i].isNum += 1;
					n[j].flag = 0;
					i--;
					break;
				}
				if(n[j].isNum == 1 && !strcmp(n[j].op2, "-") && !strcmp(n[i].op2, n[j].result)) {
					strcpy(n[i].op2, n[j].op1);
					n[i].isNum += 1;
					n[j].flag = 0;
					i--;
					break;
				}
			}
		}
	}
}

void local_copy_propagation(int index) {
	int i;
	for(i = index - 1; i >= 0; i--) {
		/* check if operand is modified
		 * case 1 : if a = b + c
		 *	       b = d + e
		 *	       e = b + c
		 *	  then e = b + c will remain as it is 
		 */	    
		if(strcmp(n[i].op2, "-")) {
			if(!strcmp(n[index].op1, n[i].result) || !strcmp(n[index].op2, n[i].result))
				break;
		}

		/*
		 * case 2 : a = b
		 * 	    tmp = a/c ----> tmp = b/c
		 */
		if(!strcmp(n[i].op2, "-")) {
			if(!strcmp(n[index].op1, n[i].result)) {
				strcpy(n[index].op1, n[i].op1);
				if(isNumber(n[i].op1))
					n[i].flag = 0;
			}
			if(!strcmp(n[index].op2, n[i].result)) {
				strcpy(n[index].op2, n[i].op1);
				if(isNumber(n[i].op1))
					n[i].flag = 0;
			} 
		}

		/*
		 * case 3 : a = b + c
		 *	    e = b + c -----> e = a
		 */
		else if(!strcmp(n[i].op, n[index].op) && !strcmp(n[i].op1, n[index].op1) && !strcmp(n[i].op2, n[index].op2)) {
			strcpy(n[index].op, "=");
			strcpy(n[index].op1, n[i].result);
			strcpy(n[index].op2, "-");
		}
	}
}

void eliminate_common_subexpression(int index) {
	int i, j;

	for(i = index; i > 0; i--) {
		for(j = i - 1; j >= 0; j --) {
			/*
			 * a = b + c
			 * b = a - d
			 * c = b + c
			 * then c = b + c should not be eliminated as b is modified
			 */
			if(strcmp(n[i].op2, "-")) {
				if(!strcmp(n[i].op1, n[j].result) || !strcmp(n[i].op1, n[j].result))
					break;
			}

			/* b = a - d
			 * c = b + c
			 * d = a - d
			 * then eliminate d = a - d as 'a' and 'd' are not modified
			 */
			if(!strcmp(n[i].op, n[j].op) && !strcmp(n[i].op1, n[j].op1) && !strcmp(n[i].op2, n[j].op2)) {
				n[i].flag = 0;
				if(!strcmp(n[j].op2, "-"))
					n[j].flag = 0;
			}
		}
	}
}

//display output
void print(int index) {
	int i, ind = 1;
	printf("Index\t\tResult\t\tOperand\t\tOperator1\tOperator2\n");
	for(i = 0; i <= index; i++) {
		if(n[i].flag) {
			printf("%d\t\t%s\t\t%s\t\t%s\t\t%s\n", ind, n[i].result, n[i].op, n[i].op1, n[i].op2); 
			ind ++;
		}
	}
}

int main() {
	char *s, str[40];
	size_t len = 0;
	ssize_t i = 0;
	int index = -1, j;

	FILE * fp = fopen("input.txt", "r");
	if(fp == NULL) {
		printf("Could not open file\n");
		return 0;
	}

	index = -1;
	printf("Intermediate Code :\nIndex\t\tResult\t\tOperand\t\tOperator1\tOperator2\n");
	while ((i = getline(&s, &len, fp)) != -1) {
		index ++;
		j = 0;
		while(s[j] != '\n') {
			str[j] = s[j];
			j++;
		}
		str[j] = '\0';
		insert_result(str, index);
    	}


	printf("\n\nEvaluating Constant Expression...\n");
	substitute_value(index);
	print(index);
	printf("\n\nAfter Local Copy Propogation...\n");
	for(i = 1; i <= index; i++)
		local_copy_propagation(i);
	print(index);

	printf("\n\nEliminating common expressions...\n");
	eliminate_common_subexpression(index);
	print(index);

	fclose(fp);

	if(s)
		free(s);

	return 0;
}
