#include <cstdio>
#include <cstdlib>
#include <ctime>

unsigned long long fac(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int next_perm(int *seq, int n) {
    int i = n - 2;
    for (; i >= 0 && seq[i] > seq[i + 1]; i -= 1);

    if (i < 0) return 0;

    int j = i + 1;
    for (; j < n && seq[j] >= seq[i]; j += 1);
    j -= 1;

    int tmp = seq[i];
    seq[i] = seq[j];
    seq[j] = tmp;

    i += 1;
    j = n - 1;
    for(; i < j; i++, j--) {
        tmp = seq[i];
        seq[i] = seq[j];
        seq[j] = tmp;
    }
    return 1;
}

int my_fun(int *seq, int n) {
    int result = 0;
    int m = 1;
    for (int i = 0; i < n; i++) {
        result += seq[i] * m;
        m *= -1;
    }
    return result;
}

inline int wife_fun_callback(int *seq, int n, int k) {
    int best = -1;
    int i = 0;
    for (; i < k; i++) {
        if (seq[i] > best) best = seq[i];
    }
    for (; i < n; i++) {
        if (seq[i] > best) break;
    }
    return seq[i] == n - 1;
}

double wife_fun(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int seq[100];
    for (int i = 0; i < n; i++) {
        seq[i] = i;
    }
    int all_result = 0;
    while (true) {
        all_result += wife_fun_callback(seq, n, k);
        int success = next_perm(seq, n);
        if (!success) break;
    }
    return ((double)all_result) / fac(n);
}

void best_wife(int n) {
    auto time_start = clock();
    double results[100];
    for (int k = 0; k < n; ++k) {
        results[k] = wife_fun(n, k);
    }
    int k_best = 0;
    for (int k = 0; k < n; ++k) {
        if (results[k_best] < results[k]) k_best = k;
    }
    auto time_end = clock();
    double duration = double(time_end - time_start) / CLOCKS_PER_SEC;
    printf("[[%d, %d, %.03f, [", n, k_best, results[k_best]);
    for (int k = 0; k < n; ++k) {
        if (k > 0) printf(", ");
        printf("%.03f", results[k]);
    }
    printf("], %.03f]\n", duration);
}


int main(int argc, char *argv[]) {
    for (int n = 1; n <= 10; ++n) {
        best_wife(n);
    }
}
