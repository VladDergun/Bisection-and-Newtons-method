#include <stdio.h>
#include <math.h>
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
            eq = (int)CheckValue("\nWhich equation do you want to solve: \n 1: cos(t/x) -2sin(1/x) +1/x = 0  \n 2: sin(lnx) - cos(lnx) + t*lnx = 0\nEnter your answer: ");
            if ((eq != 1) && (eq != 2)){
                printf("Please, enter your answer again.");
            }
            else{
                break;
            }
        }
        while(1){
            choice = (int)CheckValue("\nWhich method do you want to use: \n 1: Bisection \n 2: Newton\nEnter your answer: ");
            if ((choice != 1) && (choice != 2)){
                printf("Please, enter your answer again.");
            }
            else{
                break;
            }
        }


        a = CheckValue("Enter a: ");
        b = CheckValue("Enter b: ");
        y = CheckValue("Enter y: ");
        eps = CheckValue("Enter acc: ");




        float (*functions[])(x, y) = {fnc1, fnc2};

        if(choice == 1){
            while (((fnc1(a, y) * fnc1(b,y)) >= 0) || isnan(fnc1(a, y) * fnc1(b,y)) ){//LIMITATION
                printf("Value error. Reenter a and b.\n");
                a = CheckValue("Enter a: ");
                b = CheckValue("Enter b: ");

            }
            printf("\nx = %f", Bisection(functions[eq-1],a, b, eps, y));


        }
        else if(choice == 2){
            printf("\nx = %f", Newton(functions[eq-1],a, b, eps, y));
        }

        char answer = ' ';
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        while(answer != 'N' && answer != 'Y'){
            
            printf("\nWould you like to continue? Y/N: ");
            scanf("%c", &answer);

        }
        if(answer == 'Y'){
                printf("\n");
            }
        else if (answer == 'N'){

            break;
        }

    }




    printf("Press any key to exit");
    getch();
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
    while(fabs(a-b) > eps){
        x = (a+b)/2.0;
        (func(a, y)*func(x, y) > 0) ? (a = x): (b = x);

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

    return x1;


}


float CheckValue(char *prompt){
    char buffer[100];

    printf("%s", prompt);
    while(1){
        int checkI = 1;
        scanf("%99s", buffer);
        for(int i = 0; buffer[i]; i++){
            if (isdigit(buffer[i]) == 0 && buffer[i] != '.' && buffer[i])
            {
                printf("\nYour input is invalid. Reenter: ");
                checkI = 0;
                break;
            }

        }
        if(checkI == 1){
            break;
        }
    }
    return atof(buffer);


}



