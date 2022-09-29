
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/*################ Funções ################*/

int game_function (char palavra_misteriosa []);
void clear (void);
char get_caractere (int *teste);
int palavra_sorteada (int codigo, char vetor []);
int pontos_para_vitoria (char palavra [], int tamanho_palavra);
int verifica_caractere (char *caracteres_usados, char caractere, int l);
void frame_superior (int tentativa);
void frame_inferior (char vetor [], int fim_de_jogo);


/*######################################### Int Main ###############################################*/
int main (void) {
    char palavra_misteriosa [64];
    char game_mode;

    int restart, codigo, teste = 0;

    do {
        clear ();
        printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
        printf("\n   #                            Programacao 1                           #");
        printf("\n   #                                                                    #");
        printf("\n   #                                Menu                                #");
        printf("\n   #                                                                    #");
        printf("\n   #  1 - Modo solo                                                     #");
        printf("\n   #  2 - CO-OP                                                         #");
        printf("\n   #  [ESC] - Exit Game                                                 #");
        printf("\n   #                                                                    #");
        printf("\n   #  Alunos:                                                           #");
        printf("\n   #  Isac Freire, Gustavo Breda                                        #");
        printf("\n   ######################################################################\n");

        printf("\n   # Escolha a opcao: ");

        game_mode = get_caractere (&teste);
        if (teste == 1)
            getchar ();

        switch (game_mode) {
            case '1':
                FILE *arquivo;
                arquivo= fopen("teste.txt", "w");
                fprintf(arquivo, "jogo10000");
                fclose(arquivo);
                return 1;
            /*
                srand (time (NULL));
                codigo = (rand () % 20);
                palavra_sorteada (codigo, palavra_misteriosa);

                restart = game_function (palvra_misteriosa);*/
                break;

            case '2':
                clear ();
                printf ("Escolha uma palavra para ser descoberta: ");
                fgets (palavra_misteriosa, 64, stdin);
            
            /*if ((strlen ("palavra_misteriosa")) > 0) && (palavra_misteriosa [strlen (palavra_misteriosa) - 1] == '\n'))
                    palavra_misteriosa [strlen (palavra_misteriosa) - 1] = '\0';

                restart = game_function (palavra_misteriosa);*/
                break;

            case 3:
            case 27:
                printf ("\n");
                return 0;
        }

    }while (((game_mode != '1') && (game_mode != '2')) || (restart == 1));

}

void clear (void) {

    #if (defined (_WIN32) || defined (_WIN64))
        system ("cls");

    #elif (defined (__linux__) || defined (__unix__))
        system ("clear");

    #endif
}

char get_caractere (int *teste) {

    #if (defined (_WIN32) || defined (_WIN64))
        return getch ();

    #elif (defined (__linux__) || defined (__unix__))
        *teste = 1;
        return getchar ();

    #endif
}

int game_function (char palavra_misteriosa [64]) {
    char *caracteres_usados,
         *vetor_print,
         caractere;

    int numero_caracteres = 0,
        tamanho_palavra = 0,
        ponto_atuais = 0,
        tentativa = 0,
        pontos_totais,
        verificacao,
        teste = 0,
        correct,
        j = 0,
        k = 0;

    vetor_print = (char *) malloc (68 * sizeof (char));
    caracteres_usados = (char *) malloc (64 * sizeof (char));

    for (int i = 0; i < 64; i++) {
        if (palavra_misteriosa [i] != '\0')
            tamanho_palavra++;
        else
            break;
    }

    for (int i = 0; i < tamanho_palavra; i++) {
        if (palavra_misteriosa [i] == ' ')
            *(vetor_print + i) = ' ';
        else
            *(vetor_print + i) = '_';
        j++;
        }

    for (int i = 0; i <= (66 - tamanho_palavra); i++) {
        if (i == (66 - tamanho_palavra)) {
            *(vetor_print + j) = '#';
            j++;
        }
        else {
            *(vetor_print + j) = ' ';
            j++;
        }
    }
    *(vetor_print + j) = '\0';

    pontos_totais = pontos_para_vitoria (palavra_misteriosa, tamanho_palavra);

    k = tamanho_palavra;
    for (int i = 0; i <= (47 - tamanho_palavra); i++) {
        if (i == (47 - tamanho_palavra)) {
            palavra_misteriosa [k] = '#';
            k++;
        }
        else {
            palavra_misteriosa [k] = ' ';
            k++;
        }
    }
    palavra_misteriosa [k] = '\0';

    while (tentativa < 7) {

        if (tentativa == 6) {
            frame_superior (tentativa);
            frame_inferior (palavra_misteriosa, 1);
            free (caracteres_usados);
            free (vetor_print);
            break;
        }

        frame_superior (tentativa);
        frame_inferior (vetor_print, 0);

        printf("\n   # Escolha um caractere: ");
        caractere = get_caractere (&teste);
        if (teste == 1)
            getchar ();

        while (1) {

            correct = 0;

            while (1) {

                if (caractere == 27)
                    return 1;

                if (caractere == 3) {
                    printf ("\n");
                    return 0;
                }

                verificacao = verifica_caractere (caracteres_usados, caractere, numero_caracteres);

                if (verificacao == 0) {
                    numero_caracteres += 1;
                    break;
                }

                if ((caractere == 32) || ((caractere >= 65) && (caractere <= 90)))
                    printf("\r   # Escolha outro caractere ('%c' nao disponivel):  ");
                else
                    printf("\r   # Escolha outro caractere ('%c' usando antes): ");

                caractere = get_caractere (&teste);
                if (teste == 1)
                    getchar ();
            }

            for (int i = 0; i <= tamanho_palavra; i++) {
                if (caractere == palavra_misteriosa [i]) {
                    vetor_print [i] = caractere;
                    ponto_atuais += 1;
                    correct = 1;
                }

                if ((caractere - 32) == palavra_misteriosa [i]) {
                    vetor_print [i] = (caractere - 32);
                    ponto_atuais += 1;
                    correct = 1;
                }
            }

            if (correct == 0)
                break;

            if (ponto_atuais == pontos_totais) {
                break;
            }

            frame_superior (tentativa);
            frame_inferior (vetor_print, 0);

            printf("\n   # Escolha um caractere: ");
            caractere = get_caractere (&teste);
            if (teste == 1)
                getchar ();
        }

        if (ponto_atuais == pontos_totais) {
            frame_superior (7);
            frame_inferior (palavra_misteriosa, 1);
            break;
        }

    tentativa++;
    }

    free (caracteres_usados);
    free (vetor_print);

    return 1;
}

