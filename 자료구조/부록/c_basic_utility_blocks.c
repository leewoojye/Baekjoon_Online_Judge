/*
================================================================================
자료구조 기말 코딩테스트용 C 기본 유틸리티 코드블록 모음
================================================================================
작성 목적
- 오픈북 시험장에서 Ctrl+F로 찾아 복붙하기 쉽게 만든 단일 C 파일.
- 전체를 그대로 제출하기보다는, 필요한 블록만 prob1.c / prob2.c / prob3.c에 복사해서 사용.
- 중간 기출처럼 scanf 없이 main 내부 배열/문자열을 바꿔가며 채점되는 스타일에 맞춤.

Ctrl+F 추천 검색어
- includes, macro, sizeof, malloc, realloc, string, array
- vector, stack, char stack, queue, circular queue
- linked list, tree, level order, graph, dfs, bfs
- heap, sorting, student, radix, expression

주의
- 이 파일은 여러 블록을 한 파일에 모은 “공구상자”이다.
- 실제 제출 파일에는 문제에서 요구하는 함수명/출력 형식으로 이름과 printf를 맞춰라.
- malloc/realloc 실패 처리를 포함했지만, 시험 문제에서 error() 함수명을 요구하면 이름만 바꾸면 된다.
================================================================================
*/

/* =============================================================================
[0] 기본 include / macro
============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define U_MAX(a, b) ((a) > (b) ? (a) : (b))
#define U_MIN(a, b) ((a) < (b) ? (a) : (b))
#define U_ABS(a)    ((a) < 0 ? -(a) : (a))
#define U_SWAP(a, b, temp) do { (temp) = (a); (a) = (b); (b) = (temp); } while (0)

/* 실제 배열에서만 사용 가능. 포인터에는 사용 금지. */
#define U_ARRAY_LEN(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))

#define U_EMPTY_SLOT INT_MIN

/* =============================================================================
[1] 에러 처리 / 안전한 malloc, calloc, realloc
============================================================================= */

// 오류 메시지를 출력하고 프로그램을 종료한다.
void u_die(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

// malloc을 실행하고 실패하면 프로그램을 종료한다.
void *u_xmalloc(size_t bytes) {
    void *p = malloc(bytes);
    if (p == NULL && bytes != 0) {
        u_die("malloc failed");
    }
    return p;
}

// calloc을 안전하게 실행하고 크기 오버플로와 실패를 검사한다.
void *u_xcalloc(size_t count, size_t size) {
    if (count != 0 && size > SIZE_MAX / count) {
        u_die("calloc size overflow");
    }
    void *p = calloc(count, size);
    if (p == NULL && count != 0 && size != 0) {
        u_die("calloc failed");
    }
    return p;
}

// realloc을 실행하고 실패하면 프로그램을 종료한다.
void *u_xrealloc(void *ptr, size_t bytes) {
    void *p = realloc(ptr, bytes);
    if (p == NULL && bytes != 0) {
        u_die("realloc failed");
    }
    return p;
}

// 배열 크기 오버플로를 검사한 뒤 동적 메모리를 할당한다.
void *u_xmalloc_array(size_t count, size_t size) {
    if (count != 0 && size > SIZE_MAX / count) {
        u_die("malloc array size overflow");
    }
    return u_xmalloc(count * size);
}

// 배열 크기 오버플로를 검사한 뒤 동적 메모리를 재할당한다.
void *u_xrealloc_array(void *ptr, size_t count, size_t size) {
    if (count != 0 && size > SIZE_MAX / count) {
        u_die("realloc array size overflow");
    }
    return u_xrealloc(ptr, count * size);
}

// 문자열을 새 동적 메모리에 복사해 반환한다.
char *u_xstrdup(const char *s) {
    size_t len;
    char *copy;

    if (s == NULL) return NULL;
    len = strlen(s) + 1;
    copy = (char *)u_xmalloc(len);
    memcpy(copy, s, len);
    return copy;
}

/* 사용 예시
int *arr = (int *)u_xmalloc_array(n, sizeof(int));
arr = (int *)u_xrealloc_array(arr, new_n, sizeof(int));
free(arr);
*/

/* =============================================================================
[2] 시험 입력 스타일 / sizeof 패턴
============================================================================= */

/*
scanf 금지 스타일에서 자주 쓰는 형태:

int arr[] = {23, 56, 11, 9, 40, 99, 27, 34};
int n = U_ARRAY_LEN(arr);

int edges[][2] = {{0, 1}, {1, 2}, {2, 3}};
int edge_count = U_ARRAY_LEN(edges);

char *input = "7+8*(3-1)/2";
*/

/* =============================================================================
[3] int 배열 출력 / 복사 / 검색 / 기본 조작
============================================================================= */

// 정수 배열을 공백으로 구분해 출력한다.
void u_print_int_array(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i + 1 < n) printf(" ");
    }
    printf("\n");
}

// 라벨을 먼저 출력한 뒤 정수 배열을 출력한다.
void u_print_int_array_label(const char *label, const int a[], int n) {
    if (label != NULL) printf("%s", label);
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i + 1 < n) printf(" ");
    }
    printf("\n");
}

// 빈 슬롯 표시를 포함해 정수 배열을 출력한다.
void u_print_int_slots(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == U_EMPTY_SLOT) printf("_");
        else printf("%d", a[i]);
        if (i + 1 < n) printf(" ");
    }
    printf("\n");
}

// 정수 배열 전체를 같은 값으로 채운다.
void u_fill_int_array(int a[], int n, int value) {
    for (int i = 0; i < n; i++) a[i] = value;
}

