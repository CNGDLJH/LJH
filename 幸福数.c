#include <stdio.h>

#define MAX_NUM 10000
#define MAX_STEP 100  // ����������

int happy[MAX_NUM];          // �洢�Ҹ���
int derived[MAX_NUM][MAX_STEP];  // �������б����������е�����
int derived_cnt[MAX_NUM];    // ����������
int happy_cnt = 0;           // �Ҹ�������

// �ж��Ƿ�Ϊ�Ҹ�������¼����������ԭʼ����1�������м���������1��
int is_happy(int num) {
    int visited[MAX_NUM + 1] = {0};
    int path[MAX_STEP];
    int path_len = 0;
    int current = num;

    while (1) {
        if (current == 1) {
            // ��¼�����м�����������ԭʼ����������1��
            for (int i = 0; i < path_len; i++) {
                derived[happy_cnt][i] = path[i];
            }
            // �����¼1�������δ��¼��
            if (num != 1) {
                derived[happy_cnt][path_len++] = 1;
            }
            derived_cnt[happy_cnt] = path_len;
            return 1;
        }
        if (visited[current]) {
            return 0; // ѭ�������Ҹ���
        }
        if (path_len >= MAX_STEP - 1) { // ��һ��λ�ø�1
            return 0;
        }

        visited[current] = 1;

        // ������һ��ƽ����
        int sum = 0;
        int temp = current;
        while (temp > 0) {
            int digit = temp % 10;
            sum += digit * digit;
            temp /= 10;
        }

        // ��¼����������ǰ����������ԭʼ����
        if (current != num) {
            path[path_len++] = current;
        }

        current = sum;
    }
}

// �����ж�
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// ����Ƿ������������Ҹ���
int is_dependent(int x) {
    for (int i = 0; i < happy_cnt; i++) {
        if (happy[i] == x) continue;
        for (int j = 0; j < derived_cnt[i]; j++) {
            if (derived[i][j] == x) {
                return 1; // ������������
            }
        }
    }
    return 0;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // �ռ������������Ҹ���
    for (int i = m; i <= n; i++) {
        if (is_happy(i)) {
            happy[happy_cnt] = i;
            happy_cnt++;
        }
    }

    // ɸѡ�������е��Ҹ���
    int result[MAX_NUM], weight[MAX_NUM], res_cnt = 0;
    for (int i = 0; i < happy_cnt; i++) {
        int x = happy[i];
        if (!is_dependent(x)) {
            // Ȩ�� = ���������� �� 2���������� ��1����������
            int w = derived_cnt[i];
            if (is_prime(x)) {
                w *= 2;
            }
            result[res_cnt] = x;
            weight[res_cnt] = w;
            res_cnt++;
        }
    }

    // ����
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

    // ���
    if (res_cnt == 0) {
        printf("SAD\n");
    } else {
        for (int i = 0; i < res_cnt; i++) {
            printf("%d %d\n", result[i], weight[i]);
        }
    }

    return 0;
}
