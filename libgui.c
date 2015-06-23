
/* ******************************************************************* **
** LibGUI                                                              **
** Um conjunto de funções auxiliares destinadas a criação de controles **
** personalizados utilizando a WinAPI.                                 **
**                                                                     **
** Autor: Dennis / https://github.com/DennisAnsiC/                     **
**                                                                     **
** ******************************************************************* */

/* ** Headers ******************************************************** */
#include "libgui.h"

HWND LibGUIHoverHWND=(HWND)-1,LibGUITempHoverHWND;

int
GUIInitialize(WNDPROC wndWindowCallback,HBRUSH hbWindowColor)
{
	WNDCLASSEX wnClass;
	int result=LIBGUI_ERROR;

	wnClass.cbSize        = sizeof(WNDCLASSEX);
	wnClass.style         = CS_HREDRAW|CS_VREDRAW;
	wnClass.lpfnWndProc   = wndWindowCallback;
	wnClass.cbClsExtra    = 0;
	wnClass.cbWndExtra    = 0;
	wnClass.hInstance     = Inst;
	wnClass.hIcon         = nil;
	wnClass.hIconSm       = nil;
	wnClass.hCursor       = LoadCursorW(nil,IDC_ARROW);
	wnClass.hbrBackground = hbWindowColor;
	wnClass.lpszClassName = LIBGUI_CLASS;
	wnClass.lpszMenuName  = nil;

	if(RegisterClassEx(&wnClass)){
		result=LIBGUI_ERROR_SUCCESS;
	}

	return result;
}

HWND
CreateSimpleWindow(int iStyle,char *cTitle,int iPositionX,int iPositionY,int X,int Y,int iID,HWND hwWindowParent)
{
	HMENU hmWindowID=nil;
	HWND hwWindow;

	if ((iPositionX<0)||(iPositionY<0)||(X<0)||(Y<0)||(iID<0)){
		return nil;
	}

	if(iID>0){
		hmWindowID=(HMENU)iID;
	}

	hwWindow=CreateWindowExA(0,LIBGUI_CLASS_ANSI,cTitle,(DWORD)iStyle,iPositionX,iPositionY,X,Y,
		hwWindowParent,hmWindowID,Inst,nil);

	if(hwWindow){
		return hwWindow;
	}

	return nil;
}

HBRUSH 
GetColor(int iColor)
{
	return CreateSolidBrush((COLORREF)iColor);
}

int
RefreshWindow(HWND hwWindow)
{
	MSG mMessage;
	int iScrollControl;

	ShowWindow(hwWindow,SW_SHOW);
	UpdateWindow(hwWindow);

	while(GetMessage(&mMessage,nil,0,0)>0){
		/* Hover efect */
		if((mMessage.message==WM_MOUSEMOVE)&&(LibGUITempHoverHWND!=mMessage.hwnd)){
			LibGUITempHoverHWND=LibGUIHoverHWND;
			LibGUIHoverHWND=mMessage.hwnd;

			if(hwWindow!=LibGUITempHoverHWND){ 
				InvalidateRect(LibGUITempHoverHWND,nil,0); 
			}
			if(hwWindow!=LibGUIHoverHWND){ 
				InvalidateRect(LibGUIHoverHWND,nil,0); 
			}
		}

		/* Scroll control start */
		iScrollControl=0;
		if(mMessage.message==WM_MOUSEWHEEL){
			if(GetPropA(mMessage.hwnd,"VSCROLL")){
				SendMessage(mMessage.hwnd,WM_SETREDRAW,0,0);
				ShowScrollBar(mMessage.hwnd,SB_VERT,1);
				iScrollControl=1;
			}
		}

		TranslateMessage(&mMessage);
		DispatchMessage(&mMessage);

		/* Scroll control end */
		if(iScrollControl){
			ShowScrollBar(mMessage.hwnd,SB_VERT,0);
			SendMessage(mMessage.hwnd,WM_SETREDRAW,1,0); 
		}

		/* Enter key */
		if((mMessage.message==WM_KEYDOWN)&&(mMessage.wParam==VK_RETURN)){
			SendMessage(hwWindow,WM_SEND,(WPARAM)mMessage.hwnd,(LPARAM)0);
		}
	}

	return (int)mMessage.wParam;
}

HWND
CreateButton(int X,int Y,int iWidth,int iHeight,char *cText,int iButtonID,HWND hwWindowParent)
{
	HWND hwhWnd;

	if ((X<0)||(Y<0)||(iWidth<0)||(iHeight<0)||(iButtonID<=0)||(hwWindowParent==nil)){
		return nil;
	}

	hwhWnd=CreateWindowExA(0,"BUTTON",cText,WS_CHILD|WS_VISIBLE|BS_OWNERDRAW,X,Y,iWidth,iHeight,
		hwWindowParent,(HMENU)iButtonID,Inst,nil);

	if(hwhWnd){
		return hwhWnd;
	}

	return nil;
}