// 원본 정수 배열을 대상 배열로 복사한다.
void u_copy_int_array(int dest[], const int src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// 정수 배열의 원소 순서를 뒤집는다.
void u_reverse_int_array(int a[], int n) {
    int temp;
    for (int i = 0; i < n / 2; i++) {
        U_SWAP(a[i], a[n - 1 - i], temp);
    }
}

// 정수 배열 원소들의 합을 계산한다.
int u_sum_int_array(const int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    return sum;
}

// 정수 배열에서 key의 첫 위치를 찾는다.
int u_find_int_index(const int a[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (a[i] == key) return i;
    }
    return -1;
}

// 정수 배열에 key가 포함되어 있는지 확인한다.
int u_contains_int(const int a[], int n, int key) {
    return u_find_int_index(a, n, key) != -1;
}

// 정수 배열에서 최솟값의 인덱스를 반환한다.
int u_min_index_int(const int a[], int n) {
    if (n <= 0) return -1;
    int min_i = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] < a[min_i]) min_i = i;
    }
    return min_i;
}

// 정수 배열에서 최댓값의 인덱스를 반환한다.
int u_max_index_int(const int a[], int n) {
    if (n <= 0) return -1;
    int max_i = 0;
    for (int i = 1; i < n; i++) {
        if (a[i] > a[max_i]) max_i = i;
    }
    return max_i;
}

// 정수 배열이 오름차순으로 정렬되어 있는지 확인한다.
int u_is_sorted_asc_int(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) return FALSE;
    }
    return TRUE;
}

