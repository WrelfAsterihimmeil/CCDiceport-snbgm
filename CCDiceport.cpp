// CCDiceport.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "framework.h"
#include "CCDiceport.h"
#include <string>
#include <sstream>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名
HWND hwnd_child;

int pp = 5;
int sp = 12;
int fm = 2;
int dc = 2;

BOOL SetClipboardText(const char* Str)
{
    int    BufSize;
    char* Buf;
    HANDLE hMem;

    BufSize = strlen(Str) + 1;                               // 確保するメモリのサイズを計算する
    hMem = GlobalAlloc(GMEM_SHARE | GMEM_MOVEABLE, BufSize); // 移動可能な共有メモリを確保する
    if (!hMem) return FALSE;

    Buf = (char*)GlobalLock(hMem); // 確保したメモリをロックし，アクセス可能にする
    if (Buf)
    {
        strcpy_s(Buf, BufSize, Str);   // 文字列を複写する
        GlobalUnlock(hMem); // メモリのロックを解除する
        if (OpenClipboard(NULL))
        {
            EmptyClipboard();                  // クリップボード内の古いデータを解放する
            SetClipboardData(CF_TEXT, hMem); // クリップボードに新しいデータを入力する
            CloseClipboard();

            return TRUE;
        }
    }
    return FALSE;
}

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CCDICEPORT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CCDICEPORT));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CCDICEPORT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CCDICEPORT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//

