#include <stdio.h>

struct st{
        int id;
        char name[30];
};

int add_five(int id) {
	return id + 5;
}

int main(void) {
        FILE *fp;
        int i;
        struct st data[5];

        fp = fopen("data", "w");

        for (i=0;i<5;i++) {
                scanf("%d", &data[i].id);
                scanf("%s", &data[i].name);
        }

        for (i=0;i<5;i++) {
                data[i].id = add_five(data[i].id);
        }

        for (i=0;i<5;i++) {
                fprintf(fp, "%-5d", data[i].id);
                fprintf(fp, "%-5s\n", data[i].name);
        }

        return 0;
}
