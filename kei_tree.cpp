#include <iostream>
#include <queue>
#define NODE_NUM 10
using namespace std;

class Node {
private:
	int value;
	bool isNull;
	Node* leftChild;
	Node* rightChild;
public:
	Node() {
		value = -1;
		isNull = false;
		leftChild = NULL;
		rightChild = NULL;
	}

	~Node() {
		delete leftChild;
		delete rightChild;
	}

	int getValue() { return value; }
	bool getIsNull() { return isNull; }
	Node* getLeftChild() { return leftChild; }
	Node* getRightChild() { return rightChild; }

	void setValue(int value) { this->value = value; }
	void setIsNull(bool isNull) { this->isNull = isNull; }
	void setLeftChild(Node* leftChild) { this->leftChild = leftChild; }
	void setRightChild(Node* rightChild) { this->rightChild = rightChild; }
};

int findMaxDepth(Node* parent, int currDepth);
void fillNullNodes(Node* parent, int maxDepth, int currDepth);
int power(int n, int i);
void fillPrintArray(Node* printArray, queue<Node> queueForBfs);
void printTree(Node* printArray);


int main() {
	Node** nodes = new Node*[NODE_NUM];

	for(int i=0;i<NODE_NUM;i++) {
		nodes[i] = new Node;
		nodes[i]->setValue(i);
	}

	nodes[0]->setLeftChild(nodes[1]);
	nodes[0]->setRightChild(nodes[5]);
	nodes[1]->setLeftChild(nodes[2]);
	nodes[1]->setRightChild(nodes[3]);
	nodes[5]->setRightChild(nodes[6]);
	nodes[3]->setLeftChild(nodes[4]);
	nodes[6]->setLeftChild(nodes[7]);
	nodes[7]->setLeftChild(nodes[8]);
	nodes[7]->setRightChild(nodes[9]);

	int maxDepth = findMaxDepth(nodes[0], 0);

	fillNullNodes(nodes[0], maxDepth, 0);

	Node* printArray = new Node[power(2, maxDepth) - 1];
	queue<Node*> queueForBfs;




	delete [] nodes;

	return 0;
}


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


void fillNullNodes(Node* parent, int maxDepth, int currDepth) {
	if(currDepth == maxDepth) {
		return;
	}

	if(parent->getLeftChild() == NULL) {
		Node* leftChild = new Node;
		leftChild->setIsNull(true);
		parent->setLeftChild(leftChild);
		fillNullNodes(parent->getLeftChild(), maxDepth, currDepth + 1);
	}

	if(parent->getRightChild() == NULL) {
		Node* rightChild = new Node;
		rightChild->setIsNull(true);
		parent->setRightChild(rightChild);
		fillNullNodes(parent->getRightChild(), maxDepth, currDepth + 1);
	}
}

int power(int n, int i) {
	int result = 1;
	for(int j=0;j<i;j++) {
		result *= n;
	}

	return result;
}


void fillPrintArray(Node* root, Node* printArray, queue<Node*>* queueForBfs) {
	int idx = 0;

	(*queueForBfs).push(root);
	
	while(!((*queueForBfs).empty())) {
		Node* currNode = (*queueForBfs).front();
		if(root->getLeftChild() == NULL && root->getRightChild() == NULL) {
			return;
		} 
		(*queueForBfs).push(root->getLeftChild());
		(*queueForBfs).push(root->getRightChild());
		

	}
}

void printTree(Node* printArray) {

}












