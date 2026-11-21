#include <stdio.h>
/* For the actual two-file extern example, compile q5_extern_main.c with q5_extern_counter.c. */
int global_veg=1000,global_nonveg=1000;
int next_auto(void) { int token=1000;return ++token; }
int next_static(int kind) { static int veg=1000,nonveg=1000;return kind==0?++veg:++nonveg; }
int next_global(int kind) { return kind==0?++global_veg:++global_nonveg; }
int next_by_pointer(int *counter) { return ++*counter; }
int main(void) {
    register int i;
    int veg=1000,nonveg=1000;
    for(i=0;i<3;i++)printf("round %d: auto %d, static veg %d nonveg %d, global veg %d nonveg %d, pointer veg %d nonveg %d\n",i+1,next_auto(),next_static(0),next_static(1),next_global(0),next_global(1),next_by_pointer(&veg),next_by_pointer(&nonveg));
    return 0;
}
