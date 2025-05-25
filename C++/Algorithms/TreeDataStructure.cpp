#include <iostream>
using namespace std;



// Single Link list : One Node: It has a Value and pointer (called next) to next node... The last node has a value and a Null pointer
// It can be Traversed in onl yForward direction.
// We can add a New Node at three places i.e. at the Beginning, End and only after any Given Node.

// Doubly Linked List: Each node has Two Pointers and a Value.
// One Ponter to the next node and 2nd to the previous node.
// It can be Traversed in Forward and backward.
// We can add a New Node at four places i.e. at the Beginning, End and before and after any Given Node.
// Doubly linked list are faster at Adding or deleting a Node.
// Doubly Linked lists take more space than Singly linked lists.


class Node{
plublic: 
		int value;
		Node* next;
		Node* prev;
};



void printForward(Node* head)
{
	// Traverser starts from the head
	Node* traversingNode = head;
	
	while(traversingNode != nullptr)
	{
		cout<<traversingNode->value<<endl;
		traversingNode = traversingNode->next;	
	}
	
}

void printBackwards(Node* tail)
{
	// Traverser will start from the tail and in backwards
	Node* traversingNode = tail;
	
	while(!traversingNode->nullptr)
	{
		cout<<traversingNode->value<<endl;
		traversingNode = traversingNode->prev;	
	}
	
}


int main ()
{
	Node* head;
	Node* tail;
	
	// add 1st node
	Node* node = new Node();

	node->value = 4;
	node->next = nullptr;
	node->prev = nullptr;
	head = node;  // current Head of the List
	tail  = node; // Current Tail of the List
	
	// add 2nd node and this code block can be copy paste for the addition of new node.
	node = new Node();

	node->value = 5;
	node->next = nullptr;
	node->prev = tail;  // since tail of the list at this point has 1st Node, therefore previous should points to 1st Node which is tail at the moment
	tail->next = node;  // And Tail which is 1st node still has a next node number 2
	tail = node; // Since we added new node so the tail of the List is now the newly added node
	
	// add 3rd node
	node = new Node();

	node->value = 6;
	node->next = nullptr;
	node->prev = tail;
	tail->next = node; 
	tail = node; // here tail points to the newly added node
	
	printForward(head);
	printBackwards(tail);


}
