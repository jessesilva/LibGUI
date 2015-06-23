#pragma comment(lib, "Comctl32.lib")

#include <Windows.h>	/* Windows Run-Time headers */
#include <SonicRT.h>	/* Sonic Run-Time headers (old) */
#include <Commctrl.h>

_LIBGUI_CONFIGS_		/* LibGUI Config's */

/* Configs */
#define TITULO			"LibGUI - By Dennis - https://github.com/DennisAnsiC/"
#define LARGURA			648
#define ALTURA			600

/* Button Control's */
#define BTN_ID_01		1002
#define BTN_ID_02		1003
#define BTN_ID_03		1004

/* Edit Control's */
#define EDT_ID_01		1005
#define EDT_ID_02		1006
#define EDT_ID_03		1007

/* Frame + EditBox control */
#define FRAME_ID		3984
#define EDT_ID_04		1008

HBRUSH FrameBrush;
HBRUSH EditBoxBrush;

/* Label Transparente */
#define LABEL_TRANSPARENT	3238

/* Label com fundo de cores */
#define LABEL_COR		48435
HBRUSH LabelBrush;

/* Menu controls */
#define ID_CLOSE		9883
#define ID_MSG			8435

LRESULT CALLBACK WindowCallbackEx(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int APIENTRY
wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nShowCmd)
{
	HWND Window, EditBox;
	HMENU hMenu, hSubMenu;
	MENUINFO MenuInfo={0};
	HBRUSH hBrushMenu;
	int Result;

	/* Iniciliaza a LibGUI*/
	if(LIBGUI_ERROR==(Result=GUIInitialize(WindowCallbackEx,GetColor(0x00553929)))){
		MessageBox(0,L"Não foi possível inicializar a LibGUI.",L"ERROR",MB_OK|MB_ICONERROR);
		return 1;
	}

	/* Cria janela principal */
	Window=CreateSimpleWindow(SIMPLE_NOMAX,TITULO,CENTER_X(LARGURA),CENTER_Y(ALTURA),LARGURA,ALTURA,0,HWND_DESKTOP);

	/* Button's */
	CreateButton(33,30,190,52,"Botao 01",BTN_ID_01,Window);
	CreateButton(227,30,190,52,"Botao 02",BTN_ID_02,Window);
	CreateButton(421,30,190,52,"Botao 03",BTN_ID_03,Window);

	/* Edit's */
	CreateEdit(33,90,190,20,"",EDT_ID_01,1,Window);
	CreateEdit(227,90,190,20,"",EDT_ID_02,1,Window);
	CreateEdit(421,90,190,20,"teste",EDT_ID_03,1,Window);

	/* Frame + EditBox */
	CreateFrame(0,33,120,579,310,"",FRAME_ID,0,Window);
	CreateAdvancedEdit(SIMPLE_BOX_NOWV,33+1,120+1,579-2,310-2,"",EDT_ID_04,0,Window);

	SetPropA(EditBox,"VSCROLL",(HANDLE)1);			/* Hide scroll */
	SendMessage(EditBox,EM_SETLIMITTEXT,0,0);		/* Text Buffer 2GB */

	/* Label com fundo transparente */
	CreateLabel(0,33,435,579,18,"Label com fundo transparente =D",LABEL_TRANSPARENT,0,Window);

	/* Label com fundo de cor sólida */
	CreateLabel(0,33,458,579,18,"Label com fundo de cor solida =D",LABEL_COR,0,Window);

	/* Menu e submenu */
	hMenu = CreateMenu();

	hSubMenu = CreatePopupMenu();
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Melancia");
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Pera");
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Maca");
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Ervilhas");
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Dennis");
	AppendMenuA(hSubMenu, MF_STRING, (UINT)0, "Ritchie");
	AppendMenuA(hSubMenu, MF_STRING, ID_CLOSE, "C&lose");
	AppendMenuA(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "F&ile");

	hSubMenu = CreatePopupMenu();
	AppendMenuA(hSubMenu, MF_STRING, ID_MSG, "M&sg");
	AppendMenuA(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "A&bout");

	SetMenu(Window, hMenu);

	hBrushMenu=GetColor(0x0000BB00);
	MenuInfo.cbSize=sizeof(MenuInfo);
	MenuInfo.fMask=MIM_BACKGROUND|MIM_APPLYTOSUBMENUS;
	MenuInfo.hbrBack=hBrushMenu;

	SetMenuInfo(hMenu,&MenuInfo);

	/* Message Loop */
	return RefreshWindow(Window);
}

