


/*BIBLIOTECAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*DEFINE*/
#define ZERO 0
#define MAX_UTENTE 15
#define MAX_LOCAL 50
#define MAX_PC 30
#define MAX_PROCESSADOR 10
#define MAX_CODIGO 20
#define MAX_NOME 80
#define MAX_ESTADO 10
#define MAX_REQUISICAO 100
#define MAX_TOTALREQUISICAO 100
#define MAX_DESIG 100


typedef struct //Estrutura tData
{
    int iDia;
    int iMes;
    int iAno;
} tData;

typedef struct //Estrutura Requisição. tRequisicao;
{
    char sCodigo[MAX_CODIGO]; //codigo da requisicao
    int iIdentPC; //numero de identificacao do pc
    char sNomeUtente[MAX_NOME]; //nome da pessoa que requisitou
    char sUtente[MAX_UTENTE]; //tipo de utente
    char cEstadoReq; //estado da requisicao ativa ou concluida
    int iCampus; // qual o campus que foi devolvido 0 = residencias
    float fMulta;// valor multa(cada dia 10 euros) isto calcula se na hora
    tData tDataReq; // data da requisicao
    tData tPrazReq; //prazo de requisição
    tData tDataDevolv; //data devolucao
} tRequisicao;


typedef struct //Informação referente a todos os portáteis.tInfPortatil;
{
    int iNumero; //numero de identificacao do pc
    char sDesignacao[MAX_DESIG]; //Designacao
    float fValorPC; //valor do equipamento
    char sProcessador[MAX_PROCESSADOR];//processador
    int iRAM; //valor da ram do pc em gb
    int iAvarias; // a quantidade de avarias
    int iDisponibilidade; //0 = disponivel e 1 = indisponivel 2 = REQUISITADO
    char sLocal[MAX_LOCAL]; //localização de um computador portátil
    int iQuantReq;

} tInfPortatil;

typedef struct //Informação referente a todos os portáteis.tInfPortatil;
{
    int iNumPc; //numero de identificacao do pc FAZER PONTEIRO
    int iAvariaCod; //numero da avaria (Rafael: nao percebi, codigo/numero da avaria?)
    char cTipoAvaria; // permanente ou temporaria
    //tData tDataAvaria; //(Rafael: como diz la depois que teremos de listar no ficheiro com a data da avaria)
    // char cEstado; //avariada ou arranja EM VEZ DISTO USAMOS A DISPONIBILIDADE DO PC!
    int iDias; //durancao de dias quando reparada

} tInfAvarias;


//***************************************************************//
//FUNCOES

//Apresentar no menu principal a seguinte informação
//quantidade de portáteis existentes, quantidade de portáteis disponíveis, quantidade total de requisições efetuadas e quantidade de requisições ativas.
char menu(int iQuantPcExiste,int iQuantPcDispo,int iQuantReqEfetuadas, int iQuantReqAtivas);
// //
char menuRegistar(void);//=========
tRequisicao *criarRequisicao(tRequisicao *vRequisicaoPC, int *iQuantRequisicao, tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste);
void registarDevolucao(tRequisicao vRequisicaoPC[], int iQuantRequisicao, tInfPortatil vInformacoesPC[MAX_PC], int iQuantPCExiste, int *iQuantPCDispo);
void registarRenovar(tRequisicao *vRequisicaoPC, int iQuantRequisicao); //RAFA
char menuInserir(void);//=========//
void inserirAvarias(tInfPortatil vInformacoesPC[MAX_PC]); // RAFA 69
void inserirInformacoes(tInfPortatil vInformacoesPC[MAX_PC], int *iQuantPcExiste); // DONE
void alterarLocPC(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste);//Registar a alteração da localização de um computador portátil. RAFA 69
char menuApresentar(void);//=========//
void apresentarInformacoes(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste);
void apresentarRequisicoes(tRequisicao *vRequisicaoPC, int iQuantRequisicao);
//void registarDevolucao(tInfPortatil vInformacoesPC[MAX_PC], int iPcDevolv);
void limpaEcra(void); //DONE
void limpaBufferStdin(void); //DONE
int lerInteiro(int min, int max); //DONE
float lerFloat(float min, float max); //DONE
void lerString(char vetor[], int max); //DONE
char menuTerminar(void);
char menuFicheiro(void);
void apresentarInformacoesBin(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste);
tData lerData(void); //DONE
int procuraPC(tInfPortatil vInformacoesPC[MAX_PC],int iQuantPcExiste,int iNumPC);
int procuraRequisicao(tRequisicao *vRequisicaoPC, char codigoRequisicao[], int iQuantRequisicao);
//tData calculoPrazo(tRequisicao *vRequisicaoPC, int iQuantRequisicao, int iDias);
tData calculoPrazo(tData dataInicio, int iDias);
int subData(tData dataInicio, tData dataDevolucao);
int maxDiasCalc(int iMes, int iAno);
//Funcoes de ficheiros
int leFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC]); //DONE
void escreveFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste);//DONE
void resetFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC], int *iQuantPcExiste);
char menuConfirmar();


