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
    printf("            월별 예산 설정              \n");
    printf("========================================\n");
    printf("월 수입을 입력하세요: ");
    scanf("%d", &income);
    printf("----------------------------------------\n");

    printf("주거비 비율을 입력하세요 (%%): ");
    scanf("%d", &housingPercentage);
    printf("식비 비율을 입력하세요 (%%): ");
    scanf("%d", &foodPercentage);
    printf("교통비 비율을 입력하세요 (%%): ");
    scanf("%d", &transportPercentage);
    printf("기타 비율을 입력하세요 (%%): ");
    scanf("%d", &otherPercentage);

    int housingBudget = (income * housingPercentage) / 100;
    int foodBudget = (income * foodPercentage) / 100;
    int transportBudget = (income * transportPercentage) / 100;
    int otherBudget = (income * otherPercentage) / 100;
    monthlyBudget = housingBudget + foodBudget + transportBudget + otherBudget;
    int investableAmount = income - monthlyBudget;

    printf("========================================\n");
    printf("            월별 예산 결과              \n");
    printf("========================================\n");
    printf("주거비 예산: %d\n", housingBudget);
    printf("식비 예산: %d\n", foodBudget);
    printf("교통비 예산: %d\n", transportBudget);
    printf("기타 예산: %d\n", otherBudget);
    printf("----------------------------------------\n");
    printf("설정된 월별 예산: %d\n", monthlyBudget);
    printf("----------------------------------------\n");
    printf("투자 가능 금액: %d\n", investableAmount);
    printf("========================================\n");

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}


void setFinancialGoals() {
    int income;
    int savingsPercentage, cashPercentage, stocksPercentage;
    int age;

    printf("========================================\n");
    printf("             재무 목표 설정             \n");
    printf("========================================\n");
    printf("나이를 입력하세요: ");
    scanf("%d", &age);
    printf("자산을 입력하세요: ");
    scanf("%d", &income);
    printf("----------------------------------------\n");

    printf("저축 목표 비율을 입력하세요 (%%): ");
    scanf("%d", &savingsPercentage);

    printf("현금 목표 비율을 입력하세요 (%%): ");
    scanf("%d", &cashPercentage);

    printf("투자 목표 비율을 입력하세요 (%%): ");
    scanf("%d", &stocksPercentage);

    savingsGoal = (income * savingsPercentage) / 100;
    cashGoal = (income * cashPercentage) / 100;
    stocksGoal = (income * stocksPercentage) / 100;

    printf("========================================\n");
    printf("             재무 목표 결과             \n");
    printf("========================================\n");
    printf("저축 목표 금액: %d\n", savingsGoal);
    printf("현금 목표 금액: %d\n", cashGoal);
    printf("투자 목표 금액: %d\n", stocksGoal);
    printf("========================================\n");

    int riskyAssetsPercentage = 100 - age;
    int lowerBound = riskyAssetsPercentage - 10;
    int upperBound = riskyAssetsPercentage + 10;

    if (stocksPercentage > upperBound) {
        printf("투자 성향: 공격형\n");
    }
    else if (stocksPercentage < lowerBound) {
        printf("투자 성향: 안정형\n");
    }
    else {
        printf("투자 성향: 중립형\n");
    }

    printf("========================================\n");

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}

void drawBar(float percentage) {
    int bars = (int)(percentage / 2); // 막대그래프 길이를 50칸으로 제한 (100% / 5 = 20)
    for (int i = 0; i < bars; i++) {
        printf("#");
    }
    printf(" %.1f%%\n", percentage); // 소수점 한 자리까지 표시
}

