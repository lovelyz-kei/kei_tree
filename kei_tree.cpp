#include <iostream>		//cout
#include <queue>		//queue
#include <math.h>		//log
#define NODE_NUM 10		//# of nodes
using namespace std;

class Node {
private:
	int value;			//value of node
	bool isNull;		//whether the node is null logically
	Node* leftChild;
	Node* rightChild;
public:
	//constructor
	Node() {
		value = -1;
		isNull = false;
		leftChild = NULL;
		rightChild = NULL;
	}

	//destructor
	~Node() {
		delete leftChild;
		delete rightChild;
	}

	//getter
	int getValue() { return value; }
	bool getIsNull() { return isNull; }
	Node* getLeftChild() { return leftChild; }
	Node* getRightChild() { return rightChild; }

	//setter
	void setValue(int value) { this->value = value; }
	void setIsNull(bool isNull) { this->isNull = isNull; }
	void setLeftChild(Node* leftChild) { this->leftChild = leftChild; }
	void setRightChild(Node* rightChild) { this->rightChild = rightChild; }
};

//* function prototype
//get the max depth of tree
int findMaxDepth(Node* parent, int currDepth);

//fill the vacancies with logical null nodes
void fillNullNodes(Node* parent, int maxDepth, int currDepth);

//get n^i
int power(int n, int i);

//print tree
void printTree(Node* root, int maxDepth);

int main() {
	//initialize nodes
	Node** nodes = new Node*[NODE_NUM];

	for(int i=0;i<NODE_NUM;i++) {
		nodes[i] = new Node;
		nodes[i]->setValue(i);
	}

	//you can change the test case number
	int testCaseNum = 1;

	if(testCaseNum == 1) {
		//test case 1
		nodes[0]->setLeftChild(nodes[1]);
		nodes[0]->setRightChild(nodes[5]);
		nodes[1]->setLeftChild(nodes[2]);       
		nodes[1]->setRightChild(nodes[3]);
		nodes[5]->setRightChild(nodes[6]);
		nodes[3]->setLeftChild(nodes[4]);
		nodes[6]->setLeftChild(nodes[7]);
		nodes[7]->setLeftChild(nodes[8]);
		nodes[7]->setRightChild(nodes[9]);
	} else if(testCaseNum == 2) {
		//test case 2
		nodes[0]->setLeftChild(nodes[1]);
		nodes[0]->setRightChild(nodes[2]);
		nodes[1]->setLeftChild(nodes[3]);
		nodes[1]->setRightChild(nodes[4]);
		nodes[2]->setLeftChild(nodes[5]);
		nodes[2]->setRightChild(nodes[6]);
		nodes[3]->setLeftChild(nodes[7]);
		nodes[3]->setRightChild(nodes[8]);
		nodes[4]->setLeftChild(nodes[9]);
	} else if(testCaseNum == 3) {
		//test case 3 : skewed tree
		nodes[0]->setRightChild(nodes[1]);
		nodes[1]->setRightChild(nodes[2]);
		nodes[2]->setRightChild(nodes[3]);
		nodes[3]->setRightChild(nodes[4]);
	}

	//get the max depth of tree
	//nodes[0] is root node
	int maxDepth = findMaxDepth(nodes[0], 0);

	//fill the vacancies with logical null nodes
	fillNullNodes(nodes[0], maxDepth, 0);

	//print tree
	printTree(nodes[0], maxDepth);

	delete [] nodes;

	return 0;
}

/*
get the max depth of tree recursively
parent : parent node pointer
currDepth : current depth
*/
int findMaxDepth(Node* parent, int currDepth) {
	int leftMaxDepth, rightMaxDepth;

	leftMaxDepth = rightMaxDepth = currDepth;

	if(parent->getLeftChild() == NULL && parent->getRightChild() == NULL) {
		return currDepth;
	}

	if(parent->getLeftChild() != NULL) {
		leftMaxDepth = findMaxDepth(parent->getLeftChild(), currDepth + 1);
	}

	if(parent->getRightChild() != NULL) {
		rightMaxDepth = findMaxDepth(parent->getRightChild(), currDepth + 1);
	}

	if(leftMaxDepth > rightMaxDepth) {
		return leftMaxDepth;
	} else {
		return rightMaxDepth;
	}
}

/*
fill the vacancies with logical null nodes recursively
parent : parent node
maxDepth : the max depth of tree
currDepth : current depth
*/
void fillNullNodes(Node* parent, int maxDepth, int currDepth) {
	//if the current depth is max depth, you don't need to make logical null nodes anymore
	if(currDepth == maxDepth) {
		return;
	}

	//add a logical null node for left child
	if(parent->getLeftChild() == NULL) {
		Node* leftChild = new Node;
		leftChild->setIsNull(true);
		parent->setLeftChild(leftChild);
	}

	fillNullNodes(parent->getLeftChild(), maxDepth, currDepth + 1);

	//add a logical null node for right child
	if(parent->getRightChild() == NULL) {
		Node* rightChild = new Node;
		rightChild->setIsNull(true);
		parent->setRightChild(rightChild);
	}

	fillNullNodes(parent->getRightChild(), maxDepth, currDepth + 1);
}

/*
get n^i
*/
int power(int n, int i) {
	int result = 1;
	for(int j=0;j<i;j++) {
		result *= n;
	}

	return result;
}

/*
print tree by breadth first search
root : root node pointer
maxDepth : the max depth of tree
*/
void printTree(Node* root, int maxDepth) {
	int idx = 0;			//to count the index of node in tree
	int initLineIdx = 1;	//to decide if the node is in the beginning of the line

	//queue for breadth first search
	queue<Node*> queueForBfs;

	//start with root node
	queueForBfs.push(root);
	
	//while statement until queue is empty
	while(!(queueForBfs.empty())) {
		//to get the level of nodes
		//idx = 0 -> level = 0
		//idx != 0 -> level = log2(idx+1)
		int level;
		if(idx == 0) level = 0;
		else level = (int)(log10(idx+1) / log10(2));
	
		//get current node from the queue
		Node* currNode = queueForBfs.front();

		//push left child into the queue
		if(currNode->getLeftChild() != NULL)  
			queueForBfs.push(currNode->getLeftChild());

		//push right child into the queue
		if(currNode->getRightChild() != NULL)
			queueForBfs.push(currNode->getRightChild());
		
		//if the node is in the beginning of the line
		if((initLineIdx-1) == idx) {
			//change the start number of line
			initLineIdx *= 2;

			//new line except when index is 0
			if(idx != 0) cout << endl;

			//padding of the beginning of the line
			//2^(max depth - level) - 1
			for(int i=0;i<power(2, maxDepth-level)-1;i++) {
				cout << " ";
			}
		}

		//if the node is logically null, just print blank
		if(currNode->getIsNull() == true) 
			cout << " ";
		//else print the value of the node
		else 
			cout << currNode->getValue();

		//padding between node and node
		//2^(max depth - level + 1) - 1
		for(int i=0;i<power(2, maxDepth-level+1)-1;i++) {
			cout << " ";
		}

		//pop the current node
		queueForBfs.pop();

		//increment index
		idx++;
	}

	//final new line
	cout << endl;
}













