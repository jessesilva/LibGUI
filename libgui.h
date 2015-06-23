
/* ******************************************************************* **
** LibGUI                                                              **
** Um conjunto de funções auxiliares destinadas a criação de controles **
** personalizados utilizando a WinAPI.                                 **
**                                                                     **
** Autor: Dennis / https://github.com/DennisAnsiC/                     **
**                                                                     **
** ******************************************************************* */

/* ** Headers ******************************************************** */
#include <Windows.h>
#include <libtext.h>
#include <malloc.h>

/* ** Defines ******************************************************** */
#ifndef nil
#define nil NULL
#endif

#ifndef DEBUG
#define DEBUG OutputDebugStringA
#endif

#define LIBGUI_ERROR              1
#define LIBGUI_ERROR_SUCCESS      0

#define LIBGUI_CLASS              L"LibGUIClassEx"
#define LIBGUI_CLASS_ANSI         "LibGUIClassEx"
#define LIBGUI_DEFAULT_COLOR      (HBRUSH)(COLOR_WINDOW+1)

/* ** Controls ******************************************************* */
#define BUTTON_CONTROL            0x2784598
#define EDIT_CONTROL              0x4878483
#define EDITBOX_CONTROL           0x8834743
#define LABEL_CONTROL             0x8433873

/* ** Protos ********************************************************* */
#define CreateLabel               CreateStatic
#define CreateFrame               CreateStatic

/* ** Macros ********************************************************* */
#define Inst                      GetModuleHandle(nil)
#define CENTER_X(X)               (GetSystemMetrics(SM_CXSCREEN)-X)/2
#define CENTER_Y(Y)               (GetSystemMetrics(SM_CYSCREEN)-Y)/2

#define _LIBGUI_CONFIGS_          extern HWND LibGUIHoverHWND;\
                                  extern HWND LibGUITempHoverHWND;\

#define _LIBGUI_WM_ACTIVATE_(X)   if(X!=LibGUIHoverHWND){\
                                  LibGUITempHoverHWND=LibGUIHoverHWND;\
                                  LibGUIHoverHWND=(HWND)-1;\
                                  InvalidateRect(LibGUITempHoverHWND,nil,0);}\

#define _LIBGUI_GETHWEDIT_(X)     GetWindowLong((HWND)X,GWL_ID)
#define GetHWND(HWND,ID_CONTROL)  GetDlgItem(HWND,ID_CONTROL)
#define IsHWND(HWND,ID_CONTROL)   LibGUIHoverHWND==(GetHWND(HWND,ID_CONTROL))
#define WM_SEND                   (WM_USER+1)

/* ** Styles ********************************************************* */
#define SIMPLE_NOMAX              WS_BORDER|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU
#define SIMPLE_BOX_NOWV           ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL

/* ** Prototypes ***************************************************** */
int GUIInitialize(WNDPROC wndWindowCallback,HBRUSH hbWindowColor);
int RefreshWindow(HWND hwWindow);
void HoverButton(LPARAM lParam,int iTextColor, int iBackgroundColor,int iHoverTextColor,int iHoverBackgroundColor);
void HoverEdit(WPARAM wParam,HWND hWnd,int iIDControl,int iTextColor,int iBackgroundColorText,int iBorderColor,
  int iHoverTextColor,int iHoverBackgroundColorText,int iHoverBorderColor);
void SetControlColor(WPARAM wParam,int iControlType,int iIDControl,int iTextColor,
  int iBackgroundColorText,int iBorderColor);
HWND CreateSimpleWindow(int iStyle,char *cTitle,int iPositionX,int iPositionY,int X,int Y,int iID,HWND hwWindowParent);
HWND CreateButton(int X,int Y,int iWidth,int iHeight,char *cText,int iButtonID,HWND hwWindowParent);
HWND CreateEdit(int X,int Y,int iWidth,int iHeight,char *cText,int iEditID,int iBorder,HWND hwWindowParent);
HWND CreateAdvancedEdit(int iStyle,int X,int Y,int iWidth,int iHeight,char *cText,int iEditID,int iBorder,HWND hwWindowParent);
HBRUSH GetColor(int iColor);
HWND CreateStatic(int iStyle, int X, int Y, int iWidth, int iHeight,char *cText, 
  int iControlID, int iBorder, HWND hwWindowParent);

/* ******************************************************************* */