// 정렬된 정수 배열에서 이진 탐색으로 key의 위치를 찾는다.
int u_binary_search_int(const int a[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] == key) return mid;
        if (a[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

/* =============================================================================
[4] 문자열 유틸리티: fgets, strlen, strcpy, strcmp, 공백 제거
============================================================================= */

// 문자열 끝의 개행 문자를 제거한다.
void u_chomp_newline(char *s) {
    if (s == NULL) return;
    s[strcspn(s, "\n")] = '\0';
}

// 대상 버퍼 크기를 지키며 문자열을 복사한다.
void u_safe_strcpy(char *dest, size_t dest_size, const char *src) {
    if (dest == NULL || dest_size == 0) return;
    if (src == NULL) {
        dest[0] = '\0';
        return;
    }
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}

// 문자열에서 모든 공백 문자를 제거한다.
void u_remove_spaces(char *s) {
    int write = 0;
    if (s == NULL) return;
    for (int read = 0; s[read] != '\0'; read++) {
        if (!isspace((unsigned char)s[read])) {
            s[write++] = s[read];
        }
    }
    s[write] = '\0';
}

// 문자열의 문자 순서를 뒤집는다.
void u_reverse_string(char *s) {
    if (s == NULL) return;
    int n = (int)strlen(s);
    for (int i = 0; i < n / 2; i++) {
        char temp = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = temp;
    }
}

// 문자열 앞부분의 정수를 간단히 파싱한다.
int u_parse_int_simple(const char *s) {
    int sign = 1;
    int value = 0;
    int i = 0;

    if (s == NULL) return 0;
    while (isspace((unsigned char)s[i])) i++;
    if (s[i] == '-') {
        sign = -1;
        i++;
    }
    for (; isdigit((unsigned char)s[i]); i++) {
        value = value * 10 + (s[i] - '0');
    }
    return sign * value;
}

/* 사용 예시
char buffer[100];
fgets(buffer, sizeof(buffer), stdin);
u_chomp_newline(buffer);
*/

/* =============================================================================
[5] 동적 int 벡터: malloc/realloc로 크기 자동 증가
============================================================================= */

typedef struct {
    int *data;
    int size;
    int capacity;
} UIntVector;

// 동적 정수 벡터를 빈 상태로 초기화한다.
void u_vec_init(UIntVector *v) {
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

// 동적 정수 벡터의 용량을 필요한 크기까지 확보한다.
void u_vec_reserve(UIntVector *v, int new_capacity) {
    if (new_capacity <= v->capacity) return;
    v->data = (int *)u_xrealloc_array(v->data, (size_t)new_capacity, sizeof(int));
    v->capacity = new_capacity;
}

// 동적 정수 벡터의 끝에 값을 추가한다.
void u_vec_push_back(UIntVector *v, int value) {
    if (v->size >= v->capacity) {
        int new_capacity = (v->capacity == 0) ? 1 : v->capacity * 2;
        u_vec_reserve(v, new_capacity);
    }
    v->data[v->size++] = value;
}

// 동적 정수 벡터의 마지막 값을 삭제해 반환한다.
int u_vec_pop_back(UIntVector *v) {
    if (v->size <= 0) u_die("vector is empty");
    return v->data[--v->size];
}

// 동적 정수 벡터의 모든 값을 출력한다.
void u_vec_print(const UIntVector *v) {
    u_print_int_array(v->data, v->size);
}

// 동적 정수 벡터가 사용한 메모리를 해제한다.
void u_vec_free(UIntVector *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

/* =============================================================================
[6] int 스택: 후위식 계산, DFS 명시적 스택 등에 사용
============================================================================= */

typedef struct {
    int *data;
    int top;
    int capacity;
} UIntStack;

// 동적 int 스택을 지정한 용량으로 초기화한다.
void u_istack_init(UIntStack *s, int capacity) {
    if (capacity <= 0) capacity = 1;
    s->data = (int *)u_xmalloc_array((size_t)capacity, sizeof(int));
    s->top = -1;
    s->capacity = capacity;
}

// int 스택이 비어 있는지 확인한다.
int u_istack_is_empty(const UIntStack *s) {
    return s->top == -1;
}

// int 스택의 용량을 두 배로 늘린다.
void u_istack_grow(UIntStack *s) {
    s->capacity *= 2;
    s->data = (int *)u_xrealloc_array(s->data, (size_t)s->capacity, sizeof(int));
}

// int 스택에 값을 push한다.
void u_istack_push(UIntStack *s, int value) {
    if (s->top + 1 >= s->capacity) u_istack_grow(s);
    s->data[++s->top] = value;
}

// int 스택의 top 값을 pop해 반환한다.
int u_istack_pop(UIntStack *s) {
    if (u_istack_is_empty(s)) u_die("int stack is empty");
    return s->data[s->top--];
}

// int 스택의 top 값을 삭제하지 않고 반환한다.
int u_istack_peek(const UIntStack *s) {
    if (u_istack_is_empty(s)) u_die("int stack is empty");
    return s->data[s->top];
}

// int 스택이 사용한 메모리를 해제한다.
void u_istack_free(UIntStack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

/* =============================================================================
[7] char 스택: 중위식 -> 후위식 변환에 사용
============================================================================= */

typedef struct {
    char *data;
    int top;
    int capacity;
} UCharStack;

// 동적 char 스택을 지정한 용량으로 초기화한다.
void u_cstack_init(UCharStack *s, int capacity) {
    if (capacity <= 0) capacity = 1;
    s->data = (char *)u_xmalloc_array((size_t)capacity, sizeof(char));
    s->top = -1;
    s->capacity = capacity;
}

// char 스택이 비어 있는지 확인한다.
int u_cstack_is_empty(const UCharStack *s) {
    return s->top == -1;
}

// char 스택의 용량을 두 배로 늘린다.
void u_cstack_grow(UCharStack *s) {
    s->capacity *= 2;
    s->data = (char *)u_xrealloc_array(s->data, (size_t)s->capacity, sizeof(char));
}

// char 스택에 문자를 push한다.
void u_cstack_push(UCharStack *s, char value) {
    if (s->top + 1 >= s->capacity) u_cstack_grow(s);
    s->data[++s->top] = value;
}

// char 스택의 top 문자를 pop해 반환한다.
char u_cstack_pop(UCharStack *s) {
    if (u_cstack_is_empty(s)) u_die("char stack is empty");
    return s->data[s->top--];
}

// char 스택의 top 문자를 삭제하지 않고 반환한다.
char u_cstack_peek(const UCharStack *s) {
    if (u_cstack_is_empty(s)) u_die("char stack is empty");
    return s->data[s->top];
}

// char 스택이 사용한 메모리를 해제한다.
void u_cstack_free(UCharStack *s) {
    free(s->data);
    s->data = NULL;
    s->top = -1;
    s->capacity = 0;
}

/* =============================================================================
[8] 동적 배열 기반 원형 큐: realloc로 capacity 2배 증가
============================================================================= */

typedef struct {
    int *data;
    int front;    /* 첫 원소 위치 */
    int rear;     /* 마지막 원소 다음 위치 */
    int size;
    int capacity;
} UIntQueue;

// 동적 원형 큐를 지정한 용량으로 초기화한다.
void u_iq_init(UIntQueue *q, int capacity) {
    if (capacity <= 0) capacity = 1;
    q->data = (int *)u_xmalloc_array((size_t)capacity, sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = capacity;
}

// 동적 원형 큐가 비어 있는지 확인한다.
int u_iq_is_empty(const UIntQueue *q) {
    return q->size == 0;
}

// 동적 원형 큐가 가득 찼는지 확인한다.
int u_iq_is_full(const UIntQueue *q) {
    return q->size == q->capacity;
}

// 동적 원형 큐의 용량을 두 배로 늘리고 논리 순서를 보존한다.
void u_iq_grow_realloc(UIntQueue *q) {
    int old_capacity = q->capacity;
    int old_size = q->size;
    int old_front = q->front;
    int new_capacity = old_capacity * 2;

    q->data = (int *)u_xrealloc_array(q->data, (size_t)new_capacity, sizeof(int));

    /*
    원형으로 감겨 있는 경우:
    old_front ... old_capacity-1 부분을 새 배열 뒤쪽으로 이동하여 논리 순서 보존.
    */
    if (old_front + old_size > old_capacity) {
        int right_count = old_capacity - old_front;
        memmove(q->data + (new_capacity - right_count),
                q->data + old_front,
                (size_t)right_count * sizeof(int));
        q->front = new_capacity - right_count;
    } else {
        q->front = old_front;
    }

    q->capacity = new_capacity;
    q->rear = (q->front + old_size) % q->capacity;
}

// 동적 원형 큐의 rear에 값을 삽입한다.
void u_iq_enqueue(UIntQueue *q, int value) {
    if (u_iq_is_full(q)) u_iq_grow_realloc(q);
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

// 동적 원형 큐의 front 값을 삭제해 반환한다.
int u_iq_dequeue(UIntQueue *q) {
    int value;
    if (u_iq_is_empty(q)) u_die("queue is empty");
    value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

// 동적 원형 큐의 값을 논리 순서대로 출력한다.
void u_iq_print(const UIntQueue *q) {
    printf("[ ");
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->data[(q->front + i) % q->capacity]);
    }
    printf("]");
}

// 동적 원형 큐가 사용한 메모리를 해제한다.
void u_iq_free(UIntQueue *q) {
    free(q->data);
    q->data = NULL;
    q->front = q->rear = q->size = q->capacity = 0;
}

/* 사용 예시
UIntQueue q;
u_iq_init(&q, 1);
u_iq_enqueue(&q, 10);
u_iq_enqueue(&q, 20);
printf("dequeue -> %d\n", u_iq_dequeue(&q));
u_iq_free(&q);
*/

/* =============================================================================
[9] 단순 연결 리스트 기본 블록: insert_last, print, free
============================================================================= */

typedef struct UNode {
    int data;
    struct UNode *next;
} UNode;

// 단순 연결 리스트의 새 노드를 생성한다.
UNode *u_list_new_node(int value) {
    UNode *node = (UNode *)u_xmalloc(sizeof(UNode));
    node->data = value;
    node->next = NULL;
    return node;
}

// 단순 연결 리스트의 끝에 값을 삽입한다.
void u_list_insert_last(UNode **head, int value) {
    UNode *node = u_list_new_node(value);
    if (*head == NULL) {
        *head = node;
        return;
    }
    UNode *cur = *head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = node;
}

// 정수 배열로 단순 연결 리스트를 생성한다.
UNode *u_list_from_array(const int arr[], int n) {
    UNode *head = NULL;
    for (int i = 0; i < n; i++) {
        u_list_insert_last(&head, arr[i]);
    }
    return head;
}

// 단순 연결 리스트를 라벨과 함께 출력한다.
void u_list_print(const char *label, const UNode *head) {
    if (label != NULL) printf("%s: ", label);
    const UNode *cur = head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) printf(" -> ");
        cur = cur->next;
    }
    printf("\n");
}

// 단순 연결 리스트의 모든 노드를 해제한다.
void u_list_free(UNode *head) {
    while (head != NULL) {
        UNode *next = head->next;
        free(head);
        head = next;
    }
}

// 단순 연결 리스트의 노드 개수를 계산한다.
int u_list_length(const UNode *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// 정렬된 중복 없는 두 리스트의 합집합을 새 리스트로 만든다.
UNode *u_list_set_union_sorted(const UNode *a, const UNode *b) {
    UNode *result = NULL;
    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            u_list_insert_last(&result, a->data);
            a = a->next;
        } else if (a->data > b->data) {
            u_list_insert_last(&result, b->data);
            b = b->next;
        } else {
            u_list_insert_last(&result, a->data);
            a = a->next;
            b = b->next;
        }
    }
    while (a != NULL) {
        u_list_insert_last(&result, a->data);
        a = a->next;
    }
    while (b != NULL) {
        u_list_insert_last(&result, b->data);
        b = b->next;
    }
    return result;
}

// 정렬된 중복 없는 두 리스트의 차집합 A-B를 새 리스트로 만든다.
UNode *u_list_set_difference_sorted(const UNode *a, const UNode *b) {
    UNode *result = NULL;
    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            u_list_insert_last(&result, a->data);
            a = a->next;
        } else if (a->data > b->data) {
            b = b->next;
        } else {
            a = a->next;
            b = b->next;
        }
    }
    while (a != NULL) {
        u_list_insert_last(&result, a->data);
        a = a->next;
    }
    return result;
}

/* =============================================================================
[10] 수식 처리 기본 블록: 중위 -> 후위, 후위 계산
- 한 자리 정수 기준. 여러 자리 정수면 토큰 처리를 따로 해야 함.
============================================================================= */

// 문자가 산술 연산자인지 확인한다.
int u_expr_is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 산술 연산자의 우선순위를 반환한다.
int u_expr_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 두 피연산자에 산술 연산자를 적용한 값을 반환한다.
int u_expr_apply(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) u_die("division by zero");
            return a / b; /* 정수 나눗셈 */
        default:
            u_die("unknown operator");
    }
    return 0;
}

