//
//  main.c
//  Es54-TARTARUGA
//
//  Created by Paolo Formentelli on 11/12/20.
//

#include <stdio.h>

typedef struct{
    int l;
    int h;
} Griglia;



void stampaComandi (void){
    printf ("\nScegliere uno dei seguenti comandi:\n");
    printf ("1.Alza penna, 2.Abbassa penna, 3.Gira dx, 4.Gira sx, 5,n. Avanti n spazi, 6.Esci\n");
}

void pennaAlzata(int comando, int *penna){
    
    if (comando==2)
        *penna = 0;
    if (comando==1)
        *penna = 1;

}

int direzioneTartaruga(int comando, int direz){
    
    if (comando == 4){
        if (direz == 1)
            direz = 4;
        else
            direz = direz - 1;
    }
    if (comando == 3){
        if (direz == 4)
            direz = 1;
        else
            direz = direz + 1;
    }
    
    return direz;
}

void spostamentoTartaruga(int comando, int n, Griglia stampata, int penna, int direzione, int spostamento[][stampata.l], Griglia posPrec, Griglia *posAttuale){
    
    int i=0, j=0;
    
    if (comando == 5){
        
        if (direzione == 1){
            for (i=0; i<n && (i+posPrec.h)<(stampata.h); i++){
                if (penna == 1)
                    spostamento[posPrec.h - i][posPrec.l + j] = 0;
                else
                    spostamento[posPrec.h - i][posPrec.l + j] = 1;
            }
            posPrec.l = posPrec.l;
            posPrec.h = posPrec.h - n;
            
            spostamento[posPrec.h][posPrec.l] = 2;
            
            *posAttuale = posPrec;
        }
        
        else if (direzione == 2){
            for (j=0; j<n; j++){
                if (penna == 1)
                    spostamento[posPrec.h + i][posPrec.l + j] = 0;
                else
                    spostamento[posPrec.h + i][posPrec.l + j] = 1;
            }
            
            posPrec.l = posPrec.l + n;
            posPrec.h = posPrec.h;
            
            spostamento[posPrec.h][posPrec.l] = 2;
            
            *posAttuale = posPrec;
        }
        else if (direzione == 3){
            for (i=0; i<n; i++){
                if (penna == 1)
                    spostamento[posPrec.h + i][posPrec.l + j] = 0;
                else
                    spostamento[posPrec.h + i][posPrec.l + j] = 1;
            }
            posPrec.l = posPrec.l;
            posPrec.h = posPrec.h + n;
            
            spostamento[posPrec.h][posPrec.l] = 2;
            
            *posAttuale = posPrec;
        }
        else if (direzione == 4){
            for (j=0; j<n; j++){
                if (penna == 1)
                    spostamento[posPrec.h + i][posPrec.l - j] = 0;
                else
                    spostamento[posPrec.h + i][posPrec.l - j] = 1;
            }
            
            posPrec.l = posPrec.l - n;
            posPrec.h = posPrec.h;
   
            spostamento[posPrec.h][posPrec.l] = 2;
            
            *posAttuale = posPrec;
        }
    }

}

void stampaGriglia (Griglia stampa, int spostamento[][stampa.l], Griglia vecchiaPosizione, int penna){
    int i, j;
    
    spostamento[vecchiaPosizione.h][vecchiaPosizione.l] = 2;
    
    for (i=0; i<stampa.l+2; i++){
        printf ("-");
    }
    printf("\n");
    
    for (i=0; i<stampa.h; i++){
            printf("|");
            for (j=0; j<stampa.l; j++){
                if(spostamento[i][j]==0)
                    printf (" ");
                else if(spostamento[i][j]==1)
                    printf ("*");
                else if (spostamento[i][j] == 2){
                    if (penna==1)
                        printf ("O");
                    else
                        printf ("I");
                }
            }
            printf("|\n");
    }
    
    for (i=0; i<stampa.l+2; i++){
        printf ("-");
    }
}


int main(void) {
    
    Griglia grigliaPrincipale, posAttuale;
    int i, j, comando, spost, penna = 1, direzione=1;
    
    do{
        printf ("Inserire lunghezza griglia(max di 100): ");
        scanf ("%d", &grigliaPrincipale.l);
        printf ("Inserire altezza griglia(max di 25): ");
        scanf ("%d", &grigliaPrincipale.h);
        
    }while(grigliaPrincipale.l > 100 || grigliaPrincipale.h > 25);
    
    int traccia[grigliaPrincipale.h][grigliaPrincipale.l];
    for(i=0; i<grigliaPrincipale.h; i++){
        for (j=0; j<grigliaPrincipale.l; j++){
            traccia[i][j] = 0;
        }
    }
    
    Griglia posPrec;
    posPrec.l = grigliaPrincipale.l/2;
    posPrec.h = grigliaPrincipale.h/2;
    
    posAttuale = posPrec;
    
    do{
        spost = 0;
        stampaGriglia (grigliaPrincipale, traccia, posPrec, penna);
        stampaComandi();
        
        scanf("%d,%d", &comando, &spost);
        
        pennaAlzata(comando, &penna);
        direzione = direzioneTartaruga(comando, direzione);

        spostamentoTartaruga(comando, spost, grigliaPrincipale, penna, direzione, traccia, posPrec, &posAttuale);
        posPrec = posAttuale;
            
        
    } while(comando!=6);
    
    return 0;
}
