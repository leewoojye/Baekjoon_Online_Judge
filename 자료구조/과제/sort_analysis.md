# 자료구조 과제 #3

**제목:** 정렬 알고리즘 성능 분석 프로그램

**소속:** 공과대학 컴퓨터정보통신공학과

**학번 / 이름:** 2020112138 / 이우제

---

## 1. 과제 조건 및 수행 내용

- 5가지 정렬 알고리즘 구현: Bubble Sort, Insert Sort, Quick Sort, Merge Sort, Heap Sort
- 입력 방식: scanf 없이 프로그램 내부 고정값 NUMBER_OF_INSTANCES 50000 사용
- 랜덤 데이터: 길이 1~20의 대문자 랜덤 문자열 50000개 생성
- 성능 분석 항목: 수행 시간, 비교 횟수, swap 또는 이동 횟수, 안정성 여부
- 결과 파일 저장: bubble_sort.out, insert_sort.out, quick_sort.out, merge_sort.out, heap_sort.out 생성
- 시간 측정 범위: 정렬 함수 실행 시간만 포함하고 파일 저장 시간은 제외

---

## 2. 프로그램 전체 구조

본 프로그램은 문자열 레코드를 정렬하고 각 정렬 알고리즘의 성능을 비교하는 프로그램이다. 정렬 대상은 Record 구조체이며, 이 구조체에는 정렬 기준 문자열인 key와 안정성 검사용 위치 값인 original_index가 저장된다.

원본 데이터는 original_data 배열에 한 번 생성된다. 각 정렬을 실행하기 전에는 original_data를 work_data로 복사한다. 이렇게 하면 다섯 가지 정렬 알고리즘이 모두 동일한 입력 데이터를 사용하므로 공정한 성능 비교가 가능하다.

정렬 결과는 Result 구조체에 저장된다. Result에는 정렬 수행 시간, 비교 횟수, 교환 또는 이동 횟수, 안정성 검사 결과가 들어간다. 모든 정렬이 끝난 뒤 print_result_table 함수에서 결과를 표 형태로 출력한다.

---

## 3. 헤더와 상수 설명

프로그램에서 stdio.h, stdlib.h, string.h, time.h이 header를 사용했다.

stdio.h는 출력 및 파일 저장 함수 사용을 위해 포함하였다. stdlib.h는 srand와 rand를 이용해 랜덤 데이터를 생성하기 위해 포함하였다. string.h는 strcmp를 이용해 문자열을 사전식으로 비교하기 위해 포함하였다. time.h는 time과 clock을 사용하기 위해 포함하였다.

NUMBER_OF_INSTANCES는 과제 조건에 따라 50000으로 고정하였다. 사용자의 입력을 받지 않으므로 프로그램을 실행하면 바로 50000개의 랜덤 문자열을 생성하고 정렬 실험을 시작한다.

SORT_COUNT는 분석 대상 정렬 알고리즘의 개수인 5를 의미한다. 결과 배열과 출력 이름 배열의 크기를 이 값에 맞추었다.

코드 발췌

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    #define NUMBER_OF_INSTANCES 50000 // 과제 지정 데이터 개수
    #define MAX_STRING_LENGTH 20 // 랜덤 문자열 최대 길이
    #define ALPHABET_SIZE 26 // 대문자 알파벳 개수
    #define SORT_COUNT 5 // 분석 대상 정렬 개수

---

## 4. 구조체 설명

Record 구조체는 정렬 대상 데이터 하나를 표현한다. key에는 랜덤 문자열이 저장되고, original_index에는 데이터가 처음 생성된 위치가 저장된다. original_index는 정렬 안정성 검사에 사용된다.

Result 구조체는 정렬 알고리즘 하나의 분석 결과를 저장한다. time_sec에는 정렬 함수 실행 시간이 저장된다. compare_count에는 정렬 중 문자열을 비교한 횟수가 저장된다. swap_count에는 실제 swap 횟수 또는 자료 이동 횟수가 저장된다. stable에는 같은 key의 기존 순서가 유지되었는지 여부가 저장된다.

