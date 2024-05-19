#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	int move_count;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
ListNode* get_pre_link(ListNode* head, int pos) {
	ListNode* pre = (ListNode*)malloc(sizeof(ListNode));
	pre->link = head;
	for (int i = 0; i < pos-1; i++) {
		pre = pre->link;
	}
	return pre;
}
ListNode* insert_first(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	head->move_count = 1;
	return head;
}
ListNode* insert(ListNode* head, ListNode* pre, element value, int pos) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	head->move_count = pos;
	return head;
}
ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	head->move_count = 1;
	return head;
}
ListNode* delete(ListNode* head, ListNode* pre, int pos) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	head->move_count = pos;
	return head;
}
void print_list(ListNode* head) {
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d -> ", p->data);
	printf("NULL \n");
}
int main(void) {
	ListNode* head = (ListNode*)NULL;
	ListNode* pre;
	int choice, num, position;

	while (1) {
		printf("\n메뉴:\n");
		printf("1. 숫자를 위치에 삽입\n");
		printf("2. 위치에서 숫자 삭제\n");
		printf("3. 리스트 출력\n");
		printf("0. 프로그램 종료\n");
		printf("선택하세요: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("삽입할 숫자를 입력하세요: ");
			scanf("%d", &num);
			printf("삽입할 위치를 입력하세요: ");
			scanf("%d", &position);
			if (position == 0) {
				head = insert_first(head, num);
			}
			else {
				pre = get_pre_link(head, position);
				head->move_count = pre->move_count;
				head = insert(head, pre , num, position);
			}
			printf("삽입시 링크를 따라 이동한 횟수: %d\n", head->move_count);
			break;   
		case 2:
			printf("삭제할 위치를 입력하세요: ");
			scanf("%d", &position);
			if (position == 0) {
				head = delete_first(head);
			}
			else {
				pre = get_pre_link(head, position);
				head->move_count = pre->move_count;
				head = delete(head, pre, position);
			}
			printf("삭제시 링크를 따라 이동한 횟수: %d\n", head->move_count);
			break;
		case 3:
			print_list(head);
			break;
		case 0:
			exit(0);
		default:
			printf("유효하지 않은 선택입니다!\n");
		}
	}

}