int main()
{
    tInfPortatil vInformacoesPC[MAX_PC]; //Declaração do vetor sobre as informações de todos os pcs
    tRequisicao *vRequisicaoPC; //vetor dinamico com a informacao das requisicoes
    tInfAvarias *vAvarias;
    int iQuantAvariasT = 0;
    int iQuantPcExiste=0, iQuantPcDispo=0, iQuantRequisicao=0, iQuantReqAtivas=0;
    char iAuxI;
    char cEscolha, cSubEscolha;
    vRequisicaoPC = NULL;
    vAvarias = NULL;

    // iQuantPcExiste = leFicheiroBinario(vInformacoesPC);

    do
    {
        cEscolha = menu(iQuantPcExiste, iQuantPcDispo, iQuantRequisicao,  iQuantReqAtivas);

        switch (cEscolha)
        {
        case 'I':
            cSubEscolha = menuInserir();
            switch (cSubEscolha)
            {
            case 'I':
                inserirInformacoes(vInformacoesPC, &iQuantPcExiste);
                break;
            case 'A':
                // inserirAvarias(tInfPortatil vInformacoesPC]);
                break;
            case 'E':
                alterarLocPC(vInformacoesPC, iQuantPcExiste);
                break;
            default:
                printf("voltouuu \n");
            }
            break;
        case 'R':
            cSubEscolha = menuRegistar();
            switch (cSubEscolha)
            {
            case 'C':
                if(iQuantPcExiste == 0)
                {
                    printf("<><><><><><><><><><><><><><><><><><><><><><><><> \n");
                    printf("<>                                            <>\n");
                    printf("<>        Nao existe pcs, pretende criar?     <> \n");
                    iAuxI = menuConfirmar();
                    if(iAuxI == 'S')
                    {
                        inserirInformacoes(vInformacoesPC, &iQuantPcExiste);
                    }
                }
                else
                {
                    vRequisicaoPC = criarRequisicao(vRequisicaoPC, &iQuantRequisicao, vInformacoesPC, iQuantPcExiste);
                }

                break;
            case 'D':
                registarDevolucao(vRequisicaoPC,iQuantRequisicao,vInformacoesPC,iQuantPcExiste,&iQuantPcDispo);
                break;
            case 'R':
                registarRenovar(vRequisicaoPC,iQuantRequisicao);
                break;
            default:
                printf("voltouuu \n");
            }
            break;
        case 'A':
            cSubEscolha = menuApresentar();
            switch (cSubEscolha)
            {
            case 'I':

                if(iQuantPcExiste == 0)
                {
                    printf("<><><><><><><><><><><><><><><><><><><><><><><><> \n");
                    printf("<>                                            <>\n");
                    printf("<>        Nao existe pcs, pretende criar?     <> \n");
                    iAuxI = menuConfirmar();
                    if(iAuxI == 'S')
                    {
                        inserirInformacoes(vInformacoesPC, &iQuantPcExiste);
                    }
                }
                else
                {
                    apresentarInformacoes( vInformacoesPC, iQuantPcExiste);
                }
                break;
            case 'R':
                if(iQuantRequisicao == 0)
                {
                    printf("<><><><><><><><><><><><><><><><><><><><><><><><> \n");
                    printf("<>                                            <>\n");
                    printf("<>        Nao existe requisicoes     <> \n");

                }
                else
                {
                    apresentarRequisicoes( vRequisicaoPC, iQuantRequisicao);
                }

                break;
            case 'U':
                //registarRenovar(vRequisicaoPC);
                break;
            case 'E':
                //registarRenovar(vRequisicaoPC);
                break;
            case 'A':
                resetFicheiroBinario(vInformacoesPC, &iQuantPcExiste);
                break;
            default:
                printf("voltouuu \n");
            }
            break;
        case 'F':
            cSubEscolha = menuRegistar();
            switch (cSubEscolha)
            {
            case 'R':
                vRequisicaoPC = criarRequisicao(vRequisicaoPC, &iQuantRequisicao, vInformacoesPC, iQuantPcExiste);
                break;
            case 'L':
                //registarDevolucao(vRequisicaoPC);
                break;
            case 'A':
            //registarRenovar(vRequisicaoPC);
            case 'M':
                iQuantPcExiste = leFicheiroBinario(vInformacoesPC);
                break;
            default:
                printf("voltouuu \n");
            }
            break;
        default:
            cSubEscolha = menuTerminar();
        }
    }
    while(cEscolha != 'T' || cSubEscolha != 'S');
    printf("byeee");

    free(vRequisicaoPC);
    free(vAvarias);
    return 0;
}



