#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include "Node.h"
#include "Stack.h"
using namespace std;


int OpPrecedence(char c) {
    if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int main()
{

    while (1)//while loop that keeps on repeating until program is exited
    {
        string input;
        string postfix;
        Stack<char>operators;
        Stack<int>eval;


        cout << "Enter expression (or exit to end):" << endl;
        getline(cin, input);

        if (isdigit(input.at(0)) || input.at(0) == 'e' || input.at(0) == '(')//compare the first item in the stack to a number or '(' or exit
        {
            if (input == "exit") { //if it is "exit" then exit the program
                cout << "Exiting program ...";
                return 0;
            }
            cout << "Expression: " << input << endl;//output the normal expression given

            for (unsigned int i = 0; i < input.length(); i++)
            {

                char c = input.at(i);
                if (c == ' ')
                    continue;
                else if (c == '(')
                {
                    operators.push(c);
                }
                else if (c == ')')
                {
                    while (operators.getTop() != '(')
                    {
                        postfix += (operators.getTop());
                        operators.pop();
                        postfix += ' ';
                    }
                    operators.pop();
                }
                else if (c == '/' || c == '*' || c == '+' || c == '-')
                {
                    while (!(operators.empty()) && OpPrecedence(operators.getTop()) > OpPrecedence(c))
                    {
                        postfix += (operators.getTop());
                        operators.pop();
                        postfix += ' ';

                    }

                    operators.push(c);
                }
                else // number
                {
                    postfix += c;
                    postfix += " ";

                }
            }

            while (!operators.empty())
            {
                postfix += (operators.getTop());
                operators.pop();
                postfix += ' ';
            }
            cout << "Postfix form: " << postfix << endl;//Postfix form

            for (auto& c : postfix)
            {

                if (c == ' ')
                    continue;

                else if (c == '/' || c == '*' || c == '+' || c == '-')
                {
                    int b = eval.getTop();
                    eval.pop();
                    int a = eval.getTop();
                    eval.pop();
                    if (c == '+') {
                        eval.push(a + b);
                    }
                    if (c == '-') {
                        eval.push(a - b);
                    }
                    if (c == '*') {
                        eval.push(a * b);
                    }
                    if (c == '/') {
                        eval.push(a / b);
                    }
                }
                else // number
                    eval.push(c - '0');
            }

            cout << "Result: " << eval.getTop() << endl;//output the result of the expression

        }
        else {
            cout << "Invalid expression" << endl;
        }
    }
    return 0;
}