// 한 자리 정수 중위식을 후위식으로 변환한다.
void u_infix_to_postfix_one_digit(const char *infix, char *postfix) {
    UCharStack st;
    int k = 0;
    u_cstack_init(&st, 16);

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isspace((unsigned char)c)) continue;

        if (isdigit((unsigned char)c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            u_cstack_push(&st, c);
        } else if (c == ')') {
            while (!u_cstack_is_empty(&st) && u_cstack_peek(&st) != '(') {
                postfix[k++] = u_cstack_pop(&st);
            }
            if (!u_cstack_is_empty(&st) && u_cstack_peek(&st) == '(') {
                (void)u_cstack_pop(&st);
            }
        } else if (u_expr_is_operator(c)) {
            while (!u_cstack_is_empty(&st) &&
                   u_expr_precedence(u_cstack_peek(&st)) >= u_expr_precedence(c)) {
                postfix[k++] = u_cstack_pop(&st);
            }
            u_cstack_push(&st, c);
        }
    }

    while (!u_cstack_is_empty(&st)) {
        postfix[k++] = u_cstack_pop(&st);
    }
    postfix[k] = '\0';
    u_cstack_free(&st);
}

// 한 자리 정수 후위식을 계산한다.
int u_eval_postfix_one_digit(const char *postfix) {
    UIntStack st;
    u_istack_init(&st, 16);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isspace((unsigned char)c)) continue;

        if (isdigit((unsigned char)c)) {
            u_istack_push(&st, c - '0');
        } else if (u_expr_is_operator(c)) {
            int b = u_istack_pop(&st);
            int a = u_istack_pop(&st);
            u_istack_push(&st, u_expr_apply(a, b, c));
        }
    }

    int result = u_istack_pop(&st);
    u_istack_free(&st);
    return result;
}

/* =============================================================================
[11] 이진 트리 / BST 기본 유틸리티
============================================================================= */

typedef struct UTreeNode {
    int key;
    struct UTreeNode *left;
    struct UTreeNode *right;
} UTreeNode;