코드 발췌

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

---

## 5. 전역 배열과 카운터 설명

original_data는 모든 정렬이 공통으로 사용할 원본 데이터 배열이다. 이 배열은 직접 정렬하지 않고 처음 생성된 상태를 유지한다.

work_data는 각 정렬 실행 전에 original_data를 복사받는 작업 배열이다. 실제 정렬은 work_data에서 수행된다. 배열이 함수 인자로 전달되므로 정렬 함수 내부에서 원본 배열의 주소를 기준으로 값이 변경되는 call-by-reference 방식이 된다.

merge_temp는 병합 정렬에서 사용하는 임시 배열이다. 병합 과정에서 두 정렬 구간을 합친 결과를 잠시 저장한 뒤 다시 원래 배열로 복사한다.

compare_count는 현재 실행 중인 정렬의 비교 횟수를 저장하는 전역 변수이다. compare_record 함수가 호출될 때마다 1씩 증가한다.

swap_count는 현재 실행 중인 정렬의 교환 또는 이동 횟수를 저장하는 전역 변수이다. Bubble Sort, Quick Sort, Heap Sort에서는 실제 교환 횟수로 볼 수 있고, Insert Sort와 Merge Sort에서는 자료 이동 횟수까지 포함한다.

코드 발췌

    static Record original_data[NUMBER_OF_INSTANCES]; // 모든 정렬 공통 원본 데이터
    static Record work_data[NUMBER_OF_INSTANCES]; // 정렬 실행용 복사 배열
    static Record merge_temp[NUMBER_OF_INSTANCES]; // 병합 정렬 임시 배열
    static long long compare_count; // 현재 정렬의 비교 횟수
    static long long swap_count; // 현재 정렬의 교환 또는 이동 횟수

---

## 6. 랜덤 데이터 생성

make_random_data 함수는 과제 조건에 맞는 랜덤 문자열 50000개를 생성한다.

먼저 srand 함수에 time(NULL)을 전달하여 실행할 때마다 다른 랜덤 값이 나오도록 설정한다. 각 문자열의 길이는 rand()로 인해 1부터 20 사이의 값이 된다.

각 문자는 'A' + rand() % ALPHABET_SIZE 방식으로 생성한다. 따라서 문자열은 대문자 A부터 Z까지의 문자로만 구성된다.

문자열을 모두 채운 뒤에는 마지막 위치에 널 문자를 저장한다. 그리고 original_index에 현재 배열 인덱스를 저장하여 안정성 검사에 사용할 수 있도록 한다.

코드 발췌

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

---

## 7. 공통 함수 설명

compare_record 함수는 두 Record의 key를 strcmp로 비교한다. 이 함수가 호출될 때마다 compare_count를 1 증가시켜 비교 횟수를 누적한다. 모든 정렬 함수가 문자열 비교 시 이 함수를 사용하므로 비교 횟수 기준이 통일된다.

swap_record 함수는 두 Record의 위치를 교환한다. 자기 자신과의 교환은 실제 교환으로 보지 않으므로 카운트하지 않는다. 서로 다른 위치의 값이 실제로 바뀌면 swap_count를 1 증가시킨다.

copy_data 함수는 original_data를 work_data로 복사한다. 각 정렬을 실행하기 전에 이 함수를 호출하여 모든 정렬이 같은 입력 데이터에서 시작하도록 한다.

check_stable 함수는 정렬 결과의 안정성을 검사한다. 인접한 두 원소의 key가 같을 때 original_index가 감소하면 같은 key의 상대 순서가 뒤집힌 것이므로 불안정 정렬로 판단한다. 끝까지 역전이 없으면 안정성이 유지된 것으로 판단한다.

