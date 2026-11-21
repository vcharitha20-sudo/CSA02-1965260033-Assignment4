#include <stdio.h>
#include <string.h>
#define MAX_PATIENTS 100
typedef struct { int day, month, year; } Date;
typedef struct { int systolic, diastolic; } BloodPressure;
typedef struct { char name[40]; int age; char phone[16]; BloodPressure bp; Date visit; } Patient;
typedef struct { Patient patients[MAX_PATIENTS]; int count; } Register;
int addPatient(Register *r, const Patient *p) {
    if (!r || !p || r->count >= MAX_PATIENTS || p->age < 0 || p->age > 130) return 0;
    r->patients[r->count++] = *p;
    return 1;
}
void printPatients(const Register *r) {
    int i;
    for (i = 0; i < r->count; ++i) {
        const Patient *p = &r->patients[i];
        printf("%s age %d phone %s BP %d/%d visit %02d/%02d/%04d\n",p->name,p->age,p->phone,p->bp.systolic,p->bp.diastolic,p->visit.day,p->visit.month,p->visit.year);
    }
}
int main(void) {
    Register r = {{{0}},0};
    Patient a = {"Anu",20,"9876543210",{120,80},{19,11,2026}};
    Patient b = {"Ravi",45,"9123456780",{130,85},{20,11,2026}};
    printf("Add Anu: %s\n",addPatient(&r,&a)?"success":"failed");
    printf("Add Ravi: %s\n",addPatient(&r,&b)?"success":"failed");
    printPatients(&r);
    printf("Patient structure size: %zu bytes\n",sizeof(Patient));
    return 0;
}