void
HoverButton(LPARAM lParam,int iTextColor, int iBackgroundColor,int iHoverTextColor,int iHoverBackgroundColor)
{
	DRAWITEMSTRUCT *disDraw=(DRAWITEMSTRUCT*)lParam;
	HBRUSH hBrush;
	char *cTemporary;

	if(nil==(cTemporary=(char *)malloc((size_t)256))){
		DEBUG("HoverButton() - Erro ao alocar memoria.");
		ExitProcess(EXIT_FAILURE);
	}

	hBrush=(HBRUSH)((LibGUIHoverHWND==(disDraw->hwndItem))?CreateSolidBrush((COLORREF)iHoverBackgroundColor)
														  :CreateSolidBrush((COLORREF)iHoverTextColor));

	SetTextColor((disDraw->hDC),(COLORREF)(LibGUIHoverHWND==(disDraw->hwndItem)?iBackgroundColor:iTextColor));
	SetBkColor((disDraw->hDC),(COLORREF)(LibGUIHoverHWND==(disDraw->hwndItem))?iHoverBackgroundColor:iHoverTextColor);
	GetWindowTextA((disDraw->hwndItem),cTemporary,255);
	FillRect((disDraw->hDC),&(disDraw->rcItem),hBrush);
	DrawTextA((disDraw->hDC),cTemporary,lt_strlen(cTemporary),&(disDraw->rcItem),DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	DeleteObject((HGDIOBJ)hBrush);
	free(cTemporary);
}

HWND 
CreateEdit(int X,int Y,int iWidth,int iHeight,char *cText,int iEditID,int iBorder,HWND hwWindowParent)
{
	HWND hwhWnd;

	if ((X<0)||(Y<0)||(iWidth<0)||(iHeight<0)||(iEditID<=0)||(cText==nil)||(hwWindowParent==nil)){
		return nil;
	}

	if(iBorder==1){
		hwhWnd=CreateWindowExA(0,"EDIT",cText,WS_CHILD|WS_VISIBLE|WS_BORDER,X,Y,iWidth,iHeight,
			hwWindowParent,(HMENU)iEditID,Inst,nil);
	}else{
		hwhWnd=CreateWindowExA(0,"EDIT",cText,WS_CHILD|WS_VISIBLE,X,Y,iWidth,iHeight,
			hwWindowParent,(HMENU)iEditID,Inst,nil);
	}

	if(hwhWnd){
		return hwhWnd;
	}

	return nil;
}

void 
HoverEdit(WPARAM wParam,HWND hWnd,int iIDControl,int iTextColor,int iBackgroundColorText,int iBorderColor,
	int iHoverTextColor,int iHoverBackgroundColorText,int iHoverBorderColor)
{
	HWND TemporaryHwnd=GetHWND(hWnd,iIDControl);
	HBRUSH hBrush;
	RECT rRect;
	HDC hDC=(HDC)wParam;

	hBrush=(HBRUSH)((LibGUIHoverHWND==TemporaryHwnd)?CreateSolidBrush((COLORREF)iHoverBorderColor)
													:CreateSolidBrush((COLORREF)iBorderColor));

	SetTextColor(hDC,(COLORREF)(LibGUIHoverHWND==TemporaryHwnd)?iHoverTextColor:iTextColor);
	SetBkColor(hDC,(COLORREF)(LibGUIHoverHWND==TemporaryHwnd)?iHoverBackgroundColorText:iBackgroundColorText);
	GetClientRect(TemporaryHwnd,&rRect);
	FillRect(hDC,&rRect,hBrush);
	DeleteObject(hBrush);
}

HWND 
CreateAdvancedEdit(int iStyle,int X,int Y,int iWidth,int iHeight,char *cText,int iEditID,int iBorder,HWND hwWindowParent)
{
	HWND hwhWnd;

	if ((iStyle<0)||(X<0)||(Y<0)||(iWidth<0)||(iHeight<0)||(iEditID<=0)||(cText==nil)||(hwWindowParent==nil)){
		return nil;
	}

	if(iBorder==1){
		hwhWnd=CreateWindowExA(0,"EDIT",cText,iStyle|WS_CHILD|WS_VISIBLE|WS_BORDER,X,Y,iWidth,iHeight,
			hwWindowParent,(HMENU)iEditID,Inst,nil);
	}else{
		hwhWnd=CreateWindowExA(0,"EDIT",cText,iStyle|WS_CHILD|WS_VISIBLE,X,Y,iWidth,iHeight,
			hwWindowParent,(HMENU)iEditID,Inst,nil);
	}

	if(hwhWnd){
		return hwhWnd;
	}

	return nil;
}

void 
SetControlColor(WPARAM wParam,int iControlType,int iIDControl,int iTextColor,
	int iBackgroundColorText,int iBorderColor)
{
	HDC hDC=(HDC)wParam;

	if((iControlType<=0)||(iTextColor<0)||(iBackgroundColorText<0)||(iBorderColor<0)){
		DEBUG("SetControlColor() - Dados invalidos.");
		ExitProcess(EXIT_FAILURE);
	}

	switch(iControlType){
		case BUTTON_CONTROL: break;
		case EDIT_CONTROL: break;
		case EDITBOX_CONTROL: break;
	}

	SetTextColor(hDC,(COLORREF)iTextColor);
	SetBkColor(hDC,(COLORREF)iBackgroundColorText);
}

HWND 
CreateStatic(int iStyle,int X,int Y,int iWidth,int iHeight,char *cText, 
	int iControlID,int iBorder,HWND hwWindowParent)
{
	HWND hwhWnd;

	if((iStyle<0)||(X<0)||(Y<0)||(iWidth<0)||(iHeight<0)||(iControlID<0)||(cText==nil)||(hwWindowParent==nil)){
		return nil;
	}

	if(iStyle==0){
		if(iBorder==1){
			iStyle=WS_CHILD|WS_VISIBLE|WS_BORDER;
		}else{
			iStyle=WS_CHILD|WS_VISIBLE;
		}
	}

	hwhWnd=CreateWindowExA(0,"STATIC",cText,iStyle,X,Y,iWidth,iHeight,
		hwWindowParent,(HMENU)iControlID,Inst,nil);
	
	if(hwhWnd){
		return hwhWnd;
	}

	return nil;
}

/* ******************************************************************* */