write_output_file 함수는 정렬된 문자열을 파일에 저장한다. 파일은 쓰기 모드로 열고, 각 문자열을 한 줄에 하나씩 출력한다. 이 함수는 정렬 시간이 측정된 뒤 호출되므로 파일 저장 시간은 수행 시간에 포함되지 않는다.

코드 발췌

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

---

## 8. run_sort 함수 설명

run_sort 함수는 하나의 정렬 알고리즘 실행 과정을 공통으로 처리한다.

먼저 copy_data로 원본 데이터를 작업 배열에 복사한다. 그 다음 compare_count와 swap_count를 0으로 초기화한다.

정렬이 끝나면 compare_count와 swap_count를 Result 구조체에 저장한다. 그리고 check_stable을 호출하여 안정성 여부를 계산한다. 마지막으로 write_output_file을 호출하여 정렬 결과를 파일로 저장한다.

코드 발췌

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

---

## 9. Bubble Sort 설명

Bubble Sort는 인접한 두 원소를 비교하고, 왼쪽 원소가 오른쪽 원소보다 크면 교환하는 방식으로 정렬한다.

바깥 반복이 한 번 끝날 때마다 가장 큰 원소가 뒤쪽에 확정된다. 따라서 안쪽 반복은 NUMBER_OF_INSTANCES - 1 - i까지만 수행한다.

같은 key인 경우에는 compare_record 결과가 0이므로 교환하지 않는다. 따라서 같은 key의 상대 순서가 유지되어 안정 정렬로 동작한다.

Bubble Sort는 무작위 데이터에서 비교 횟수가 매우 많고, 인접 교환도 자주 발생하므로 수행 시간이 가장 길게 나타나는 편이다.

코드 발췌

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

---

## 10. Insert Sort 설명

Insert Sort는 i번째 원소를 왼쪽의 이미 정렬된 구간에 삽입하는 방식으로 동작한다.

현재 삽입할 값을 temp에 저장하고, 왼쪽 원소들이 temp보다 큰 동안 오른쪽으로 한 칸씩 이동시킨다. 이때의 이동 횟수도 swap_count에 누적한다.

같은 key를 만나면 compare_record 결과가 0이므로 while 조건이 거짓이 되어 이동을 멈춘다. 따라서 같은 key의 기존 순서가 유지되어 안정 정렬로 동작한다.

무작위 데이터에서는 삽입 위치를 찾기 위해 많은 원소를 이동해야 하므로 O(N^2) 특성이 나타난다.

코드 발췌

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

---

## 11. Quick Sort 설명

Quick Sort는 pivot을 기준으로 배열을 분할하고, 왼쪽 구간과 오른쪽 구간을 재귀적으로 정렬한다.

partition 함수는 현재 구간의 가운데 위치를 pivot 후보로 선택한다. pivot을 오른쪽 끝으로 옮긴 뒤, pivot보다 작은 원소를 왼쪽 구간으로 이동시킨다. 마지막에는 pivot을 작은 값들 뒤에 배치하여 pivot의 최종 위치를 확정한다.

quick_sort_recursive 함수는 partition이 반환한 pivot 위치를 기준으로 왼쪽 구간과 오른쪽 구간을 다시 정렬한다.

Quick Sort는 평균적으로 빠른 정렬 알고리즘이지만, 분할 과정에서 멀리 떨어진 원소끼리 교환될 수 있다. 따라서 같은 key의 상대 순서가 보장되지 않아 불안정 정렬로 판단될 수 있다.

코드 발췌

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

---

## 12. Merge Sort 설명

Merge Sort는 배열을 절반씩 나누어 정렬한 뒤, 두 정렬 구간을 다시 병합하는 방식으로 동작한다.

merge_sort_recursive 함수는 현재 구간을 왼쪽 구간과 오른쪽 구간으로 나누어 재귀 정렬한다. 두 구간이 정렬된 후에는 merge 함수가 두 구간을 하나의 정렬된 구간으로 합친다.

