//
//  main.cpp
//  RunParticles
//
//  Created by Doug Letterman on 9/27/13.
//
//

#include <QApplication>

#include "GLWidget.h"
#include "MainWindow.h"
#include "Map.h"

#ifdef Q_OS_WIN
#define ULONG_PTR ULONG
#include <Windows.h>
#include <Shlobj.h>
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define LOSHORT(l)           ((SHORT)(l))
#define HISHORT(l)           ((SHORT)(((DWORD)(l) >> 16) & 0xFFFF))
#include <gdiplus.h>
#undef min
#undef max
#pragma comment(lib, "gdiplus")
#endif

int main(int argc, char **argv)
{

#ifdef Q_OS_WIN
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiPlusToken;
	Gdiplus::GdiplusStartup( &gdiPlusToken, &gdiplusStartupInput, NULL );
#endif
    QApplication app(argc, argv);
    app.setApplicationName("RunParticles");
    app.setOrganizationDomain("renderfast.com");
    app.setOrganizationName("Renderfast");
    app.setApplicationVersion("1.0");
    
    MainWindow mainWindow;

#ifndef Q_OS_MAC
	mainWindow.show();
#endif
    
    app.exec();
}

