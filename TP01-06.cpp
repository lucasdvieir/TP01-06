#include <iostream>

using namespace std;

struct Lista {
    int senha;
    Lista* next;
};

struct Guiche {
    int id;
    Lista* senhasAtendidas;
};

Lista* senhasGeradas = NULL;
Guiche guiches[10];
int proximaSenha = 1;

void gerarSenha()
{
    Lista* novoNo = new Lista;
    novoNo->senha = proximaSenha++;
    novoNo->next = NULL;

    if (senhasGeradas == NULL) {
        senhasGeradas = novoNo;
    } else {
        Lista* atual = senhasGeradas;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novoNo;
    }
}

void abrirGuiche(int id)
{
    Guiche novoGuiche;
    novoGuiche.id = id;
    novoGuiche.senhasAtendidas = NULL;

    guiches[id] = novoGuiche;
}

void realizarAtendimento()
{
    if (senhasGeradas != NULL) {
        int idGuiche;
        cout << "Digite o ID do guichê que está realizando o atendimento: ";
        cin >> idGuiche;

        if (idGuiche >= 0 && idGuiche < 10) {
            Lista* noRemover = senhasGeradas;
            senhasGeradas = senhasGeradas->next;

            noRemover->next = NULL;

            if (guiches[idGuiche].senhasAtendidas == NULL) {
                guiches[idGuiche].senhasAtendidas = noRemover;
            } else {
                Lista* atual = guiches[idGuiche].senhasAtendidas;
                while (atual->next != NULL) {
                    atual = atual->next;
                }
                atual->next = noRemover;
            }

            cout << "Senha atendida: " << noRemover->senha << endl;
        } else {
            cout << "Guichê não encontrado." << endl;
        }
    } else {
        cout << "Não há senhas aguardando atendimento." << endl;
    }
}

void listarSenhasAtendidas(int idGuiche)
{
    if (guiches[idGuiche].senhasAtendidas != NULL) {
        cout << "Senhas atendidas pelo guichê " << idGuiche << ":" << endl;
        Lista* atual = guiches[idGuiche].senhasAtendidas;
        while (atual != NULL) {
            cout << atual->senha << endl;
            atual = atual->next;
        }
    } else {
        cout << "Nenhuma senha foi atendida pelo guichê " << idGuiche << "." << endl;
    }
}

void liberarMemoria(Lista* no)
{
    if (no == NULL) {
        return;
    }

    liberarMemoria(no->next);
    delete no;
}

void liberarListas()
{
    liberarMemoria(senhasGeradas);
    for (int i = 0; i < 10; i++) {
        liberarMemoria(guiches[i].senhasAtendidas);
    }
}

int main()
{
    int opcao = -1;

    while (senhasGeradas != NULL || opcao != 0)
    {
        cout << "Quantidade de senhas aguardando atendimento: ";

        int count = 0;
        Lista* atual = senhasGeradas;
        while (atual != NULL) {
            atual = atual->next;
            count++;
        }
        cout << count << endl;

        cout << "Número de guichês abertos para atendimento: ";
        int guichesAbertos = 0;
        for (int i = 0; i < 10; i++) {
            if (guiches[i].senhasAtendidas != NULL) {
                guichesAbertos++;
            }
        }
        cout << guichesAbertos << endl;

        cout << "Selecione uma opção:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Gerar senha" << endl;
        cout << "2. Abrir guichê" << endl;
        cout << "3. Realizar atendimento" << endl;
        cout << "4. Listar senhas atendidas" << endl;
        cin >> opcao;

        switch (opcao)
        {
            case 0:
                if (senhasGeradas != NULL)
                {
                    cout << "Ainda há senhas aguardando atendimento." << endl;
                    cout << "Quantidade de senhas atendidas: ";

                    count = 0;
                    for (int i = 0; i < 10; i++) {
                        count += (guiches[i].senhasAtendidas != NULL) ? 1 : 0;
                    }
                    cout << count << endl;
                }
                else
                {
                    cout << "Encerrando o programa." << endl;
                    cout << "Quantidade de senhas atendidas: ";

                    count = 0;
                    for (int i = 0; i < 10; i++) {
                        Lista* atual = guiches[i].senhasAtendidas;
                        while (atual != NULL) {
                            atual = atual->next;
                            count++;
                        }
                    }
                    cout << count << endl;
                }
                break;
            case 1:
                gerarSenha();
                break;
            case 2:
                int id;
                cout << "Digite o ID do guichê a ser aberto: ";
                cin >> id;
                abrirGuiche(id);
                break;
            case 3:
                realizarAtendimento();
                break;
            case 4:
                int idGuiche;
                cout << "Digite o ID do guichê para listar as senhas atendidas: ";
                cin >> idGuiche;
                listarSenhasAtendidas(idGuiche);
                break;
            default:
                cout << "Opção inválida. Por favor, selecione novamente." << endl;
                break;
        }

        cout << endl;
    }

    liberarListas();

    return 0;
}