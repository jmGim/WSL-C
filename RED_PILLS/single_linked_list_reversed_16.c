// - **입력:** `1 -> 2 -> 3 -> NULL`
// - **출력:** `3 -> 2 -> 1 -> NULL`
// - **제약조건:** 메모리 재할당 없이 포인터 방향만 조작하여 구현.


#include <stdio.h>
#include <stdlib.h>

// 1. Define Node Structure
struct Node {
	int data;
	struct Node* next;
};

// Function to add data at the beginning (using pointer reference)
void push(struct Node** head, int new_data) {
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head);
	(*head) = new_node;
}

// 2. Common Printing Function
void printList(struct Node* node) {
	while (node != NULL) {
		printf("%d -> ", node->data);
		node = node->next;
	}
	printf("NULL\n");
}

// 3. Ordering Data in Reverse (In-place)
// Uses pointer reference to update the head of the list permanently
void reverseList(struct Node** head) {
	struct Node* prev = NULL;
	struct Node* current = *head;
	struct Node* next = NULL;

	while (current != NULL) {
		next = current->next;  // Store next node
		current->next = prev;  // Reverse current node's pointer
		prev = current;        // Move pointers forward
		current = next;
	}
	*head = prev;          // Update the head pointer reference
}

// 4. Main Function
int main() {
	struct Node* head = NULL;

	push(&head, 1);
	push(&head, 2);
	push(&head, 3);
	
	
	printf("입력: ");
	reverseList(&head);
	printList(head);

	printf("\n출력: ");
	reverseList(&head);
	printList(head);

	return 0;
}
