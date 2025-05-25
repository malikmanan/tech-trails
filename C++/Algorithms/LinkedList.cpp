#include <iostream>

using namespace std;


struct Node
{
	int value;
    Node* next;	
};

void printList(Node* n)
{
	while(n!=NULL)
	{
std::cout << n->value << std::endl;
		n = n->next;
	}
}

void insertAtTheFront(Node** head, int newValue)
{
	// preapre a newNode
	Node* newNode = new Node();
	newNode->value = newValue;
	
	// Put it in front of current head
	newNode->next = *head;  // deferencing head pointer to head node as head is recived as an address **head.
	
	// Assign the head of the linked list to point to newNode.
	*head =  newNode;  // since head is passed as pointer(contains address) to pointer head thats why dereferncing is required.
}


void insertAtTheEnd(Node** head, int newValue)
{
    // Prepare a newNode
    Node* newNode = new Node();
    newNode->value = newValue;
    newNode->next = NULL;
    
    // Check if given list is empty
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    
    // else Find the last node of the linked List
    
    Node* last = *head;
    
    while(last->next != NULL)
    {
        last = last->next;
    }
    
    // Insert newNode after the current last node of the linked list
    
    last->next = newNode;
    
}


void insertAfter(Node* anyNode, int newValue)
{
    if (anyNode == NULL)
    {
        cout<<"Node cant be null \n";
        return;
    }
    
    // Prepare a new Node
    Node* newNode = new Node();
    newNode->value = newValue;
    
    // insert newNode after given node
    // nodeA->nodeB  and newNode
    // step 1: newNode->nodeB   meaning newNode should point to what nodeA is currently pointing to i.e. nodeA has the address of nodeB which will be stored by newNode.
    // Step2: nodeA->newNode    now break connection b/w nodeA and nodeB and nodeA should now point to newNode which points to nodeB due to step 1.
    newNode->next = anyNode->next;
    anyNode->next = newNode;
    
}


int main ()
{
	Node* head = new Node();
	Node* second = new Node();
	Node* third = new Node();
	
	head->value = 10;	
	head->next = second;
	
	second->value = 20;
	second->next = third;

	third->value = 30;
	third->next = NULL;
		
	insertAtTheFront(&head, -1);
		
	insertAtTheEnd(&head, 100);
	
	insertAfter(head, -80);
	//printList(head);
	
	insertAfter(second, -555);
	printList(head);
	
}
