// ECW: Execução de Comandos do Windows
// Autor: Isllan
// Sobre: Aplicativo de executar comandos do windows feito em C++ usando bliotecas padrões

#include <iostream>
#include <Windows.h>
#include <string>
#include "resource.h"

void PersonalizarConsoleECW() {
    // 1. Alterar o título da janela do console
    SetConsoleTitleA("ECW: Execucao de Comandos do Windows");

    // 2. Obter o identificador (HWND) da janela do console atual
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) {
        // --- Aplica o ícone embutido nos recursos do executável ---
        HINSTANCE hInst = GetModuleHandle(NULL);
        HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

        if (hIcon != NULL) {
            // Define o ícone na barra de título (pequeno) e no Alt+Tab (grande)
            SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        }

        // --- Remove os botões de minimizar e maximizar ---
        LONG style = GetWindowLong(hwnd, GWL_STYLE);
        style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
        SetWindowLong(hwnd, GWL_STYLE, style);

        // Atualiza a moldura da janela para forçar a renderização visual imediata das mudanças
        SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }

    // 3. Mudar o fundo para branco e as letras para preto com intensidade (negrito)
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdout != INVALID_HANDLE_VALUE) {
        // Combinação RGB para fundo branco de alta intensidade + texto preto com negrito
        WORD atributoCor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY;

        // Aplica o atributo para as próximas saídas de texto
        SetConsoleTextAttribute(hStdout, atributoCor);

        // Preenche retroativamente todo o buffer da tela com a cor de fundo branca
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hStdout, &csbi)) {
            DWORD written;
            DWORD size = csbi.dwSize.X * csbi.dwSize.Y;

            // Pinta os atributos de cor e preenche o fundo com espaços vazios
            FillConsoleOutputAttribute(hStdout, atributoCor, size, { 0, 0 }, &written);
            FillConsoleOutputCharacterA(hStdout, ' ', size, { 0, 0 }, &written);

            // Reposiciona o cursor no canto superior esquerdo (0,0) para iniciar a escrita limpa
            SetConsoleCursorPosition(hStdout, { 0, 0 });
        }
    }
}


void command(const std::string& comando) {
	if (comando.empty() == true) {
		std::cout << "Erro: Comando vazio.\n";
		return;
	}

	std::cout << system(comando.c_str()) << "\n";
	std::cout << "Executado com sucesso!\n";
}

int main() {
	std::string comando = "";
	PersonalizarConsoleECW();

	std::cout << "Ola, querido usuario\n";
	std::cout << "Para sair, digite: Alt + F4\n";
	std::cout << "\n";
	std::cout << "ECW: Execucao de Comandos do Windows\n";
	std::cout << "Autor: Isllan\n";
	std::cout << "\n";
	std::cout << "Digite os comando abaixo:\n";
	std::cout << "(Para limpar o terminal, digite: /clear --terminal\n";

	while (true) {
		std::cout << "User: > ";
		std::getline(std::cin, comando);

		if (comando == "/clear --terminal") {
			std::cout << "\033[2J\033[H";
			std::cout << "Ola, querido usuario\n";
			std::cout << "Para sair, digite: Alt + F4\n";
			std::cout << "\n";
			std::cout << "ECW: Execucao de Comandos do Windows\n";
			std::cout << "Autor: Isllan\n";
			std::cout << "\n";
			std::cout << "Digite os comando abaixo:\n";
			std::cout << "(Para limpar o terminal, digite: /clear --terminal\n";
		}

		command(comando);
	}
}