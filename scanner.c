/*scanner.c
  This lexical scanner for arithmetic expressions is part of the term project
  for the MIT SIPB Crash Course in C for IAP 1999.  Copyright (c) 1998 Matthew
  Belmonte.*/

#include "scanner.h"
//#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
extern char inputstring[250];
extern int position;
int is_space( int c) {
        /*
         * Depends on ASCII-like character ordering.
         */
        return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int isdigit( int c) {
        /*
         * Depends on ASCII-like character ordering.
         */
        return ((c >= 48  && c <= 57) ? 1 : 0);
}

static char current_char;		/*next character to be scanned*/
Token token;				/*the token most recently scanned*/
int number;				/*if token==NumberToken, here's the #*/
int * array; /****/
int arraylength = 1;
static char next_char()			/*all input comes through here*/
  {
//  current_char = getchar();
   current_char = inputstring[position]; position++;
  }

/*sets the token type and gets the next character*/
static void make_token(Token t)
//Token t;
  {
  next_char();
  token = t;
  }

/*On entry, 'current_char' is a digit.  Set the global variable 'number' to
  the integer represented by the string of digits, and set the global
  variable 'token' to NumberToken.*/
/* add storage of the scalar into a 1 element array for apl */
static void string_to_number()
  {
  token = NumberToken;
  int arrayindex = 0;
  array = malloc (sizeof (int) * 3);

/* loop here to do entire array */
  while(isdigit(current_char) || current_char == ' ')
  { 
  number = 0;
/*invariant: The portion of the digit string that is to the left of the
  position of 'current_char' is the base-ten representation of 'number'.
  (For ease of specification, define the null string as a valid base-ten
  representation of the integer 0.)*/
/*In other, less declarative words, 'number' is accumulating the
  digits by place value.*/
/*bound: the number of digits that remain to be processed*/
  do
    {
    if (isdigit( current_char)) number = 10*number + (current_char - '0');
   /* printf("IN NUMBER = %d ", number); */
    next_char();
    } while(isdigit(current_char));

/* add for apl*/

/* do first for now dont loop it  array = malloc (sizeof (int) * 3); */

/*    array[0] = number;   */
/////////////this is a hack to debug  needs fixing
  if (arrayindex <= 2)  array[arrayindex] = number;
////DEBUG    printf("ARRAY[%d] = NUMBER %d", arrayindex, number);  
    arrayindex++;


  }
///printf("LEAVING %d %d %d", array[0], array[1],array[2]);  
  }


/*initialise the scanner by loading the first character*/
void init_scanner()
  {
position=0;  next_char();
  }
/*top-level scanner function*/
void next_token()
  {
///  printf("IN NEXT_TOKEN ");
  while(is_space(current_char))
    next_char();			/*skip blanks*/
  if(isdigit(current_char))
    string_to_number();
  else switch(current_char)
    {
    case '+': make_token(PlusToken); break;
    case '-': make_token(MinusToken); break;
    case '*': make_token(TimesToken); break;
    case '/': make_token(DivideToken); break;
//    case '\xA3': make_token(DivideToken); break; //hex A3
//    case 163: make_token(DivideToken); break; //hex A3

    case '(': make_token(LeftParenToken); break;
    case ')': make_token(RightParenToken); break;
    case '.': token = PeriodToken; break; /*don't wait for more input*/
    default: printf("ILLEGAL CHAR %c (HEX %x)\n", current_char, current_char);
    }
  }

/*print the type and value of the token - useful in debugging*/
void print_token(Token t)
//Token t;
  {
  switch(t)
    {
    case NumberToken: printf(" %d", number); /* break; */
              printf(" %d %d %d ", array[0], array[1],array[2] ); break;

    case PlusToken:  putchar(' '); putchar('+'); break;
    case MinusToken: putchar(' ');putchar('-'); break;
    case TimesToken: putchar(' ');putchar('*'); break;
    case DivideToken: putchar(' '); putchar('/'); break;
    case LeftParenToken: putchar(' '); putchar('('); break;
    case RightParenToken: putchar(' ');putchar(')'); break;
    case PeriodToken: putchar(' ');putchar('.'); break;
    default: printf("UNDEFINED TOKEN%d", (int)t);
    }
  }



