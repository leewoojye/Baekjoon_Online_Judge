#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMBER_OF_INSTANCES 50000 // 과제 지정 데이터 개수
#define MAX_STRING_LENGTH 20 // 랜덤 문자열 최대 길이
#define ALPHABET_SIZE 26 // 대문자 알파벳 개수
#define SORT_COUNT 5 // 분석 대상 정렬 개수

// 정렬 대상 데이터 구조체
typedef struct {
    char key[MAX_STRING_LENGTH + 1]; // 정렬 기준 문자열 저장
    int original_index; // 안정성 검사용 최초 위치 저장
} Record;

// 정렬별 분석 결과 구조체
typedef struct {
    double time_sec; // 정렬 함수 실행 시간 저장
    long long compare_count; // 문자열 비교 횟수 저장
    long long swap_count; // 교환 또는 이동 횟수 저장
    int stable; // 같은 key의 기존 순서 유지 여부 저장
} Result;

static Record original_data[NUMBER_OF_INSTANCES]; // 모든 정렬 공통 원본 데이터
static Record work_data[NUMBER_OF_INSTANCES]; // 정렬 실행용 복사 배열
static Record merge_temp[NUMBER_OF_INSTANCES]; // 병합 정렬 임시 배열
static long long compare_count; // 현재 정렬의 비교 횟수
static long long swap_count; // 현재 정렬의 교환 또는 이동 횟수

// 두 Record의 key 비교 및 비교 횟수 누적
static int compare_record(const Record *a, const Record *b)
{
    compare_count++; // key 비교 1회 누적
    return strcmp(a->key, b->key);
}

// 두 Record의 위치 교환 및 교환 횟수 누적
static void swap_record(Record *a, Record *b)
{
    Record temp;

    if (a == b) {
        return; // 같은 위치 교환 제외
    }

    temp = *a;
    *a = *b;
    *b = temp;
    swap_count++; // 실제 위치 교환 1회 누적
}

// 원본 배열을 작업 배열로 복사
static void copy_data(Record dest[], const Record src[])
{
    for (int i = 0; i < NUMBER_OF_INSTANCES; i++) {
        dest[i] = src[i]; // 동일 입력 사용을 위한 원본 복사
    }
}

// 과제 조건에 맞는 랜덤 문자열 데이터 생성
static void make_random_data(void)
{
    srand((unsigned int)time(NULL)); // 실행마다 다른 랜덤 문자열 생성

    for (int i = 0; i < NUMBER_OF_INSTANCES; i++) {
        int len = rand() % MAX_STRING_LENGTH + 1; // 문자열 길이 1~20 지정

        for (int j = 0; j < len; j++) {
            original_data[i].key[j] = (char)('A' + rand() % ALPHABET_SIZE); // A~Z 중 랜덤 문자 저장
        }

        original_data[i].key[len] = '\0'; // C 문자열 끝 표시
        original_data[i].original_index = i; // 같은 key의 원래 순서 비교용 값
    }
}

// 정렬 결과의 안정성 검사
static int check_stable(const Record data[])
{
    for (int i = 1; i < NUMBER_OF_INSTANCES; i++) {
        // 같은 key에서 original_index 증가 순서 유지 여부 확인
        if (strcmp(data[i - 1].key, data[i].key) == 0 &&
            data[i - 1].original_index > data[i].original_index) {
            return 0; // 같은 key의 원래 순서 뒤집힘
        }
    }

    return 1;
}

// 정렬 결과 파일 저장
static int write_output_file(const char *filename, const Record data[])
{
    FILE *fp = fopen(filename, "w"); // 출력 파일 쓰기 모드 열기

    if (fp == NULL) {
        fprintf(stderr, "%s 파일을 열 수 없습니다.\n", filename);
        return 0;
    }

    for (int i = 0; i < NUMBER_OF_INSTANCES; i++) {
        fprintf(fp, "%s\n", data[i].key); // 정렬된 문자열 한 줄씩 저장
    }

    fclose(fp);
    return 1;
}

