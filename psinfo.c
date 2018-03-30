/*
* Julián Muñoz M 
* SO y lab 2018 -1
* UdeA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

void usage(char *filename);
int searchInFile(char *filename, char *s);
void print_status(char *pid);

int main (int argc, char *argv[]){

    // int result;
    if(argc < 2){
        usage(argv[0]);
        exit(1);
    }

 /*    printf("%s", argv[1]);

    char str[30] = "VmData";
    char *fname = "/proc/";
    strncat(fname, argv[1], 5);
    strncat(fname, "/status", 10); */

    /* if(result == -1){
        perror("Error");
        exit(1);
    } */

    printf("\n");
    if(strncmp(argv[1], "-l", 2) == 0){
        int i;
        for(i = 2; i < argc; i++){
            // printf("oie %s\n", argv[i]);
            print_status(argv[i]);
        }
    }
    else{
        print_status(argv[1]);
    }

    return 0;
}

void usage(char *app){
    printf("Usage: %s [PID]\n\n", app);
}

// Función parser
void print_status(char *pid){
    printf("********* PID del proceso: %s *********\n", pid);
    int salto = 0;

    char path[40], line[100], *p;
    FILE *statusf;

    // Crea la ruta para el proceso
    snprintf(path, 40, "/proc/%s/status", pid);

    printf("Ruta:\t\t/proc/%s/status\n", pid);
    
    statusf = fopen(path, "r");
    if(!statusf)
        return;
    
    while(fgets(line, 100, statusf)){
        // La función strncmp, compara 2 strings y devuelve 0 si son iguales.
        if(strncmp(line, "Name:", 5) == 0)
        {   // Sirve para saltarse los caracteres Name: y obtener el valor de la linea
            // Ejemplo 1: si la linea es "Name: gedit", se obtiene "gedit".
            salto = 6;
            printf("Nombre: \t");
        }
        if(strncmp(line, "State:", 6) == 0)
        {
            salto = 7;
            printf("Estado: \t");
        }
        if(strncmp(line, "VmExe:", 6) == 0){
            salto = 7;
            printf("\tTEXT: \t\t");
        }
        if(strncmp(line, "VmData:", 7) == 0){
            salto = 8;
            printf("Tamaño de las regiones de memoria:\n");
            printf("\tDATA: \t\t");
        }
        if(strncmp(line, "VmStk:", 6) == 0){
            salto = 7;
            printf("\tSTACK: \t\t");
        } 
        if(strncmp(line, "voluntary_ctxt_switches:", 24) == 0){
            salto = 25;
            printf("Número de cambios de contexto realizados:\n");
            printf("\tVoluntarios: \t");
        }
        if(strncmp(line, "nonvoluntary_ctxt_switches:", 27) == 0){
            salto = 28;
            printf("\tNo voluntarios: ");
        }
        // Si salto = 0 significa que 
        if(salto == 0)
            continue;
        
        
        // Ignorar Name:
        p = line + salto;
        // Ignorar espacio en blanco
        // Del ejemplo 1, se puede obtener p = "  gedit", la siguiente instrucción
        // devuelve p = "gedit"
        // *p caracter a la izquierda de p, ++p remueve un caracter a la izquierda de p.
        // de p.
        while(isspace(*p)) ++p;
        printf("%s", p);
        salto = 0;
        // break;
    }

    fclose(statusf);
    printf("\n");
}

int searchInFile2(char *filename, char *s){
    FILE *fp;
    int findResutl = 0;
    char temp[512];

    // Abre el archivo y lo asigna a la variable fp
    if((fp = fopen(filename, "r")) == NULL){
        return -1;
    }

    // Busca la cadena en el archivo e imprime la linea completa que contiene 
    // dicha cadena.
    while(fgets(temp, 512, fp) != NULL){
        if(strstr(temp, s) != NULL){
            printf("\n%s\n", temp);
            findResutl++;
        }
    }

    // Cierra el archivo si todavia está abierto.
    if(fp){
        fclose(fp);
    }   
    return 0;
}