void viewFinancialStatus() {
    int totalIncome = 0;
    int totalExpense = 0;

    // 총 수입과 총 지출 계산
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].type, "수입") == 0) {
            totalIncome += transactions[i].amount;
        }
        else if (strcmp(transactions[i].type, "지출") == 0) {
            totalExpense += transactions[i].amount;
        }
    }

    balance = totalIncome - totalExpense;

    printf("========================================\n");
    printf("              재무 상태 보기            \n");
    printf("========================================\n");
    printf("-----------------내 계좌----------------\n");
    printf("총 수입: %d\n", totalIncome);
    printf("총 지출: %d\n", totalExpense);
    printf("잔여 금액: %d\n", balance);
    printf("-----------------내 자산----------------\n");

    int savings, cash, stocks, loans, age;
    printf("저축 금액을 입력하세요: ");
    scanf("%d", &savings);
    printf("현금 금액을 입력하세요: ");
    scanf("%d", &cash);
    printf("주식 금액을 입력하세요: ");
    scanf("%d", &stocks);
    printf("대출 금액을 입력하세요: ");
    scanf("%d", &loans);
    printf("----------------------------------------\n");
    printf("분석을 위해 나이를 입력하세요: ");
    scanf("%d", &age);

    int totalAssets = savings + cash + stocks + balance;
    float savingsPercentage = (savings / (float)totalAssets) * 100;
    float cashPercentage = (cash / (float)totalAssets) * 100;
    float stocksPercentage = (stocks / (float)totalAssets) * 100;
    float loansPercentage = (loans / (float)totalAssets) * 100;
    printf("----------------------------------------\n");
    printf("------------------분석------------------\n");
    printf("\n저축: ");
    drawBar(savingsPercentage);
    printf("현금: ");
    drawBar(cashPercentage);
    printf("주식: ");
    drawBar(stocksPercentage);
    printf("대출: ");
    drawBar(loansPercentage);
    printf("========================================\n");

    // 투자 성향 분석
    int riskyAssetsPercentage = 100 - age;
    int lowerBound = riskyAssetsPercentage - 10;
    int upperBound = riskyAssetsPercentage + 10;

    if (stocksPercentage > upperBound) {
        printf("투자 성향: 공격형\n");
    }
    else if (stocksPercentage < lowerBound) {
        printf("투자 성향: 안정형\n");
    }
    else {
        printf("투자 성향: 중립형\n");
    }

    printf("========================================\n");

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}