// 주어진 key를 저장하는 새 이진 트리 노드를 생성한다.
UTreeNode *u_tree_new_node(int key) {
    UTreeNode *node = (UTreeNode *)u_xmalloc(sizeof(UTreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 이진 탐색 트리에 key를 삽입하고 루트를 반환한다.
UTreeNode *u_bst_insert(UTreeNode *root, int key) {
    if (root == NULL) return u_tree_new_node(key);
    if (key < root->key) root->left = u_bst_insert(root->left, key);
    else if (key > root->key) root->right = u_bst_insert(root->right, key);
    return root;
}

// 이진 탐색 트리에서 key를 가진 노드를 찾는다.
UTreeNode *u_bst_search(UTreeNode *root, int key) {
    while (root != NULL) {
        if (key == root->key) return root;
        if (key < root->key) root = root->left;
        else root = root->right;
    }
    return NULL;
}

// 이진 탐색 트리에서 가장 작은 key의 노드를 찾는다.
UTreeNode *u_bst_min_node(UTreeNode *root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

// 이진 탐색 트리에서 key를 삭제하고 루트를 반환한다.
UTreeNode *u_bst_delete(UTreeNode *root, int key) {
    if (root == NULL) return NULL;

    if (key < root->key) {
        root->left = u_bst_delete(root->left, key);
    } else if (key > root->key) {
        root->right = u_bst_delete(root->right, key);
    } else {
        if (root->left == NULL) {
            UTreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            UTreeNode *temp = root->left;
            free(root);
            return temp;
        } else {
            UTreeNode *temp = u_bst_min_node(root->right);
            root->key = temp->key;
            root->right = u_bst_delete(root->right, temp->key);
        }
    }
    return root;
}

// 이진 트리를 전위 순회하며 key를 출력한다.
void u_tree_preorder(UTreeNode *root) {
    if (root == NULL) return;
    printf("%d ", root->key);
    u_tree_preorder(root->left);
    u_tree_preorder(root->right);
}

// 이진 트리를 중위 순회하며 key를 출력한다.
void u_tree_inorder(UTreeNode *root) {
    if (root == NULL) return;
    u_tree_inorder(root->left);
    printf("%d ", root->key);
    u_tree_inorder(root->right);
}

// 이진 트리를 후위 순회하며 key를 출력한다.
void u_tree_postorder(UTreeNode *root) {
    if (root == NULL) return;
    u_tree_postorder(root->left);
    u_tree_postorder(root->right);
    printf("%d ", root->key);
}

// 이진 트리의 전체 노드 수를 계산한다.
int u_tree_count_nodes(UTreeNode *root) {
    if (root == NULL) return 0;
    return 1 + u_tree_count_nodes(root->left) + u_tree_count_nodes(root->right);
}

// 이진 트리의 높이를 계산한다.
int u_tree_height(UTreeNode *root) {
    if (root == NULL) return 0;
    return 1 + U_MAX(u_tree_height(root->left), u_tree_height(root->right));
}

// 이진 트리의 리프 노드 수를 계산한다.
int u_tree_leaf_count(UTreeNode *root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return u_tree_leaf_count(root->left) + u_tree_leaf_count(root->right);
}

// 이진 트리가 높이 균형 조건을 만족하는지 확인한다.
int u_tree_is_balanced(UTreeNode *root) {
    if (root == NULL) return TRUE;
    int lh = u_tree_height(root->left);
    int rh = u_tree_height(root->right);
    if (U_ABS(lh - rh) > 1) return FALSE;
    return u_tree_is_balanced(root->left) && u_tree_is_balanced(root->right);
}

// 이진 트리의 모든 노드를 후위 순회로 해제한다.
void u_tree_free(UTreeNode *root) {
    if (root == NULL) return;
    u_tree_free(root->left);
    u_tree_free(root->right);
    free(root);
}

/* 트리 레벨 순회용 포인터 큐 */
typedef struct {
    UTreeNode **data;
    int front;
    int rear;
    int size;
    int capacity;
} UTreeQueue;

// 트리 노드 포인터 큐를 지정한 용량으로 초기화한다.
void u_tq_init(UTreeQueue *q, int capacity) {
    if (capacity <= 0) capacity = 1;
    q->data = (UTreeNode **)u_xmalloc_array((size_t)capacity, sizeof(UTreeNode *));
    q->front = q->rear = q->size = 0;
    q->capacity = capacity;
}

// 트리 노드 포인터 큐가 비어 있는지 확인한다.
int u_tq_is_empty(const UTreeQueue *q) {
    return q->size == 0;
}

// 트리 노드 포인터 큐의 용량을 두 배로 늘린다.
void u_tq_grow(UTreeQueue *q) {
    int old_capacity = q->capacity;
    int new_capacity = old_capacity * 2;
    UTreeNode **new_data = (UTreeNode **)u_xmalloc_array((size_t)new_capacity, sizeof(UTreeNode *));
    for (int i = 0; i < q->size; i++) {
        new_data[i] = q->data[(q->front + i) % old_capacity];
    }
    free(q->data);
    q->data = new_data;
    q->capacity = new_capacity;
    q->front = 0;
    q->rear = q->size;
}

// 트리 노드 포인터 큐에 노드를 삽입한다.
void u_tq_enqueue(UTreeQueue *q, UTreeNode *node) {
    if (q->size == q->capacity) u_tq_grow(q);
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

// 트리 노드 포인터 큐에서 노드를 삭제해 반환한다.
UTreeNode *u_tq_dequeue(UTreeQueue *q) {
    if (u_tq_is_empty(q)) u_die("tree queue is empty");
    UTreeNode *node = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return node;
}

// 트리 노드 포인터 큐가 사용한 메모리를 해제한다.
void u_tq_free(UTreeQueue *q) {
    free(q->data);
    q->data = NULL;
    q->front = q->rear = q->size = q->capacity = 0;
}

// 이진 트리를 레벨 순서로 순회하며 key를 출력한다.
void u_tree_level_order(UTreeNode *root) {
    if (root == NULL) return;
    UTreeQueue q;
    u_tq_init(&q, 16);
    u_tq_enqueue(&q, root);
    while (!u_tq_is_empty(&q)) {
        UTreeNode *cur = u_tq_dequeue(&q);
        printf("%d ", cur->key);
        if (cur->left != NULL) u_tq_enqueue(&q, cur->left);
        if (cur->right != NULL) u_tq_enqueue(&q, cur->right);
    }
    u_tq_free(&q);
}

/* =============================================================================
[12] 그래프 인접 행렬 / DFS / BFS / 차수
============================================================================= */

#define U_MAX_VERTICES 100

typedef struct {
    int n;
    int adj[U_MAX_VERTICES][U_MAX_VERTICES];
} UGraph;

// 인접행렬 그래프를 지정한 정점 수로 초기화한다.
void u_graph_init(UGraph *g, int n) {
    if (n < 0 || n > U_MAX_VERTICES) u_die("invalid vertex count");
    g->n = n;
    for (int i = 0; i < U_MAX_VERTICES; i++) {
        for (int j = 0; j < U_MAX_VERTICES; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// 무방향 그래프에 양방향 간선을 추가한다.
void u_graph_insert_edge_undirected(UGraph *g, int u, int v) {
    if (u < 0 || v < 0 || u >= g->n || v >= g->n) u_die("invalid edge");
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

// 방향 그래프에 단방향 간선을 추가한다.
void u_graph_insert_edge_directed(UGraph *g, int from, int to) {
    if (from < 0 || to < 0 || from >= g->n || to >= g->n) u_die("invalid edge");
    g->adj[from][to] = 1;
}

// 간선 배열로 무방향 인접행렬 그래프를 만든다.
void u_graph_build_undirected(UGraph *g, int n, int edges[][2], int edge_count) {
    u_graph_init(g, n);
    for (int i = 0; i < edge_count; i++) {
        u_graph_insert_edge_undirected(g, edges[i][0], edges[i][1]);
    }
}

// 간선 배열로 방향 인접행렬 그래프를 만든다.
void u_graph_build_directed(UGraph *g, int n, int edges[][2], int edge_count) {
    u_graph_init(g, n);
    for (int i = 0; i < edge_count; i++) {
        u_graph_insert_edge_directed(g, edges[i][0], edges[i][1]);
    }
}

// 그래프의 인접행렬을 출력한다.
void u_graph_print_matrix(const UGraph *g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            printf("%d ", g->adj[i][j]);
        }
        printf("\n");
    }
}

// 무방향 그래프에서 정점의 차수를 계산한다.
int u_graph_degree_undirected(const UGraph *g, int v) {
    int count = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[v][i]) count++;
    }
    return count;
}

// 방향 그래프에서 정점의 진출 차수를 계산한다.
int u_graph_outdegree(const UGraph *g, int v) {
    int count = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[v][i]) count++;
    }
    return count;
}

// 방향 그래프에서 정점의 진입 차수를 계산한다.
int u_graph_indegree(const UGraph *g, int v) {
    int count = 0;
    for (int i = 0; i < g->n; i++) {
        if (g->adj[i][v]) count++;
    }
    return count;
}

// 인접행렬 그래프를 재귀 DFS로 순회하며 방문 정점을 출력한다.
void u_dfs_matrix_rec(const UGraph *g, int v, int visited[]) {
    visited[v] = TRUE;
    printf("%d ", v);
    for (int w = 0; w < g->n; w++) {
        if (g->adj[v][w] && !visited[w]) {
            u_dfs_matrix_rec(g, w, visited);
        }
    }
}

// 방문 배열을 준비한 뒤 인접행렬 DFS를 실행한다.
void u_dfs_matrix(const UGraph *g, int start) {
    int visited[U_MAX_VERTICES] = {0};
    u_dfs_matrix_rec(g, start, visited);
    printf("\n");
}

// 무방향 그래프가 시작 정점 기준으로 연결되어 있는지 확인한다.
int u_graph_is_connected_undirected(const UGraph *g, int start) {
    int visited[U_MAX_VERTICES] = {0};
    u_dfs_matrix_rec(g, start, visited);
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) return FALSE;
    }
    return TRUE;
}

// DFS 후 방문하지 못한 정점들을 출력한다.
void u_graph_print_unvisited_after_dfs(const UGraph *g, int start) {
    int visited[U_MAX_VERTICES] = {0};
    u_dfs_matrix_rec(g, start, visited);
    printf("\nUnvisited: ");
    for (int i = 0; i < g->n; i++) {
        if (!visited[i]) printf("%d ", i);
    }
    printf("\n");
}

// BFS로 시작 정점부터 각 정점까지의 거리를 계산한다.
void u_bfs_distance_matrix(const UGraph *g, int start, int dist[]) {
    UIntQueue q;
    for (int i = 0; i < g->n; i++) dist[i] = -1;

    u_iq_init(&q, 16);
    dist[start] = 0;
    u_iq_enqueue(&q, start);

    while (!u_iq_is_empty(&q)) {
        int v = u_iq_dequeue(&q);
        for (int w = 0; w < g->n; w++) {
            if (g->adj[v][w] && dist[w] == -1) {
                dist[w] = dist[v] + 1;
                u_iq_enqueue(&q, w);
            }
        }
    }
    u_iq_free(&q);
}

// DFS로 현재 정점에서 목표 정점까지 경로가 있는지 탐색한다.
int u_graph_path_exists_dfs_rec(const UGraph *g, int v, int target, int visited[]) {
    if (v == target) return TRUE;
    visited[v] = TRUE;
    for (int w = 0; w < g->n; w++) {
        if (g->adj[v][w] && !visited[w]) {
            if (u_graph_path_exists_dfs_rec(g, w, target, visited)) return TRUE;
        }
    }
    return FALSE;
}

// 두 정점 사이의 경로 존재 여부를 반환한다.
int u_graph_path_exists(const UGraph *g, int start, int target) {
    int visited[U_MAX_VERTICES] = {0};
    return u_graph_path_exists_dfs_rec(g, start, target, visited);
}

/* =============================================================================
[13] 동적 최대 힙: priority queue / heap sort 준비용
============================================================================= */

typedef struct {
    int key;
} UHeapElement;

typedef struct {
    UHeapElement *heap; /* 1번 인덱스부터 사용 */
    int heap_size;
    int capacity;
} UMaxHeap;

// 동적 최대 힙을 지정한 용량으로 초기화한다.
void u_maxheap_init(UMaxHeap *h, int capacity) {
    if (capacity <= 0) capacity = 1;
    h->heap = (UHeapElement *)u_xmalloc_array((size_t)(capacity + 1), sizeof(UHeapElement));
    h->heap_size = 0;
    h->capacity = capacity;
}

// 동적 최대 힙의 용량을 두 배로 늘린다.
void u_maxheap_grow(UMaxHeap *h) {
    h->capacity *= 2;
    h->heap = (UHeapElement *)u_xrealloc_array(h->heap, (size_t)(h->capacity + 1), sizeof(UHeapElement));
}

// 최대 힙에 원소를 삽입한다.
void u_maxheap_insert(UMaxHeap *h, UHeapElement item) {
    if (h->heap_size >= h->capacity) u_maxheap_grow(h);

    int i = ++h->heap_size;
    while (i != 1 && item.key > h->heap[i / 2].key) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 최대 힙에서 가장 큰 원소를 삭제해 반환한다.
UHeapElement u_maxheap_delete(UMaxHeap *h) {
    if (h->heap_size <= 0) u_die("heap is empty");

    UHeapElement item = h->heap[1];
    UHeapElement temp = h->heap[h->heap_size--];
    int parent = 1;
    int child = 2;

    while (child <= h->heap_size) {
        if (child < h->heap_size && h->heap[child].key < h->heap[child + 1].key) {
            child++;
        }
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 최대 힙의 내부 배열 상태를 출력한다.
void u_maxheap_print(const UMaxHeap *h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d", h->heap[i].key);
        if (i < h->heap_size) printf(" ");
    }
    printf("\n");
}

// 최대 힙이 사용한 메모리를 해제한다.
void u_maxheap_free(UMaxHeap *h) {
    free(h->heap);
    h->heap = NULL;
    h->heap_size = 0;
    h->capacity = 0;
}

// 최대 힙을 이용해 정수 배열을 오름차순 정렬한다.
void u_heap_sort_ascending(int arr[], int n) {
    UMaxHeap h;
    u_maxheap_init(&h, n > 0 ? n : 1);
    for (int i = 0; i < n; i++) {
        UHeapElement e = { arr[i] };
        u_maxheap_insert(&h, e);
    }
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = u_maxheap_delete(&h).key;
    }
    u_maxheap_free(&h);
}

/* =============================================================================
[14] 정렬 기본 함수: 선택/삽입/버블/합병/퀵/기수
============================================================================= */

// 선택 정렬로 정수 배열을 오름차순 정렬한다.
void u_selection_sort_int(int list[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        int least = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[least]) least = j;
        }
        U_SWAP(list[i], list[least], temp);
    }
}

