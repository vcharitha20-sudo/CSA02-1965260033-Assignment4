#include <stdio.h>
struct account { int number; float balance; };
void addInterest(struct account *a,float rate) {
    a->balance += a->balance*rate/100.0f;
}
int main(void) {
    struct account list[3]={{101,5000},{102,12000},{103,800}};
    struct account *p=list;
    int i;
    for(i=0;i<3;i++)addInterest(&list[i],4);
    for(i=0;i<3;i++)printf("Account %d balance %.2f\n",p[i].number,p[i].balance);
    return 0;
}
