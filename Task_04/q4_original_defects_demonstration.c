#include <stdio.h>
struct account { int number; float balance; };
void addInterest(struct account a,float rate) {
    printf("Inside function, copy address: %p\n",(void*)&a);
    a.balance=a.balance+a.balance*rate/100.0f;
}
int main(void) {
    struct account list[3]={{101,5000},{102,12000},{103,800}};
    int i;
    for(i=0;i<3;i++) {
        printf("In main, original address: %p\n",(void*)&list[i]);
        addInterest(list[i],4);
        printf("Unchanged account %d: %.2f\n",list[i].number,list[i].balance);
    }
    /* Original p.number does not compile because p is a pointer; use p->number. */
    return 0;
}
