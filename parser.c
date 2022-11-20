/*parser.c
  This recursive-descent parser for arithmetic expressions is part of the term
  project for the MIT SIPB Crash Course in C for IAP 1999.  Copyright (c) 1998
  Matthew Belmonte.*/

/*There is, in general, one parsing function for each nonterminal symbol in the
  grammar.  Refer to the grammar (or syntax chart) to understand how these
  routines interact with each other.  Some regions of the code are commented
  very lightly, because their structure and function follow from the grammar.
 -There are two important and related invariant conditions over all these
  parsing functions.  On entry, the first token in the phrase about to be
  parsed is in 'token'.  On exit, the token immediately following the
  last token in the expression just parsed is in 'token' (except in the
  case of parse_program, where, if all is well, there is nothing following the
  '.').  To maintain these invariants, it is necessary to keep track of tokens
  that delimit expressions and to eat them where appropriate.
 -In other words, each parsing function assumes that the input stream of tokens
  has been prepared for it, and it in turn prepares the input stream for
  whatever parsing function may be called next.*/

#include "scanner.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
//#include <errno.h>

/*Build an internal tree node, which contains an operator and points to two
  subtrees.*/
static Tree *NewTree(Token op, Tree * left,Tree * right)
//Token op;
//Tree *left, *right;
  {
  Tree *new_tree;
  new_tree = (Tree *)malloc(sizeof(*new_tree));
  if(new_tree == (Tree *)0)		/*out of memory?*/
    {
//    perror((char *)0);
//    exit(errno);
      exit(1);
    }
  TreeOper(new_tree) = op;
  TreeLeft(new_tree) = left;
  TreeRight(new_tree) = right;
  return(new_tree);
  }

Tree * pp;
/*Build a new leaf, which contains an operator of NumberToken, and a number.*/
static Tree *NewLeaf(int value, int * array)
//int value;
  {
  Tree *new_tree;
  new_tree = (Tree *)malloc(sizeof(*new_tree));
  if(new_tree == (Tree *)0)		/*out of memory?*/
    {
//    perror((char *)0);
//   exit(errno);
      exit(1);

    }
  TreeOper(new_tree) = NumberToken;
  TreeValue(new_tree) = number;
  new_tree->u.value = number;
  new_tree->u.arrayvalue = array;
//printf("ARRAY %d NEWLEAF ARRAY %d ",array, new_tree->u.arrayvalue);

//printf("ARRAY ADDRESS = %d ", array);
//printf("NEW_TREE->U.ARRAYVALUE ADDRESS = %d ", new_tree->u.arrayvalue);

  return new_tree;
  }

static Tree *parse_leaf()
  {
  Tree *ptr;
  ptr = NewLeaf(number, array);
  next_token(); return(ptr);
  }

/*Parse a list of expressions, for example factors separated by multiplication
  and division operators or terms separated by addition and subtraction
  operators.  'parsing_fn' is the parsing function for the expressions that
  comprise the list, and 'op0' and 'op1' are the operators that separate those
  expressions within the list.*/
static Tree *parse_expressions(Tree *(*parsing_fn)(),Token op0,Token op1)
//Tree *(*parsing_fn)();
//Token op0, op1;
  {
  Tree *left_tree, *tree;
//   printf("IN PARSING FN  ");
  left_tree = (*parsing_fn)();
 //  printf("LEFT TREE WAS ASSIGNED  ");
/*invariant: 'left_tree' points to the root of a parse tree that represents all
  the tokens in the expression that are to the left of 'token'.*/
/*bound: the number of expressions that remain to be parsed*/
  while((token == op0) || (token == op1))
    { //printf("GOT POST OP0 OR OP1  ");
    tree = NewTree(token, left_tree, NULLTREE);
       //printf("GOT POST NEWTREE  ");
    next_token();
       //printf("GOT POST NEXTTOKEN  ");
    TreeRight(tree) = (*parsing_fn)();
       //printf("GOT POST TREERIGHT  ");
    left_tree = tree;

        //     printf("GOT POST LEFTTREE ");
    }
//  printf("LEAVING PARSING_FN \n");
  return(left_tree);
  }

static Tree *parse_arith_expr();

static Tree *parse_factor()
  {
  Tree *factor;
  if(token == LeftParenToken)
    {
    next_token();			/*eat the '('*/
    factor = parse_arith_expr();
    if(token != RightParenToken)
      {
      printf("EXPTECTED \")\" IN FACTOR BUT FOUND ");
      print_token(token);
      printf("\n");
      while(1){};exit(1);  //stop dont exit
      }
    next_token();			/*eat the ')'*/
    return(factor);
    }
  else if(token == NumberToken)
    return(parse_leaf());
  else
    {
    printf("UNEPECTED FACTOR");
    print_token(token);
    printf("\n");
while(1){}; //stop dont exit
    exit(1);
    }
  }

static Tree *parse_term()
  { //printf("IN PARSE_TERM");
  return(parse_expressions(&parse_factor, TimesToken, DivideToken));
  }

static Tree *parse_arith_expr()
  { //printf("IN PARSE_ARITH_EXPR");
  return(parse_expressions(&parse_term, PlusToken, MinusToken));
  }

/*This is the top-level parsing function.*/
Tree *parse_expr()
  {
int i,k;
  Tree *expr;
//printf("INITSCANNER\n");
  init_scanner();
//printf("NEXTTOKEN\n");

  next_token();
//printf("EXPR=PARSEAIRTHEXP\n");
  expr = parse_arith_expr();
//printf("PARSED");
//printf("PARSEDOK");

/////while(1){};

  if(token != PeriodToken)
    {
    printf("UNEXPECTED TOKEN AT END OF INPUT: ");
//      while(1){};
    print_token(token);
    printf("WHILE1\n");
    while(1){};exit(1);
    }
//  printf("RETURN EXPR "); 
  return(expr);
  }

/*print an indented subtree - used by print_tree() below*/
static void print_subtree(Tree * t,int indent)
//Tree *t;
//int indent;
  {
//  register int spaces;
int spaces;

/*invariant: all nodes to the left of 't' have been printed*/
  while(TreeOper(t) != NumberToken)
    {
    for(spaces = 0; spaces != indent; spaces++)
      putchar(' ');
    print_token(TreeOper(t));
    putchar('\n');
    print_subtree(TreeLeft(t), 2+indent);
    indent += 2;
    t = TreeRight(t);
    }
  for(spaces = 0; spaces != indent; spaces++)
    putchar(' ');
////////////  printf(" %d ", TreeValue(t));
//printf(" %d %d %d ARRAY ADR %d \n", t->u.arrayvalue[0],t->u.arrayvalue[1],  t->u.arrayvalue[2], t->u.arrayvalue);
printf(" %d %d %d \n", t->u.arrayvalue[0],t->u.arrayvalue[1],  t->u.arrayvalue[2]);

  }

/*print the contents of a tree - useful for debugging*/
void print_tree(Tree * t)
//Tree *t;
  {
  putchar('\n');
   print_subtree(t, 0);
  }