void viewTransactions() {
    int totalIncome = 0;
    int totalExpense = 0;
    int categorySum[100] = { 0 };
    int categoryCount = 0;
    char categories[100][20];

    printf("========================================\n");
    printf("               거래 내역                \n");
    printf("========================================\n");

    for (int i = 0; i < transactionCount; i++) {
        printf("%02d | 날짜: %s\n", i + 1, transactions[i].date);
        printf("   | 유형: %s\n", transactions[i].type);
        printf("   | 카테고리: %s\n", transactions[i].category);
        printf("   | 설명: %s\n", transactions[i].description);
        printf("   | 금액: %d\n", transactions[i].amount);
        printf("----------------------------------------\n");

        if (strcmp(transactions[i].type, "수입") == 0) {
            totalIncome += transactions[i].amount;
        }
        else if (strcmp(transactions[i].type, "지출") == 0) {
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

    printf("총 수입: %d\n", totalIncome);
    printf("총 지출: %d\n", totalExpense);
    printf("잔여 금액: %d\n", totalIncome - totalExpense);
    printf("========================================\n");
    printf("                     \n");
    printf("========================================\n");
    printf("          카테고리별 지출 비율          \n");
    printf("----------------------------------------\n");
    for (int i = 0; i < categoryCount; i++) {
        float percentage = (categorySum[i] / (float)totalExpense) * 100;
        printf("%s: %.2f%%\n", categories[i], percentage);
    }
    printf("========================================\n");

    printf("Press the Enter key\n");

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}


void writeTransaction() {
    if (transactionCount >= MAX_TRANSACTIONS) {
        printf("더 이상 거래를 추가할 수 없습니다.\n");
        return;
    }

    char type[10];
    char date[20];
    char category[20];
    char description[50];
    int amount;


    printf("========================================\n");
    printf("                 가계부                 \n");
    printf("========================================\n");
    printf("날짜를 입력하세요 (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("                                \n");
    printf("입출금 유형을 입력하세요 (수입/지출): ");
    scanf("%s", type);
    printf("                           \n");
    printf("카테고리를 입력하세요: ");
    scanf("%s", category);
    printf("                          \n");
    printf("설명을 입력하세요: ");
    scanf(" %[^\n]", description); // 공백 포함 문자열 입력 받기
    printf("                              \n");
    printf("금액을 입력하세요: ");
    scanf("%d", &amount);
    printf("                          \n");
    printf("========================================\n");

    strcpy(transactions[transactionCount].date, date);
    strcpy(transactions[transactionCount].type, type);
    strcpy(transactions[transactionCount].category, category);
    strcpy(transactions[transactionCount].description, description);
    transactions[transactionCount].amount = amount;

    if (strcmp(type, "수입") == 0) {
        balance += amount;
    }
    else if (strcmp(type, "지출") == 0) {
        balance -= amount;
    }
    else {
        printf("잘못된 유형입니다. 수입 또는 지출만 가능합니다.\n");
        return;
    }

    transactionCount++;

    printf("========================================\n");
    printf("              거래 추가 완료            \n");
    printf("========================================\n");
    printf("날짜: %s\n", date);
    printf("유형: %s\n", type);
    printf("카테고리: %s\n", category);
    printf("설명: %s\n", description);
    printf("금액: %d\n", amount);
    printf("잔여 금액: %d\n", balance);
    printf("========================================\n");

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}



void modifyOrDeleteTransaction() {
    int index;
    printf("========================================\n");
    printf("수정 또는 삭제할 거래의 번호를 입력하세요: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= transactionCount) {
        printf("잘못된 번호입니다.\n");
        return;
    }

    printf("----------------------------------------\n");
    printf(" 선택한 거래\n \n날짜: %s\n 유형: %s\n 카테고리: %s\n 설명: %s\n 금액: %d\n",
        transactions[index].date, transactions[index].type, transactions[index].category, transactions[index].description, transactions[index].amount);

    int choice;
    printf("========================================\n");
    printf("   수정 시 1번            삭제 시 2번\n");
    printf("   선택:");
    scanf("%d", &choice);

    if (choice == 1) {
        char type[10];
        char category[20];
        char description[50];
        int amount;

        printf("========================================\n");
        printf("------------------수정------------------\n");
        printf("\n입출금 유형을 입력하세요 (수입/지출):");
        scanf("%s", type);
        printf("새로운 카테고리를 입력하세요: ");
        scanf("%s", category);
        printf("새로운 설명을 입력하세요: ");
        scanf(" %[^\n]", description); // 공백 포함 문자열 입력 받기
        printf("새로운 금액을 입력하세요: ");
        scanf("%d", &amount);

        if (strcmp(transactions[index].type, "수입") == 0) {
            balance -= transactions[index].amount;
        }
        else if (strcmp(transactions[index].type, "지출") == 0) {
            balance += transactions[index].amount;
        }

        strcpy(transactions[index].type, type);
        strcpy(transactions[index].category, category);
        strcpy(transactions[index].description, description);
        transactions[index].amount = amount;

        if (strcmp(type, "수입") == 0) {
            balance += amount;
        }
        else if (strcmp(type, "지출") == 0) {
            balance -= amount;
        }
        else {
            printf("잘못된 유형입니다. 수입 또는 지출만 가능합니다.\n");
            return;
        }

        printf("========================================\n");
        printf("           거래 수정 완료               \n");
        printf("========================================\n");
        printf("날짜: %s\n", transactions[index].date);
        printf("유형: %s\n", type);
        printf("카테고리: %s\n", category);
        printf("설명: %s\n", description);
        printf("금액: %d\n", amount);
        printf("잔여 금액: %d\n", balance);
        printf("========================================\n");
    }
    else if (choice == 2) {
        if (strcmp(transactions[index].type, "수입") == 0) {
            balance -= transactions[index].amount;
        }
        else if (strcmp(transactions[index].type, "지출") == 0) {
            balance += transactions[index].amount;
        }

        for (int i = index; i < transactionCount - 1; i++) {
            transactions[i] = transactions[i + 1];
        }
        transactionCount--;

        printf("========================================\n");
        printf("           거래 삭제 완료               \n");
        printf("========================================\n");
    }
    else {
        printf("잘못된 선택입니다.\n");
    }

    getchar();  // Enter 키 입력을 소비하여 화면이 즉시 지워지지 않도록 함
    getchar();
}

int main() {
    char inputPassword[20];
    int choice;

    // 비밀번호 입력

    printf("========================================\n");
    printf("                 가계부                 \n");
    printf("========================================\n");
    printf("사용자 : 김윤서                         \n");
    printf("                                   \n");
    printf("비밀번호를 입력하세요: ");
    scanf("%s", inputPassword);

    // 비밀번호 검증
    if (strcmp(inputPassword, PASSWORD) != 0) {
        printf("비밀번호가 잘못되었습니다.\n");
        return 1;
    }

    // 화면 지우기
    clearScreen();

    // 메뉴
    while (1) {

        printf("========================================\n");
        printf("                 가계부                 \n");
        printf("========================================\n");
        printf("\n가계부 메뉴:\n");
        printf("                          \n");
        printf("1. 수입/지출 내역 추가\n");
        printf("2. 수입/지출 내역 조회\n");
        printf("3. 내역 수정 및 삭제\n");
        printf("4. 월별 예산 설정\n");
        printf("5. 재무 목표 설정\n");
        printf("6. 재무 상태 보기\n");
        printf("7. 종료\n");
        printf("                              \n");
        printf("========================================\n");
        printf("선택: ");
        scanf("%d", &choice);

        // 화면 지우기
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
            printf("프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }

        // 화면 지우기
        clearScreen();
    }

    return 0;
}