int palavra_sorteada (int codigo, char vetor []) {

    char dicionario [20] [64] = {
                                 {"Landelino"},
                                 {"Gustavo"},
                                 {"Isac"},
                                 {"Computador"},
                                 {"Televisao"},
                                 {"Teclado"},
                                 {"Mouse"},
                                 {"Fluminense"},
                                 {"Botafogo"},
                                 {"Flamengo"},
                                 {"Vasco"},
                                 {"Portugal"},
                                 {"Brasil"},
                                 {"Burguer King"},
                                 {"McDonalds"},
                                 {"Juan Roman Riquelme"},
                                 {"Cristiano Ronaldo"},
                                 {"Neymar"},
                                 {"Mbappe"},
                                 {"Messi"}
                                };

    strcpy (vetor, dicionario [codigo]);

    return 0;
}

int pontos_para_vitoria (char palavra [], int tamanho_palavra) {
    int pontos_totais = 0;

    for (int i = 0; i < tamanho_palavra; i++)
        if (palavra [i] == ' ');
        else
            pontos_totais += 1;

    return pontos_totais;
}

int verifica_caractere (char *caracteres_usados, char caractere, int numero_caracteres) {

    if ((caractere == 32) || ((caractere >= 65) && (caractere <= 90)))
        return 1;

    for (int i = 0; i < numero_caracteres; i++) {
        if (caractere == caracteres_usados [i])
            return 1;
    }

    caracteres_usados [numero_caracteres] = caractere;
    return 0;
}

void frame_superior (int tentativa) {

    switch (tentativa) {

        case 0:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
            printf("\n   #                            Programacao 1                           #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            break;

        case 1:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
            printf("\n   #                            Programacao 1                           #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |          O                                                      #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            break;

        case 2:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
            printf("\n   #                            Programacao 1                           #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |          O                                                      #");
            printf("\n   #  |          |                                                      #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            break;

        case 3:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
            printf("\n   #                            Programacao 1                           #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |          O                                                      #");
            printf("\n   #  |          |\\                                                     #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            break;

        case 4:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                 UFRJ                 <<<<<<<<<<<<<<<<<");
            printf("\n   #                           Programacao 1                            #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |          O                                                      #");
            printf("\n   #  |         /|\\                                                     #");
            printf("\n   #  |                                                                 #");
            printf("\n   #  |                                                                 #");
            break;

        case 5:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                 UFRJ                 <<<<<<<<<<<<<<<<<");
            printf("\n   #                           Programacao 1                            #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |         Voltar ao Menu [ESC]                         #");
            printf("\n   #  |          O                                                      #");
            printf("\n   #  |         /|\\                                                     #");
            printf("\n   #  |           \\                                                     #");
            printf("\n   #  |                                                                 #");
            break;

        case 6:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                  UFRJ                <<<<<<<<<<<<<<<<<");
            printf("\n   #                            Programacao 1                           #");
            printf("\n   #                                                                    #");
            printf("\n   #   __________                                                       #");
            printf("\n   #  |          |                                                      #");
            printf("\n   #  |          O                You Lose                              #");
            printf("\n   #  |         /|\\        (Homem-Palito morreu)                        #");
            printf("\n   #  |         / \\                                                     #");
            printf("\n   #                  (APERTE ENTER PARA CONTINUAR)                     #");
            break;

        case 7:
            clear ();
            printf("\n   >>>>>>>>>>>>>>>                 UFRJ                 <<<<<<<<<<<<<<<<<");
            printf("\n   #                           Programacao 1                            #");
            printf("\n   #                                                                    #");
            printf("\n   #                                                                    #");
            printf("\n   #                                                                    #");
            printf("\n   #                             PARABENS                               #");
            printf("\n   #                    VOCE SALVOU O HOMEM-PALITO                      #");
            printf("\n   #                  (APERTE ENTER PARA CONTINUAR)                     #");
            printf("\n   #                                                                    #");
            break;
    }
}

void frame_inferior (char vetor [], int fim_de_jogo) {

    switch (fim_de_jogo) {
        case 0:
            printf("\n   #                                                                    #");
            printf("\n   #  %s", vetor);
            printf("\n   #                                                                    #");
            printf("\n   ######################################################################\n");
            break;

        case 1:
            printf("\n   #                                                                    #");
            printf("\n   # Palavra Misteriosa: %s", vetor);
            printf("\n   #                                                                    #");
            printf("\n   ######################################################################\n");

            printf("\n   ");
            getchar ();
            break;
    }

}
