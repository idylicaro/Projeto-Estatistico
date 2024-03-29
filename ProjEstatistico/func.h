#include <iostream>
#include <math.h>
#include <fstream>
#include <string.h>
using namespace std;

float KclassesCalculo(int n)
{
    float k=0;
    k = 1+(3.22*log10(n));
    return k;
}
int maior(int vet[],int TAM)
{
    int maior = vet[0];
    for (int i = 1; i < TAM; i++)
    {
        if (vet[i] > maior)
        {
            maior    = vet[i];
        }
    }
    return maior;
}
int menor(int vet[],int TAM)
{
    int menor = vet[0];
    for (int i = 1; i < TAM; i++)
    {
        if (vet[i] < menor)
        {
            menor    = vet[i];
        }
    }
    return menor;
}

int verificaIntervalo(int k,int vet[],int tam,int h)
{
    float menorr = menor(vet,tam);
    float maiorr = maior(vet,tam);

    menorr -=0.5;
    maiorr -=0.5;
    float intervaloTest = menorr;
    int contador=0;
    while(intervaloTest <= maiorr)
    {
        intervaloTest +=h;
        contador++;
    }
    return contador;
}

void definindoIntervalos(int small,int k,int h,float intervalo[][2])
{
    float interval = small - 0.5;

    for(int i = 0; i<k; i++)
    {
        for(int j =0; j<2; j++)
        {
            intervalo[i][j] = interval + (h*j);
            interval += (h*j); // quando h for 0 vai ser o primeiro intervalo
        }
    }

}

void calculoPMedio(float tabela[][6],float intervalos[][2],int k)
{
    for(int i = 0; i<k; i++)
    {
        tabela[i][0]= (intervalos[i][0] + intervalos[i][1])/2;
    }
}
void zeraTAbela(float tabela[][6],int k)
{
    for(int i=0; i<k; i++)
    {
        for(int g = 0; g<6; g++)
        {
            tabela[i][g] = 0;
        }
    }
}
void calculoFrequenciaClasse(float tabela[][6],float intervalos[][2],int k,int dados[],int tam)
{

    for(int i = 0; i<k; i++)
    {
        for(int j=0; j<tam; j++)
        {
            //cout <<dados[j]<<endl;
            if(dados[j]>=intervalos[i][0] && dados[j]<=intervalos[i][1] )
            {
                tabela[i][1]+=1;
            }

        }
    }
}
void calculoFrequenciaClasseAcumulada(float tabela[][6],int k)
{
    float soma=0;
    for(int i = 0; i<k; i++)
    {
        if(i==0)
        {
            tabela[i][2] = tabela[i][1];
            soma = tabela[i][1];
        }
        else
        {
            soma+=tabela[i][1];
            tabela[i][2] = soma;
        }
    }
}
void calculoFrequenciaClasseRelativa(float tabela[][6],int k,int tam)
{
    for(int i = 0; i<k; i++)
    {
        tabela[i][3] = tabela[i][1]/tam;
    }
}
void calculoFrequenciaClasseRelativaAcumulada(float tabela[][6],int k)
{
    float soma=0;
    for(int i = 0; i<k; i++)
    {
        if(i==0)
        {
            tabela[i][4] = tabela[i][3];
            soma = tabela[i][3];
        }
        else
        {
            soma+=tabela[i][3];
            tabela[i][4] = soma;
        }
    }
}
void calculoMediaClasse(float tabela[][6],int k)
{
    for(int i = 0; i<k; i++)
    {
        tabela[i][5] = tabela[i][0]*tabela[i][1];
    }
}
float calculoMediaClasseAcumulada(float tabela[][6],int k,int tam)
{
    float soma=0;
    for(int i = 0; i<k; i++)
    {
        if(i==0)
        {
            soma = tabela[i][5];
        }
        else
        {
            soma+=tabela[i][5];
        }
    }
    return soma/(tam);
}
float calculoVariancia(float tabela[][6],int k,int tam,float media)
{
    double variancia=0,aux1=0,aux2=0;
    aux2 = (tam*(pow(media,2))) ;
    for(int i = 0; i<k; i++)
    {
        aux1 +=(pow(tabela[i][0],2) * tabela[i][1]);
    }
    variancia = (aux1-aux2)/(tam-1);
    return variancia;
}
void selecioArchive(char nameArquivo[20]){  //quando for chamar essa funçao o parametro tem q ser zerado
    char nameAux[15];
    cout << "Nome do Arquivo.txt a Selecionar:"<<endl;
    cin >> nameAux;
    strcat(nameAux,".txt");
    strcat(nameArquivo,nameAux);
}
void lerArquivo(int vet[],int tam){
    char nameArchive[20] = "";
    selecioArchive(nameArchive);
    fstream archive;
    archive.open(nameArchive,ios::in);

    if(archive.fail())
        cout <<"Arquivo NAO foi encontrado!Feche e verifique os arquivos"<<endl;

    for(int i=0;i<tam;i++){
        archive >> vet[i];
    }
}
