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

// from ruby sources
double wife_fun(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int result = 0;
    char used[100] = {0};
    int p[100] = {0};
    int index = 0; // depth
    int i = 0;
    for (;;) {
        int unused_idx = i;
        while (unused_idx < n && used[unused_idx]) ++unused_idx;
        if (unused_idx == n) {
            if (!index) break;
            i = p[--index];
            used[i++] = 0;
        } else {
            i = unused_idx;
            p[index] = i;
            used[i] = 1;
            ++index;
            if (index < n) {
                p[index] = i = 0;
                continue;
            }

            result += wife_fun_callback(p, n, k);

            i = p[--index];
            used[i] = 0;
            p[index] = ++i;
        }
    }
    return ((double)result) / fac(n);
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