merge 함수에서는 왼쪽 구간의 시작 위치와 오른쪽 구간의 시작 위치를 각각 i와 j로 관리한다. 두 key를 비교해 더 작은 값을 merge_temp에 저장하고, 한쪽 구간이 먼저 끝나면 남은 원소를 순서대로 복사한다.

두 key가 같을 때는 왼쪽 값을 먼저 저장한다. 이 규칙 때문에 같은 key의 원래 순서가 유지되어 Merge Sort는 안정 정렬로 동작한다.

코드 발췌

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

---

## 13. Heap Sort 설명

Heap Sort는 배열을 최대 힙으로 만든 뒤, 루트에 있는 최댓값을 뒤쪽으로 보내는 과정을 반복한다.

heapify 함수는 root 위치를 기준으로 부모와 두 자식을 비교하여 가장 큰 값을 부모 위치로 올린다. 교환이 발생하면 바뀐 자식 위치에서 다시 힙 조건을 확인한다.

heap_sort 함수는 먼저 배열 전체를 최대 힙으로 만든다. 이후 루트와 마지막 원소를 교환하여 최댓값을 정렬 구간 뒤쪽에 확정하고, 남은 구간에 대해 다시 heapify를 수행한다.

Heap Sort는 O(N log N)의 시간 복잡도를 가지지만, 루트와 마지막 원소의 반복 교환 때문에 같은 key의 상대 순서가 유지되지 않을 수 있다. 따라서 불안정 정렬로 판단될 수 있다.

코드 발췌

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

---

## 14. main 실행 흐름

main 함수에서는 Result 배열을 선언하여 다섯 정렬의 결과를 저장한다.

먼저 make_random_data를 호출하여 공통 랜덤 입력 데이터를 생성한다. 이후 run_sort를 다섯 번 호출하여 Bubble Sort, Insert Sort, Quick Sort, Merge Sort, Heap Sort를 차례대로 실행한다.

각 run_sort 호출은 같은 original_data를 work_data로 복사한 뒤 정렬을 수행한다. 따라서 앞에서 실행된 정렬 결과가 뒤의 정렬에 영향을 주지 않는다.

정렬별 결과 파일은 bubble_sort.out, insert_sort.out, quick_sort.out, merge_sort.out, heap_sort.out으로 저장된다. 모든 정렬이 끝나면 print_result_table 함수가 시간, 비교 횟수, 교환 또는 이동 횟수, 안정성 여부를 표 형태로 출력한다.

코드 발췌

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

---

## 15. 실행 결과 분석

Bubble Sort와 Insert Sort는 O(N^2) 계열의 알고리즘이므로 NUMBER_OF_INSTANCES가 50000일 때 비교와 이동 횟수가 매우 크게 나타난다. 특히 Bubble Sort는 인접한 원소를 반복적으로 비교하므로 수행 시간이 길게 나타난다.

Quick Sort, Merge Sort, Heap Sort는 O(N log N) 계열의 알고리즘이므로 대용량 데이터에서 Bubble Sort와 Insert Sort보다 빠르게 동작한다.

안정성 측면에서는 Bubble Sort, Insert Sort, Merge Sort가 안정 정렬로 동작한다. Bubble Sort와 Insert Sort는 같은 key일 때 교환하거나 이동하지 않기 때문이다. Merge Sort는 같은 key일 때 왼쪽 원소를 먼저 복사하기 때문에 안정성이 유지된다.

Quick Sort와 Heap Sort는 정렬 과정에서 멀리 떨어진 원소를 교환할 수 있으므로 같은 key의 상대 순서가 바뀔 수 있다. 따라서 안정성이 보장되지 않는다.

전체적으로 속도만 고려하면 Quick Sort, Merge Sort, Heap Sort가 유리하다. 그러나 같은 key의 순서 보존까지 고려하면 Merge Sort가 대용량 문자열 레코드 정렬에 적합하다고 볼 수 있다.
