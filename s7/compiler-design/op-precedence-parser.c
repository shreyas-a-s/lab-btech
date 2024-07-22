// OPERATOR PRECEDENCE PARSER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isoperator(char op) {
  if ((op=='+') || (op=='-') || (op=='*') || (op=='/') || (op=='^') || (op=='%'))
    return 0;
  else
    return 1;
}

void main() {
  char stack[20], ip[20], opt[20][10][1], ter[10];
  int i, j, k, n, top=0, col, row;
  for (i=0; i<10; i++) {
    stack[i]=NULL;
    ip[i]=NULL;
    for (j=0; j<10; j++)
      opt[i][j][1] = NULL;
  }

  printf("Enter the no of terminals\n");
  scanf("%d", &n);
  printf("Enter the terminals\n");
  scanf("%s", ter);
  printf("Enter the table value\n");
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      printf("Enter the value for %c%c:", ter[i], ter[j]);
      scanf("%s", opt[i][j]);
    }
  }

  printf("\nOPERATOR PRECEDENCE TABLE:\n");
  for (i=0; i<n; i++) {
    printf("\t%c", ter[i]);
  }
  printf("\n");

  for (i=0; i<n; i++) {
    printf("\n%c", ter[i]);
    for (j=0; j<n; j++) {
      printf("\t%c", opt[i][j][0]);
    }
    printf("\n");
  }

  do {
    top=-1;
    stack[++top]='$';

    printf("\nEnter the input string\n");
    scanf("%s", ip);
    i = 0;

    printf("\nSTACK\t\t\tINPUT STRING\t\t\tACTION\n");
    printf("\n%s\t\t\t%s\t\t\t", stack, ip);
    while (i<=strlen(ip)) {
      if ((isoperator(ip[i])==0) && (isoperator(ip[i+1])==0)) {
        printf("ERROR");
        break;
      }

      for (k=0; k<n; k++) {
        if(stack[top]==ter[k])
          col=k;
        if (ip[i]==ter[k])
          row=k;
      }

      if ((stack[top]=='$') && (ip[i]=='$')) {
        printf("Accepted");
        printf("\nString is Accepted");
        break;
      }
      else if ((opt[col][row][0]=='<') || (opt[col][row][0]=='=')) {
        stack[++top] = opt[col][row][0];
        stack[++top] = ip[i];
        printf("shift %c", ip[i]);
        printf("\n");
        i++;
      }
      else {
        if (opt[col][row][0]=='>') {
          while (stack[top]!='<') {
            --top;
          }
          top=top-1;
          printf("Reduce\n");
        }
        else {
          printf("\nString is not accepted");
          break;
        }
      }
      printf("\n");

      for (k=0; k<=top; k++) {
        printf("%c", stack[k]);
      }
      printf("\t\t\t");
      for (k=i; k<strlen(ip); k++) {
        printf("%c", ip[k]);
      }
      printf("\t\t\t");
    }
    printf("\nDo you want to continue(yes: Enter 1, no: enter 0)\n");
    scanf("%d", &i);
  }
  while(i==1);
}

/*OUTPUT
Enter the no of terminals
4
Enter the terminals
i+*$
Enter the table value
Enter the value for ii:A
Enter the value for i+:>
Enter the value for i*:>
Enter the value for i$:>
Enter the value for +i:<
Enter the value for ++:>
Enter the value for +*:<
Enter the value for +$:>
Enter the value for *i:<
Enter the value for *+:>
Enter the value for **:>
Enter the value for *$:>
Enter the value for $i:<
Enter the value for $+:<
Enter the value for $*:<
Enter the value for $$:A

OPERATOR PRECEDENCE TABLE:
	i	+	*	$

i	A	>	>	>

+	<	>	<	>

*	<	>	>	>

$	<	<	<	A

Enter the input string
i+i*i$

STACK			INPUT STRING			ACTION

$			i+i*i$			shift i

$<i			+i*i$			Reduce

$			+i*i$			shift +

$<+			i*i$			shift i

$<+<i			*i$			Reduce

$<+			*i$			shift *

$<+<*			i$			shift i

$<+<*<i			$			Reduce

$<+<*			$			Reduce

$<+			$			Reduce

$			$			Accepted
String is Accepted
Do you want to continue(yes: Enter 1, no: enter 0)
1

Enter the input string
i++i$

STACK			INPUT STRING			ACTION

$<+<*<i			i++i$			shift i

$<i			++i$			ERROR
Do you want to continue(yes: Enter 1, no: enter 0)
1

Enter the input string
i+*i$

STACK			INPUT STRING			ACTION

$<i<*<i			i+*i$			shift i

$<i			+*i$			ERROR
Do you want to continue(yes: Enter 1, no: enter 0)
0
*/