char menu(int iQuantPcExiste,int iQuantPcDispo,int iQuantRequisicao, int iQuantReqAtivas)
{
    char cEscolha;
    char sMsg[60] = "                                               ";
    iQuantPcDispo = 24;
    iQuantReqAtivas = 400000;

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                       GESTAO DE COMPUTADORES                         | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                           SEJA BEM-VINDO                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | SELECIONE A OPCAO:               INFORMACOES:                        | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (I)NSERIR                        'PORTATEIS EXISTENTES  - %-7d    | |\n", iQuantPcExiste);
        printf("| | (R)ESGISTAR                      'PORTATEIS DISPONIVEIS - %-7d    | |\n", iQuantPcDispo);
        printf("| | (A)PRESENTAR                     'REQUISICOES ATIVAS    - %-7d    | |\n", iQuantRequisicao);
        printf("| | (F)ICHEIROS                      'TOTAL DE REQUISICOES  - %-7d    | |\n", iQuantReqAtivas);
        printf("| | (T)ERMINAR                                                           | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  MENSAGEM: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");


        printf("| |                                                                      | |\n");
        printf("| | Opcao: (I)(R)(A)(T) Selecione: ");
        scanf(" %c", &cEscolha);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaEcra();
        limpaBufferStdin();
        cEscolha = toupper(cEscolha);
        if(cEscolha != 'I' && cEscolha != 'R' && cEscolha != 'A' && cEscolha != 'F' && cEscolha != 'T' )
        {
            strcpy(sMsg,"POR FAVOR, SELECIONE UMA DAS OPCOES EXISTENTES!");
        }
        else
        {
            strcpy(sMsg,"                                               ");
        }

    }
    while(cEscolha != 'I' && cEscolha != 'R' && cEscolha != 'A' && cEscolha != 'F' && cEscolha != 'T' );

    return cEscolha;

}


char menuRegistar(void)
{
    char cSubEscolha;
    char sMsg[60] = "                                               ";

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                       REGISTAR COMPUTADORES                          | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | SELECIONE A OPCAO:                                                   | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (C)RIAR REGISTO                                                      | |\n");
        printf("| | (D)EVOLVER                                                           | |\n");
        printf("| | (R)ENOVAR                                                            | |\n");
        printf("| | (V)OLTAR                                                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  MENSAGEM: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");


        printf("| |                                                                      | |\n");
        printf("| | Opcao: (C)(D)(R)(V) Selecione: ");
        scanf(" %c", &cSubEscolha);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaEcra();
        limpaBufferStdin();
        cSubEscolha = toupper(cSubEscolha);
        if(cSubEscolha != 'C' && cSubEscolha != 'D' && cSubEscolha != 'R' && cSubEscolha != 'V' )
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");
        }
        else
        {
            strcpy(sMsg,"                                               ");
        }

    }
    while(cSubEscolha != 'C' && cSubEscolha != 'D' && cSubEscolha != 'R'&& cSubEscolha != 'V' );

    return cSubEscolha;
}


tRequisicao *criarRequisicao(tRequisicao *vRequisicaoPC, int *iQuantRequisicao, tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste)
{
    int iNumPC, iPosicao =-1, iPosReq = -1, iDias;
    tRequisicao *vRequisicaoAUX;
    vRequisicaoAUX = vRequisicaoPC;
    char codigoRequisicao[MAX_CODIGO],cOpcao;

    printf("========REQUISICOES========\n");

    do
    {
        printf("\nIntroduza o numero do portatil: ");
        iNumPC = lerInteiro(1,9999);
        iPosicao = procuraPC(vInformacoesPC, iQuantPcExiste, iNumPC);
        cOpcao = 'N';
        if(iPosicao == -1)
        {
            printf("\n O portatil nao existe!");
            printf("\nPretende introduzir outro numero? \n");
            cOpcao = menuConfirmar();
        }
    }
    while(cOpcao == 'S');

    if(iPosicao != -1)
    {

        vRequisicaoPC = realloc(vRequisicaoPC, (*iQuantRequisicao+1)*sizeof(tRequisicao));
        if(vRequisicaoPC==NULL)
        {
            printf("\nERRO -  Impossivel ao alocar memoria");
            vRequisicaoPC = vRequisicaoAUX;
        }
        else
        {
            vRequisicaoPC[*iQuantRequisicao].iIdentPC = iNumPC;

            printf("\nIntroduza o tipo de utente: ");
            lerString(vRequisicaoPC[*iQuantRequisicao].sUtente, 15);

            printf("Introduza o nome do utente: ");
            lerString(vRequisicaoPC[*iQuantRequisicao].sNomeUtente,MAX_NOME);

            do
            {
                printf("Codigo da requisicao: ");
                lerString(codigoRequisicao, MAX_CODIGO);

                iPosReq = procuraRequisicao( vRequisicaoPC, codigoRequisicao, *iQuantRequisicao);

                if(iPosReq !=-1)
                {
                    printf("Codigo ja existente! - Insira novamente!");
                }
                else
                {
                    strcpy(vRequisicaoPC[*iQuantRequisicao].sCodigo,codigoRequisicao);
                }

            }
            while(iPosReq != -1);


            vRequisicaoPC[*iQuantRequisicao].cEstadoReq = 'a';
            printf("dia de hoje: ");
            vRequisicaoPC[*iQuantRequisicao].tDataReq = lerData();
            printf("Duracao da requisicao: ");
            iDias= lerInteiro(1,30);
            vRequisicaoPC[*iQuantRequisicao].tPrazReq = calculoPrazo(vRequisicaoPC[*iQuantRequisicao].tDataReq,  iDias);//devolucao
            vRequisicaoPC[*iQuantRequisicao].iCampus = -1; // n pode ser 3 nem 4
            vRequisicaoPC[*iQuantRequisicao].fMulta = 0.0;
            (*iQuantRequisicao)++;
            vInformacoesPC[iPosicao].iQuantReq ++;
            vInformacoesPC[iPosicao].iDisponibilidade = 1;


        }
    }


    return vRequisicaoPC;
}


