#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// Function prototypes
float CheckValue(char *prompt);
float fnc1(float x, float y);
float fnc2(float x, float y);
float Bisection(float (*func)(float, float), float a, float b, float eps, float y);
float Newton(float (*func)(float,float), float a, float b, float eps, float y);

int main() {
    float a, b, y, x, eps;
    int choice, eq;

    while(1){
        while(1){

            eq = (int)CheckValue("\nWdhich equation do you want to solve: \n1: cos(t/x) -2sin(1/x) +1/x = 0 \n2: sin(lnx) - cos(lnx) + t*lnx = 0 \nEnter your answer: ");

            if ((eq != 1) && (eq != 2)){
                printf("Please, enter your answer again.");
            }
            else{
                break;
            }
        }


        while(1) {
            choice = (int)CheckValue("\nWhich method do you want to use:\n 1: Bisection\n 2: Newton\nEnter your answer: ");
            if ((choice == 1) || (choice == 2)) {
                break;
            } else {
                printf("Please, enter your answer again.\n");
            }
        }

        a = CheckValue("Enter a: ");
        b = CheckValue("Enter b: ");
        if(a >= b){
            printf("\na must be less than b\n");
            continue;
        }
        y = CheckValue("Enter y: ");
        eps = CheckValue("Enter acc: ");

        float (*functions[])(float, float) = {fnc1, fnc2};






        if (choice == 1) {
            x = Bisection(functions[eq - 1], a, b, eps, y);
            if(isnanf(x)){
                printf("\nThere are no roots on this range");
            }
            else if((eq == 2 && (a <= 0)) || (eq == 1 && (a <= 0 && b > 0))){
                printf("\nThe function is not completely defined on this range.\n");
                continue;
            }
            else if(x >= b - eps)
            {
                printf("The interval has more than one root or none. Select another.\n ");
                continue;
            }
            else{
                printf("\nx = %f", x);
            }
        }
        else if (choice == 2) {
            x = Newton(functions[eq - 1], a, b, eps, y);
            if(isnanf(x)){
                printf("\nThere are no roots on this range");
            }

            else{
                printf("\nx = %f", x);
            }


        }
        char answer = ' ';

        int c;
        while ((c = getchar()) != '\n');

        while(answer != 'N' && answer != 'Y'){
            printf("\nWould you like to continue? Y/N: ");
            scanf("%c", &answer);
            while ((c = getchar()) != '\n');
        }
        if(answer == 'Y'){
            printf("\n");
        }
        else if (answer == 'N'){
            break;
        }
    }

    printf("\nPress any key to exit");
    getchar();
    return 0;
}



float fnc1(float x, float y){

    return cos(y/x) - 2*sin(1/x) + 1/x;
}
float fnc2(float x, float y){
    return sin(log(x)) - cos(log(x)) + y*log(x);

}
float Bisection(float (*func)(float, float), float a, float b, float eps, float y){
    float x;

        while (fabs(a - b) > eps) {
        x = (a + b) / 2.0;
        if((func(x,y) == 0))
           {
               break;
           }
        else if (func(a, y) * func(x, y) > 0) {
            a = x;
        }
        else {
            b = x;
        }
    }

   return x;

}
float Newton(float (*func)(float,float), float a, float b, float eps, float y){
    float x1 = func(b, y);
    float delta = 1.0;
    float fx;

    while(fabs(delta) > eps){
        fx = (func(x1 + eps, y) - func(x1, y))/eps;
        delta = func(x1,y)/fx;
        x1 = x1 - delta;
    }
    if(x1 < a){
            while(x1 < a){
            b+= eps; //shifting right border
            x1 = func(b, y);
            delta = 1.0;
            while(fabs(delta) > eps){
                fx = (func(x1 + eps, y) - func(x1, y))/eps;
                delta = func(x1,y)/fx;
                x1 = x1 - delta;
            }
        }
    }



    return x1;


}


float CheckValue(char *prompt) {
    char buffer[100];

    printf("%s", prompt);
    while (1) {
        int checkI = 1;
        int dotCount = 0;

        scanf("%99s", buffer);

        for (int i = 0; buffer[i]; i++) {
            if (i == 0 && buffer[i] == '-') {
                // Allow a minus sign at the beginning
                continue;
            }

            if (isdigit(buffer[i]) == 0) {
                if (buffer[i] == '.' && dotCount == 0) {
                    // Allow one dot in the middle of the number
                    dotCount = 1;
                } else {
                    printf("\nYour input is invalid. Reenter: ");
                    checkI = 0;
                    break;
                }
            }
        }

        if (checkI == 1) {
            break;
        }
    }

    return atof(buffer);
}



