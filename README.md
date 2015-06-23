# LibGUI

A simple and small library for creating graphical user interface.



![alt tag](https://github.com/jessesilva/LibGUI/raw/master/example.gif)


### Reference...

- Language: Portuguese Brazilian
- Nome: LibGUI
- Descrição: Conjunto de funções auxiliares destinadas a criação de controles personalizados utilizando a WinAPI.
- Data: 7 de março de 2014
- Autor: Constantine / jessesilvabr1994@gmail.com


###Sumário
- 0x00 - GUIInitialize
- 0x01 - CreateSimpleWindow
- 0x02 - GetColor
- 0x03 - RefreshWindow
- 0x04 - CreateButton
- 0x05 - ButtonHover
- 0x06 - CreateEdit
- 0x07 - HoverEdit
- 0x08 - CreateEditBox
- 0x09 - SetControlColor
- 0x10 - CreateStatic


### 0x00 - GUIInitialize
- Função utilizada para inicializar a LibGUI. Onde a mesma cria a classe da janela e a registra.

		Protótipo:
		 int result = GUIInitialize(WNDPROC WindowCallback, HBRUSH WindowColor);

		Retorno:
		 Se tudo ocorrer bem, o retorno será LIBGUI_ERROR_SUCCESS, caso con-
		 trário se ocorrer algum erro o retorno será LIBGUI_ERROR.
		 
		Argumentos:
		 WindowCallback, Trata-se do nome da Callback que irá utilizar para
		 receber e tratar as mensagens da janela.
		 WindowColor, Cor de fundo da janela.


### 0x01 - CreateSimpleWindow
- Função utilizada para criar uma nova janela.

		Protótipo:
		 HWND Result = CreateSimpleWindow(int Style, char *Title, int PositionX, 
						int PositionY, int X, int Y, int ID, HWND WindowParent);

		Retorno:
		 Se tudo ocorrer bem, o retorno será o identificador da janela, caso con-
		 trário se ocorrer algum erro o retorno será NULL.
		 
		Argumentos:
		 Style, Estilo da janela, utilizar as mesmas constantes de estilo da 
		 CreateWindowEx.
		 Title, Título da janela.
		 PositionX, Posição X da janela no ParentWindow.
		 PositionY, Posição Y da janela no ParentWindow.
		 X, Largura da janela, se valor for -1, então usa .
		 Y, Altura da janela.
		 ID, Identificador HMENU da janela.
		 WindowParent, Janela pai.


### 0x02 - GetColor
-  Função responsável por retornar HBRUSH de alguma cor.

		Protótipo:
		 HBRUSH Color = GetColor(int Color);

		Retorno:
		 Retorna um dado do tipo HBRUSH da cor passada no argmento da função.
		 Em caso de erro retorna NULL.

		Argumentos:
		 Color, cor em hexadecimal. Ex: 0x00008000.


### 0x03 - RefreshWindow
- Função responsável por atualizar janela, é o loop message em sí.

		Protótipo:
		 int Result = RefreshWindow(HWND Window);

		Retorno:
		 Retorna valor de Message.wParam.

		Argumentos:
		 Window, Identificador da janela principal.


### 0x04 - CreateButton
-  Função responsável por criar botões de cor sólida. Tratar efeitos do botão na WM_DRAWITEM.

		Protótipo:
		 HWND Result = CreateButton(int X, int Y, int iWidth, int iHeight,
							char *cText, int iButtonID, HWND hwWindowParent);

		Retorno:
		 Retorna identificador do botão.

		Argumentos:
		 X, posição X do botão em sua janela pai.
		 Y, posição Y do botão em sua janela pai.
		 iWidth, largura do botão.
		 iHeight, altura do botão.
		 cText, texto do botão.
		 iButtonID, ID do botão.
		 hwWindowParent, identificador da janela pai.


### 0x05 - HoverButton
- Função responsável adicionar efeito hover de cor sólida nos botões.

		Protótipo:
		 void HoverButton(LPARAM lParam,int iTextColor, int iBackgroundColor,
					int iHoverTextColor,int iHoverBackgroundColor);

		Argumentos:
		 lParam, passar como argumento o valor do lParam da Callback do loop 
		 de mensagens.
		 iTextColor, Cor do texto do botão em modo normal.
		 iTextBackgroundColor, Cor do texto do botão quando o mouse passar sobre
		 o botão.
		 iColorBackground, Cor do fundo do botão em modo normal.
		 iColorBackgroundHover, Cor do fundo do bõtão quando o mouse passar sobre ele.


### 0x06 - CreateEdit
- Função responsável por criar caixas de texto simples. Tratar efeitos do botão na WM_CTLCOLOREDIT.

		Protótipo:
		 HWND Result = CreateEdit(int X, int Y, int iWidth, int iHeight,
							char *cText, int iEditID, int iBorder, HWND hwWindowParent);

		Retorno:
		 Retorna identificador da edit.

		Argumentos:
		 X, posição X da edit em sua janela pai.
		 Y, posição Y da edit em sua janela pai.
		 iWidth, largura.
		 iHeight, altura.
		 cText, texto padrão.
		 iEditID, ID da edit.
		 iBorder, define se usa borda na edit ou não.
		 hwWindowParent, identificador da janela pai.


### 0x07 - HoverEdit
-  Função responsável adicionar efeito hover de cor sólida nas edit's.

		Protótipo:
		 void HoverEdit(WPARAM wParam, HWND hWnd, int iIDControl, int iTextColor,
				int iBackgroundColorText, int iBorderColor, int iHoverTextColor,
				int iHoverBackgroundColorText, int iHoverBorderColor);

		Argumentos:
		 wParam, passar como argumento o valor do wParam da Callback do loop 
		 de mensagens.
		 hWnd, identificar da edit.
		 iIDControl, ID de controle da edit.
		 iTextColor, cor do text da edit em modo normal.
		 iBackgroundColorText, cor de fundo da edit.
		 iBorderColor, cor da borda em modo normal.
		 iHoverTextColor, cor do texto da edit no momento do hover.
		 iHoverBackgroundColorText, cor do texto de fundo no momento do hover.
		 iHoverBorderColor, cor do texto da borda no momento do hover.


### 0x08 - CreateAdvancedEdit
-  Resposável por criar caixas de texto para uso de multiplas linhas.

		Protótipo:
		 HWND Result = CreateAdvancedEdit(int iStyle, int X, int Y, int iWidth, int iHeight,
				char *cText, int iEditID, int iBorder, HWND hwWindowParent);

		Retorno:
		 Retorna identificador da edit.

		Argumentos:
		 iStyle, define os estilos da edit.
		 X, posição X da edit em sua janela pai.
		 Y, posição Y da edit em sua janela pai.
		 iWidth, largura.
		 iHeight, altura.
		 cText, texto padrão.
		 iEditID, ID da edit.
		 iBorder, define se usa borda na edit ou não.
		 hwWindowParent, identificador da janela pai.


### 0x09 - SetControlColor
-  Função responsável adicionar efeitos de cores nos controles.

		Protótipo:
		 void SetControlColor(int iControlType, WPARAM wParam, LPARAM lParam, HWND hWnd, 
					int iIDControl,int iTextColor,int iBackgroundColorText,int iBorderColor);

		Argumentos:
		 iControlType, tipo do controle.
		 wParam, passar como argumento o valor do wParam da Callback do loop 
		 de mensagens.
		 lParam, passar como argumento o valor do lParam da Callback do loop 
		 de mensagens.
		 hWnd, identificar do controle.
		 iIDControl, ID do controle.
		 iTextColor, cor do text.
		 iBackgroundColorText, cor de fundo.
		 iBorderColor, cor da borda.


### 0x10 - CreateStatic
-  Resposável por criar um frame.

		Protótipo:
		 HWND Result = CreateStatic(int iStyle, int X, int Y, int iWidth, int iHeight,
				char *cText, int iControlID, int iBorder, HWND hwWindowParent);

		Retorno:
		 Retorna identificador do controle.

		Argumentos:
		 iStyle, define os estilos do controle.
		 X, posição X do controle em sua janela pai.
		 Y, posição Y do controle em sua janela pai.
		 iWidth, largura.
		 iHeight, altura.
		 cText, texto padrão.
		 iControlID, ID do controle.
		 iBorder, define se usa borda do controle ou não.
		 hwWindowParent, identificador da janela pai.

		Macros / Atalhos:
		 CreateFrame, utilizada para criar frames.
		 CreateLabel, utilizada para criar textos.