void registarDevolucao(tRequisicao vRequisicaoPC[], int iQuantRequisicao, tInfPortatil vInformacoesPC[MAX_PC], int iQuantPCExiste, int *iQuantPCDispo)
{
    char sCodigo[MAX_CODIGO];
    int iPos, iDias, iPosPC, iAvaria;
    tData DataDev, DataPraz;


    printf("\nIntroduza o codigo da requisicao: ");
    lerString(sCodigo,MAX_CODIGO);

    iPos = procuraRequisicao(vRequisicaoPC, sCodigo, iQuantRequisicao);

    if(iPos == -1)
    {
        printf("\nCodigo inexistente - Requisicao nao existe!\n");
    }
    else
    {

        printf("\nIntroduza o campus da devolucao: ");
        vRequisicaoPC[iPos].iCampus = lerInteiro(1,5);


        printf("\nIntroduza a data de devolucao: ");
        DataDev = lerData();
        vRequisicaoPC[iPos].tDataDevolv = DataDev;
        DataPraz = vRequisicaoPC[iPos].tPrazReq;
        iDias = subData(vRequisicaoPC[iPos].tPrazReq, DataDev);

        if(iDias > 0)
        {
            vRequisicaoPC[iPos].fMulta = iDias*10.0;
            printf("Multa a pagar: %.2f\n", vRequisicaoPC[iPos].fMulta);

        }
        else
        {
            vRequisicaoPC[iPos].fMulta = 0;
        }

        vRequisicaoPC[iPos].cEstadoReq = 'c';
        iPosPC = procuraPC(vInformacoesPC, iQuantPCExiste, vRequisicaoPC[iPos].iIdentPC);
        if(iPosPC == -1)
        {
            printf("\nPC nao existe!");
        }
        else
        {

            printf("\nO Portatil tem alguma avaria? Sim - (1) Nao - (0)");
            iAvaria = lerInteiro(0,1);
            if(iAvaria == 0)
            {
                vInformacoesPC[iPosPC].iDisponibilidade = 0;
                (*iQuantPCDispo)++;
            }
            else
            {
                //inserirAvarias(vInformacoesPC[iPosPC]);//Funcao ainda nao feita
            }
        }

        //escrever no ficheiro (Dados da requisicao, processador e ram do pc)

    }
}

void registarRenovar(tRequisicao *vRequisicaoPC, int iQuantRequisicao)
{
    int iDias, iPos;
    char sCodigo[MAX_CODIGO];

    printf("Introduza o codigo de requisicao: ");
    lerString(sCodigo, MAX_CODIGO);

    iPos = procuraRequisicao(vRequisicaoPC, sCodigo, iQuantRequisicao);
    if(iPos == -1)
    {
        printf("Requisicao Inexistente!");
    }
    else
    {
        printf("Introduza o numero de dias a renovar a Requisicao: ");
        iDias = lerInteiro(1,7);

        calculoPrazo(vRequisicaoPC[iPos].tPrazReq, iDias);
    }
}

char menuInserir(void)
{
    char cSubEscolha;
    char sMsg[60] = "                                               ";

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                             INSERIR                                  | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | SELECIONE A OPCAO:                                                   | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (I)NFORMACOES                                                        | |\n");
        printf("| | (E)DITAR LOCALIZACAO                                                 | |\n");
        printf("| | (A)VARIAS/REPARACOES                                                 | |\n");
        printf("| | (V)OLTAR                                                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  MENSAGEM: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");


        printf("| |                                                                      | |\n");
        printf("| | Opcao: (I)(A)(E)(V) Selecione: ");
        scanf(" %c", &cSubEscolha);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaEcra();
        limpaBufferStdin();
        cSubEscolha = toupper(cSubEscolha);
        if(cSubEscolha != 'I' && cSubEscolha != 'A' && cSubEscolha != 'E' && cSubEscolha != 'V' )
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");
        }
        else
        {
            strcpy(sMsg,"                                               ");
        }

    }
    while(cSubEscolha != 'I' && cSubEscolha != 'A' && cSubEscolha != 'E'&& cSubEscolha != 'V' );

    return cSubEscolha;
}
void inserirInformacoes(tInfPortatil vInformacoesPC[MAX_PC], int *iQuantPcExiste)
{

    int i, iNumPC;
    i = *iQuantPcExiste;
    if(*iQuantPcExiste == MAX_PC)
    {
        printf("Impossivel adicionar mais portateis - Limite atingido!");
    }
    else
    {
        printf("<----------------------------------------------------->\n");
        printf("<----------------------------------------------------->\n");
        printf("\n   Introduza o valor de portateis a registar: ");
        iNumPC = lerInteiro(ZERO,MAX_PC);
        (*iQuantPcExiste) += iNumPC;
        while(i < (*iQuantPcExiste))

        {


            vInformacoesPC[i].iNumero = i+1;
            printf("\n  N. Identificacao PC:|| %d ||",vInformacoesPC[i].iNumero);
            printf("\n    PC designacao: ");
            lerString(vInformacoesPC[i].sDesignacao, 20);
            printf("    Valor PC: ");
            vInformacoesPC[i].fValorPC = lerFloat(50,9999);
            printf("    Processador PC: ");
            lerString(vInformacoesPC[i].sProcessador, MAX_PROCESSADOR);
            printf("    Quantidade RAM (em GB): ");
            vInformacoesPC[i].iRAM = lerInteiro(1,64);
            vInformacoesPC[i].iAvarias = 0;
            printf("    Localizacao do PC: ");
            lerString(vInformacoesPC[i].sLocal, 10);
            i++;
            printf("<----------------------------------------------------->\n");
            printf("<----------------------------------------------------->\n");
        }

        // escreveFicheiroBinario(vInformacoesPC, *iQuantPcExiste);
    }
}

