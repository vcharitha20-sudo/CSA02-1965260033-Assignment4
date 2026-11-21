#include <stdio.h>
#include <string.h>
typedef struct { int day,month,year; } Date;
typedef struct { char name[40],city[30],pin[7]; } Person;
typedef struct { int id; float weight,charge; Date booked; Person sender,receiver; int express; } Parcel;
void sort_weight(Parcel a[],int n) { int i,j,k; for(i=0;i<n-1;i++){k=i;for(j=i+1;j<n;j++)if(a[j].weight<a[k].weight)k=j;if(k!=i){Parcel t=a[i];a[i]=a[k];a[k]=t;}} }
void list_city(const Parcel a[],int n,const char city[]) { int i;for(i=0;i<n;i++)if(strcmp(a[i].receiver.city,city)==0)printf("Parcel %d to %s, %.1f kg\n",a[i].id,city,a[i].weight); }
int main(void) {
    Parcel p[3] = {
        {501,4.5f,120,{12,10,2026},{"Anu","Chennai","600001"},{"Ravi","Madurai","625001"},0},
        {502,1.2f,90,{12,10,2026},{"Bala","Chennai","600077"},{"Meena","Chennai","600077"},1},
        {503,2.8f,100,{13,10,2026},{"Kavi","Salem","636001"},{"Deepa","Madurai","625002"},0}
    };
    int i;sort_weight(p,3);
    puts("Sorted parcels:");for(i=0;i<3;i++)printf("%d %.1f kg\n",p[i].id,p[i].weight);
    puts("Receiver city Madurai:");list_city(p,3,"Madurai");
    printf("Third parcel PIN via dot: %s\n",p[2].receiver.pin);
    { Parcel *ptr=&p[2];printf("Third parcel PIN via arrow: %s\n",ptr->receiver.pin); }
    return 0;
}
