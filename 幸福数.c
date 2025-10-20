#include <stdio.h>

#define MAX_NUM 10000
#define MAX_STEP 100  // 最大迭代步数

int happy[MAX_NUM];          // 存储幸福数
int derived[MAX_NUM][MAX_STEP];  // 衍生数列表（迭代过程中的数）
int derived_cnt[MAX_NUM];    // 衍生数数量
int happy_cnt = 0;           // 幸福数总数

// 判断是否为幸福数，记录衍生数（从原始数到1的所有中间数，包含1）
int is_happy(int num) {
    int visited[MAX_NUM + 1] = {0};
    int path[MAX_STEP];
    int path_len = 0;
    int current = num;

    while (1) {
        if (current == 1) {
            // 记录所有中间数（不包含原始数，但包含1）
            for (int i = 0; i < path_len; i++) {
                derived[happy_cnt][i] = path[i];
            }
            // 补充记录1（如果尚未记录）
            if (num != 1) {
                derived[happy_cnt][path_len++] = 1;
            }
            derived_cnt[happy_cnt] = path_len;
            return 1;
        }
        if (visited[current]) {
            return 0; // 循环，非幸福数
        }
        if (path_len >= MAX_STEP - 1) { // 留一个位置给1
            return 0;
        }

        visited[current] = 1;

        // 计算下一次平方和
        int sum = 0;
        int temp = current;
        while (temp > 0) {
            int digit = temp % 10;
            sum += digit * digit;
            temp /= 10;
        }

        // 记录衍生数（当前数，不包含原始数）
        if (current != num) {
            path[path_len++] = current;
        }

        current = sum;
    }
}

// 素数判断
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// 检查是否依附于其他幸福数
int is_dependent(int x) {
    for (int i = 0; i < happy_cnt; i++) {
        if (happy[i] == x) continue;
        for (int j = 0; j < derived_cnt[i]; j++) {
            if (derived[i][j] == x) {
                return 1; // 依附于其他数
            }
        }
    }
    return 0;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // 收集区间内所有幸福数
    for (int i = m; i <= n; i++) {
        if (is_happy(i)) {
            happy[happy_cnt] = i;
            happy_cnt++;
        }
    }

    // 筛选特立独行的幸福数
    int result[MAX_NUM], weight[MAX_NUM], res_cnt = 0;
    for (int i = 0; i < happy_cnt; i++) {
        int x = happy[i];
        if (!is_dependent(x)) {
            // 权重 = 衍生数个数 × 2（素数）或 ×1（非素数）
            int w = derived_cnt[i];
            if (is_prime(x)) {
                w *= 2;
            }
            result[res_cnt] = x;
            weight[res_cnt] = w;
            res_cnt++;
        }
    }

    // 排序
    for (int i = 0; i < res_cnt - 1; i++) {
        for (int j = 0; j < res_cnt - 1 - i; j++) {
            if (result[j] > result[j + 1]) {
                int temp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = temp;
                temp = weight[j];
                weight[j] = weight[j + 1];
                weight[j + 1] = temp;
            }
        }
    }

    // 输出
    if (res_cnt == 0) {
        printf("SAD\n");
    } else {
        for (int i = 0; i < res_cnt; i++) {
            printf("%d %d\n", result[i], weight[i]);
        }
    }

    return 0;
}
