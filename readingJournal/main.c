#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Protótipos das funções
int fazerLogin(MYSQL *con, int *usuario_id);
void cadastrarLeitura(MYSQL *con, int usuario_id);
void listarLeituras(MYSQL *con, int usuario_id);
void cadastrarUsuario(MYSQL *con);
void mostrarMenuInicial(void);
void mostrarMenuPrincipal(void);

int fazerLogin(MYSQL *con, int *usuario_id) {
    char nome[50], senha[50];

    printf("======== LOGIN ======== \n");
    printf("Usuário: ");
    scanf(" %[^\n]", nome);
    printf("Senha: ");
    scanf(" %[^\n]", senha);

    char query[200];
    sprintf(query, "SELECT id FROM usuarios WHERE nome = '%s' AND senha = '%s'",
                nome, senha);

    if(mysql_query(con, query)) {
        printf("Erro: %s\n", mysql_error(con));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(con);
    if(mysql_num_rows(result) == 0) {
        printf("Usuário ou senha incorretos! Tente novamente.\n");
        mysql_free_result(result);
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    *usuario_id = atoi(row[0]);
    mysql_free_result(result);

    printf("Login bem-sucedido!\n");
    return 1;
}

void cadastrarLeitura(MYSQL *con, int usuario_id) {
    char titulo[200], autor[100], data[11];
    int nota;

    printf("Titulo do livro: ");
    scanf(" %[^\n]", titulo);
    printf("Autor: ");
    scanf(" %[^\n]", autor);
    printf("Data (AAAA/MM/DD): ");
    scanf("%s", data);
    printf("Nota (1-10): ");
    scanf("%d", &nota);

    char query[500];
    sprintf(query, "INSERT INTO leituras (titulo, autor, data_leitura, nota, usuario_id) "
        "VALUES ('%s', '%s', '%s', %d, %d)",
        titulo, autor, data, nota, usuario_id);

    if(mysql_query(con, query)) {
        printf("Erro: %s\n", mysql_error(con));
    } else {
        printf("Livro cadastrado com sucesso!\n");
    }
}

void listarLeituras(MYSQL *con, int usuario_id) {
    char query[200];
    sprintf(query, "SELECT * FROM leituras WHERE usuario_id = %d", usuario_id);

    if(mysql_query(con, query)) {
        printf("Erro: %s\n", mysql_error(con));
        return;
    }

    MYSQL_RES *result = mysql_store_result(con);
    MYSQL_ROW row;

    printf("\n======== LEITURAS ========\n\n");
    while((row = mysql_fetch_row(result))) {
        printf("--------------------");
        printf("\nLivro: %s\n", row[1]);
        printf("Autor: %s\n", row[2]);
        printf("Data: %s\n", row[3]);
        printf("Nota: %s/10\n", row[4]);
        printf("--------------------");
    }
    mysql_free_result(result);
}

void cadastrarUsuario(MYSQL *con) {
    char nome[50], senha[50];

    printf("Novo usuário: ");
    scanf(" %[^\n]", nome);
    printf("Senha: ");
    scanf(" %[^\n]", senha);

    char query[200];
    sprintf(query, "INSERT INTO usuarios (nome, senha) VALUES ('%s', '%s')", nome, senha);

    if(mysql_query(con, query)) {
        printf("Erro: %s\n", mysql_error(con));
    } else {
        printf("Usuário cadastrado com sucesso! Faça login.\n");
    }
}

void menuInicial() {
    printf("\n\n====== DIARIO DE LEITURA ======\n\n");
    printf("1- Fazer login\n2- Cadastrar usuario\n0- Sair\n");
    printf("==============================\n\n");
    printf("Digite sua escolha: ");
}

void menuPrincipal() {
    printf("\n\n============ MENU ============\n");
    printf("1- Cadastrar leitura\n2- Listar leituras\n3- Sair da conta\n0- Sair\n");
    printf("==============================\n");
    printf("Digite sua escolha: ");
}

int main() {
    MYSQL *con = mysql_init(NULL);
    if (!mysql_real_connect(con, "localhost", "root", "Kaw!789657", // adicione o usuario e senha do seu banco de dados
                           "diario_leitura", 0, NULL, 0)) {
        printf("Erro: %s\n", mysql_error(con));
        return 1;
    }

    int opcao1 = 0, opcao2 = 0;
    int usuario_id = 0, logged_in = 0;

    do {
        if(!logged_in) {
            menuInicial();
            scanf("%d", &opcao1);

            switch(opcao1) {
                case 1: system("cls"); logged_in = fazerLogin(con, &usuario_id); break;
                case 2: system("cls"); cadastrarUsuario(con); break;
                case 0: system("cls"); printf("Encerrando...\n"); mysql_close(con); break;
                default: system("cls"); printf("Opcao invalida!\n"); break;
            }
        } else {
            menuPrincipal();
            scanf("%d", &opcao2);

            switch(opcao2) {
                case 1: system("cls"); cadastrarLeitura(con, usuario_id); break;
                case 2: system("cls"); listarLeituras(con, usuario_id); break;
                case 3:
                    system("cls");
                    printf("Logout realizado com sucesso!\n");
                    logged_in = 0;
                    usuario_id = 0;
                    break;
                case 0: system("cls"); printf("Encerrando..."); mysql_close(con); break;
                default: system("cls"); printf("Opcao invalida!\n"); break;
            }
        }
    } while (1);

    return 0;
}
