//Catarina Meirelles 10239324
//Heloísa Martelle 10738274
//Lívia Calado Dias 10737709


#include <stdio.h>
#include <string.h>

void tratarInput(int tamanhoMSG, char msgMatriz[][5]){

    printf("\nDigite a mensagem codificada: ");
    char msgINPUT[tamanhoMSG];
    fgets(msgINPUT,tamanhoMSG,stdin);
    msgINPUT[strcspn(msgINPUT, "\n")] = '\0';
    
    
    char letra[5]={0};
    int currentLetraIndex=0;
    int indexPalavrasMSGfinal=0;

    for(int i=0; i< strlen(msgINPUT);i++){
        
        
        if(msgINPUT[i]==' '){
            if (currentLetraIndex>0){
                letra[currentLetraIndex] = '\0';
                
                strncpy(msgMatriz[indexPalavrasMSGfinal],letra,5);
                indexPalavrasMSGfinal++;
                memset(letra, 0, sizeof(letra));
                currentLetraIndex=0;
            }
            
            if (msgINPUT[i+1] == ' '){
                strncpy(msgMatriz[indexPalavrasMSGfinal], "_", 5);
                indexPalavrasMSGfinal++;
                i++;
            }
            
            
        }else{
            if (currentLetraIndex <= 4){
                letra[currentLetraIndex] = msgINPUT[i];
                currentLetraIndex++;
            }
        }
        
    }

    if (currentLetraIndex > 0) {
        letra[currentLetraIndex] = '\0';
        strncpy(msgMatriz[indexPalavrasMSGfinal], letra, 5);
        indexPalavrasMSGfinal++;
    }
    
}

char* resolverCorrompimento(char *msgCompleta, char alfabetoMorse[][5], char alfabeto[], int tamanhoAlfabeto){ 
    
    static char candidatos[28];
    int count = 0;

    for(int i = 0; i < tamanhoAlfabeto; i++){
           if (strncmp(msgCompleta, alfabetoMorse[i], strlen(msgCompleta)-1) == 0){
            candidatos[count++] = alfabeto[i];
        }
    }
    candidatos[count] = '\0';
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
        
        if (strcmp(msgTratada[i], "_") == 0){
            msgDecodificada[posicaoMsgFinal++] = ' ';
            continue;
        }

        int len = strlen(msgTratada[i]);
        
        if (len > 0 && msgTratada[i][len - 1] == '*'){
            char *candidatos = resolverCorrompimento(msgTratada[i], alfabetoMorse, alfabeto, 26);
            msgDecodificada[posicaoMsgFinal++] = '[';
            for (int k = 0; candidatos[k] != '\0'; k++){
                msgDecodificada[posicaoMsgFinal++] = candidatos[k];
            }
            msgDecodificada[posicaoMsgFinal++] = ']';
            continue;
        }

        
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
    char msgTratada[tamanhoMSG/5][5];
    char msgDecodificada[tamanhoMSG/5];
    char deNovo;

    do{
        memset(msgTratada, 0, sizeof(msgTratada));
        memset(msgDecodificada, 0, sizeof(msgDecodificada));
        
        printf("\n*⣾⠛⠛⠲⣤           ⣠⡴⠞⠛⢻⡆*\n*⣿      ⠙⢦⡀    ⣠⠞⠁   ⢸⡇ ⁺⊹*\n*⢿⡄        ⠹╄⡼⠁      ⣼⠇*\n*⠘⢷⣄╀.    ⠙⠁     ⣀╀╴⠟*\n  *⣼⠛⠉⠉          ⠈⠉⠙⢻⡄*\n *⠘⣷        ⡞⣦     ⣰⡟*\n*⊹ ⠈⠻⣦╤⡶⠋⠈   ⠳╦╤⡾⠋   ₊*");
        printf("\n✩₊˚.⋆☾⋆⁺₊✧ Bem vindo ao Decodificador Morse 3000 ✩₊˚.⋆☾⋆⁺₊✧ \n\n-resolvendo códigos desde a era da guerra");
        printf("\n--------🗝️⋆.⚚.⋆꩜.⚚ᐟ⋆.🗝️--------\n");

        tratarInput(tamanhoMSG, msgTratada);

        decodificar(tamanhoMSG, msgTratada, msgDecodificada);
        
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
