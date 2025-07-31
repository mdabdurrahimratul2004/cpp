#include <stdio.h>
#include <stdlib.h>

int strlength(char str[]) {
    int l;
    for (l = 0; str[l] != '\0'; l++);
    return l;
}

char* SubString(char str[], int st, int nofc) {
    int l = strlength(str), i;
    if (st < 0 || st >= l || nofc <= 0 || st + nofc > l) {
        char *empty = (char *)malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    } 

    char *sub = (char *)malloc(nofc + 1);
    for (i = 0; i < nofc; i++) {
        sub[i] = str[st + i];
    }
    sub[nofc] = '\0';
    return sub;
}

char* Concatenation(char str1[], char str2[]) {
    int l1 = strlength(str1), l2 = strlength(str2), i;
    char *res = (char *)malloc(l1 + l2 + 1);
    for (i = 0; i < l1; i++) res[i] = str1[i];
    for (i = 0; i < l2; i++) res[l1 + i] = str2[i];
    res[l1 + l2] = '\0';
    return res;
}

int Indexing(char str[], char pattern[]) {
    int len = strlength(str), pat = strlength(pattern);
    for (int i = 0; i <= len - pat; i++) {
        int found = 1;
        for (int j = 0; j < pat; j++) {
            if (str[i + j] != pattern[j]) {
                found = 0;
                break;
            }
        }
        if (found) return i;
    }
    return -1;
}

char* Insertion(char str[], int pos, char insert[]) {
    int l1 = strlength(str), l2 = strlength(insert), i = 0, j;
    if (pos < 0 || pos > l1) return NULL;

    char *res = (char *)malloc(l1 + l2 + 1);
    for (; i < pos; i++) res[i] = str[i];
    for (j = 0; j < l2; j++) res[i++] = insert[j];
    for (j = pos; j < l1; j++) res[i++] = str[j];
    res[i] = '\0';
    return res;
}

char* Delete(char str[], char pattern[]) {
    int pos = Indexing(str, pattern);
    if (pos == -1) return str;

    int len = strlength(str), pat = strlength(pattern);
    char *res = (char *)malloc(len - pat + 1);
    int i = 0, j = 0;
    while (i < len) {
        if (i == pos) {
            i += pat;
        } else {
            res[j++] = str[i++];
        }
    }
    res[j] = '\0';
    return res;
}

char* Replace(char str[], char old[], char new[]) {
    int pos = Indexing(str, old);
    if (pos == -1) return str;

    char *left = SubString(str, 0, pos);
    char *right = SubString(str, pos + strlength(old), strlength(str) - pos - strlength(old));
    char *temp = Concatenation(left, new);
    char *final = Concatenation(temp, right);

    free(left);
    free(right);
    free(temp);

    return final;
}

char* DeleteAll(char str[], char pattern[]) {
    char *temp = str, *res;
    while (Indexing(temp, pattern) != -1) {
        res = Delete(temp, pattern);
        if (temp != str) free(temp);
        temp = res;
    }
    return temp;
}

char* ReplaceAll(char str[], char old[], char new[]) {
    char *temp = str, *res;
    while (Indexing(temp, old) != -1) {
        res = Replace(temp, old, new);
        if (temp != str) free(temp);
        temp = res;
    }
    return temp;
}

int main() {
    int option, st, nofc, Loc;
    char str1[100], str2[100], str3[100];
    char *result;

    while (1) {
        printf("\n1. Input a string\n");
        printf("2. String length\n");
        printf("3. Display string\n");
        printf("4. Substring of the string\n");
        printf("5. Concatenate two strings\n");
        printf("6. Indexing of a Sub String\n");
        printf("7. Insert a string at a position\n");
        printf("8. Delete a substring\n");
        printf("9. Replace a substring\n");
        printf("10. Delete All Pattern\n");
        printf("11. Replace All Pattern\n");
        printf("0. Exit\nEnter your option: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                printf("Enter a string: ");
                gets(str1);
                break;

            case 2:
                printf("Length of the string: %d\n", strlength(str1));
                break;

            case 3:
                printf("Inputted string: ");
                puts(str1);
                break;

            case 4:
                printf("Enter the starting position: ");
                scanf("%d", &st);
                printf("Enter number of characters: ");
                scanf("%d", &nofc);
                getchar();
                result = SubString(str1, st, nofc);
                printf("Substring is: ");
                puts(result);
                free(result);
                break;

            case 5:
                printf("Enter second string: ");
                gets(str2);
                result = Concatenation(str1, str2);
                printf("Concatenation is: ");
                puts(result);
                free(result);
                break;

            case 6:
                printf("Enter the pattern to find: ");
                gets(str2);
                Loc = Indexing(str1, str2);
                if (Loc == -1)
                    printf("Pattern not found.\n");
                else
                    printf("Pattern found at position: %d\n", Loc);
                break;

            case 7:
                printf("Enter the string to insert: ");
                gets(str2);
                printf("Enter the position to insert at: ");
                scanf("%d", &Loc);
                getchar();
                result = Insertion(str1, Loc, str2);
                if (result != NULL) {
                    printf("After insertion: ");
                    puts(result);
                    free(result);
                } else {
                    printf("Invalid position.\n");
                }
                break;

            case 8:
                printf("Enter the pattern to delete: ");
                gets(str2);
                result = Delete(str1, str2);
                printf("After deletion: ");
                puts(result);
                break;

            case 9:
                printf("Enter the old substring: ");
                gets(str2);
                printf("Enter the new substring: ");
                gets(str3);
                result = Replace(str1, str2, str3);
                printf("After replacement: ");
                puts(result);
                break;

            case 10:
                printf("Enter the pattern to delete all: ");
                gets(str2);
                result = DeleteAll(str1, str2);
                printf("After deleting all: ");
                puts(result);
                break;

            case 11:
                printf("Enter the old substring: ");
                gets(str2);
                printf("Enter the new substring: ");
                gets(str3);
                result = ReplaceAll(str1, str2, str3);
                printf("After replacing all: ");
                puts(result);
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid Input. Try again\n");
        }
    }
    return 0;
}