// 삽입 정렬로 정수 배열을 오름차순 정렬한다.
void u_insertion_sort_int(int list[], int n) {
    for (int i = 1; i < n; i++) {
        int key = list[i];
        int j;
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
        }
        list[j + 1] = key;
    }
}

// 버블 정렬로 정수 배열을 오름차순 정렬한다.
void u_bubble_sort_int(int list[], int n) {
    int temp;
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (list[j] > list[j + 1]) {
                U_SWAP(list[j], list[j + 1], temp);
            }
        }
    }
}

// 첫 원소를 피벗으로 사용해 퀵 정렬 구간을 분할한다.
int u_partition_first_pivot(int list[], int left, int right) {
    int pivot = list[left];
    int low = left;
    int high = right + 1;
    int temp;

    do {
        do {
            low++;
        } while (low <= right && list[low] < pivot);

        do {
            high--;
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            U_SWAP(list[low], list[high], temp);
        }
    } while (low < high);

    U_SWAP(list[left], list[high], temp);
    return high;
}

// 퀵 정렬로 정수 배열 구간을 오름차순 정렬한다.
void u_quick_sort_int(int list[], int left, int right) {
    if (left < right) {
        int q = u_partition_first_pivot(list, left, right);
        u_quick_sort_int(list, left, q - 1);
        u_quick_sort_int(list, q + 1, right);
    }
}

