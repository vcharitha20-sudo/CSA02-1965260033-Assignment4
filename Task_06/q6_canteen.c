#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 20
#define MAX_COMPONENTS 3
typedef struct { int day,month,year; } Date;
typedef struct { int hour,minute; } Time;
typedef enum { PACKAGED,COOKED,COMBO } Kind;
typedef struct {
    int id;char name[40];Kind kind;int stock;double price;int sold;double revenue;
    union { struct { Date expiry; } packaged;struct { Time prepared; } cooked;struct { int ids[MAX_COMPONENTS];int count; } combo; } detail;
} Item;
typedef struct { Item items[MAX_ITEMS];int count; } Inventory;
int date_days(Date d) { /* Days since 01/01/0001, valid Gregorian dates. */
    int y=d.year-1;static const int before[]={0,31,59,90,120,151,181,212,243,273,304,334};
    int leap=(d.year%4==0&&(d.year%100!=0||d.year%400==0));
    return 365*y+y/4-y/100+y/400+before[d.month-1]+d.day+(leap&&d.month>2);
}
int find_item(const Inventory *inv,int id) {int i;for(i=0;i<inv->count;i++)if(inv->items[i].id==id)return i;return -1;}
int sell(Inventory *inv,int id,int qty) {
    int i,j,indices[MAX_COMPONENTS],need[MAX_COMPONENTS]={0,0,0};Item *p;
    if(qty<=0 || (i=find_item(inv,id))<0)return 0;
    p=&inv->items[i];
    if(p->kind!=COMBO) { if(p->stock<qty)return 0;p->stock-=qty; }
    else {
        int count=p->detail.combo.count;
        if(count<1||count>MAX_COMPONENTS)return 0;
        for(j=0;j<count;j++) {
            int k=find_item(inv,p->detail.combo.ids[j]);
            if(k<0||k==i||inv->items[k].kind==COMBO)return 0;
            indices[j]=k;
        }
        for(j=0;j<count;j++) {int k,required=0;for(k=0;k<count;k++)if(indices[k]==indices[j])required+=qty;need[j]=required;}
        for(j=0;j<count;j++)if(inv->items[indices[j]].stock<need[j])return 0;
        for(j=0;j<count;j++) {int k,seen=0;for(k=0;k<j;k++)if(indices[k]==indices[j])seen=1;if(!seen)inv->items[indices[j]].stock-=need[j];}
    }
    p->sold+=qty;p->revenue+=qty*p->price;return 1;
}
void warn_expiry(const Inventory *inv,Date today) {
    int i;puts("Expiry warnings (within two days):");
    for(i=0;i<inv->count;i++)if(inv->items[i].kind==PACKAGED) {
        int diff=date_days(inv->items[i].detail.packaged.expiry)-date_days(today);
        if(diff<=2)printf("%s: %s (%d days)\n",inv->items[i].name,diff<0?"expired":"expiring",diff);
    }
}
void summary(const Inventory *inv) {
    int order[MAX_ITEMS],i,j,t;for(i=0;i<inv->count;i++)order[i]=i;
    for(i=0;i<inv->count;i++)for(j=i+1;j<inv->count;j++)if(inv->items[order[j]].revenue>inv->items[order[i]].revenue){t=order[i];order[i]=order[j];order[j]=t;}
    puts("Daily revenue (descending):");
    for(i=0;i<inv->count;i++){const Item *p=&inv->items[order[i]];printf("%-15s sold=%d revenue=Rs %.2f stock=%d\n",p->name,p->sold,p->revenue,p->stock);}
}
int main(void) {
    Inventory inv={0};Date today={19,11,2026};
    Item milk={101,"Milk",PACKAGED,10,25.0,0,0,{.packaged={{20,11,2026}}}};
    Item sandwich={102,"Sandwich",COOKED,8,50.0,0,0,{.cooked={{9,30}}}};
    Item combo={103,"Breakfast Combo",COMBO,0,70.0,0,0,{.combo={{101,102,0},2}}};
    inv.items[inv.count++]=milk;inv.items[inv.count++]=sandwich;inv.items[inv.count++]=combo;
    printf("Sell 2 sandwiches: %s\n",sell(&inv,102,2)?"OK":"REJECTED");
    printf("Sell 2 combos: %s\n",sell(&inv,103,2)?"OK":"REJECTED");
    printf("Sell 20 milk packets: %s\n",sell(&inv,101,20)?"OK":"REJECTED (insufficient stock)");
    warn_expiry(&inv,today);summary(&inv);
    return 0;
}
