#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define IDC_UPDATE_BUTTON   100
#define IDC_CLEAR_BUTTON    101
#define IDC_QUIT_BUTTON     102
#define IDC_FONT1_BUTTON    103
#define IDC_FONT2_BUTTON    104
#define IDC_FONT3_BUTTON    105
#define IDC_INPUT_TEXT      106
#define IDC_OUTPUT_TEXT     107

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

char szClassName[ ] = "Lab1Class";
HINSTANCE hProgramInstance;

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
  HWND hwnd;               /* This is the handle for our window */
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */

  /* The Window structure */
  wincl.hInstance = hThisInstance;
  wincl.lpszClassName = szClassName;
  wincl.lpfnWndProc = WindowProcedure;
  wincl.style = CS_DBLCLKS;
  wincl.cbSize = sizeof (WNDCLASSEX);

  /* Use default icon and mouse-pointer */
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName = NULL;
  wincl.cbClsExtra = 0;
  wincl.cbWndExtra = 0;
  wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

  /* Register the window class, and if it fails quit the program */
  if(!RegisterClassEx(&wincl)) return 0;

  /* The class is registered, let's create the program*/
  hwnd = CreateWindowEx (
  0,                    /* Extended possibilites for variation */
  szClassName,          /* Classname */
  "Laboratory Work #1", /* Title Text */
  WS_OVERLAPPEDWINDOW,  /* default window */
  CW_USEDEFAULT,        /* Windows decides the position */
  CW_USEDEFAULT,        /* where the window ends up on the screen */
  544,                  /* The programs width */
  375,                  /* and height in pixels */
  HWND_DESKTOP,         /* The window is a child-window to desktop */
  NULL,                 /* No menu */
  hThisInstance,        /* Program Instance handler */
  NULL                  /* No Window Creation data */
  );

  /* Make the window visible on the screen */
  ShowWindow (hwnd, nCmdShow);

  srand(time(NULL));

  /* Run the message loop. It will run until GetMessage() returns 0 */
  while (GetMessage (&messages, NULL, 0, 0))
  {
    TranslateMessage(&messages); /* Translate virtual-key messages into character messages */
    DispatchMessage(&messages);  /* Send message to WindowProcedure */
  }

  /* The program return-value is 0 - The value that PostQuitMessage() gave */
  return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  // Declare handles for buttons
  static HWND hwndUpdateButton;
  static HWND hwndClearButton;
  static HWND hwndQuitButton;
  static HWND hwndFont1Button;
  static HWND hwndFont2Button;
  static HWND hwndFont3Button;
  // Declare handles for input and output text areas
  static HWND hwndInputText;
  static HWND hwndOutputText;
  int iScreenW;
  int iScreenH;
  RECT rect;
  PAINTSTRUCT ps;
  HDC hdc;
  int iTextLength;
  char * szText;
  HFONT hfFont;
  HWND hwndBtn;


  switch(message)
  {
    case WM_CREATE:
      iScreenW = GetSystemMetrics(SM_CXSCREEN);
      iScreenH = GetSystemMetrics(SM_CYSCREEN);

      GetWindowRect(hwnd, &rect);
      SetWindowPos(
        hwnd, 0,
        (iScreenW - rect.right)/2,
        (iScreenH - rect.bottom)/2,
        0, 0,
        SWP_NOZORDER|SWP_NOSIZE);

      hwndUpdateButton = CreateWindowEx(
        (DWORD)NULL,
        TEXT("button"), // class
        TEXT("Update"), // caption
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 170,        // X & Y
        60, 20,         // width x height
        hwnd,
        (HMENU)IDC_UPDATE_BUTTON,
        hProgramInstance,
        NULL);

      hwndClearButton = CreateWindowEx(
        (DWORD)NULL,
        TEXT("button"), // class
        TEXT("Clear"),  // caption
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        220, 200,        // X & Y
        60, 20,         // width x height
        hwnd,
        (HMENU)IDC_CLEAR_BUTTON,
        hProgramInstance,
        NULL);

      hwndQuitButton = CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"), // class
      TEXT("Quit"),   // caption
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW,
      220, 230,        // X & Y
      60, 20,         // width x height
      hwnd,
      (HMENU)IDC_QUIT_BUTTON,
      hProgramInstance,
      NULL);

      hwndFont1Button = CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),   // class
      TEXT("Tahoma"),    // caption
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      10, 230,          // X & Y
      60, 20,          // width x height
      hwnd,
      (HMENU)IDC_FONT1_BUTTON,
      hProgramInstance,
      NULL);

      hwndFont2Button = CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),   // class
      TEXT("Courier"),   // caption
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      80, 230,          // X & Y
      60, 20,          // width x height
      hwnd,
      (HMENU)IDC_FONT2_BUTTON,
      hProgramInstance,
      NULL);

      hwndFont3Button = CreateWindowEx(
      (DWORD)NULL,
      TEXT("button"),   // class
      TEXT("Comic"),   // caption
      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      150, 230,          // X & Y
      60, 20,          // width x height
      hwnd,
      (HMENU)IDC_FONT3_BUTTON,
      hProgramInstance,
      NULL);

      hwndOutputText = CreateWindowEx(
      (DWORD)NULL,
      TEXT("edit"),    // class
      TEXT(""),        // caption
      WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_READONLY | ES_MULTILINE,
      10, 10,         // X & Y
      270, 150,         // width x height
      hwnd,
      (HMENU)IDC_OUTPUT_TEXT,
      hProgramInstance,
      NULL);

      hwndInputText = CreateWindowEx(
      (DWORD)NULL,
      TEXT("edit"),    // class
      TEXT("Your text goes here..."),        // caption
      WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE,
      10, 170,         // X & Y
      200, 50,         // width x height
      hwnd,
      (HMENU)IDC_INPUT_TEXT,
      hProgramInstance,
      NULL);

      hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
      SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
      break;

    case WM_COMMAND:
      switch(LOWORD(wParam))
      {
        case IDC_UPDATE_BUTTON:
          iTextLength = SendMessage(hwndInputText, WM_GETTEXTLENGTH, 0, 0);
          szText = (char*)malloc(iTextLength+1);
          SendMessage(hwndInputText, WM_GETTEXT, iTextLength+1, (LPARAM)szText);
          SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)szText);
          free(szText);
          break;

        case IDC_CLEAR_BUTTON:
          SendMessage(hwndOutputText, WM_SETTEXT, 0, (LPARAM)"");
          break;

        case IDC_QUIT_BUTTON:
          if(MessageBox(NULL, TEXT("Are you sure you want to quit?"), TEXT(""), MB_YESNO) == IDYES) {
            SendMessage(hwnd, WM_DESTROY, 0, 0);
          };
          break;

        case IDC_FONT1_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Tahoma"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

        case IDC_FONT2_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

        case IDC_FONT3_BUTTON:
          hfFont = CreateFont(20,0,0,0,0,0,0,0,0,0,0,0,0,TEXT("Comic Sans MS"));
          SendMessage(hwndOutputText, WM_SETFONT, (WPARAM)hfFont, 1);
          break;

      }
      break;

    case WM_CTLCOLORBTN:
      hdc = (HDC)wParam;
      hwndBtn = (HWND)lParam;
      GetClientRect(hwndBtn, &rect);
      hdc = BeginPaint(hwndBtn, &ps);
      SetBkMode(hdc, TRANSPARENT);
      SetBkColor(hdc, RGB(200, 50, 50));
      SetTextColor(hdc, RGB(0, 0, 0));
      DrawText(hdc, "Quit", -1,  &rect, DT_CENTER);
      EndPaint(hwndBtn, &ps);
      return (LRESULT)CreateSolidBrush(RGB(200, 50, 50));
      break;

    case WM_CLOSE:
      iScreenW = GetSystemMetrics(SM_CXSCREEN);
      iScreenH = GetSystemMetrics(SM_CYSCREEN);

      GetWindowRect(hwnd, &rect);
      SetWindowPos(
        hwnd, 0,
        (iScreenW - rect.right) / 10 * (rand() % 11),
        (iScreenH - rect.bottom) / 10 * (rand() % 11),
        0, 0,
        SWP_NOZORDER|SWP_NOSIZE);

      MessageBox(NULL, TEXT("Gotcha!\nTo quit safely, click Quit button."), TEXT("HAHAHA!"), MB_OK);
      break;

    case WM_DESTROY:
      PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
      break;

    default:                      /* for messages that we don't deal with */
      return DefWindowProc (hwnd, message, wParam, lParam);
  }

  return 0;
}

