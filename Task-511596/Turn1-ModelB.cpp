#include <stdio.h>
#include <stdlib.h>

enum {
    SUCCESS = 0,
    I2C_ERROR = 1,
    SPIDEV_ERROR = 2,
    GENERIC_ERROR = 3
};

int read_i2c(void) {
    printf("Reading I2C...\n");
    // Simulate an I2C error
    return I2C_ERROR;
}

int read_spidev(void) {
    printf("Reading SPI...\n");
    // Simulate an SPI error
    return SPIDEV_ERROR;
}

int main(void) {
    int ret;

    while (1) {
        int operation;
        printf("Choose an operation:\n");
        printf("1. Read I2C\n");
        printf("2. Read SPI\n");
        printf("3. Exit\n");
        scanf("%d", &operation);

        switch (operation) {
            case 1:
                ret = read_i2c();
                switch (ret) {
                    case SUCCESS:
                        printf("I2C read successful.\n");
                        break;
                    case I2C_ERROR:
                        printf("Error reading I2C: device not found.\n");
                        break;
                    default:
                        printf("Unknown I2C error (%d).\n", ret);
                        break;
                }
                break;
            case 2:
                ret = read_spidev();
                switch (ret) {
                    case SUCCESS:
                        printf("SPI read successful.\n");
                        break;
                    case SPIDEV_ERROR:
                        printf("Error reading SPI: device timeout.\n");
                        break;
                    default:
                        printf("Unknown SPI error (%d).\n", ret);
                        break;
                }
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid operation. Please try again.\n");
                break;
        }
    }

    return 0;
}
