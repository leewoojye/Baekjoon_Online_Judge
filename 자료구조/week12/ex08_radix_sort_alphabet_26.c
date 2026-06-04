#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 27
#define MAX_QUEUE_SIZE 100

typedef const char *element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

static void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

static void init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

static int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

static int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

static void enqueue(QueueType *q, element item)
{
    if (is_full(q)) {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

static element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

static int word_len(const char *word)
{
    int len = 0;

    while (word[len] != '\0') {
        len++;
    }
    return len;
}

static int get_max_word_len(const char *list[], int n) // strlen 없이 최대 문자열 길이 계산
{
    int max_len = 0;

    for (int i = 0; i < n; i++) {
        int len = word_len(list[i]);
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

static int bucket_index(const char *word, int pos)
{
    if (pos >= (int)strlen(word)) {
        return 0;
    }
    if (word[pos] < 'A' || word[pos] > 'Z') {
        error("only uppercase alphabet keys are supported");
    }
    return word[pos] - 'A' + 1;
}

static void print_words(const char *list[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s ", list[i]);
    }
    printf("\n");
}

static void radix_sort_alphabet(const char *list[], int n)
{
    QueueType queues[BUCKETS];
    int pass = 1;
    int max_len = get_max_word_len(list, n);

    for (int pos = max_len - 1; pos >= 0; pos--) {
        for (int b = 0; b < BUCKETS; b++) {
            init(&queues[b]);
        }

        for (int i = 0; i < n; i++) {
            enqueue(&queues[bucket_index(list[i], pos)], list[i]);
        }

        int i = 0;
        for (int b = 0; b < BUCKETS; b++) {
            while (!is_empty(&queues[b])) {
                list[i++] = dequeue(&queues[b]);
            }
        }

        printf("pass %d: ", pass++);
        print_words(list, n);
    }
}

int main(void)
{
    const char *list[] = { "GO", "TREE", "A", "TEAM", "TO", "TEA", "TEN", "T", "TOP", "APPLE", "APP", "BAT" };
    int n = (int)(sizeof(list) / sizeof(list[0]));

    printf("start : ");
    print_words(list, n);
    radix_sort_alphabet(list, n);

    printf("result: ");
    print_words(list, n);
    return 0;
}

//   #include <ctype.h>
//   #include <stdio.h>

//   int main(void)
//   {
//       char ch = 'a';

//       ch = toupper(ch);
//       printf("%c\n", ch); // A

//       ch = tolower(ch);
//       printf("%c\n", ch); // a

//       return 0;
//   }

//   #include <stdio.h>

//   int main(void) // 문자열 전체 대문자 변환
//   {
//       char str[] = "Hello C";

//       for (int i = 0; str[i] != '\0'; i++) {
//           if ('a' <= str[i] && str[i] <= 'z') {
//               str[i] = str[i] - ('a' - 'A');
//           }
//       }

//       printf("%s\n", str); // HELLO C
//       return 0;
//   }

//   int my_strcmp(char a[], char b[]) // 두 문자열 알파벳순 비교
//   {
//       int i = 0;

//       while (a[i] != '\0' && b[i] != '\0') {
//           if (a[i] < b[i]) {
//               return -1;
//           } else if (a[i] > b[i]) {
//               return 1;
//           }
//           i++;
//       }

//       if (a[i] == '\0' && b[i] == '\0') {
//           return 0;
//       } else if (a[i] == '\0') {
//           return -1;
//       } else {
//           return 1;
//       }
//   }