// 병합 정렬의 두 정렬된 구간을 하나로 합친다.
void u_merge_int(int list[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (list[i] <= list[j]) temp[k++] = list[i++];
        else temp[k++] = list[j++];
    }
    while (i <= mid) temp[k++] = list[i++];
    while (j <= right) temp[k++] = list[j++];

    for (int t = left; t <= right; t++) {
        list[t] = temp[t];
    }
}

// 보조 배열을 사용해 병합 정렬을 재귀 수행한다.
void u_merge_sort_int_rec(int list[], int temp[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        u_merge_sort_int_rec(list, temp, left, mid);
        u_merge_sort_int_rec(list, temp, mid + 1, right);
        u_merge_int(list, temp, left, mid, right);
    }
}

// 병합 정렬로 정수 배열을 오름차순 정렬한다.
void u_merge_sort_int(int list[], int n) {
    if (n <= 1) return;
    int *temp = (int *)u_xmalloc_array((size_t)n, sizeof(int));
    u_merge_sort_int_rec(list, temp, 0, n - 1);
    free(temp);
}

// 음이 아닌 정수 배열에서 기수 정렬에 필요한 자리수를 계산한다.
int u_count_digits_nonnegative(int arr[], int n) {
    int max_value = 0;
    int digits = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) u_die("radix sort here supports nonnegative integers only");
        if (arr[i] > max_value) max_value = arr[i];
    }
    while (max_value >= 10) {
        digits++;
        max_value /= 10;
    }
    return digits;
}