void alterarLocPC(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste)
{
    int iPosPC, iNumeroPC;

    printf("\nIntroduza o numero do PC a alterar a  localizacao: ");
    iNumeroPC = lerInteiro(1, 99);

    iPosPC = procuraPC(vInformacoesPC, iQuantPcExiste, iNumeroPC);
    if(iPosPC == -1)
    {
        printf("\nPC nao existe!");
    }
    else
    {
        printf("\nIntroduza a localizacao do portatil: ");
        lerString(vInformacoesPC[iPosPC].sLocal, MAX_LOCAL);
    }
}


tInfAvarias *AvariasPC(tInfAvarias *vAvarias, tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste, int *iQuantAvariasT)
{
    int iPosPC, iNumeroPC;
    tInfAvarias *vAvariasAUX;
    char cTipoAvaria;

    vAvariasAUX = vAvarias;

    printf("\nIntroduza o numero do PC com a avaria: ");
    iNumeroPC = lerInteiro(1, 99);

    iPosPC = procuraPC(vInformacoesPC, iQuantPcExiste, iNumeroPC);
    if(iPosPC == -1)
    {
        printf("\nPC nao existe!");
    }
    else
    {
        vAvarias = realloc(vAvarias, (*iQuantAvariasT+1)*sizeof(tInfAvarias));
        if(vAvarias==NULL)
        {
            printf("\nERRO -  Impossivel ao alocar memoria");
            vAvarias = vAvariasAUX;
        }
        else
        {

            //vAvarias[*iQuantAvariasT].tDataAvaria = lerData(); //VER ESTRUTURA
            do
            {
                printf("\nIntroduza o tipo de avaria - (P)ermanente / (T)emporaria: ");
                scanf(" %c", &cTipoAvaria);
                cTipoAvaria = toupper(cTipoAvaria);

                if(cTipoAvaria != 'P' && cTipoAvaria != 'T')
                {
                    printf("OPCAO INVALIDA - Tente novamente!");
                }
            }
            while(cTipoAvaria != 'P' && cTipoAvaria != 'T');

            vAvarias[*iQuantAvariasT].cTipoAvaria = cTipoAvaria;

            if(cTipoAvaria == 'P')
            {
                vInformacoesPC[iPosPC].iDisponibilidade = 1; //indisponivel para dizer que está avariado permanente?
                vAvarias[*iQuantAvariasT].iDias = -1; //para identificar que é uma avaria permanente?
            }
            else
            {
                vInformacoesPC[iPosPC].iDisponibilidade = 0; //REPARADO
                printf("\nIntroduza o numero de dias que o portatil esteve avariado: ");
                vAvarias[*iQuantAvariasT].iDias = lerInteiro(0,9999);
            }
            (*iQuantAvariasT)++;

        }
    }
    return vAvarias;
}




char menuApresentar(void)
{
    char cSubEscolha;
    char sMsg[60] = "                                               ";

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                         APRESENTAR INFORMACOES                       | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | SELECIONE A OPCAO:                                                   | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (I)NFORMACOES                                                        | |\n");
        printf("| | (R)EQUISICAO                                                         | |\n");
        printf("| | (U)MA REQUISICAO                                                     | |\n");
        printf("| | (E)STATISTICAS                                                       | |\n");
        printf("| | (A)VARIAS  //reseta                                                  | |\n");
        printf("| | (V)OLTAR                                                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  MENSAGEM: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");


        printf("| |                                                                      | |\n");
        printf("| | Opcao: (I)(R)(U)(E)(A)(V) Selecione: ");
        scanf(" %c", &cSubEscolha);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaEcra();
        limpaBufferStdin();
        cSubEscolha = toupper(cSubEscolha);
        if(cSubEscolha != 'I' && cSubEscolha != 'R' && cSubEscolha != 'U' && cSubEscolha != 'E' && cSubEscolha != 'A' && cSubEscolha != 'V' )
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");
        }
        else
        {
            strcpy(sMsg,"                                               ");
        }

    }
    while(cSubEscolha != 'I' && cSubEscolha != 'R' && cSubEscolha != 'U' && cSubEscolha != 'E' && cSubEscolha != 'A' && cSubEscolha != 'V');

    return cSubEscolha;
}