enum {
    pp2 = 1,
    pp3,
    pp4,
    pp5,
    pp6,
    pp7,
    pp8,
    pp9,
    pp10,
    pp11,
    pp12,
    sp2,
    sp3,
    sp4,
    sp5,
    sp6,
    sp7,
    sp8,
    sp9,
    sp10,
    sp11,
    sp12,
    fm2,
    fm3,
    fm4,
    fm5,
    fm6,
    fm7,
    fm8,
    fm9,
    fm10,
    fm11,
    fm12,
    dc1,
    dc2,
    dc3,
    dc4,
    bg,
    cpy,
};

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   hwnd_child = CreateWindowA("STATIC", "", WS_VISIBLE | WS_CHILD, 0, 0, 480, 400, hWnd, (HMENU)bg, hInstance, NULL);
   hwnd_child = CreateWindowA("STATIC", "目標値", WS_VISIBLE | WS_CHILD, 20, 0, 100, 20, hWnd, (HMENU)bg, hInstance, NULL);
   hwnd_child = CreateWindowA("STATIC", "スペシャル", WS_VISIBLE | WS_CHILD, 120, 0, 100, 20, hWnd, (HMENU)bg, hInstance, NULL);
   hwnd_child = CreateWindowA("STATIC", "ファンブル", WS_VISIBLE | WS_CHILD, 220, 0, 100, 20, hWnd, (HMENU)bg, hInstance, NULL);
   hwnd_child = CreateWindowA("STATIC", "ダイス数", WS_VISIBLE | WS_CHILD, 320, 0, 100, 20, hWnd, (HMENU)bg, hInstance, NULL);
   //radio button
      //mokuhyouti
       hwnd_child = CreateWindowA("button", "2", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 20, 20, 100, 30, hWnd, (HMENU)pp2, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "3", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 50, 100, 30, hWnd, (HMENU)pp3, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "4", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 80, 100, 30, hWnd, (HMENU)pp4, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "5", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 110, 100, 30, hWnd, (HMENU)pp5, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "6", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 140, 100, 30, hWnd, (HMENU)pp6, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "7", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 170, 100, 30, hWnd, (HMENU)pp7, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "8", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 200, 100, 30, hWnd, (HMENU)pp8, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "9", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 230, 100, 30, hWnd, (HMENU)pp9, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "10", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 260, 100, 30, hWnd, (HMENU)pp10, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "11", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 290, 100, 30, hWnd, (HMENU)pp11, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "12", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 20, 320, 100, 30, hWnd, (HMENU)pp12, hInstance, NULL);

   
       ////special
       hwnd_child = CreateWindowA("button", "2", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 120, 20, 100, 30, hWnd, (HMENU)sp2, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "3", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 50, 100, 30, hWnd, (HMENU)sp3, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "4", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 80, 100, 30, hWnd, (HMENU)sp4, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "5", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 110, 100, 30, hWnd, (HMENU)sp5, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "6", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 140, 100, 30, hWnd, (HMENU)sp6, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "7", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 170, 100, 30, hWnd, (HMENU)sp7, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "8", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 200, 100, 30, hWnd, (HMENU)sp8, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "9", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 230, 100, 30, hWnd, (HMENU)sp9, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "10", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 260, 100, 30, hWnd, (HMENU)sp10, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "11", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 290, 100, 30, hWnd, (HMENU)sp11, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "12", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 120, 320, 100, 30, hWnd, (HMENU)sp12, hInstance, NULL);

       ////fumble
       hwnd_child = CreateWindowA("button", "2", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 220, 20, 100, 30, hWnd, (HMENU)fm2, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "3", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 50, 100, 30, hWnd, (HMENU)fm3, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "4", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 80, 100, 30, hWnd, (HMENU)fm4, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "5", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 110, 100, 30, hWnd, (HMENU)fm5, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "6", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 140, 100, 30, hWnd, (HMENU)fm6, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "7", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 170, 100, 30, hWnd, (HMENU)fm7, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "8", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 200, 100, 30, hWnd, (HMENU)fm8, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "9", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 230, 100, 30, hWnd, (HMENU)fm9, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "10", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 260, 100, 30, hWnd, (HMENU)fm10, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "11", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 290, 100, 30, hWnd, (HMENU)fm11, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "12", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 220, 320, 100, 30, hWnd, (HMENU)fm12, hInstance, NULL);

       ////dice
       hwnd_child = CreateWindowA("button", "1", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP, 320, 20, 100, 30, hWnd, (HMENU)dc1, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "2", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 320, 50, 100, 30, hWnd, (HMENU)dc2, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "3", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 320, 80, 100, 30, hWnd, (HMENU)dc3, hInstance, NULL);
       hwnd_child = CreateWindowA("button", "4", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 320, 110, 100, 30, hWnd, (HMENU)dc4, hInstance, NULL);

       ////button
       hwnd_child = CreateWindowA("button", "コピー", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 340, 180, 60, 40, hWnd, (HMENU)cpy, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

                //ボタン処理
            case pp2:
                pp = 2;
                break;
            case pp3:
                pp = 3;
                break;
            case pp4:
                pp = 4;
                break;
            case pp5:
                pp = 5;
                break;
            case pp6:
                pp = 6;
                break;
            case pp7:
                pp = 7;
                break;
            case pp8:
                pp = 8;
                break;
            case pp9:
                pp = 9;
                break;
            case pp10:
                pp = 10;
                break;
            case pp11:
                pp = 11;
                break;
            case pp12:
                pp = 12;
                break;

            case sp2:
                sp = 2;
                break;
            case sp3:
                sp = 3;
                break;
            case sp4:
                sp = 4;
                break;
            case sp5:
                sp = 5;
                break;
            case sp6:
                sp = 6;
                break;
            case sp7:
                sp = 7;
                break;
            case sp8:
                sp = 8;
                break;
            case sp9:
                sp = 9;
                break;
            case sp10:
                sp = 10;
                break;
            case sp11:
                sp = 11;
                break;
            case sp12:
                sp = 12;
                break;

            case fm2:
                fm = 2;
                break;
            case fm3:
                fm = 3;
                break;
            case fm4:
                fm = 4;
                break;
            case fm5:
                fm = 5;
                break;
            case fm6:
                fm = 6;
                break;
            case fm7:
                fm = 7;
                break;
            case fm8:
                fm = 8;
                break;
            case fm9:
                fm = 9;
                break;
            case fm10:
                fm = 10;
                break;
            case fm11:
                fm = 11;
                break;
            case fm12:
                fm = 12;
                break;

            case dc1:
                dc = 1;
                break;
            case dc2:
                dc = 2;
                break;
            case dc3:
                dc = 3;
                break;
            case dc4:
                dc = 4;
                break;
            case cpy:
            {
                std::string cp = "";
                std::stringstream is;
                is << dc << "SG@" << sp << "#" << fm << ">=" << pp << std::endl;
                cp = is.str();
                SetClipboardText(cp.c_str());
            }
           

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_CREATE://最前面固定
    {
        SetWindowPos(
            hWnd, HWND_TOPMOST,
            0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE
        );

        return 0;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
