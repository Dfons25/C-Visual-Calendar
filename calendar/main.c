#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <locale.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>


void gotoxy(int x,int y){SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});}

void printinBox (int x, int y){
        int espaco = 1;

        gotoxy(x+espaco+1,y+espaco);putchar(217);
        gotoxy(x+espaco+1,y-espaco);putchar(191);
        gotoxy(x-espaco,y-espaco);putchar(218);
        gotoxy(x-espaco,y+espaco);putchar(192);
}

void printin (int x, int y, int inDay){
        gotoxy(x,y);printf("%d",inDay);
}

int numberOfDaysF(int month, int year){
int numberOfDays;

if (month == 4 || month == 6 || month == 9 || month == 11)
  numberOfDays = 30;
else if (month == 2)
{bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  if (isLeapYear)
    numberOfDays = 29;
  else
    numberOfDays = 28;
}
else
  numberOfDays = 31;

return numberOfDays;
}

int dayOfWeek(y, m, d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;

    return((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7);
}

const char * dayOfWeekString(y, m, d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    char *diaS;

    switch((y + y/4 - y/100 + y/400 + t[m-1] + d) % 7){
        case 0: diaS="Domingo/Segunda-feira";
        break;
        case 1: diaS="Segunda-feira";
        break;
        case 2: diaS="Terça-feira";
        break;
        case 3: diaS="Quarta-feira";
        break;
        case 4: diaS="Quinta-feira";
        break;
        case 5: diaS="Sexta-feira";
        break;
        case 6: diaS="Sábado";
        break;}
    return diaS;};



void desenharCalendario(int inicioX, int y, int mes, int ano){

    int espaco = 4;

    int diaFinal = numberOfDaysF(mes,ano);
    int diaDaSemana = dayOfWeek(ano, mes, 1) + 1;
    int primeiroDia = inicioX + (diaDaSemana*espaco);
    int dia = 1;
    int x;



    system("cls");
    printf(" Numero de dias %d \n Dia semana inicial %s \n Coord Dia semana inicial %d \n Mes %d \n Ano %d",diaFinal,dayOfWeekString(ano, mes, 1),primeiroDia,mes,ano);

    for(x = primeiroDia; dia <= diaFinal; dia++, x+=espaco){
        printinBox(x,y);
        printin(x,y,dia);
        if((diaDaSemana)%7 == 0){y+=(espaco-1);
                     x = inicioX;
                     diaDaSemana = 1;}else{diaDaSemana+=1;};
    }
}

void desenharAno(int ano){
    int inicioX = 13;
    int inicioY = 10;

    int mes;
    system("cls");

    for(mes = 1; mes <= 12; mes++){
    if(inicioX==13+(30*4)){inicioX=13;inicioY+=19;}
    desenharCalendario(inicioX, inicioY, mes, ano);
    inicioX+=30;
    }
}

typedef struct Calendar{
    int inicioX;
    int inicioY;
    int ano;
    int mes;
   // void (*outPut)(int inicioX, int y, int mes, int ano);
} Calendar;

/*void assoc(Calendar cal){
cal.outPut = &desenharCalendario;
}*/

Calendar new_calendar(int inicioX, int y, int mes, int ano){
Calendar cal;
cal.inicioX = inicioX;
cal.inicioY = y;
cal.ano = ano;
cal.mes = mes;
//assoc(cal);
desenharCalendario(cal.inicioX, cal.inicioY, cal.mes, cal.ano);
return cal;
}


int main()
{
    int inicioX = 13;
    int inicioY = 10;

    int ano = 2017;
    int mes = 12;
    system("mode 200, 120");
    char teclaPremida;
    do{
    teclaPremida=getch();

        switch(teclaPremida){
        case 77:/*ano++;break;*/if(mes == 12){ano++;mes=1;}else{mes++;}break;
        case 75:/*ano--;break;*/if(mes == 1){ano--;mes=12;}else{mes--;}break;
        }
        desenharCalendario(inicioX, inicioY, mes, ano);
        //desenharAno(ano);
        }
        while(teclaPremida != 13);
           // desenharAno(2017);

   // Calendar cal1 = new_calendar(inicioX, inicioY, mes, ano);
  //  toString(cal1);
// cal1.outPut(inicioX, inicioY, mes, ano);

  //  cal1 = new_calendar(40, 30, 10, 2017);
//    toString(cal2);
    return (0);
}
