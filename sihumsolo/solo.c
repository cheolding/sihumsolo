#include<stdio.h>
#include<stdlib.h>

#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10
typedef struct { // 교체!
	short r;
	short c;
} element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;
// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}
// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}




char maze[MAZE_SIZE][MAZE_SIZE] = {

{'1','1','1','1','1','1','1','1','1','1'},

{'e','1','0','1','0','0','0','1','0','1'},

{'0','0','0','1','0','0','0','1','0','1'},

{'0','1','0','0','0','1','1','0','0','1'},

{'1','0','0','0','1','0','0','0','0','1'},

{'1','0','0','0','1','0','0','0','0','1'},

{'1','0','0','0','0','0','1','0','1','1'},

{'1','0','1','1','1','0','1','1','0','1'},

{'1','1','0','0','0','0','0','0','0','x'},

{'1','1','1','1','1','1','1','1','1','1'}

};

element here = { 1,0 }, entry = { 1,0 };

int count = 0;
// 미로를 화면에 출력한다.
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}
int main(void)
{
	int r, c;
	StackType s;
	StackType s2;

	init_stack(&s);
	init_stack(&s2);
	here = entry;


	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;

		maze[r][c] = '.';
		maze_print(maze);
		printf("현재의 좌표(%d %d)\n", r, c);
		int possibleMoves = 0; // 가능한 이동 방향 개수 초기화

		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		// 가능한 이동 방향 개수 측정
		if (maze[r - 1][c] != '1' && maze[r - 1][c] != '.') possibleMoves++;
		if (maze[r + 1][c] != '1' && maze[r + 1][c] != '.') possibleMoves++;
		if (maze[r][c - 1] != '1' && maze[r][c - 1] != '.') possibleMoves++;
		if (maze[r][c + 1] != '1' && maze[r][c + 1] != '.') possibleMoves++;

		if (is_empty(&s)) {
			printf("실패\n");
			return;
		}
		else if (possibleMoves == 0) { // 가능한 이동 방향이 없는 경우
			here = pop(&s2);
		}
		else
		{
			

			here = pop(&s);
			push(&s2, here);

		}



	}
	printf("\n count:%d\n", count);
	printf("성공\n");
	return 0;
}