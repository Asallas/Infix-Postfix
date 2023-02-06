/*
 * Name: Armando Sallas
 * Date Submitted: Feb 1, 2023
 * Lab Section: 005
 * Assignment Name: Infix to Postfix conversion
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Converts an infix arithmetic expression into postfix
//The function takes 3 parameters
//First parameter: array of strings for infix expression
//    each string is either an integer number or operator symbol
//Second parameter: number of strings in infix expression
//Third parameter: array of strings for postfix expression
//    generated by function, same format as first parameter
//    assumes that postfix is at least the size of postfix
//Return value: int, number of strings in postfix expression
//    Returns 0 if an error is encountered when converting expression
//    An error occurs with a mismatched parenthesis, e.g. ( ( ) or ( ) ) etc.
//Operator symbols:
// ( : left parenthesis, all operations between this and ")" take place first
// ) : right parenthesis, all op.s back to previous "(" take place first
// * : multiplication, higher precedence - takes place before "+" and "-"
// / : division, higher precedence - takes place before "+" and "-"
// % : remainder, higher precedence - takes place before "+" and "-"
// + : addition, lower precedence - takes place after "*" , "/" , "%"
// - : subtraction, lower precedence - takes place after "*" , "/" , "%"
//The function is not specified to work with any other operator symbols
//Any string in infix may be assumed to be an integer operand if none
// of the above symbols
int infixToPostfix(string infix[], int length, string postfix[])
{
    stack<string> operators;
    stack<string> parentheses;
    int count = 0;
    /*Runs through the infix array and adds left parentheses to stack and removes them
      if a right parentheses is found. If a right parentheses is found the funtion returns
      0 and if there is still a left parenteses left over the funcion returns 0
    */
    for (int i = 0; i < length; i++) {
        if (infix[i] == "(") {
            parentheses.push(infix[i]);
        }
        else if (infix[i] == ")") {
            if (parentheses.empty()) {
                return 0;
            }
            else if (parentheses.top() == "(") {
                parentheses.pop();
            }
        }
    }
    if (!parentheses.empty()) {
        return 0;
    }

    //Loops through infix to do the conversion
    for (int i = 0; i < length; i++) {
        //adds integers immedietly to the postfix array
        if (infix[i] >= "0" && infix[i] <= "9") {
            postfix[count] = infix[i];
            count++;
        }
        //Runs for when "*" "/" and "%" are found
        else if (infix[i] == "*" || infix[i] == "/" || infix[i] == "%") {
            //If the stack is empty, the operator is immediately added
            if (operators.empty()) {
                operators.push(infix[i]);
            }
            /*If a lower precedence operator is on top of the
            stack the current operator is added to the stack*/
            else if (operators.top() == "+" || operators.top() == "-") {
                operators.push(infix[i]);
            }
            /*If the same precendence operator is at the top of the class,
            then the top operator is added to post fix and the new one is added
            to the stack*/
            else if (operators.top() == "*" || operators.top() == "/" || operators.top() == "%") {
                postfix[count] = operators.top();
                operators.pop();
                count++;
                operators.push(infix[i]);
            }
            //Runs if there is a left perentheses at the top of the stack
            else {
                operators.push(infix[i]);
            }
        }
        //Runs when "+" and "-" are found
        else if (infix[i] == "+" || infix[i] == "-") {
            //Adds operator immedietly to the stack if it is empty
            if (operators.empty()) {
                operators.push(infix[i]);
            }
            //When a higher precedent operator is found at the top it is added to postfix
            //and the new operator is added to the stack
            else if (operators.top() == "*" || operators.top() == "/" || operators.top() == "%") {
                postfix[count] = operators.top();
                operators.pop();
                count++;
                //Checks for a simliar precedence operator that could have been before the higher 
                //precdence operator and adds it to postfix it if one is found
                if ((operators.size() >= 1) && (operators.top() == "+" || operators.top() == "-")) {
                    postfix[count] = operators.top();
                    operators.pop();
                    count++;
                }
                operators.push(infix[i]);
            }
            //If there is a similar precedence operator then it is added to postfix and the new one
            //is added to the stack
            else if (operators.top() == "+" || operators.top() == "-") {
                postfix[count] = operators.top();
                operators.pop();
                operators.push(infix[i]);
                count++;
            }
            //Runs when a left perentheses is at the top of the stack
            else {
                operators.push(infix[i]);
            }

        }
        //Immedietly adds the left perentheses to the stack
        else if (infix[i] == "(") {
            operators.push(infix[i]);
        }
        //When a right perentheses is found, every operator left after the left
        //perentheses is added to postfix and then the left pernetheses is removed
        else if (infix[i] == ")") {
            while (operators.top() != "(") {
                postfix[count] = operators.top();
                count++;
                operators.pop();
            }
            if (operators.top() == "(") {
                operators.pop();
            }
        }
    }
    //Empties the remaining operators left in the stack and adds them to postfix
    while (!operators.empty()) {
        postfix[count] = operators.top();
        count++;
        operators.pop();
    }
    return count;
}
