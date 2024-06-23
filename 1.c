#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PASSWORD "1234"
#define MAX_TRANSACTIONS 100

typedef struct {
    char date[20];
    char type[10];
    char category[20];
    char description[50];
    int amount;
} Transaction;

Transaction transactions[MAX_TRANSACTIONS];
int transactionCount = 0;
int balance = 0;
int monthlyBudget = 0;
int savingsGoal = 0;
int cashGoal = 0;
int stocksGoal = 0;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void setMonthlyBudget() {
    int income;
    int housingPercentage, foodPercentage, transportPercentage, otherPercentage;

    printf("========================================\n");
    printf("            ���� ���� ����              \n");
    printf("========================================\n");
    printf("�� ������ �Է��ϼ���: ");
    scanf("%d", &income);
    printf("----------------------------------------\n");

    printf("�ְź� ������ �Է��ϼ��� (%%): ");
    scanf("%d", &housingPercentage);
    printf("�ĺ� ������ �Է��ϼ��� (%%): ");
    scanf("%d", &foodPercentage);
    printf("����� ������ �Է��ϼ��� (%%): ");
    scanf("%d", &transportPercentage);
    printf("��Ÿ ������ �Է��ϼ��� (%%): ");
    scanf("%d", &otherPercentage);

    int housingBudget = (income * housingPercentage) / 100;
    int foodBudget = (income * foodPercentage) / 100;
    int transportBudget = (income * transportPercentage) / 100;
    int otherBudget = (income * otherPercentage) / 100;
    monthlyBudget = housingBudget + foodBudget + transportBudget + otherBudget;
    int investableAmount = income - monthlyBudget;

    printf("========================================\n");
    printf("            ���� ���� ���              \n");
    printf("========================================\n");
    printf("�ְź� ����: %d\n", housingBudget);
    printf("�ĺ� ����: %d\n", foodBudget);
    printf("����� ����: %d\n", transportBudget);
    printf("��Ÿ ����: %d\n", otherBudget);
    printf("----------------------------------------\n");
    printf("������ ���� ����: %d\n", monthlyBudget);
    printf("----------------------------------------\n");
    printf("���� ���� �ݾ�: %d\n", investableAmount);
    printf("========================================\n");

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}


void setFinancialGoals() {
    int income;
    int savingsPercentage, cashPercentage, stocksPercentage;
    int age;

    printf("========================================\n");
    printf("             �繫 ��ǥ ����             \n");
    printf("========================================\n");
    printf("���̸� �Է��ϼ���: ");
    scanf("%d", &age);
    printf("�ڻ��� �Է��ϼ���: ");
    scanf("%d", &income);
    printf("----------------------------------------\n");

    printf("���� ��ǥ ������ �Է��ϼ��� (%%): ");
    scanf("%d", &savingsPercentage);

    printf("���� ��ǥ ������ �Է��ϼ��� (%%): ");
    scanf("%d", &cashPercentage);

    printf("���� ��ǥ ������ �Է��ϼ��� (%%): ");
    scanf("%d", &stocksPercentage);

    savingsGoal = (income * savingsPercentage) / 100;
    cashGoal = (income * cashPercentage) / 100;
    stocksGoal = (income * stocksPercentage) / 100;

    printf("========================================\n");
    printf("             �繫 ��ǥ ���             \n");
    printf("========================================\n");
    printf("���� ��ǥ �ݾ�: %d\n", savingsGoal);
    printf("���� ��ǥ �ݾ�: %d\n", cashGoal);
    printf("���� ��ǥ �ݾ�: %d\n", stocksGoal);
    printf("========================================\n");

    int riskyAssetsPercentage = 100 - age;
    int lowerBound = riskyAssetsPercentage - 10;
    int upperBound = riskyAssetsPercentage + 10;

    if (stocksPercentage > upperBound) {
        printf("���� ����: ������\n");
    }
    else if (stocksPercentage < lowerBound) {
        printf("���� ����: ������\n");
    }
    else {
        printf("���� ����: �߸���\n");
    }

    printf("========================================\n");

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}

