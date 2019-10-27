#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<iostream>
#include<string.h>
#include<winbgim.h>
#include <iostream>
#include <math.h>

#define cantOps 6
#define ANCHOVENTANA 700
#define ALTOVENTANA 700
#define MARGEN 50

char fun_opciones[cantOps][30] = { "Lineal", "cuadratica", "Cubica", "Seno", "Coseno", "Exponencial" };

float valorMaximo = 10;
float v = 0;
int queFuncion = 0;


/***** def de funciones ***/
void DibujarEje();
void DibujarLineas(float mitadAncho, float mitadAlto);
void MostrarMenuPrincipal();
bool PreguntarSiSeguir();
void funcionLineal();

float convertirPixelANum();
float getmiX(float x);
float getmiY(float y);
float xaCursor(float x);

void graficarFuncion(float a, float b);

float getValorLineal(float x, float a , float b );
float getValorCuadratica(float x, float a, float b, float c, float expo);
float getValorCubica(float x, float a, float b, float c, float d);
float getValorCoseno(float x, float a, float b );

bool marcarValorIndividual(float a, float b);


float roundMeUp(float var);

/**************************/

int main()
{

    convertirPixelANum();

    bool seguirEnPrograma = true;

    do{

        int opcionElegida = 0;

        MostrarMenuPrincipal();
        scanf("\n%d", &opcionElegida);

        queFuncion = opcionElegida;

        printf("Ha seleccionado la funcion %d\n ", queFuncion);
        _getch();

        funcionLineal();
        seguirEnPrograma =  PreguntarSiSeguir();

    }while(seguirEnPrograma);


    return 0;

}

/****** MENU ********/

void MostrarMenuPrincipal(){

    system("cls");

    printf("Graficadora de funciones");

    for( int i = 0; i< cantOps; i++ ){
        printf("\n %d - funcion %s", (i+1), fun_opciones[i] );
    }

    printf("\n\n");
}

bool PreguntarSiSeguir(){

    system("cls");


    int opcionElegida = 0;

    printf("Deseas volver al menu principal");
    printf("\n\n 1 - Si");
    printf("\n\n 2 - No\n");

    scanf("%d", &opcionElegida);

    if(opcionElegida == 1){
        return true;
    }else if(opcionElegida == 2){
        return false;
    }else {
        PreguntarSiSeguir();
    }

}


/********************/

/****** Comun de todos los Graficos ******/

void DibujarEje()
{

    initwindow( ANCHOVENTANA, ALTOVENTANA);

    setbkcolor(WHITE);
    setcolor(BLACK);
    clearviewport();

    float mitadAncho = ANCHOVENTANA/2;
    float mitadAlto = ALTOVENTANA/2;

    //Linea horizontal
    line(MARGEN , mitadAlto, ANCHOVENTANA - MARGEN, mitadAlto );

    //linea vertical
    line(mitadAncho, MARGEN, mitadAncho , ALTOVENTANA - MARGEN );

    DibujarLineas(mitadAncho, mitadAlto);
}

void DibujarLineas(float mitadAncho, float mitadAlto){

    //pixeles
    float cantidadLineas = 20;
    float cada  = (ANCHOVENTANA - MARGEN * 2)/cantidadLineas;

    //numeros
    float pasoValor = (valorMaximo * 2) / cantidadLineas;

    float acumX = MARGEN;
    float acumY = MARGEN;

    float lineaAnchoMitad = 3;

    float rotuloX = valorMaximo - (pasoValor * cantidadLineas);
    float rotuloY = valorMaximo;

    settextstyle(2,4,4);

    for( int i= 0; i< cantidadLineas + 1; i++ ){

        char msg[128];

        //lineas horizontales
        line(acumX, mitadAlto - lineaAnchoMitad , acumX, mitadAlto + lineaAnchoMitad );

        //numeritos
        sprintf(msg, "%2.1f", rotuloX);
        outtextxy(acumX - lineaAnchoMitad,mitadAlto + lineaAnchoMitad* 6, msg );
        rotuloX = rotuloX + pasoValor;

        acumX = acumX + cada;

        //lineas verticales
        line(mitadAncho - lineaAnchoMitad, acumY , mitadAncho + lineaAnchoMitad, acumY );

        //numeritos
        sprintf(msg, "%2.1f", rotuloY);
        outtextxy(mitadAncho + lineaAnchoMitad * 6 , acumY , msg );
        rotuloY = rotuloY - pasoValor;


        acumY = acumY + cada;
    }

}

/****** FUNCION LINEAL ******/