void apresentarInformacoes(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste)
{

    int i, iOpcaoPC;
    printf("APRESENTAR INFORMACOES");
    printf("Qual o pc pretendido? // todos = 0 \n");
    iOpcaoPC = lerInteiro(ZERO,iQuantPcExiste);


    if(iOpcaoPC == 0)
    {
        printf("A mostrar todos os pcs");
        for(i=0; i<(iQuantPcExiste); i++)
        {
            printf("\n N. Identificacao PC: %d", vInformacoesPC[i].iNumero);
            printf("\nValor PC designacao: %s ", vInformacoesPC[i].sDesignacao);
            printf("\nValor PC: %2.f ", vInformacoesPC[i].fValorPC );
            printf("\nProcessador PC: %s ", vInformacoesPC[i].sProcessador);
            printf("\n Quantidade RAM (em GB): %d", vInformacoesPC[i].iRAM );
            printf("\n Avariado: %d", vInformacoesPC[i].iAvarias );
            printf("\nLocalizacao do PC: %s", vInformacoesPC[i].sLocal);

        }
    }

    else
    {
        iOpcaoPC--;
        printf("A mostrar PC %d", iOpcaoPC);
        printf("\n N. Identificacao PC: %d", vInformacoesPC[iOpcaoPC].iNumero);
        printf("\n Valor PC designacao: %s ", vInformacoesPC[iOpcaoPC].sDesignacao);
        printf("\nValor PC: %2.f ", vInformacoesPC[iOpcaoPC].fValorPC );
        printf("\nProcessador PC: %s ", vInformacoesPC[iOpcaoPC].sProcessador);
        printf("\n Quantidade RAM (em GB): %d", vInformacoesPC[iOpcaoPC].iRAM );
        printf("\n Avariado: %d", vInformacoesPC[iOpcaoPC].iAvarias );
        printf("\nLocalizacao do PC: %s", vInformacoesPC[iOpcaoPC].sLocal);

    }
}


void apresentarRequisicoes(tRequisicao *vRequisicaoPC, int iQuantRequisicao)
{

    int i, iOpcaoPC;
    printf("APRESENTAR INFORMACOES");



    printf("A mostrar todas as requisicoes");
    for(i=0; i<(iQuantRequisicao); i++)
    {
        printf("\n N. Identificacao PC: %d",vRequisicaoPC[i].iIdentPC);
        printf("\n N. codigo req PC: %s",vRequisicaoPC[i].sCodigo);
        printf("\n nome do utente: %s",vRequisicaoPC[i].sNomeUtente);
        printf("\n data da requisicao");
        printf("\n dia da requisicao %d",vRequisicaoPC[i].tDataReq.iDia);
        printf("\nmes da requisicao %d", vRequisicaoPC[i].tDataReq.iMes);
        printf("\nano da requisicao %d", vRequisicaoPC[i].tDataReq.iAno);
        printf("\n prazo");
        printf("\n dia do prazo %d",vRequisicaoPC[i].tPrazReq.iDia);
        printf("\nmes do prazo %d",vRequisicaoPC[i].tPrazReq.iMes);
        printf("\nano do prazo %d", vRequisicaoPC[i].tPrazReq.iAno);
        printf("\n estado da req %c",vRequisicaoPC[i].cEstadoReq);
        if(vRequisicaoPC[i].cEstadoReq == 'c')
        {
            printf("\n data de devolucao");
            printf("\n dia da devolucao %d",vRequisicaoPC[i].tDataDevolv.iDia);
            printf("\nmes da devolucao %d", vRequisicaoPC[i].tDataDevolv.iMes);
            printf("\n ano da devolucao %d", vRequisicaoPC[i].tDataDevolv.iAno);
            printf("\n local da devolucao %d", vRequisicaoPC[i].iCampus);
            printf("\n multa valor %f", vRequisicaoPC[i].fMulta);



        }



    }


}

char menuTerminar()
{
    char cEscolhaSN;
    char sMsg[60] = "                                               ";

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                       Gestao de computadores                         | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                            Obrigado!                                 | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | Pretende mesmo terminar?                                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (S)im                                                                | |\n");
        printf("| | (N)ao                                                                | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  Mensagem: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        printf("| |                                                                      | |\n");
        printf("| | Opcao: (S)(N) Selecione: ");
        scanf(" %c", &cEscolhaSN);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaBufferStdin();
        limpaEcra();
        cEscolhaSN = toupper(cEscolhaSN);

        if(cEscolhaSN != 'S' && cEscolhaSN != 'N')
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");

        }
        else
        {
            strcpy(sMsg,"Obrigado!");
        }

    }
    while(cEscolhaSN != 'S' && cEscolhaSN != 'N');
    return cEscolhaSN;

}


