#define MAX_ELEMENTS 100

int scores[MAX_ELEMENTS];
int score[MAX_ELEMENTS];

int get_max_score(int n)
{
    int i;
    int largest;

    largest = scores[0];
    for (i = 1; i < n; i++) {
        if (scores[i] > largest) {
            largest = scores[i];
        }
    }
    return largest;
}

int find_max_score(int n)
{
    int i;
    int tmp;

    tmp = score[0];
    for (i = 1; i < n; i++) {
        if (score[i] > tmp) {
            tmp = score[i];
        }
    }
    return tmp;
}