void funcionLineal(){
    float a=0,b=0,c=0;

    system("cls");

    printf("Estamos en funcion lineal, Vieja\n");
    printf("Ingrese A:  ");
    scanf("%f", &a);
    printf("\nIngrese B:  ");
    scanf("%f", &b);

    DibujarEje();
    graficarFuncion(a,b);

    bool seguirIterando = true;

    do{
        seguirIterando =  marcarValorIndividual(a,b);
    }while(seguirIterando);

    _getch();
}


void graficarFuncion(float a, float b){

    float valorMinimo = valorMaximo * -1;

    float cursor = MARGEN;
    float fin = ANCHOVENTANA - MARGEN;
    int cnt = 0;

    float xAnterior = 0;
    float yAnterior = 0;

    setcolor(BLUE);

    do{
        cnt++;

        float x = getmiX(cursor);

        float y = 0;
        switch
        (queFuncion){

            case 1:
                y = getValorLineal(x,a,b);
                break;
            case 2:
                y = getValorCuadratica(x,a,b, -2, 0 );
                break;
            case 3:
                y = getValorCubica(x, a, b, 0, 0 );
                break;
            case 4:
                y = getValorCoseno(x, a,b);
                break;
        }

        y = roundMeUp(y);

        //if( cnt % 50 == 0 ) //pausar cada 50
            //_getch();

       if(cnt == 1)
            putpixel(cursor, getmiY(y) , GREEN );
        else
            line(xAnterior, yAnterior, cursor,getmiY(y));

        xAnterior = cursor;
        yAnterior = getmiY(y);

       cursor = cursor +1;

    }while(cursor <= fin);

}


bool marcarValorIndividual(float a, float b){

    bool resultado = true;

    float vl = 0;
    //LO DEL VALOR INDIVIDUAL

    printf("Ingrese un numero del %2.2f al %2.2f. Ingrese - 1 para salir. \n ", valorMaximo * -1 , valorMaximo );
    scanf("%f", &vl);

    if(vl == -1)
        return false;

    float cursor =  xaCursor(vl);
    float x = vl;

    float y = 0;

    switch(queFuncion){

        case 1:
            y = getValorLineal(x,a,b);
            break;
        case 2:
            y = getValorCuadratica(x,a,b, -2, 0 );
            break;
        case 3:
            y = getValorCubica(x, a, b, 0, 0 );
            break;
        case 4:
            y = getValorCoseno(x, a,b);
            break;
    }

    printf(" ---> %f\n", y);

    float cursory = getmiY(y);

    setlinestyle(2, 0, 1);

    int numeroDeColor = 0;

    numeroDeColor = rand() % 14 + 1;

    setcolor(numeroDeColor);

    char msg[128];
    sprintf(msg, "%2.1f", vl);
    outtextxy(cursor , ALTOVENTANA/2 - 10 , msg );
    line(cursor , ALTOVENTANA/2 , cursor, cursory);

    sprintf(msg, "%2.1f", y);
    outtextxy(ANCHOVENTANA/2 + 10 ,  cursory , msg );
    line( cursor, cursory, ANCHOVENTANA/2, cursory  );

    return resultado;
}

/****************************/


float getValorLineal(float x, float a, float b){

    return (a*x) + b;
}

float getValorCuadratica(float x, float a, float b, float c, float expo){

    return pow(x,2)* a + (b * x) + c;
}

float getValorCubica(float x, float a, float b, float c, float d){
    return pow(x,3) *a + pow(x,2) * b + c*x + d;
}

float getValorCoseno(float x, float a, float b ){
    return a*cos(x)+b;
}

float getmiX(float cursor){

    float diff = cursor - MARGEN;
    float diffEnNum = diff* v;

    return ((float)valorMaximo * -1) + diffEnNum;
}
float getmiY(float y){

    float diff = valorMaximo - y;
    float diffEnPix = diff/v;

    return ((float)MARGEN ) + diffEnPix;
}

float xaCursor(float x){

    float diff = x - (valorMaximo * -1 );
    float diffEnPix = diff/v;

    return (MARGEN ) + diffEnPix;
}

float convertirPixelANum(){

    float anchoPixceles = ANCHOVENTANA - MARGEN * 2;
    float anchoNumeros =  valorMaximo * 2;

    v = (float)(1*anchoNumeros)/(float)anchoPixceles;
}

float roundMeUp(float var)
{


    // we use array of chars to store number
    // as a string.
    char str[40];

    // Print in string the value of var
    // with two decimal point
    sprintf(str, "%1.6f", var);

    // scan string value in var
    sscanf(str, "%f", &var);

    return var;
}


