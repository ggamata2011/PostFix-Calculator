#include <iostream>
#include <stack>
//for use of getline, also to convert a string to a c string, along with .length
#include <string>
//for use of atof
#include <stdlib.h>
//for use of isdigit, can probably use it to see if it is not a number
#include <cctype>
//for use of strtok
#include <cstring>
//for use of pow
#include <cmath>
//use of exceptions
#include <stdexcept>

using namespace std;
bool isbinaryOp(char *op);

int main()
{
  // holds expression, used a string so I can make the expression as big as I want
   string inputline;
   char *postfix;
   char *token;

  stack<double> MainStack;
  //variable to hold
  double value;
  //left handside and right hand operands
  double left;
  double right;

  cout << "\n\nEnter a Postfix Expression:";
  getline(cin,inputline);

  //creating cstring
  postfix = new char[inputline.length()];

  //input line string to c-string
  for(int i = 0;i < inputline.length();i++)
  {
     postfix[i] = inputline[i];

  }
  //adding null terminating character
  postfix[inputline.length()] = '\0';

  //tokenizing cstring, point of this is so I can get numbers that arent single digits
  token = strtok(postfix," ");


  //should be only one left in the expression or else is a malformed expression
  // probably throw an exception if stack is empty or there is still one more value
  // maybe keep a count of values in stack, or getsize

  try{

  while(token!= NULL)
  {
      //If we encounter a binary operator and we dont have enough operands, throw exception
      if(isbinaryOp(token) && MainStack.size() < 2)
      {
          throw logic_error("\nNot Enough operands to work with");
      }

     if(*token == '+' && MainStack.size() >= 2 )
     {
       right= MainStack.top();
       MainStack.pop();
       left = MainStack.top();
       MainStack.pop();
       MainStack.push(left+right);
     }
     if(*token == '-'&& MainStack.size() >= 2)
     {
       right = MainStack.top();
       MainStack.pop();
       left = MainStack.top();
       MainStack.pop();
       MainStack.push(left-right);
     }
     if(*token == '*'&& MainStack.size() >= 2)
     {
       right = MainStack.top();
       MainStack.pop();
       left = MainStack.top();
       MainStack.pop();
       MainStack.push(left*right);
     }
     //CANNOT DIVIDE BY ZERO
     if(*token == '/'&& MainStack.size() >= 2)
     {
       right = MainStack.top();
       MainStack.pop();
       if(right == 0)
       {
           throw logic_error("\nCannot Divide by 0");
       }
       left = MainStack.top();
       MainStack.pop();
       MainStack.push(left/right);
     }

     //can use a for loop of some sort
     if(*token == 'S')
     {
        int countsum = MainStack.top();
        MainStack.pop();
        double sum = 0;

        for(int i = 0;i < countsum;i++)
        {
            if(MainStack.empty())
            {
              throw logic_error("\nNot enough Operands");
            }
            sum = sum + MainStack.top();
            MainStack.pop();

        }
       MainStack.push(sum);

     }
     // change num to additive opposite
      if(*token == '~')
     {
       if(MainStack.empty())
       {
           throw logic_error("\nNo Operand to work with");
       }

       double opp = MainStack.top();
       MainStack.pop();
       opp = opp* (-1);
       MainStack.push(opp);
     }

     //pop, multiply, pop
     if(*token == '!')
     {
       if(MainStack.empty())
       {
           throw logic_error("\nNo Operand to work with");
       }

       double fact = MainStack.top();
       MainStack.pop();
       //iterative factorial
       for(int i = fact-1;i >= 1;i--)
       {
           fact = fact*i;
       }
       MainStack.push(fact);

     }
     //if NaN or infinity, throw exception
     if(*token == '^'&& MainStack.size() >= 2)
     {
       right = MainStack.top();
       MainStack.pop();
       left = MainStack.top();
       MainStack.pop();
       MainStack.push(pow(left,right));
     }

     //average, divide sum by k, cannot divide sum by 0
      if(*token == '$')
     {
       int countsum = MainStack.top();
        MainStack.pop();
        double sum = 0;

        if(countsum == 0)
        {
             throw logic_error("\nCannot Divide by 0");
        }

        for(int i = 0;i < countsum;i++)
        {
            if(MainStack.empty())
            {
               throw logic_error("\nNot enough Operands");
            }
            sum = sum + MainStack.top();
            MainStack.pop();

        }
        //getting average
       sum = sum/countsum;
       MainStack.push(sum);
     }

     //If token is a digit, will convert to digit and push onto stack
     if(isdigit(*token))
     {
     value = atof(token);
     //cout << "\n" << value;
     MainStack.push(value);
     }

     token = strtok(NULL," ");


  }

  if(MainStack.size() == 1)
  {
  cout << "\n\nAnswer:" << MainStack.top();
  }
  else
  {
      throw logic_error("\nStack has more than one item, malformed expression");
  }


  }
  catch(const exception &what_arg)
  {
    cout << what_arg.what();
  }

return 0;
}


bool isbinaryOp(char *op)
{
    if(*op == '+')
     {
       return true;
     }
     if(*op == '-')
     {
       return true;
     }
     if(*op == '*')
     {
       return true;
     }
     //CANNOT DIVIDE BY ZERO
     if(*op == '/')
     {
       return true;
     }
     //if NaN or infinity, throw exception
     if(*op == '^')
     {
       return true;
     }

return false;
}
