#include <stdio.h>
#include <string.h>
struct all_fields { float celsius; int percent; char status[8]; };
enum kind { TEMPERATURE,HUMIDITY,STATUS };
union value { float celsius; int percent; char status[8]; };
struct packet { enum kind type; union value data; };
int main(void) {
    struct packet p={TEMPERATURE,{.celsius=31.5f}};
    int bits=0;
    memcpy(&bits,&p.data.celsius,sizeof bits);
    printf("All-fields struct: %zu bytes\n",sizeof(struct all_fields));
    printf("Tagged union packet: %zu bytes\n",sizeof(struct packet));
    printf("Temperature: %.1f\n",p.data.celsius);
    printf("Same stored bytes interpreted as integer bits: %d (0x%08X)\n",bits,(unsigned int)bits);
    puts("Only the member selected by the tag should be interpreted as a reading.");
    return 0;
}