char menuFicheiro(void)
{
    char cSubEscolha;
    char sMsg[60] = "                                               ";

    do
    {

        printf("____________________________________________________________________________ \n");
        printf("| ________________________________________________________________________ |\n");
        printf("| |                                                                      | |\n");
        printf("| |                              FICHEIROS                               | |\n");
        printf("| |    ^_^                                                               | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| | SELECIONE A OPCAO:                                                   | |\n");
        printf("| |                                                                      | |\n");
        printf("| | (R)EGISTAR DEVOLUCAO (log)                                           | |\n");
        printf("| | (L)ER (log)                                                          | |\n");
        printf("| | (A)RMAZENAR  (bin)                                                   | |\n");
        printf("| | (M)OSTRAR (bin)                                                      | |\n");
        printf("| | (V)OLTAR                                                             | |\n");
        printf("| |                                                                      | |\n");
        printf("| |                                                                      | |\n");
        printf("| |  MENSAGEM: %.47s           | |\n", sMsg);
        printf("| |                                                                      | |\n");
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");


        printf("| |                                                                      | |\n");
        printf("| | Opcao: (I)(R)(U)(E)(A)(V) Selecione: ");
        scanf(" %c", &cSubEscolha);
        printf("| |______________________________________________________________________| |\n");
        printf("|__________________________________________________________________________| \n");

        limpaEcra();
        limpaBufferStdin();
        cSubEscolha = toupper(cSubEscolha);
        if(cSubEscolha != 'A' && cSubEscolha != 'R' && cSubEscolha != 'L' && cSubEscolha != 'M'  && cSubEscolha != 'V' )
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");
        }
        else
        {
            strcpy(sMsg,"                                               ");
        }

    }
    while(cSubEscolha != 'A' && cSubEscolha != 'R' && cSubEscolha != 'L' && cSubEscolha != 'M'  && cSubEscolha != 'V');

    return cSubEscolha;
}


char menuConfirmar(void)
{
    char cEscolhaSN;
    char sMsg[60] = "                                               ";

    do
    {
        printf("<>                                            <>\n");
        printf("<>  (S)im (N)ao                               <>\n");
        printf("<>   Opcao: ");
        scanf("%c", &cEscolhaSN);
        printf("<>                                            <>\n");
        printf("<><><><><><><><><><><><><><><><><><><><><><><><>\n");


        limpaBufferStdin();
        cEscolhaSN = toupper(cEscolhaSN);

        if(cEscolhaSN != 'S' && cEscolhaSN != 'N')
        {
            strcpy(sMsg,"Por favor, selecione uma das opcoes existentes!");

        }
        else
        {
            strcpy(sMsg,"Obrigado!");
        }

    }
    while(cEscolhaSN != 'S' && cEscolhaSN != 'N');
    return cEscolhaSN;

}

void limpaEcra()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void limpaBufferStdin(void)
{
    char lixo;
    do
    {
        lixo=getchar();
    }
    while (lixo!='\n' && lixo!=EOF);
}
int lerInteiro(int min, int max) /* Le e devolve valor no intervalo desejado (min -> max) */
{
    int numero;
    do  /* Repete leitura enquanto valor introduzido não estiver no intervalo desejado (min -> max) */
    {
        scanf("%d", &numero);
        limpaBufferStdin(); /* limpa dados do buffer stdin */
    }
    while (numero<min || numero>max);
    return numero;
}

float lerFloat(float min, float max)
{
    float numero;
    int controlo;
    do  // Repete leitura enquanto valor introduzido não for numérico e não estiver no intervalo desejado (min -> max)
    {
        controlo = scanf("%f", &numero); // scanf devolve quantidade de valores válidos obtidos
        limpaBufferStdin(); // limpa dados do buffer stdin
    }
    while (numero<min || numero>max || controlo==0);
    return numero;
}

void lerString(char vetor[], int max)
{
    int tamanhoString;
    do  // Repete leitura caso sejam introduzidas strings apenas com o \n (tamanhoString == 1)
    {
        fgets(vetor, max, stdin);
        tamanhoString = strlen(vetor);
    }
    while (tamanhoString == 1);
    if (vetor[tamanhoString-1] != '\n') // não foram armazenados no vetor todos os caracteres
    {
        limpaBufferStdin(); // elimina caracteres que ficaram no buffer stdin
    }
    else
    {
        vetor[tamanhoString-1] ='\0';/* substitui por \0 o caracter \n da string armazenada */
    }
}


int leFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC])
{
    int iQuantPcExiste=0;
    FILE *ficheiroB;

    ficheiroB = fopen("InfoPortateis.dat", "rb");
    if(ficheiroB == NULL)
    {
        printf("\n \n =========================================== \n\n");
        printf("\t    Erro ao abrir o ficheiro");
        printf("\n \n =========================================== \n");
    }
    else
    {
        fread(&iQuantPcExiste, sizeof(int),1, ficheiroB);
        fread(vInformacoesPC, sizeof(tInfPortatil), iQuantPcExiste, ficheiroB);
        fclose(ficheiroB);
    }

    return iQuantPcExiste;
}

void escreveFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC], int iQuantPcExiste)
{
    FILE *ficheiroB;

    ficheiroB = fopen("InfoPortateis.dat", "wb");
    if(ficheiroB == NULL)
    {
        printf("Erro ao abrir o ficheiro");
    }
    else
    {
        fwrite(&iQuantPcExiste, sizeof(int),1, ficheiroB);
        fwrite(vInformacoesPC, sizeof(tInfPortatil), iQuantPcExiste, ficheiroB);
        fclose(ficheiroB);
    }
}

void resetFicheiroBinario(tInfPortatil vInformacoesPC[MAX_PC], int *iQuantPcExiste)
{
    FILE *ficheiroB;
    int i;

    ficheiroB = fopen("InfoPortateis.dat", "wb");
    if(ficheiroB == NULL)
    {
        printf("Erro ao abrir o ficheiro");
    }
    else
    {
        fclose(ficheiroB);
        *iQuantPcExiste = 0;
    }
}


