#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"    /*needed for input*/
#include "parser.h"

//Tree * pp;
int position = 0;

char inputstring[250];

int * arsum ( int * m1, int * m2)
{
  int * arrayp;
  arrayp = (int *)malloc(sizeof(int) * 3 );
  int i;
  for (i = 0; i < 3; i++){ arrayp[i] = m1[i]+m2[i]; }
  return arrayp;
}

int * artimes ( int * m1, int * m2)
{
  int * arrayp;
  arrayp = (int *)malloc(sizeof(int) * 3 );
  int i;
//  for (i = 0; i < 3; i++){ arrayp[i] = m1[i]*m2[i]);}
for (i = 0; i < 3; i++){ arrayp[i] = (m1[i]*m2[i]);}

  return arrayp;
}

int * ardivide( int * m1, int * m2)
{// printf("\nIN ARDIV in ardiv\n");
  int * arrayp;
  arrayp = (int *)malloc(sizeof(int) * 3 );
  int i;
  for (i = 0; i < 3; i++){ arrayp[i] =m1[i]/m2[i];}
  return arrayp;
}



static int *  eval2(Tree * expr)
//Tree *expr;
  {
  int divisor;
  switch(TreeOper(expr))
    {
    case NumberToken: return((expr->u.arrayvalue));
//  case PlusToken: return(eval2(TreeLeft(expr)) + eval2(TreeRight(expr)));
    case PlusToken: return  arsum(eval2(TreeLeft(expr)), eval2(TreeRight(expr)));
    case TimesToken: return artimes(eval2(TreeLeft(expr)), eval2(TreeRight(expr)));
///////////////    case DivideToken: return ardivide(eval2(TreeLeft(expr)), eval2(TreeRight(expr)));
    case DivideToken: return ardivide(eval2(TreeLeft(expr)), eval2(TreeRight(expr)));


    default:  print_tree(expr);}
   //shouldnt reach
   printf("ERR");
    return NULL;
}



int is_alpha( int c) {
	/*
	 * Depends on ASCII-like character ordering.
	 */
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0);
}

int main(void) {
  /* rig input here */
  strcpy(inputstring, "1 2 3*4 5 6+7 8 9+100 101 102+500 501 502+1000 2000 3000.");
// strcpy(inputstring, "2 3 4+4 5 6 + 2 3 4.");

  printf(" %s\n", inputstring);
//  printf("ENTER ARITHMETIC EXPRESSION:\n");
Tree *  pp;
pp = parse_expr();
//  printf("\nPARSE TREE STRUCTURE:\n");
 // print_tree(pp);
//  printf("\nEXPRESSION EVALUATES TO:\n");
  //  printf("\n%d\n", eval(parse_expr()));
  //printf(" %d\n", eval(pp));
  //printf(" %d\n", eval2(pp));
  int * rabbit;
  rabbit = eval2(pp);
  printf("  %d %d %d \n", rabbit[0], rabbit[1], rabbit[2]);

  strcpy(inputstring, "2 3 4+4 5 6 * 2 3 4.");
  pp = parse_expr();
  rabbit = eval2(pp);
  printf(" %s\n", inputstring);
  printf("  %d %d %d \n", rabbit[0], rabbit[1], rabbit[2]);
//  print_tree(pp);

  strcpy(inputstring, "4 5 6 + 2 5 10 / 10 3 4.");
  pp = parse_expr();
 // print_tree(pp);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf(" %s\n", inputstring);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);

//strcpy(inputstring, "5 1 1 / 4 8 2 / 2 2 1.");
strcpy(inputstring, "4 5 6 * 2 5 10 + 10 3 4.");

//breaks    strcpy(inputstring, "2 2 1 / 1 3 4.");
  pp = parse_expr();
//  print_tree(pp);
  rabbit = eval2(pp);
  printf("%s\n", inputstring);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
strcpy(inputstring, "4 5 6 * 2 5 10 * 10 3 4.");

///breaks  strcpy(inputstring, "4 5 6 / 2 5 10 / 10 3 4.");
/////tooo looong
  //parses ok strcpy(inputstring, "5 10 15 + 4 8 12 / 2 2 1.");
  //////////////strcpy(inputstring, "5 10 15 / 4 8 12 / 2 2 1.");

  printf("%s\n", inputstring);

  pp = parse_expr();
//  print_tree(pp);
  pp = parse_expr();
  rabbit = eval2(pp);
  //printf("%s\n", inputstring);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
/////////////////////break it
//shatter
strcpy(inputstring, "2 3 4 * 2 4 6 / 2 2 1.");
//breaks
//  strcpy(inputstring, "4 5 6 + 2 5 10 / 10 3 4.");


  printf("%s\n", inputstring);

  pp = parse_expr();
//  print_tree(pp);
  pp = parse_expr();
  rabbit = eval2(pp);
  //printf("%s\n", inputstring);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
/* ALL divided on lefts fail  FAILS
strcpy(inputstring, "2 3 4 / 2 4 6 + 2 2 1.");
  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf("    %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
FAILS
strcpy(inputstring, "2 3 4 / 2 4 6 * 2 2 1.");
  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf(" %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
strcpy(inputstring, "2 3 4 / 2 4 6 / 2 2 1.");
  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf(" %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
FAILS
strcpy(inputstring, "2 3 4 / 2 4 6 / 2 2 1.");
  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf(" %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);
 all left divideds fail
*/

strcpy(inputstring, "2 3 4 * 2 4 6 / 2 2 1 + 3 2 1 + 1 2 3.");
  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);

strcpy(inputstring, "2 3 4 * 2 4 6 / 2 2 1 + 3 2 1 * 1 2 3.");

  printf("%s\n", inputstring);
  pp = parse_expr();
  rabbit = eval2(pp);
  printf("  %d %d %d \n ", rabbit[0], rabbit[1], rabbit[2]);

printf("ALL DONE\n");
while(1){};


} //while 1