void drawBar(float percentage) {
    int bars = (int)(percentage / 2); // ����׷��� ���̸� 50ĭ���� ���� (100% / 5 = 20)
    for (int i = 0; i < bars; i++) {
        printf("#");
    }
    printf(" %.1f%%\n", percentage); // �Ҽ��� �� �ڸ����� ǥ��
}

void viewFinancialStatus() {
    int totalIncome = 0;
    int totalExpense = 0;

    // �� ���԰� �� ���� ���
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].type, "����") == 0) {
            totalIncome += transactions[i].amount;
        }
        else if (strcmp(transactions[i].type, "����") == 0) {
            totalExpense += transactions[i].amount;
        }
    }

    balance = totalIncome - totalExpense;

    printf("========================================\n");
    printf("              �繫 ���� ����            \n");
    printf("========================================\n");
    printf("-----------------�� ����----------------\n");
    printf("�� ����: %d\n", totalIncome);
    printf("�� ����: %d\n", totalExpense);
    printf("�ܿ� �ݾ�: %d\n", balance);
    printf("-----------------�� �ڻ�----------------\n");

    int savings, cash, stocks, loans, age;
    printf("���� �ݾ��� �Է��ϼ���: ");
    scanf("%d", &savings);
    printf("���� �ݾ��� �Է��ϼ���: ");
    scanf("%d", &cash);
    printf("�ֽ� �ݾ��� �Է��ϼ���: ");
    scanf("%d", &stocks);
    printf("���� �ݾ��� �Է��ϼ���: ");
    scanf("%d", &loans);
    printf("----------------------------------------\n");
    printf("�м��� ���� ���̸� �Է��ϼ���: ");
    scanf("%d", &age);

    int totalAssets = savings + cash + stocks + balance;
    float savingsPercentage = (savings / (float)totalAssets) * 100;
    float cashPercentage = (cash / (float)totalAssets) * 100;
    float stocksPercentage = (stocks / (float)totalAssets) * 100;
    float loansPercentage = (loans / (float)totalAssets) * 100;
    printf("----------------------------------------\n");
    printf("------------------�м�------------------\n");
    printf("\n����: ");
    drawBar(savingsPercentage);
    printf("����: ");
    drawBar(cashPercentage);
    printf("�ֽ�: ");
    drawBar(stocksPercentage);
    printf("����: ");
    drawBar(loansPercentage);
    printf("========================================\n");

    // ���� ���� �м�
    int riskyAssetsPercentage = 100 - age;
    int lowerBound = riskyAssetsPercentage - 10;
    int upperBound = riskyAssetsPercentage + 10;

    if (stocksPercentage > upperBound) {
        printf("���� ����: ������\n");
    }
    else if (stocksPercentage < lowerBound) {
        printf("���� ����: ������\n");
    }
    else {
        printf("���� ����: �߸���\n");
    }

    printf("========================================\n");

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}


void viewTransactions() {
    int totalIncome = 0;
    int totalExpense = 0;
    int categorySum[100] = { 0 };
    int categoryCount = 0;
    char categories[100][20];

    printf("========================================\n");
    printf("               �ŷ� ����                \n");
    printf("========================================\n");

    for (int i = 0; i < transactionCount; i++) {
        printf("%02d | ��¥: %s\n", i + 1, transactions[i].date);
        printf("   | ����: %s\n", transactions[i].type);
        printf("   | ī�װ�: %s\n", transactions[i].category);
        printf("   | ����: %s\n", transactions[i].description);
        printf("   | �ݾ�: %d\n", transactions[i].amount);
        printf("----------------------------------------\n");

        if (strcmp(transactions[i].type, "����") == 0) {
            totalIncome += transactions[i].amount;
        }
        else if (strcmp(transactions[i].type, "����") == 0) {
            totalExpense += transactions[i].amount;

            int categoryIndex = -1;
            for (int j = 0; j < categoryCount; j++) {
                if (strcmp(categories[j], transactions[i].category) == 0) {
                    categoryIndex = j;
                    break;
                }
            }

            if (categoryIndex == -1) {
                strcpy(categories[categoryCount], transactions[i].category);
                categorySum[categoryCount] = transactions[i].amount;
                categoryCount++;
            }
            else {
                categorySum[categoryIndex] += transactions[i].amount;
            }
        }
    }

    printf("�� ����: %d\n", totalIncome);
    printf("�� ����: %d\n", totalExpense);
    printf("�ܿ� �ݾ�: %d\n", totalIncome - totalExpense);
    printf("========================================\n");
    printf("                     \n");
    printf("========================================\n");
    printf("          ī�װ��� ���� ����          \n");
    printf("----------------------------------------\n");
    for (int i = 0; i < categoryCount; i++) {
        float percentage = (categorySum[i] / (float)totalExpense) * 100;
        printf("%s: %.2f%%\n", categories[i], percentage);
    }
    printf("========================================\n");

    printf("Press the Enter key\n");

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}