// 버블 정렬 실행
static void bubble_sort(Record data[])
{
    for (int i = 0; i < NUMBER_OF_INSTANCES - 1; i++) {
        // 마지막 i개는 이미 정렬된 구간
        for (int j = 0; j < NUMBER_OF_INSTANCES - 1 - i; j++) {
            // 인접한 두 원소 비교 후 필요 시 교환
            if (compare_record(&data[j], &data[j + 1]) > 0) {
                swap_record(&data[j], &data[j + 1]);
            }
        }
    }
}

// 삽입 정렬 실행
static void insert_sort(Record data[])
{
    for (int i = 1; i < NUMBER_OF_INSTANCES; i++) {
        Record temp = data[i]; // 삽입 대상 임시 보관
        int j = i - 1; // 삽입 위치 탐색 시작점

        // temp보다 큰 원소들을 오른쪽으로 이동
        while (j >= 0 && compare_record(&data[j], &temp) > 0) {
            data[j + 1] = data[j]; // temp보다 큰 값 오른쪽 이동
            swap_count++; // 삽입 정렬 이동 횟수 누적
            j--;
        }

        if (j + 1 != i) {
            data[j + 1] = temp; // 비워진 위치에 temp 삽입
            swap_count++;
        }
    }
}

// 퀵 정렬의 pivot 기준 분할
static int partition(Record data[], int left, int right)
{
    int pivot_index = left + (right - left) / 2; // 가운데 값을 pivot으로 선택
    Record pivot; // pivot 값 보관
    int small = left; // pivot보다 작은 값이 들어갈 위치

    swap_record(&data[pivot_index], &data[right]); // pivot을 오른쪽 끝으로 이동
    pivot = data[right];

    for (int i = left; i < right; i++) {
        // pivot보다 작은 원소를 왼쪽 구간으로 이동
        if (compare_record(&data[i], &pivot) < 0) {
            swap_record(&data[small], &data[i]);
            small++;
        }
    }

    swap_record(&data[small], &data[right]); // pivot을 작은 값들 뒤에 배치
    return small;
}

// 퀵 정렬 재귀 처리
static void quick_sort_recursive(Record data[], int left, int right)
{
    if (left < right) {
        int pivot = partition(data, left, right); // pivot 위치 확정

        // pivot 왼쪽과 오른쪽 구간 재귀 정렬
        quick_sort_recursive(data, left, pivot - 1);
        quick_sort_recursive(data, pivot + 1, right);
    }
}

// 퀵 정렬 실행
static void quick_sort(Record data[])
{
    quick_sort_recursive(data, 0, NUMBER_OF_INSTANCES - 1);
}

// 병합 정렬의 두 정렬 구간 병합
static void merge(Record data[], int left, int mid, int right)
{
    int i = left; // 왼쪽 구간 시작 위치
    int j = mid + 1; // 오른쪽 구간 시작 위치
    int k = left; // 임시 배열 저장 위치

    // 왼쪽과 오른쪽 구간의 작은 값부터 임시 배열에 저장
    while (i <= mid && j <= right) {
        if (compare_record(&data[i], &data[j]) <= 0) {
            merge_temp[k++] = data[i++]; // 같을 때 왼쪽 값 우선 저장
        } else {
            merge_temp[k++] = data[j++]; // 오른쪽 값이 더 작은 경우 저장
        }
        swap_count++; // 임시 배열 이동 횟수 누적
    }

    // 왼쪽 구간 잔여 원소 복사
    while (i <= mid) {
        merge_temp[k++] = data[i++];
        swap_count++;
    }

    // 오른쪽 구간 잔여 원소 복사
    while (j <= right) {
        merge_temp[k++] = data[j++];
        swap_count++;
    }

    // 병합된 임시 배열을 원래 배열에 반영
    for (i = left; i <= right; i++) {
        data[i] = merge_temp[i]; // 병합 결과를 원래 배열로 복사
        swap_count++;
    }
}

