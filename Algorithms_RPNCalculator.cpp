/*
/	Written by Ricardo Williams II								/
/	Reverse Poilish Notation Calulator							/			
/	ID: 1043326													/
/	Description: This program uses post fix notation to add,	/
/	multiply and divide input values from the user				/
																*/

#include<string>
#include<iostream>
#include<iomanip>
#include <sstream> 
using namespace std;

class Node
{
public:
	double input;   //Our data that will be updated per node
	Node* next; //connection to next node
	Node(double d);
	Node::Node()
	{
	}
};
Node::Node(double data) {  //constructor to convert int to node data type
	input = data;

}
class LinkedStack {
public:
	Node * top;
	LinkedStack()
	{
		top = 0;
	}
	bool isEmpty()
	{
		return top == 0;
	}
	double count = 0;
	void Push(double inp);
	void Pop();
	void Print();
	void Operate(string s);
};

void LinkedStack::Push(double inp)  //accepting input data from the user
{
	Node * temp = new Node(inp);
	if (isEmpty())
		top = temp;
	else {
		temp->next = top;
		top = temp;
	}
}

void LinkedStack::Pop()
{
	if (isEmpty()) //if Stack is empty zero is returned and following code executes
		cout << "Err: The stack is empty" << endl;
	else  // if not empty following code executes
	{
		Node * temp = top; // create temporary variable 
		top = top->next;   // top now set to previous next pointer
		delete temp;       // clean up
	}
}
void LinkedStack::Print()
{
	cout << top->input << endl;;
}

void LinkedStack::Operate(string s) {
	double count = 0.0, ans =0.0;
	double oper1 = top->input;
	Pop();

	if(s == "+" && top != NULL) //this part essentially checks every pass if the input value is an operator
	{				//If it is it then adds to the count of operators which gets checked at the end to see if it less than the amount of operands
		ans = oper1 + top->input;
		Pop();
		Push(ans);
	}
	if(s == "-" && top != NULL)
	{
		ans = top->input - oper1;
		Pop();
		Push(ans);
	}
	if(s == "*" && top != NULL)
	{
		ans = oper1 * top->input;
		Pop();
		Push(ans);
	}
	if(s == "/" && top != NULL) //if the operator is a division sign it goes in to check if the denominator will be a zero
	{ // if it is, it continues
		if (oper1 == 0) {
	cout << "Err you can not divide by zero, nice try" << endl;
		}
	else if(top != NULL) {
			ans = top->input / oper1;
			Pop();
			Push(ans);
		}
	}
}

int Check(int ran, int rate) {
	if (rate >= ran)
	{
		cout << "operands:" << ran << " operators:" << rate << endl;
		cout << "Err: Too many operators" << endl;
		return -1;
	}
	if (ran >= (2+rate) )
	{
		cout << "Err: Too many operands" << endl;
		cout << "operands:" << ran << " operators:" << rate << endl;
		return -1;
	}
}
int main()
{
	string line ;
	double input = 0.1;
	int operators = 0, operands = 0, retu = 0;
	LinkedStack link;
	bool ran = false;
	cout << "Welcome to the Reverse Polish Calculator" << endl;
	cout << "Please enter the operands followed by the operator \nPLEASE enter a space after the equal sign e.g. '34 5 * 12 - = '" << endl;
	cout << "Enter 0\s to exit" << endl;
		do {
		while (line != "\n0") {
			getline(cin, line, ' '); //find a place for the check to run before the operate gets called
			if (line == "\n0") // it is creating a null ptr when being called after an operation has been alread performed
				break;
			if (line == "=")
				break;
			if (line == "+") {
				link.Operate("+");
				operators++;
			}
			else if (line == "-") {
				link.Operate("-");
				operators++;
			}
			else if (line == "*") {
				link.Operate("*");
				operators++;
			}
			else if (line == "/") {
				link.Operate("/");
				operators++;
			}
			else {
				input = stod(line);
				link.Push(input);
				operands++;
			}
		}
		retu = Check(operands, operators);
		if( retu != -1 && line != "\n0"){
		link.Print();
		link.Pop(); //possibly pop off all of the stack to clear to clear memory 
		cin.clear();
		}

			operands = 0;
			operators = 0;
			ran = true;
		} while (line != "\n0");
	cout << "Thank you! Goodbye" << endl;
	system("pause");
	}

/*Output:
Welcome to the Reverse Polish Calculator
Please enter the operands followed by the operator
PLEASE enter a space after the equal sign e.g. '34 5 * 12 - = '
Enter 0s to exit
10 15 + =
25
10 15 - =
-5
2.5 3.5 + =
6
10 0 / =
Err you can not divide by zero, nice try
10
10 20 * / =
operands:2 operators:2
Err: Too many operators
12 20 30 / =
Err: Too many operands
operands:3 operators:1
-10 -30 - =
20
100 10 50 25 / * - -2 / =
-40
0
operands:0 operators:0
Err: Too many operators
Thank you! Goodbye
Press any key to continue . . .

*/