LRESULT CALLBACK 
WindowCallbackEx(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	DRAWITEMSTRUCT *disDraw=(DRAWITEMSTRUCT*)lParam;
	
	switch(uMsg){
		case WM_CLOSE: DestroyWindow(hWnd); break;
		case WM_DESTROY: PostQuitMessage(WM_QUIT); break;

		/* Ações */
		case WM_COMMAND:
			switch(wParam){
				case BTN_ID_01: 
					OutputDebugStringA("Ativou scroll");
					ShowScrollBar(GetDlgItem(hWnd, EDT_ID_04),SB_VERT,1);
				break;
				case BTN_ID_02: 
					OutputDebugStringA("Desativou scroll");
					ShowScrollBar(GetDlgItem(hWnd, EDT_ID_04),SB_VERT,0);
				break;
				case BTN_ID_03: 
					OutputDebugStringA("Clicou botão 03");
				break;
				case ID_CLOSE:
					PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
				case ID_MSG:
					MessageBoxA(nil, "LibGUI - Um conjunto de funcoes pra me ajudar =D", "By Sonic", MB_OK);
				break;
			}
		break;

		case WM_ACTIVATE:
			_LIBGUI_WM_ACTIVATE_(hWnd)
		break;

		/* Efeitos botões */
		case WM_DRAWITEM:
			switch(disDraw->CtlID){
				case BTN_ID_01: 
					HoverButton(lParam,0x00F2F2F2,0x00000000,0x009A35FF,0x005C00B9);
					break;
				case BTN_ID_02:
					HoverButton(lParam,0x00F2F2F2,0x00000000,0x0000FF00,0x00008000);
					break;
				case BTN_ID_03:
					HoverButton(lParam,0x00F2F2F2,0x00000000,0x00FF4040,0x009F0000);
					break;
			}
		return 1;
		
		/* Efeitos edit's */
		case WM_CTLCOLOREDIT:
			switch(_LIBGUI_GETHWEDIT_(lParam)){
				case EDT_ID_01 :
					HoverEdit(wParam,hWnd,EDT_ID_01,0x00FFFFFF,0x00008000,0x00008000,0x0000FF00,0x00000000,0x00000000);
					break;
				case EDT_ID_02 :
					HoverEdit(wParam,hWnd,EDT_ID_02,0x0000FF00,0x00808080,0x00808080,0x0000FF00,0x009A9A9A,0x009A9A9A);
					break;
				case EDT_ID_03 :
					HoverEdit(wParam,hWnd,EDT_ID_03,0x00F2F2F2,0x00FF4040,0x00FF4040,0x009F0000,0x00000000,0x00000000);
					break;

				/* EditBox control */
				case EDT_ID_04 :
					SetControlColor(wParam,EDITBOX_CONTROL,EDT_ID_04,0x0000FF00,0x00808080,0x00808080);
					EditBoxBrush=GetColor(0x00808080);
					return (LRESULT)EditBoxBrush;

			}
		return (LRESULT)DC_BRUSH;

		/* Efeitos static's / (Frames, Labels) */
		case WM_CTLCOLORSTATIC:
			switch(_LIBGUI_GETHWEDIT_(lParam)){
				case FRAME_ID:
					FrameBrush=GetColor(0x00FFFF00);
					return (LRESULT)FrameBrush;

				case LABEL_TRANSPARENT:
					SetControlColor(wParam,LABEL_CONTROL,LABEL_TRANSPARENT,0x0000FF00,0x00808080,0x00808080);
					SetBkMode ((HDC)wParam,TRANSPARENT);
					return (LRESULT)GetStockObject(NULL_BRUSH);

				case LABEL_COR:
					SetControlColor(wParam,LABEL_CONTROL,LABEL_COR,0x00800000,0x0000FFFF,0x0000FFFF);
					LabelBrush=GetColor(0x0000FFFF);
					return (LRESULT)LabelBrush;
			}
		return (LRESULT)DC_BRUSH;

		default:
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
	}

	return 0;
}
