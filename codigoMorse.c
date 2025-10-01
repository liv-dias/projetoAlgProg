//Catarina Meirelles 10239324
//Heloísa Martelle 10738274
//Lívia Calado Dias 10737709


#include <stdio.h>
#include <string.h>

void tratarInput(int tamanhoMSG, char msgMatriz[][5]){

    printf("\nDigite a mensagem codificada: ");
    char msgINPUT[tamanhoMSG]; 
    fgets(msgINPUT,tamanhoMSG,stdin); //lê a mensagem do usuário
    msgINPUT[strcspn(msgINPUT, "\n")] = '\0'; //remove o \n do final
    
    
    char letra[5]={0}; //cria um buffer temporário para armazenar cada código morse
    int currentLetraIndex=0; //posição dentro de 'letra'
    int indexPalavrasMSGfinal=0; //posição dentro da matriz final

    for(int i=0; i< strlen(msgINPUT);i++){
        
        
        if(msgINPUT[i]==' '){ //espaço separa letras ou palavras
            if (currentLetraIndex>0){ //terminou de ler uma letra
                letra[currentLetraIndex] = '\0';
                
                strncpy(msgMatriz[indexPalavrasMSGfinal],letra,5); //salva no vetor
                indexPalavrasMSGfinal++;
                memset(letra, 0, sizeof(letra)); //zera 'letra'
                currentLetraIndex=0;
            }
            
            if (msgINPUT[i+1] == ' '){ //dois espaços = separação de palavras
                strncpy(msgMatriz[indexPalavrasMSGfinal], "_", 5); //usa "_" como marcador de espaço
                indexPalavrasMSGfinal++;
                i++; //pula o segundo espaço
            }
            
            
        }else{
            if (currentLetraIndex <= 4){ //adiciona sinal (ponto ou traço) em 'letra'
                letra[currentLetraIndex] = msgINPUT[i];
                currentLetraIndex++;
            }
        }
        
    }

    if (currentLetraIndex > 0) { //salva última letra que ficou em buffer
        letra[currentLetraIndex] = '\0';
        strncpy(msgMatriz[indexPalavrasMSGfinal], letra, 5);
        indexPalavrasMSGfinal++;
    }
    
}

char* resolverCorrompimento(char *msgCompleta, char alfabetoMorse[][5], char alfabeto[], int tamanhoAlfabeto){ 
    
    static char candidatos[28]; //letras possiveis para o codigo corrompido
    int count = 0;

    for(int i = 0; i < tamanhoAlfabeto; i++){
           if (strncmp(msgCompleta, alfabetoMorse[i], strlen(msgCompleta)-1) == 0){ //compara só até o tamanho-1 (ignora último símbolo, que pode estar corrompido)
            candidatos[count++] = alfabeto[i];//adiciona candidato
        }
    }
    candidatos[count] = '\0';
    //ordena os candidatos em ordem alfabetica (bubble sort)
    for (int i=0; i<count-1; i++){
        for (int j=i+1; j<count; j++){
            if (candidatos[i] > candidatos[j]){
                char tmp = candidatos[i];
                candidatos[i] = candidatos[j];
                candidatos[j] = tmp;
            }
        }
    }
    return candidatos;
} 

void decodificar(int tamanhoMSG, char msgTratada[][5], char msgDecodificada[]){
    char alfabetoMorse[][5] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",
                              ".---","-.-",".-..","--","-.","---",".--.","--.-",".-.",
                              "...","-","..-","...-",".--","-..-","-.--","--.."};
    char alfabeto[] = {'A','B','C','D','E','F','G','H','I','J','K','L',
                       'M','N','O','P','Q','R','S','T','U','V','W','X',
                       'Y','Z'};

    int posicaoMsgFinal = 0;

    for (int i = 0; i < (tamanhoMSG/5) && msgTratada[i][0] != '\0'; i++){
        
        if (strcmp(msgTratada[i], "_") == 0){ //"_" representa espaço
            msgDecodificada[posicaoMsgFinal++] = ' ';
            continue;
        }

        int len = strlen(msgTratada[i]);

        //caso de letra corrompida (termina com '*')
        if (len > 0 && msgTratada[i][len - 1] == '*'){
            char *candidatos = resolverCorrompimento(msgTratada[i], alfabetoMorse, alfabeto, 26);
            msgDecodificada[posicaoMsgFinal++] = '[';
            for (int k = 0; candidatos[k] != '\0'; k++){
                msgDecodificada[posicaoMsgFinal++] = candidatos[k];//escreve todos os possiveis candidatos
            }
            msgDecodificada[posicaoMsgFinal++] = ']';
            continue;
        }

        //caso normal= procura no alfabeto Morse
        int encontrado = 0;
        for (int j = 0; j < 26; j++){
            if (strcmp(msgTratada[i], alfabetoMorse[j]) == 0){
                msgDecodificada[posicaoMsgFinal++] = alfabeto[j];
                encontrado = 1;
                break;
            }
        }
        if (!encontrado){
            
            msgDecodificada[posicaoMsgFinal++] = '?';
        }
    }

    
    msgDecodificada[posicaoMsgFinal] = '\0';
}

int main(){
    
    int tamanhoMSG=300;
    char msgTratada[tamanhoMSG/5][5];//armazena codigo morse
    char msgDecodificada[tamanhoMSG/5];//mensagem final
    char deNovo;

    do{
        memset(msgTratada, 0, sizeof(msgTratada));
        memset(msgDecodificada, 0, sizeof(msgDecodificada));
        
        printf("\n*⣾⠛⠛⠲⣤           ⣠⡴⠞⠛⢻⡆*\n*⣿      ⠙⢦⡀    ⣠⠞⠁   ⢸⡇ ⁺⊹*\n*⢿⡄        ⠹╄⡼⠁      ⣼⠇*\n*⠘⢷⣄╀.    ⠙⠁     ⣀╀╴⠟*\n  *⣼⠛⠉⠉          ⠈⠉⠙⢻⡄*\n *⠘⣷        ⡞⣦     ⣰⡟*\n*⊹ ⠈⠻⣦╤⡶⠋⠈   ⠳╦╤⡾⠋   ₊*");
        printf("\n✩₊˚.⋆☾⋆⁺₊✧ Bem vindo ao Decodificador Morse 3000 ✩₊˚.⋆☾⋆⁺₊✧ \n\n-resolvendo códigos desde a era da guerra");
        printf("\n--------🗝️⋆.⚚.⋆꩜.⚚ᐟ⋆.🗝️--------\n");

        tratarInput(tamanhoMSG, msgTratada);//lê mensagem

        decodificar(tamanhoMSG, msgTratada, msgDecodificada);//traduz
        
        printf("\nHmm, os nossos detetives chegaram a conclusão de que a sua mensagem significa: \n");
        printf("\n%s\n", msgDecodificada);
        printf("\n\n                  ╱|、                   \n                (˚ˎ 。7  \n                 |、˜〵          \n                じしˍ,)ノ");
        
        printf("\nDeseja decodificar outra mensagem?(s/n): ");
        scanf("%c", &deNovo);
        getchar();

    }while(deNovo == 's' || deNovo == 'S');
    
    printf("\nPrograma encerrado com sucesso, obrigada por usar o Decodificador Morse 3000!\n\n ∧,,,∧\n( ̳• ·• ̳)\n/   づ♡ \n");

    return 0;
}
