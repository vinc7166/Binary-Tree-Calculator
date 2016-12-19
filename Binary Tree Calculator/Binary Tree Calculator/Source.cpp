/*
Expression Tree
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>     
#include <string>
using namespace std;

struct TreeNode//The base information structure for a node in the expression tree.
{
	char data;//Holds a character.
	TreeNode *left, *right;//Holds data that points to child nodes.

	TreeNode(char data)		//Serves as a constructor for
	{						//each leaf in the tree.  The
		this->data = data;	//data is put into the data
		this->left = NULL;	//slot, and the left and
		this->right = NULL;	//right nodes are set to NULL.
	}
};

struct StackNode//The base information structure for a node in the ???
{
	TreeNode *treeNode;//Holds a pointer to a node in the tree.
	StackNode *next;//Holds a pointer to the next node in the stack.

	StackNode(TreeNode *treeNode)	//Serves as a constructor for
	{							//each node in the stack.
		this->treeNode = treeNode;	//Each node points to a node in
		next = NULL;				//the tree.
	}
};

class ExpressionTree
{
private:
	StackNode *top;//Holds a pointer to the top element of the tree.
public:
	ExpressionTree()	//This is a constructor for
	{				//the expression tree, which
		top = NULL;	//sets top to NULL.
	}

	~ExpressionTree()
	{
		deleteN(top);//Calls the deleteN function
	}

	void deleteN(StackNode *ptr)
	{
		if (ptr != NULL)			//This function will run through the entirety
		{						//of the stack and delete each node, which
			deleteN(ptr->next);		//will also delete each associated node in the
			delete ptr;			//tree.
		}
	}

	void pushed(TreeNode *ptr)			//This function will take a node that had been
	{								//placed into the expression tree and creates
		if (top == NULL)				//a copy of it into a stack.
			top = new StackNode(ptr);
		else
		{
			StackNode *nptr = new StackNode(ptr);
			nptr->next = top;
			top = nptr;
		}
	}

	TreeNode *popped()	//This function will take the top node of the stack
	{					//and return it.  It will also make the top pointer
		if (top == NULL)	//point to the next one in the stack.  If there is
		{				//no top, an error message will be outputed.
			cout << "Underflow" << endl;
		}
		else
		{
			TreeNode *ptr = top->treeNode;
			top = top->next;
			return ptr;
		}
	}

	TreeNode *peek()//This function grabs the top node of
	{				//the expression tree.
		return top->treeNode;
	}

	void construct(string eqn)						//This funciton takes a string
	{											//and calls the insert function
		for (int i = eqn.length() - 1; i >= 0; i--)	//one at a time to send one
			insert(eqn[i]);						//bit of the string in a for loop.
	}

	void insert(char val)						//This function takes a character and 
	{										//inserts it into the tree.  If it's 
		if (isdigit(val))						//an operand, the digit is placed into 
		{									//the expression tree, and then pusheded 
			TreeNode *nptr = new TreeNode(val);	//into the stack.  If it's an operator,
			pushed(nptr);						//then the first two nodes in the stack 
		}									//are called and are made the children
		else if (isOperator(val))				//of the operator; it is then finally
		{									//put into the stack.
			TreeNode *nptr = new TreeNode(val);
			nptr->left = popped();
			nptr->right = popped();
			pushed(nptr);
		}
		else
		{
			cout << "Invalid" << endl;
			return;
		}
	}

	bool isOperator(char ch)//This function checks to see if 
	{					  //the character is an operator.
		return ch == '+' || ch == '-' || ch == '*' || ch == '/';
	}

	int toDigit(char ch)//This function converts
	{				   //a char that's a digit 
		return ch - '0';//into an integer.
	}

	void fix(int choice)					//This function will call a function
	{										//based on a passed integer.  The
		if (choice == 1) { inOrder(peek()); }		//functions will either evaluate
		else if (choice == 2) { preOrder(peek()); }	//the function, or print the
		else if (choice == 3) { postOrder(peek()); }//funciton in one three ways.
		else if (choice == 4) { cout << evaluate(peek()) << endl; }
	}

	float evaluate(TreeNode *ptr)						//This funciton will evaluate
	{												//the tree.  If there is only
		if (ptr->left == NULL && ptr->right == NULL)		//a root, then the value in
		{										//the root will be returned.
			return toDigit(ptr->data);				//If not, then the function
		}										//will first evaluate the 
		else										//left side of the tree, then
		{											//the right, and finally the
			float result = 0.0;						//center of the tree.  When an
			float left = evaluate(ptr->left);				//operator is found in a tree,
			float right = evaluate(ptr->right);			//the two children (or the results
			char op = ptr->data;						//of the two children) are evaluated
			switch (op)								//based on the evaluator, which
			{										//is handeled with a switch statement.
			case '+':								//The result is then returned.
				result = left + right;
				break;
			case '-':
				result = left - right;
				break;
			case '*':
				result = left * right;
				break;
			case '/':
				result = left / right;
				break;
			default:
				result = left + right;
				break;
			}
			return result;
		}
	}

	void postOrder(TreeNode *ptr)
	{							//This funciton will 
		if (ptr != NULL)			//print the entire
		{						//expression tree in
			postOrder(ptr->left);	//post order format.
			postOrder(ptr->right);
			cout << ptr->data;
		}
	}

	void inOrder(TreeNode *ptr)
	{							//This function will
		if (ptr != NULL)			//print the entire
		{						//expression tree in
			inOrder(ptr->left);	//in order format.
			cout << ptr->data;
			inOrder(ptr->right);
		}
	}

	void preOrder(TreeNode *ptr)
	{							//This funciton will
		if (ptr != NULL)			//print the entire
		{						//expression tree in
			cout << ptr->data;		//post order format.
			preOrder(ptr->left);
			preOrder(ptr->right);
		}
	}
};

int main()
{
	ExpressionTree ET;//Creates an expression tree.
	string s;//Creates a string variable.
	cout << "Enter equation in Prefix form: ";
	cin >> s;
	ET.construct(s);//Calls the construct function
	cout << "Infix   : ";
	ET.fix(1);//Calls the fix function to call the infix function.
	cout << endl;
	cout << "Prefix  : ";
	ET.fix(2);//Calls the fix function to call the prefix function.
	cout << endl;
	cout << "Postfix : ";
	ET.fix(3);//Calls the fix function to call the postfix function.
	cout << endl;
	cout << "Evaluated Result : ";
	ET.fix(4);//Calls the fix function to call the evaluate function.
	return 0;
}