void writeTransaction() {
    if (transactionCount >= MAX_TRANSACTIONS) {
        printf("�� �̻� �ŷ��� �߰��� �� �����ϴ�.\n");
        return;
    }

    char type[10];
    char date[20];
    char category[20];
    char description[50];
    int amount;


    printf("========================================\n");
    printf("                 �����                 \n");
    printf("========================================\n");
    printf("��¥�� �Է��ϼ��� (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("                                \n");
    printf("����� ������ �Է��ϼ��� (����/����): ");
    scanf("%s", type);
    printf("                           \n");
    printf("ī�װ��� �Է��ϼ���: ");
    scanf("%s", category);
    printf("                          \n");
    printf("������ �Է��ϼ���: ");
    scanf(" %[^\n]", description); // ���� ���� ���ڿ� �Է� �ޱ�
    printf("                              \n");
    printf("�ݾ��� �Է��ϼ���: ");
    scanf("%d", &amount);
    printf("                          \n");
    printf("========================================\n");

    strcpy(transactions[transactionCount].date, date);
    strcpy(transactions[transactionCount].type, type);
    strcpy(transactions[transactionCount].category, category);
    strcpy(transactions[transactionCount].description, description);
    transactions[transactionCount].amount = amount;

    if (strcmp(type, "����") == 0) {
        balance += amount;
    }
    else if (strcmp(type, "����") == 0) {
        balance -= amount;
    }
    else {
        printf("�߸��� �����Դϴ�. ���� �Ǵ� ���⸸ �����մϴ�.\n");
        return;
    }

    transactionCount++;

    printf("========================================\n");
    printf("              �ŷ� �߰� �Ϸ�            \n");
    printf("========================================\n");
    printf("��¥: %s\n", date);
    printf("����: %s\n", type);
    printf("ī�װ�: %s\n", category);
    printf("����: %s\n", description);
    printf("�ݾ�: %d\n", amount);
    printf("�ܿ� �ݾ�: %d\n", balance);
    printf("========================================\n");

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}



void modifyOrDeleteTransaction() {
    int index;
    printf("========================================\n");
    printf("���� �Ǵ� ������ �ŷ��� ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= transactionCount) {
        printf("�߸��� ��ȣ�Դϴ�.\n");
        return;
    }

    printf("----------------------------------------\n");
    printf(" ������ �ŷ�\n \n��¥: %s\n ����: %s\n ī�װ�: %s\n ����: %s\n �ݾ�: %d\n",
        transactions[index].date, transactions[index].type, transactions[index].category, transactions[index].description, transactions[index].amount);

    int choice;
    printf("========================================\n");
    printf("   ���� �� 1��            ���� �� 2��\n");
    printf("   ����:");
    scanf("%d", &choice);

    if (choice == 1) {
        char type[10];
        char category[20];
        char description[50];
        int amount;

        printf("========================================\n");
        printf("------------------����------------------\n");
        printf("\n����� ������ �Է��ϼ��� (����/����):");
        scanf("%s", type);
        printf("���ο� ī�װ��� �Է��ϼ���: ");
        scanf("%s", category);
        printf("���ο� ������ �Է��ϼ���: ");
        scanf(" %[^\n]", description); // ���� ���� ���ڿ� �Է� �ޱ�
        printf("���ο� �ݾ��� �Է��ϼ���: ");
        scanf("%d", &amount);

        if (strcmp(transactions[index].type, "����") == 0) {
            balance -= transactions[index].amount;
        }
        else if (strcmp(transactions[index].type, "����") == 0) {
            balance += transactions[index].amount;
        }

        strcpy(transactions[index].type, type);
        strcpy(transactions[index].category, category);
        strcpy(transactions[index].description, description);
        transactions[index].amount = amount;

        if (strcmp(type, "����") == 0) {
            balance += amount;
        }
        else if (strcmp(type, "����") == 0) {
            balance -= amount;
        }
        else {
            printf("�߸��� �����Դϴ�. ���� �Ǵ� ���⸸ �����մϴ�.\n");
            return;
        }

        printf("========================================\n");
        printf("           �ŷ� ���� �Ϸ�               \n");
        printf("========================================\n");
        printf("��¥: %s\n", transactions[index].date);
        printf("����: %s\n", type);
        printf("ī�װ�: %s\n", category);
        printf("����: %s\n", description);
        printf("�ݾ�: %d\n", amount);
        printf("�ܿ� �ݾ�: %d\n", balance);
        printf("========================================\n");
    }
    else if (choice == 2) {
        if (strcmp(transactions[index].type, "����") == 0) {
            balance -= transactions[index].amount;
        }
        else if (strcmp(transactions[index].type, "����") == 0) {
            balance += transactions[index].amount;
        }

        for (int i = index; i < transactionCount - 1; i++) {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;

        printf("========================================\n");
        printf("           �ŷ� ���� �Ϸ�               \n");
        printf("========================================\n");
    }
    else {
        printf("�߸��� �����Դϴ�.\n");
    }

    getchar();  // Enter Ű �Է��� �Һ��Ͽ� ȭ���� ��� �������� �ʵ��� ��
    getchar();
}

int main() {
    char inputPassword[20];
    int choice;

    // ��й�ȣ �Է�

    printf("========================================\n");
    printf("                 �����                 \n");
    printf("========================================\n");
    printf("����� : ������                         \n");
    printf("                                   \n");
    printf("��й�ȣ�� �Է��ϼ���: ");
    scanf("%s", inputPassword);

    // ��й�ȣ ����
    if (strcmp(inputPassword, PASSWORD) != 0) {
        printf("��й�ȣ�� �߸��Ǿ����ϴ�.\n");
        return 1;
    }

    // ȭ�� �����
    clearScreen();

    // �޴�
    while (1) {

        printf("========================================\n");
        printf("                 �����                 \n");
        printf("========================================\n");
        printf("\n����� �޴�:\n");
        printf("                          \n");
        printf("1. ����/���� ���� �߰�\n");
        printf("2. ����/���� ���� ��ȸ\n");
        printf("3. ���� ���� �� ����\n");
        printf("4. ���� ���� ����\n");
        printf("5. �繫 ��ǥ ����\n");
        printf("6. �繫 ���� ����\n");
        printf("7. ����\n");
        printf("                              \n");
        printf("========================================\n");
        printf("����: ");
        scanf("%d", &choice);

        // ȭ�� �����
        clearScreen();

        switch (choice) {
        case 1:
            writeTransaction();
            break;
        case 2:
            viewTransactions();
            break;
        case 3:
            viewTransactions();
            modifyOrDeleteTransaction();
            break;
        case 4:
            setMonthlyBudget();
            break;
        case 5:
            setFinancialGoals();
            break;
        case 6:
            viewFinancialStatus();
            break;
        case 7:
            printf("���α׷��� �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }

        // ȭ�� �����
        clearScreen();
    }

    return 0;
}