// 병합 정렬 재귀 처리
static void merge_sort_recursive(Record data[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2; // 현재 구간의 중간 위치

        // 왼쪽 구간과 오른쪽 구간 분할 정렬
        merge_sort_recursive(data, left, mid);
        merge_sort_recursive(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

// 병합 정렬 실행
static void merge_sort(Record data[])
{
    merge_sort_recursive(data, 0, NUMBER_OF_INSTANCES - 1);
}

// 힙 정렬의 최대 힙 조건 복구
static void heapify(Record data[], int size, int root)
{
    while (1) {
        int largest = root; // 부모와 자식 중 가장 큰 값의 위치
        int left = root * 2 + 1; // 왼쪽 자식 위치
        int right = root * 2 + 2; // 오른쪽 자식 위치

        // 왼쪽 자식이 부모보다 큰 경우 largest 갱신
        if (left < size && compare_record(&data[left], &data[largest]) > 0) {
            largest = left;
        }

        // 오른쪽 자식이 현재 largest보다 큰 경우 largest 갱신
        if (right < size && compare_record(&data[right], &data[largest]) > 0) {
            largest = right;
        }

        if (largest == root) {
            break; // 부모가 가장 큰 경우 종료
        }

        swap_record(&data[root], &data[largest]);
        root = largest; // 바뀐 자식 위치에서 힙 조건 재확인
    }
}

// 힙 정렬 실행
static void heap_sort(Record data[])
{
    for (int i = NUMBER_OF_INSTANCES / 2 - 1; i >= 0; i--) {
        heapify(data, NUMBER_OF_INSTANCES, i); // 배열 전체 최대 힙 생성
    }

    for (int i = NUMBER_OF_INSTANCES - 1; i > 0; i--) {
        swap_record(&data[0], &data[i]); // 현재 최댓값을 정렬 구간 뒤로 이동
        heapify(data, i, 0); // 줄어든 힙 구간 최대 힙 재구성
    }
}

// 하나의 정렬 실행, 시간 측정, 결과 저장
static int run_sort(void (*sort_func)(Record[]), const char *filename, Result *result)
{
    clock_t start;
    clock_t end;

    copy_data(work_data, original_data); // 공통 원본 데이터 복사
    compare_count = 0; // 비교 횟수 초기화
    swap_count = 0; // 교환 또는 이동 횟수 초기화

    start = clock(); // 정렬 시작 시각 저장
    sort_func(work_data); // 정렬 함수 실행
    end = clock(); // 정렬 종료 시각 저장

    result->time_sec = (double)(end - start) / CLOCKS_PER_SEC; // 초 단위 수행 시간 계산
    result->compare_count = compare_count; // 비교 횟수 결과 저장
    result->swap_count = swap_count; // 교환 또는 이동 횟수 결과 저장
    result->stable = check_stable(work_data); // 안정성 결과 저장

    return write_output_file(filename, work_data);
}

// 정렬 분석 결과 표 출력
static void print_result_table(const Result results[])
{
    const char *names[SORT_COUNT] = {
        "Bubble Sort",
        "Insert Sort",
        "Quick Sort",
        "Merge Sort",
        "Heap Sort"
    };

    printf("Algorithm      | Time(s) | Compare | Swap | Stable\n");
    printf("---------------------------------------------------------------\n");

    // 각 정렬의 시간, 비교 횟수, 교환 횟수, 안정성 출력
    for (int i = 0; i < SORT_COUNT; i++) {
        printf("%-14s | %.3f   | %lld | %lld | %s\n",
               names[i],
               results[i].time_sec,
               results[i].compare_count,
               results[i].swap_count,
               results[i].stable ? "YES" : "NO");
    }
}

// 전체 프로그램 실행 흐름
int main(void)
{
    Result results[SORT_COUNT]; // 정렬 5개의 분석 결과 저장

    make_random_data(); // 공통 랜덤 입력 데이터 생성

    if (!run_sort(bubble_sort, "bubble_sort.out", &results[0])) { // 버블 정렬 실행 및 파일 저장
        return 1;
    }

    if (!run_sort(insert_sort, "insert_sort.out", &results[1])) { // 삽입 정렬 실행 및 파일 저장
        return 1;
    }

    if (!run_sort(quick_sort, "quick_sort.out", &results[2])) { // 퀵 정렬 실행 및 파일 저장
        return 1;
    }

    if (!run_sort(merge_sort, "merge_sort.out", &results[3])) { // 병합 정렬 실행 및 파일 저장
        return 1;
    }

    if (!run_sort(heap_sort, "heap_sort.out", &results[4])) { // 힙 정렬 실행 및 파일 저장
        return 1;
    }

    print_result_table(results); // 최종 분석 표 출력
    return 0;
}
