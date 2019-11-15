#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

int i2c_fd;
void ctrl_c(int sig)
{
        close(i2c_fd);
        exit(-1);
}

int main(void)
{
        char user_input=1, slave_addr=0x0F;
        char msp430_ret;
        unsigned int c=0;
        double a1,a2,a3,a4,a5,a0;
        double resoluc=(3.3)/1023;

        signal(SIGINT, ctrl_c);
        i2c_fd = open("/dev/i2c-1", O_RDWR);
        ioctl(i2c_fd, I2C_SLAVE, slave_addr);

        int i=0;
        //while(i==0){
        for(int cont=1;cont<=6;cont++)
        {
                //puts("Digite um numero entre 1 e 5");
                //puts("para mandar o MSP430 piscar seus LEDs,");
                //puts("ou digite 0 para terminar o programa. ");
                //scanf("%d", &user_input);
                //c=1;
		//      puts("enviando atravez do if c para a msp");
                  //      write(i2c_fd, &user_input, 1);
                    //    sleep(3);
                      //  read(i2c_fd, &msp430_ret,1);
                       // printf("retorna send = %d\n", msp430_ret);

                user_input = cont;
                //printf("Pedindo valor do sensor %d\n",user_input);

                write(i2c_fd, &user_input, 1);
                sleep(0.5);
                read(i2c_fd, &msp430_ret,1);
                sleep(0.5);
                //printf("msp retornou = %d\n \n", msp430_ret);

                if (cont==1){
                        a5=msp430_ret*(1023/255);
                        printf("Valor do sensor em A5 (SEM NADA) é: %.2f\n", a5);
                }
		else if (cont==2){
                        a4=msp430_ret*(1023/255);
                        //a4 = (a4*resoluc*100)-273.15;
                        printf("Valor do sensor em A4 (LDR) é: %.2f\n", a4);
                }
                else if (cont==3){
                        a3=msp430_ret*(1023/255);
                        printf("Valor do sensor em A3 (UV) é: %.2f\n", a3);
                }
                else if (cont==4){
                        a2=(1023/255)*msp430_ret;
                        printf("Valor do sensor em A2 (LM335_1) é %.2f\n", a2);
                }
                else if (cont==5){
                        a1=(1023/255)*msp430_ret;
                        printf("Valor do sensor em A1 (LM335_2) é %.2f\n", a1);
                }
                else if (cont==6){
                        a0=msp430_ret*(1023/255);
                        printf("Valor do sensor em A0 (LM335_3_PISTÃO) é %.2f\n", a0);
		}
		puts("");
                //user_input++;
        }
        //}
        close(i2c_fd);

        char user_input2=1, msp430_ret2, slave_addr2=0x0A;
        //unsigned int c=0;
        double ad5,ad4,ad3,ad2,ad1,ad0;
        double media_temp, divt1, divt2;

        signal(SIGINT, ctrl_c);
        i2c_fd = open("/dev/i2c-1", O_RDWR);
        ioctl(i2c_fd, I2C_SLAVE, slave_addr2);

        for(int cont2=1;cont2<=6;cont2++)
        {
                user_input2 = cont2;
                //printf("Pedindo valor do sensor %d\n",user_input2);

                write(i2c_fd, &user_input2, 1);
                sleep(0.5);
                read(i2c_fd, &msp430_ret2,1);
                sleep(0.5);
                //printf("msp retornou = %d\n \n", msp430_ret2);

                if (cont2==1){
                        ad5=msp430_ret2*(1023/255);
                        printf("Valor do sensor em AD5 (LDR_1) é: %.2f\n", ad5);
                }
                else if (cont2==2){
                        ad4=msp430_ret2*(1023/255);
                        printf("Valor do sensor em AD4 (LDR_2) é: %.2f\n", ad4);
                }
                else if (cont2==3){
			ad3=msp430_ret2*(1023/255);
                        printf("Valor do sensor em AD3 (CORRENTE_BATERIA): %.2f\n", ad3);
                }
                else if (cont2==4){
                        ad2=msp430_ret2*(1023/255);
                        printf("Valor do sensor em AD2 (CORRENTE_GERADOR) é %.2f\n", ad2);
                }
                else if (cont2==5){
                        ad1=msp430_ret2*(1023/255); //*resoluc*(2.194410693);
                        divt1 = ad1*resoluc*(2.194410693);
                        printf("Valor do sensor em AD1 (TENSÃO_BATERIA) é %.2f\n", ad1);
                        printf("TENSÃ0 NA BATERIA = %f \n", divt1);
                }
                else if (cont2==6){
                        ad0=msp430_ret2*(1023/255); //*resoluc*(3.1205074);
                        divt2 = ad1*resoluc*3.1205074;
                        printf("Valor do sensor em AD0 (TENSÃO_GERADOR) é %.2f\n", ad0);
                        printf("TENSÃO NO GERADOR = %.2f \n", divt2);
                }

                puts("");
        }

        close(i2c_fd);

        media_temp =(a1+a2)/2;
        FILE * fp;
        //int x[5] = {0,1,2,5,5};
        fp = fopen ("file.txt", "w+");
        //char c[] = "oi";
        //fputc(x,fp);
        fprintf(fp, "%f,%f,%f,",ad5,ad4,ad3);
        fclose(fp);
	
	      //char command[50];

        //strcpy(command, "python3 read_gps.py" );
        //system(command);
        return (0);
}

