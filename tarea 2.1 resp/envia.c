//envia archivos

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h> //printf, perror,fdopen
#include <string.h>
#include <netdb.h> //gethostbyname
#include <unistd.h>//close
#include <stdlib.h> //exit

int main(int argc, char* argv[]){
    char host[10];
    int pto;

    printf("Escribe la direccion del servidor:");
    //gets(host);
    fgets(host,sizeof(host),stdin);
    printf("\nEscribe el puerto:");
    scanf("%d",&pto);
    fflush(stdin);
    getchar();
    struct hostent *dst = gethostbyname(host);
    if(dst==NULL){
        perror("Direccion no valida");
        main(argc,argv);
    }//if

    //aqui empieza mi modificacion

    char *archivo;

    archivo=(char*)calloc(200,sizeof(char));

    printf("ingrese ruta del archivo: ");

    scanf("%[^\n]",archivo);

    FILE *f1;
    f1=fopen(archivo,"r");
    if(f1==NULL){
        printf("ERROR: no se puede abrir el archivo\n");
        exit(0);
    }

    char *token,aux[100];
    while(token!=NULL){
        memcpy(aux,token,100);
        token=strtok_r(archivo,"/",&archivo);
    }

    //aqui termina

    struct sockaddr_in sdir;
    bzero((char *)&sdir, sizeof(sdir));
    sdir.sin_family=AF_INET;
    sdir.sin_port=htons(pto);
    memcpy((char*)&sdir.sin_addr.s_addr,dst->h_addr,dst->h_length);
    int cd = socket(AF_INET,SOCK_STREAM,0);
    FILE *f = fdopen(cd,"w+");
    if (connect(cd,(struct sockaddr *)&sdir,sizeof(sdir))<0){
        perror("error en funcion connect()\n");
        exit(0);
    }//if
    printf("\n Conexion establecida.. enviando datos..\n");

    //aqui se envian los datos
    int n;
    n=write(cd,aux,strlen(aux)+1);
    if(n<0)
        perror("Error al escribir");
    else if(n==0)
        perror("Socket cerrado inesperadamente");
    else
        printf("nombre enviado\n");
    
    fflush(f);
    char buffer[1024];
    while(!feof(f1)){
        //aqui leo lo que contiene el archivo
        fread(buffer,sizeof(char),1024,f1);
        //printf("%s\n",buffer);
        n=write(cd,buffer,1024);
        if(n<0) 
            perror("Error de escritura\n");
        else if(n==0)
            perror("Socket cerrado error de escritura\n");
        fflush(f);
    }
    printf("Se envio el archivo %s\n",aux );
    close(cd);
    fclose(f);

    return 0;
}//main