int procuraPC(tInfPortatil vInformacoesPC[MAX_PC],int iQuantPcExiste,int iNumPC)
{
    int i, localizacao = -1;
    for(i=0; i<iQuantPcExiste; i++)
    {
        if(iNumPC == vInformacoesPC[i].iNumero)
        {
            localizacao = i;
            i =iQuantPcExiste ;
        }
    }
    return localizacao;
}

int procuraRequisicao(tRequisicao *vRequisicaoPC, char codigoRequisicao[], int iQuantRequesicao)
{
    int i, localizacao = -1;
    for(i=0; i<iQuantRequesicao; i++)
    {
        if(strcmp(codigoRequisicao, vRequisicaoPC[i].sCodigo) == 0)
        {
            localizacao = i;
            i = iQuantRequesicao;
        }
    }
    return localizacao;
}


int subData(tData dataInicio,tData dataDevolucao)
{
    int  iSomaDia = 0, iMaxDias = 0;
    tData data;


    data.iDia = dataInicio.iDia;
    data.iMes = dataInicio.iMes;
    data.iAno = dataInicio.iAno;
    dataDevolucao.iDia;
    dataDevolucao.iMes;
    dataDevolucao.iAno;


    if ((data.iMes == dataDevolucao.iMes) && (data.iAno == dataDevolucao.iAno)) // se sao dos mesmo mes so subtrai
    {
        iSomaDia +=  dataDevolucao.iDia - data.iDia;

    }
    else
    {
        iMaxDias = maxDiasCalc(data.iMes,  data.iAno);
        iSomaDia = iSomaDia + iMaxDias - data.iDia + dataDevolucao.iDia;

        do
        {
            iMaxDias = maxDiasCalc(data.iMes,  data.iAno);
            data.iMes++;

            if((data.iMes > 12 )&& (data.iAno != dataDevolucao.iAno))
            {
                data.iMes=1;
                data.iAno ++;
                iSomaDia = iSomaDia + 31;

            }
            if((data.iMes == dataDevolucao.iMes) && (data.iAno == dataDevolucao.iAno))
            {
            }
            else
            {


                if(((data.iMes != dataDevolucao.iMes)  || (data.iAno != dataDevolucao.iAno))&& (data.iMes != 12))
                {
                    iMaxDias = maxDiasCalc(data.iMes,  data.iAno);
                    iSomaDia = iSomaDia + iMaxDias;
                }

            }


        }
        while((data.iMes != dataDevolucao.iMes) || (data.iAno != dataDevolucao.iAno));
    }
    return iSomaDia;
}


tData calculoPrazo(tData dataInicio, int iDias)
{
    int iMaxDias;
    tData data;
    data.iDia = dataInicio.iDia +  iDias;
    data.iMes = dataInicio.iMes;
    data.iAno = dataInicio.iAno;


    do
    {

        iMaxDias = maxDiasCalc(data.iMes,  data.iAno);



        if((data.iDia > iMaxDias) && (data.iMes != 12))
        {
            data.iDia = data.iDia - iMaxDias;
            data.iMes++;
        }
        else
        {
            if((data.iDia > iMaxDias) && (data.iMes == 12))
            {
                data.iDia = data.iDia - iMaxDias;
                data.iMes = 1;
                data.iAno ++;
            }
        }
    }
    while(data.iDia > iMaxDias);
    return data;
}

int maxDiasCalc(int iMes, int iAno)
{

    int iMaxDias,iRestoDIV,iRestoDiv4CEM,iRestoDivCEM  ;

    iRestoDIV = iAno%4;
    iRestoDivCEM = iAno%100;
    iRestoDiv4CEM = iAno%400;
    switch(iMes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        iMaxDias=30;
        break;
    case 2:
        if((iRestoDiv4CEM == 0 || iRestoDIV==0) && iRestoDivCEM!=100)
        {
            iMaxDias=29;
        }
        else
        {
            iMaxDias=28;
        }
        break;
    default:
        iMaxDias=31;
    }
    return iMaxDias;
}

tData lerData()
{

    int iRestoDIV,restoDivCEM, restoDiv4CEM, iMaxDias;
    tData data;

    printf("\nIntroduza o ano: ");
    data.iAno=lerInteiro(2014,2025);

    iRestoDIV = data.iAno%4;
    restoDivCEM = data.iAno%100;
    restoDiv4CEM = data.iAno%400;

    printf("\nIntroduza o mes: ");
    data.iMes = lerInteiro(1,12);

    switch(data.iMes)
    {
    case 4:
    case 6:
    case 9:
    case 11:
        iMaxDias=30;
        break;
    case 2:
        if((restoDiv4CEM == 0 || iRestoDIV==0) && restoDivCEM!=100)
        {
            iMaxDias=29;
        }
        else
        {
            iMaxDias=28;
        }
        break;
    default:
        iMaxDias=31;
    }
    printf("\nIntroduza o dia: ");
    data.iDia = lerInteiro(1,iMaxDias);

    return data;
}