// 큐 버킷을 이용해 음이 아닌 정수 배열을 기수 정렬한다.
void u_radix_sort_nonnegative(int list[], int n) {
    UIntQueue buckets[10];
    int factor = 1;
    int digits = u_count_digits_nonnegative(list, n);

    for (int b = 0; b < 10; b++) u_iq_init(&buckets[b], 4);

    for (int d = 0; d < digits; d++) {
        for (int i = 0; i < n; i++) {
            int bucket = (list[i] / factor) % 10;
            u_iq_enqueue(&buckets[bucket], list[i]);
        }
        int index = 0;
        for (int b = 0; b < 10; b++) {
            while (!u_iq_is_empty(&buckets[b])) {
                list[index++] = u_iq_dequeue(&buckets[b]);
            }
        }
        factor *= 10;
    }

    for (int b = 0; b < 10; b++) u_iq_free(&buckets[b]);
}

/* =============================================================================
[15] 구조체 레코드 정렬 예시: 학생 학번/점수 기준
============================================================================= */

typedef struct {
    char name[20];
    int id;
    int score;
} UStudent;

// 학생 배열을 다른 배열로 복사한다.
void u_copy_students(UStudent dest[], const UStudent src[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

// 학번 오름차순 정렬에서 a가 b 뒤에 와야 하는지 확인한다.
int u_student_after_by_id(UStudent a, UStudent b) {
    return a.id > b.id; /* true면 a가 b보다 뒤에 가야 함 */
}

// 점수 내림차순 정렬에서 a가 b 뒤에 와야 하는지 확인한다.
int u_student_after_by_score(UStudent a, UStudent b) {
    if (a.score != b.score) return a.score < b.score; /* 점수 내림차순 */
    return a.id > b.id;                               /* 동점이면 학번 오름차순 */
}

// 학생 배열을 학번 오름차순으로 삽입 정렬한다.
void u_sort_students_by_id(UStudent arr[], int n) {
    for (int i = 1; i < n; i++) {
        UStudent key = arr[i];
        int j = i - 1;
        while (j >= 0 && u_student_after_by_id(arr[j], key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 학생 배열을 점수 내림차순으로 삽입 정렬한다.
void u_sort_students_by_score(UStudent arr[], int n) {
    for (int i = 1; i < n; i++) {
        UStudent key = arr[i];
        int j = i - 1;
        while (j >= 0 && u_student_after_by_score(arr[j], key)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 학생 배열을 제목과 함께 표 형태로 출력한다.
void u_print_students(const char *title, const UStudent arr[], int n) {
    if (title != NULL) printf("%s\n", title);
    printf("Name                 ID Score\n");
    printf("-------------------- -- -----\n");
    for (int i = 0; i < n; i++) {
        printf("%-20s %d %5d\n", arr[i].name, arr[i].id, arr[i].score);
    }
}

/* =============================================================================
[16] 자주 쓰는 main 패턴 모음
============================================================================= */

/*
패턴 A: 배열 입력
int arr[] = {23, 56, 11, 9, 40, 99, 27, 34};
int n = U_ARRAY_LEN(arr);
u_print_int_array(arr, n);

패턴 B: 그래프 입력
int n = 8;
int edges[][2] = {{0, 1}, {1, 2}, {2, 3}, {4, 5}, {6, 7}};
int edge_count = U_ARRAY_LEN(edges);
UGraph g;
u_graph_build_undirected(&g, n, edges, edge_count);

패턴 C: 문자열 입력
char *input = "7+8*(3-1)/2";
char postfix[200];
u_infix_to_postfix_one_digit(input, postfix);
printf("%s\n", postfix);
printf("%d\n", u_eval_postfix_one_digit(postfix));

패턴 D: 동적 큐 연산 입력
int operations[] = {1, 2, 3, -1, 4, 5, 6, 7, 8, -1};
int op_count = U_ARRAY_LEN(operations);
UIntQueue q;
u_iq_init(&q, 1);
for (int i = 0; i < op_count; i++) {
    if (operations[i] == -1) printf("dequeue -> %d\n", u_iq_dequeue(&q));
    else u_iq_enqueue(&q, operations[i]);
    u_iq_print(&q);
    printf(" capacity=%d\n", q.capacity);
}
u_iq_free(&q);
*/

/* =============================================================================
[17] 선택적 테스트 main
- gcc -DUTIL_BLOCKS_TEST_MAIN ds_c_basic_utility_blocks.c -o util_test
============================================================================= */

#ifdef UTIL_BLOCKS_TEST_MAIN
// 유틸리티 코드블록들의 기본 동작을 간단히 테스트한다.
int main(void) {
    printf("[array]\n");
    int arr[] = {4, 7, 1, 8, 6, 2, 5, 3};
    int n = U_ARRAY_LEN(arr);
    u_quick_sort_int(arr, 0, n - 1);
    u_print_int_array(arr, n);

    printf("\n[expression]\n");
    char *input = "7+8*(3-1)/2";
    char postfix[100];
    u_infix_to_postfix_one_digit(input, postfix);
    printf("postfix=%s result=%d\n", postfix, u_eval_postfix_one_digit(postfix));

    printf("\n[queue]\n");
    UIntQueue q;
    u_iq_init(&q, 1);
    for (int i = 1; i <= 6; i++) {
        u_iq_enqueue(&q, i);
        u_iq_print(&q);
        printf(" cap=%d\n", q.capacity);
    }
    u_iq_free(&q);

    printf("\n[bst]\n");
    int keys[] = {35, 18, 68, 7, 26, 99, 3, 12, 22, 30};
    UTreeNode *root = NULL;
    for (int i = 0; i < U_ARRAY_LEN(keys); i++) root = u_bst_insert(root, keys[i]);
    u_tree_inorder(root); printf("\n");
    printf("height=%d leaf=%d balanced=%d\n", u_tree_height(root), u_tree_leaf_count(root), u_tree_is_balanced(root));
    u_tree_free(root);

    return 0;
}
#endif
