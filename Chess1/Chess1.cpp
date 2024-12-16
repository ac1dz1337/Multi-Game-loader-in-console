#include<iostream>
#include<windows.h>
#include<conio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <stdio.h>
/*
 * Import library
 */
#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <time.h>
#include <random>
const std::string colors[] = {
	"\033[31m", // Red
	"\033[33m", // Yellow
	"\033[32m", // Green
	"\033[36m", // Cyan
	"\033[34m", // Blue
	"\033[35m", // Magenta
	"\033[37m"  // White
};

 /*
  * MACRO
  */
#define WIDTH 40
#define HEIGHT 20
#define BODY '*'
#define APPLE 'O'
// Map Detail
const uint32_t ROWS = 28, COLS = 36;
const uint32_t size = ROWS * COLS;
#define cord(x,y) (x * COLS + y);

using std::cout;
using std::cin;
using std::vector;
using std::wstring;
using std::endl;
// Defining the screen size
int nScreenWidth = 80;
int nScreenHeight = 30;
wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char* pField = nullptr;
enum pieceName { BLANK = 0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 7 };
void gotoxy(int x, int y);
void set_data_highlight(int xx, int yy, int pp, bool uh);
void check_and_unhighlight();
bool end_game_or_not();
void tell_about_check(int, int);

enum class Direction
{
	up,
	right,
	down,
	left
};

// Each point is a part of the snake
struct Point
{
	int x;
	int y;
};

#pragma region GlobalVariable
// Create snake
vector<Point> snake = {
	Point{ WIDTH / 2 + 2, HEIGHT / 2 },
	Point{ WIDTH / 2 + 1, HEIGHT / 2 },
	Point{ WIDTH / 2, HEIGHT / 2 },
	Point{ WIDTH / 2 - 1, HEIGHT / 2 },
	Point{ WIDTH / 2 - 2, HEIGHT / 2 }
};
Direction direction = Direction::right;
Point apple;
int score = 0;
int speed = 300;
Point prevTail;
#pragma endregion




#pragma region Prototype
void drawSnakePart(Point);
void drawSnake();
void gotoxy(int, int);
void ShowConsoleCursor(bool);
void move();
void drawBox();
bool isHitWall();
bool isBiteItself();
void drawHeadnTail();
void genApple();
bool isAteApple();
void growing();
void displayScore();
void showEndMenu();
void startGame();
void resetSnake();
void showStartMenu();

#pragma endregion
#pragma region GameFunction
// Draw snakeboard with WIDTH and HEIGHT was set
void drawBox()
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	gotoxy(0, HEIGHT);
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(WIDTH, i);
		cout << '|';
	}
}

// Check if the snake hit the wall
bool isHitWall()
{
	return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}

// Generate apple on the board
void genApple()
{
	srand(time(0));
	int x = rand() % (WIDTH - 1) + 1;
	int y = rand() % (HEIGHT - 1) + 1;
	apple = {
		x,
		y,
	};
	gotoxy(x, y);
	cout << APPLE;
}

// Check if the snake ate apple
bool isAteApple()
{
	return snake[0].x == apple.x && snake[0].y == apple.y;
}

// Show score on right side of the board
void displayScore()
{
	gotoxy(WIDTH + 5, 2);
	cout << "Your score: " << score;
}

// Show menu at the end of the game
void showEndMenu()
{
	system("cls");
	gotoxy(0, 0);
	cout << "End game!" << endl;
	cout << "Your score: " << score << endl;
	cout << "Do you want to play again ([y]/[n]): ";
	char option;
	cin >> option;
	option = tolower(option);
	if (option == 'y')
	{
		resetSnake();
		startGame();
	}
	else if (option == 'n')
		exit(1);
}

void startGame()
{
	system("cls");
	ShowConsoleCursor(false);

	drawBox();
	drawSnake();
	genApple();
	displayScore();

	while (true)
	{
		if (_kbhit())
		{
			char ch = _getch();
			ch = tolower(ch);
			if (ch == 'a' && direction != Direction::right)
				direction = Direction::left;
			else if (ch == 'w' && direction != Direction::down)
				direction = Direction::up;
			else if (ch == 's' && direction != Direction::up)
				direction = Direction::down;
			else if (ch == 'd' && direction != Direction::left)
				direction = Direction::right;
			else if (ch == 'q') // Quit game
			{
				showEndMenu();
				break;
			}
		}
		move();
		drawHeadnTail();
		if (isAteApple())
		{
			score++;
			displayScore();
			growing();
			genApple();
		}
		if (isBiteItself())
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		if (isHitWall())
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		Sleep(speed);
	}
}
void beep() {
#ifdef _WIN32
	Beep(750, 300); // Frequency in Hz and duration in milliseconds for Windows
#else
	std::cout << "\a"; // 'Beep' sound in Console (cross-platform for many)
#endif
}
void resetSnake()
{
	score = 0;
	direction = Direction::right;
	snake = {
		Point{ WIDTH / 2 + 2, HEIGHT / 2 },
		Point{ WIDTH / 2 + 1, HEIGHT / 2 },
		Point{ WIDTH / 2, HEIGHT / 2 },
		Point{ WIDTH / 2 - 1, HEIGHT / 2 },
		Point{ WIDTH / 2 - 2, HEIGHT / 2 }
	};
}

void gotoxyx(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
// ANSI escape codes for colored text
const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string yellow = "\033[33m";
const std::string cyan = "\033[36m";
const std::string reset_color = "\033[0m";
// Show at the begining of the game
void showStartMenu()
{
	system("cls");
	cout << green << "Welcome to Snake Game!" << reset_color << endl;
	cout << yellow << "Options:" << reset_color << endl;
	cout << "1. Start" << endl;
	cout << "2. Quit" << endl;
	cout << "Your choice: ";

	int option;
	cin >> option;

	if (option == 1) {
		system("cls");
		cout << "Choose your level (1 - 5): ";
		int t;
		cin >> t;

		int speed = 600 - t * 100; // Calculate speed depending on level
		system("cls");
		cout << cyan << "Tip: While playing the game, you can press 'q' to quit" << reset_color << endl;
		gotoxy(0, 3);
		cout << green << "Ready!" << reset_color << endl; // Colored "Ready!"
		Sleep(1000);

		for (size_t i = 3; i > 0; i--) {
			gotoxy(0, 3);
			cout << yellow << i << "         " << reset_color; // Print countdown in yellow
			Sleep(1000);
		}

		gotoxy(0, 3);
		cout << green << "GO!" << reset_color << endl; // Colored "GO!"
		Sleep(1000);
		beep(); // Beep sound to mark the start of the game
		startGame();

		// startGame();
	}
	else if (option == 2) {
		beep(); // Beep sound before quitting
		cout << red << "Exiting the game..." << reset_color << endl; // Colored exit message
		exit(1);
	}
	else {
		beep(); // Beep sound for invalid choice
		cout << red << "Invalid option. Please try again." << reset_color << endl;
	}

	
}
#pragma endregion
#pragma region SnakeFunction
// Draw a part of snake
void drawSnakePart(Point p)
{
	gotoxyx(p.x, p.y);
	cout << BODY;
}

// Draw whole snake
void drawSnake()
{
	for (size_t i = 0; i < snake.size(); i++)
		drawSnakePart(snake[i]);
}

// move the snake
void move()
{
	prevTail = snake.back();
	for (size_t i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	if (direction == Direction::up)
		snake[0].y -= 1;
	else if (direction == Direction::down)
		snake[0].y += 1;
	else if (direction == Direction::left)
		snake[0].x -= 1;
	else if (direction == Direction::right)
		snake[0].x += 1;
}
void drawHeadnTail()
{
	gotoxy(snake[0].x, snake[0].y);
	cout << BODY;
	gotoxy(prevTail.x, prevTail.y);
	cout << ' '; // Clear the old tail
}

// Check if snake bite itself
bool isBiteItself()
{
	Point head = snake[0];
	for (size_t i = 1; i < snake.size(); i++)
		if (head.x == snake[i].x && head.y == snake[i].y)
			return true;
	return false;
}

// Growing snake when it ate an apple
void growing()
{
	snake.push_back(prevTail);
}
#pragma endregion


#pragma region ConsoleFunction
// Goto position (x, y)
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

// Set the visibility of cursor
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
#pragma endregion
/*
 * Let's the game start
 */
//Highlighted Steps Data Structure

// ANSI escape codes for colored text


int Rotate(int px, int py, int r) {

	int pi = 0;

	switch (r % 4) {
	case 0: // 0 de	grees			
		pi = py * 4 + px;
		break;
	case 1: // 90 degrees			
		pi = 12 + py - (px * 4);
		break;
	case 2: // 180 degrees			
		pi = 15 - (py * 4) - px;
		break;
	case 3: // 270 degrees			
		pi = 3 - py + (px * 4);
		break;
	}

	return pi;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {
	// The field is full so zero spaces
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++) {
			int pi = Rotate(px, py, nRotation);

			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

			// Check that test is in bounds. Note out of bounds does
			// not necessarily mean a fail, as the long vertical piece
			// can have cells that lie outside the boundary, so we'll
			// just ignore them
			if (nPosX + px >= 0 && nPosX + px < nFieldWidth) {
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight) {
					if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}

	return true;
}
void optionOne() {
	std::cout << "\n You selected Option 1: Hello World!" << std::endl;
}

void optionTwo() {
	std::cout << "\n You selected Option 2: Goodbye!" << std::endl;
}
void tetris()
{

	// Now, we create a screen buffer!

	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	// And then the tetrominos!
	tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++)
		for (int y = 0; y < nFieldHeight; y++)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	// Game Logic
	bool bKey[4];
	int nCurrentPiece = 0;
	int nCurrentRotation = 0;
	int nCurrentX = nFieldWidth / 2;
	int nCurrentY = 0;
	int nSpeed = 20;
	int nSpeedCount = 0;
	bool bForceDown = false;
	bool bRotateHold = true;
	int nPieceCount = 0;
	int nScore = 0;
	vector<int> vLines;
	bool bGameOver = false;

	while (!bGameOver) {
		Sleep(50);
		nSpeedCount++;
		bForceDown = (nSpeedCount == nSpeed);

		// No we define the user input!
		// controls are the arrow keys(down, left and right) and piece rotation it's with Z
		for (int k = 0; k < 4; k++)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

		// And here we have the game logic!

		// Handling player movement
		nCurrentX += (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) ? 1 : 0;
		nCurrentX -= (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) ? 1 : 0;
		nCurrentY += (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) ? 1 : 0;

		// Rotation without spinning
		if (bKey[3]) {
			nCurrentRotation += (bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) ? 1 : 0;
			bRotateHold = false;
		}
		else
			bRotateHold = true;

		// Force the piece down the playfield if it's time
		if (bForceDown) {
			// Update difficulty every 50 pieces
			nSpeedCount = 0;
			nPieceCount++;
			if (nPieceCount % 50 == 0)
				if (nSpeed >= 10) nSpeed--;

			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
				nCurrentY++; // It can, so do it!
			else {
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

				// Check for lines
				for (int py = 0; py < 4; py++)
					if (nCurrentY + py < nFieldHeight - 1) {
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine) {
							// Remove Line if it's complete
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							vLines.push_back(nCurrentY + py);
						}
					}

				nScore += 25;
				if (!vLines.empty())	nScore += (1 << vLines.size()) * 100;

				nCurrentX = nFieldWidth / 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = rand() % 7;

				// If the player reachs the field limits, game over!
				bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
			}
		}

		// Now we draw the field!

		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		// Drawing the pieces
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

		// Socring old school way
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

		// Animate Line Completion
		if (!vLines.empty()) {
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			Sleep(400);
			for (auto& v : vLines)
				for (int px = 1; px < nFieldWidth - 1; px++) {
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}

			vLines.clear();
		}

		// Display Frame by Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	// Now, we're done!
	CloseHandle(hConsole);
	cout << "Game Over!! Score:" << nScore << endl;
	system("pause");

}




void rainbowMenu() {
	std::cout << colors[0] << "\n============================" << reset_color << std::endl; // Red border
	std::cout << colors[1] << "         Main Menu         " << reset_color << std::endl; // Yellow title
	std::cout << colors[0] << "============================" << reset_color << std::endl; // Red border
	std::cout << colors[2] << "1. Option 1: Play Tetris" << reset_color << std::endl; // Green option
	std::cout << colors[3] << "2. Option 2: Play Chess" << reset_color << std::endl;  // Cyan option
	std::cout << colors[4] << "3. Option 3: Play Snake" << reset_color << std::endl; // Blue option
	std::cout << "Please enter your choice (1-3): "; // No color for the prompt
}
void rainbowText(const std::string& text) {
	// Print each letter of the text in different colors
	static int colorIndex = 0;
	for (const char& ch : text) {
		std::cout << colors[colorIndex % 7] << ch << reset_color; // Print letter with color
		colorIndex++;
	}
	std::cout << std::endl; // Move to the next line after printing the text
}

void rainbowLoadingScreen(const std::string& text) {
	std::cout << "Loading";
	for (int i = 0; i < 5; ++i) {
		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate loading
	}
	std::cout << std::endl;

	// Rainbow text for the loading message
	rainbowText(text);

	// More detailed loading information with rainbow effect
	std::string loadingLines[] = {
		"\n Initializing resources...",
		"\n Setting up game environment...",
		"\n Loading graphics assets...",
		"\n Preparing game logic...",
		"\n Finalizing setup..."

	};
	

	for (const auto& line : loadingLines) {
		rainbowText(line); // Print each loading line as rainbow text
		std::this_thread::sleep_for(std::chrono::milliseconds(800)); // Simulate each step loading time
	}
}
struct dataHighlight {
	int x_coordinate;
	int y_coordinate;
	int kept_piece;
	bool unhighlight_it;
};
//Game Board Class__________________________________________________
class CChessBoard {
public:
	bool change;        //for alternating rows
	//0-Orgument Constructor
	CChessBoard() {
		change = 0;
	}
	//Green Step
	void greenStep() {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);          //Green Colour Code = 2 
		for (int i = 0; i < 5; i++) {
			cout << "\xB0";
		}
	}
	//Gray Step
	void grayStep() {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 8);          //Gray Colour Code = 8
		for (int i = 0; i < 5; i++) {
			cout << "\xDB";
		}
	}
	//Printing Row starting with Green Step
	void printRowGreen() {
		for (int i = 0; i < 4; i++) {
			greenStep();
			grayStep();
		}
	}
	//Printing Row starting with Gray Step
	void printRowGray() {
		for (int i = 0; i < 4; i++) {
			grayStep();
			greenStep();
		}
	}
	//Printing Whole Board of the Game
	void printBoard() {
		change = 0;
		cout << "\t\t";
		for (int i = 0; i < 8; i++) {
			if (change == 0) {
				printRowGreen(); cout << "\n"; cout << "\t\t";
				printRowGreen(); cout << "\n"; cout << "\t\t";   //Print 3 rows of green
				printRowGreen(); cout << "\n"; cout << "\t\t";
				change = 1;
			}
			else {
				printRowGray(); cout << "\n"; cout << "\t\t";
				printRowGray(); cout << "\n"; cout << "\t\t";
				printRowGray(); cout << "\n"; cout << "\t\t";
				change = 0;
			}
		}
	}
	//Printing X-Axis Label
	void PrintX_Label() {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);          //Red Colour Code = 12
		int cnt = 1;
		for (int i = 18; i < 58; i += 5) {
			gotoxy(i, 24);
			cout << cnt;
			cnt++;
		}
	}
	//Printing Y-Axis Label
	void PrintY_Label() {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);          //Red Colour Code = 12
		int cnt = 1;
		for (int i = 22; i >= 1; i -= 3) {
			gotoxy(15, i);
			cout << cnt;
			cnt++;
		}
	}
	//Move To Function
	void MoveTo(int numx, int numy) {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);          //Green Colour Code = 2 
		int X = (numx * 5) + 16 - 3;
		int Y = 24 - (numy * 3) + 1;
		gotoxy(X, Y);
	}
	//Move Function
	void Move(char chx, char chy) {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 12);          //Red Colour Code = 12 
		int numx = chx - '0'; int numy = chy - '0';
		int X = (numx * 5) + 16 - 3;
		int Y = 24 - (numy * 3) + 1;
		gotoxy(X, Y);
		cout << "\xDB";
	}
	//MoveInt Function
	void MoveInt(int numx, int numy, int color) {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);          //Green Colour Code = 2 
		int X = (numx * 5) + 16 - 3;
		int Y = 24 - (numy * 3) + 1;
		gotoxy(X, Y);
		cout << "\xDB";
	}
};
//Piece Class__________________________________________________
class CPiece {
public:
	//Data Members
	bool is_empty;
	bool is_highlight;
	int which_piece;
	bool kill_him;
	int square_x, square_y;
	//Constructor
	CPiece() {
		square_x = 0;
		square_y = 0;
		is_empty = 1;
		is_highlight = 0;
		which_piece = BLANK;
		kill_him = 0;
	}
	//Set This Square Function
	void setSquare(int sx, int sy, bool isEmp, bool isHigh, int which, bool kill) {
		square_x = sx;
		square_y = sy;
		is_empty = isEmp;
		is_highlight = isHigh;
		which_piece = which;
		kill_him = kill;
	}
	//Select Piece Function
	bool selectPiece() {
		if (is_empty == 0) {
			return 1;
		}
		else return 0;
	}
	//Select New Position Function
	bool selectNewPosition() {
		if (is_highlight == 1) {
			return 1;
		}
		else return 0;
	}
	//Print Blank
	void printBlank(int cx, int cy) {
		if (cx % 2 == 0 && cy % 2 == 0) {            //If x is even, y is evem
			HANDLE hConsole;                  //Print Gray Step
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 8);          //Gray Colour Code = 8 
			int X = (cx * 5) + 16 - 3;
			int Y = 24 - (cy * 3) + 1;
			gotoxy(X, Y);
			cout << "\xDB\xDB";
		}
		else if (cx % 2 != 0 && cy % 2 != 0) {       //If x is odd, y is odd
			HANDLE hConsole;                  //Print Gray Step
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 8);          //Gray Colour Code = 8 
			int X = (cx * 5) + 16 - 3;
			int Y = 24 - (cy * 3) + 1;
			gotoxy(X, Y);
			cout << "\xDB\xDB";
		}
		else if (cx % 2 != 0 && cy % 2 == 0) {       //If x is odd, y is even
			HANDLE hConsole;                  //Print Green Step
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 2);          //Green Colour Code = 2 
			int X = (cx * 5) + 16 - 3;
			int Y = 24 - (cy * 3) + 1;
			gotoxy(X, Y);
			cout << "\xB0\xB0";
		}
		else if (cx % 2 == 0 && cy % 2 != 0) {       //If x is even, y is odd
			HANDLE hConsole;                  //Print Green Step
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 2);          //Green Colour Code = 2 
			int X = (cx * 5) + 16 - 3;
			int Y = 24 - (cy * 3) + 1;
			gotoxy(X, Y);
			cout << "\xB0\xB0";
		}
	}
	//Print Piece
	void printPiece(int cx, int cy, int color, int pieceNum) {
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		gotoxy(X, Y);
		if (pieceNum == PAWN) {
			cout << "\xDB";
		}
		else if (pieceNum == ROOK) {
			cout << "[]";
		}
		else if (pieceNum == KNIGHT) {
			cout << "\x15";
		}
		else if (pieceNum == BISHOP) {
			cout << "\x0F";
		}
		else if (pieceNum == QUEEN) {
			cout << "\x03";
		}
		else if (pieceNum == KING) {
			cout << "\x05";
		}
	}
	//Highlighted Pink Step
	void pinkHighlightStep(int cx, int cy, int pieceNum);
	void highlightPiece(int cx, int cy, int thisPiece);
	void unhighlightStep(int cx, int cy);
};
//Global Game Board
CPiece gameSquares[9][9];
//Global Highlight Steps Data Container
struct dataHighlight data[9][9];
//Game Play Class__________________________________________________
class CGamePlay {
public:
	//Data Members
	CChessBoard board;
	//Setting Game Board Function
	void settingGameBoard() {
		board.printBoard();
		board.PrintX_Label();
		board.PrintY_Label();
		//Player Pieces_________
		//Pawns for Player
		for (int i = 1; i < 9; i++) {
			gameSquares[i][2].printPiece(i, 2, 10, PAWN);
			gameSquares[i][2].setSquare(i, 2, 0, 0, PAWN, 0);
		}
		//Rooks for Players
		gameSquares[1][1].printPiece(1, 1, 10, ROOK);
		gameSquares[1][1].setSquare(1, 1, 0, 0, ROOK, 0);
		gameSquares[8][1].printPiece(8, 1, 10, ROOK);
		gameSquares[8][1].setSquare(8, 1, 0, 0, ROOK, 0);
		//Knights for Players
		gameSquares[2][1].printPiece(2, 1, 10, KNIGHT);
		gameSquares[2][1].setSquare(2, 1, 0, 0, KNIGHT, 0);
		gameSquares[7][1].printPiece(7, 1, 10, KNIGHT);
		gameSquares[7][1].setSquare(7, 1, 0, 0, KNIGHT, 0);
		//Bishops for Players
		gameSquares[3][1].printPiece(3, 1, 10, BISHOP);
		gameSquares[3][1].setSquare(3, 1, 0, 0, BISHOP, 0);
		gameSquares[6][1].printPiece(6, 1, 10, BISHOP);
		gameSquares[6][1].setSquare(6, 1, 0, 0, BISHOP, 0);
		//Queen & King for Players
		gameSquares[5][1].printPiece(5, 1, 10, KING);
		gameSquares[5][1].setSquare(5, 1, 0, 0, KING, 0);
		gameSquares[4][1].printPiece(4, 1, 10, QUEEN);
		gameSquares[4][1].setSquare(4, 1, 0, 0, QUEEN, 0);
		//Computer Pieces_________
		//Pawns for Computer
		for (int i = 1; i < 9; i++) {
			gameSquares[i][7].printPiece(i, 7, 15, PAWN);
			gameSquares[i][7].setSquare(i, 7, 0, 0, PAWN, 1);
		}
		//Rooks for Computer
		gameSquares[1][8].printPiece(1, 8, 15, ROOK);
		gameSquares[1][8].setSquare(1, 8, 0, 0, ROOK, 1);
		gameSquares[8][8].printPiece(8, 8, 15, ROOK);
		gameSquares[8][8].setSquare(8, 8, 0, 0, ROOK, 1);
		//Knights for Computer
		gameSquares[2][8].printPiece(2, 8, 15, KNIGHT);
		gameSquares[2][8].setSquare(2, 8, 0, 0, KNIGHT, 1);
		gameSquares[7][8].printPiece(7, 8, 15, KNIGHT);
		gameSquares[7][8].setSquare(7, 8, 0, 0, KNIGHT, 1);
		//Bishops for Computer
		gameSquares[3][8].printPiece(3, 8, 15, BISHOP);
		gameSquares[3][8].setSquare(3, 8, 0, 0, BISHOP, 1);
		gameSquares[6][8].printPiece(6, 8, 15, BISHOP);
		gameSquares[6][8].setSquare(6, 8, 0, 0, BISHOP, 1);
		//Queen & King for Computer
		gameSquares[4][8].printPiece(4, 8, 15, KING);
		gameSquares[4][8].setSquare(4, 8, 0, 0, KING, 1);
		gameSquares[5][8].printPiece(5, 8, 15, QUEEN);
		gameSquares[5][8].setSquare(5, 8, 0, 0, QUEEN, 1);
	}
	//Remove Piece Function
	void removePiece(int cx, int cy) {
		gameSquares[cx][cy].setSquare(cx, cy, 1, 0, 0, 0);
		gameSquares[cx][cy].printBlank(cx, cy);
	}
};
//Main Function__________________________________________________
int main() {

	int choice;

	while (true) {
		rainbowMenu(); // Print the rainbow menu

		std::cin >> choice;

		switch (choice) {
		case 1:
			beep();
			system("cls");
			rainbowLoadingScreen("Loading Tetris...");  // Rainbow loading text
			Sleep(100);
			system("cls");
			tetris();
			break;
		case 2:
			beep();
			Sleep(100);
			system("cls");
			rainbowLoadingScreen("Loading Chess...");   // Rainbow loading text
			system("cls"); // Clear the console for Windows
			goto chess;
			break;
		case 3:
			showStartMenu();
			return 0;
		
		default:
			std::cout << "Invalid choice. Please try again." << std::endl;
		}
	}

	

	chess:
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CGamePlay game1;
	game1.settingGameBoard();
	SetConsoleTextAttribute(hConsole, 7);          //Light White Colour Code = 7
	char chx; char chy;
	int coord_x, coord_y, X, Y;
	int pieceColor;
	bool whose_turn = 0;
	gotoxy(0, 10);
	cout << "Green to Move!";
	while (true) {
	SELECT_PIECE:
		gotoxy(0, 26);
		SetConsoleTextAttribute(hConsole, 7);          //Light White Colour Code = 7
		cout << "Which Piece (in form of XY, for e.g. 62): ";
		gotoxy(42, 26);
		chx = _getch(); chy = _getch();
		//cin>>chx; cin>>chy;
		coord_x = chx - '0'; coord_y = chy - '0';
		if (gameSquares[coord_x][coord_y].kill_him != whose_turn) { goto WRONG_PIECE; }
		else {
			if (gameSquares[coord_x][coord_y].selectPiece()) {
				gameSquares[coord_x][coord_y].highlightPiece(coord_x, coord_y, gameSquares[coord_x][coord_y].which_piece);
			NEW_MOVE:
				if (gameSquares[coord_x][coord_y].kill_him == 1) { pieceColor = 15; }
				else { pieceColor = 10; }
				gotoxy(0, 25);
				SetConsoleTextAttribute(hConsole, 14);          //Yellow Colour Code = 14
				cout << "Where to Move (New Coordinates):  ";
				gotoxy(33, 25);
				//cin>>chx; cin>>chy;
				chx = _getch(); chy = _getch();
				X = chx - '0';
				Y = chy - '0';
				if (X == 0 && Y == 0) {
					check_and_unhighlight();
					gameSquares[coord_x][coord_y].printPiece(coord_x, coord_y, pieceColor, gameSquares[coord_x][coord_y].which_piece);
					whose_turn = gameSquares[coord_x][coord_y].kill_him;
					goto SELECT_PIECE;
				}
				if (gameSquares[X][Y].is_highlight == 1) {
					check_and_unhighlight();
					game1.removePiece(X, Y);
					if (gameSquares[coord_x][coord_y].which_piece == PAWN && gameSquares[coord_x][coord_y].kill_him == 0 && Y == 8) {
						if (X == 1 || X == 8) { gameSquares[coord_x][coord_y].which_piece = ROOK; }
						else if (X == 2 || X == 7) { gameSquares[coord_x][coord_y].which_piece = KNIGHT; }
						else if (X == 3 || X == 6) { gameSquares[coord_x][coord_y].which_piece = BISHOP; }
						else if (X == 4 || X == 5) { gameSquares[coord_x][coord_y].which_piece = QUEEN; }
					}
					if (gameSquares[coord_x][coord_y].which_piece == PAWN && gameSquares[coord_x][coord_y].kill_him == 1 && Y == 1) {
						if (X == 1 || X == 8) { gameSquares[coord_x][coord_y].which_piece = ROOK; }
						else if (X == 2 || X == 7) { gameSquares[coord_x][coord_y].which_piece = KNIGHT; }
						else if (X == 3 || X == 6) { gameSquares[coord_x][coord_y].which_piece = BISHOP; }
						else if (X == 4 || X == 5) { gameSquares[coord_x][coord_y].which_piece = QUEEN; }
					}
					gameSquares[coord_x][coord_y].printPiece(X, Y, pieceColor, gameSquares[coord_x][coord_y].which_piece);
					gameSquares[X][Y].setSquare(X, Y, 0, 0, gameSquares[coord_x][coord_y].which_piece, gameSquares[coord_x][coord_y].kill_him);
					game1.removePiece(coord_x, coord_y);
					data[X][Y].unhighlight_it = 0;
					gotoxy(5, 15);
					SetConsoleTextAttribute(hConsole, 0);          //RED Colour Code = 207
					cout << "      ";
					tell_about_check(X, Y);
				}
				else {
					gotoxy(0, 27);
					SetConsoleTextAttribute(hConsole, 12);          //Red Colour Code = 12
					cout << "Invalid Move!";
					goto NEW_MOVE;
				}
				if (whose_turn == 0) {
					whose_turn = 1;
					gotoxy(0, 10);
					cout << "Green to Move!";
				}
				else {
					whose_turn = 0;
					gotoxy(0, 10);
					cout << "White to Move!";
				}
				gotoxy(0, 27);
				SetConsoleTextAttribute(hConsole, 0);          //Red Colour Code = 12
				cout << "                       ";
			}
			else {
			WRONG_PIECE:
				gotoxy(0, 27);
				SetConsoleTextAttribute(hConsole, 12);          //Red Colour Code = 12
				cout << "Wrong Piece Selected!";
			}
		}
		if (end_game_or_not()) { break; }
		if (whose_turn == 0) {
			SetConsoleTextAttribute(hConsole, 10);          //Green Colour Code = 10
			gotoxy(0, 10);
			cout << "Green to Move!";
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);          //White Colour Code = 15
			gotoxy(0, 10);
			cout << "White to Move!";
		}
	}
	gotoxy(0, 25);
	cout << "Game Over!";
	system("Pause");
}
//gotoxy Function__________________________________________________
//Set Data Function for dataHighlight stru//////cture
void set_data_highlight(int xx, int yy, int pp, bool uh) {
	data[xx][yy].x_coordinate = xx;
	data[xx][yy].y_coordinate = yy;
	data[xx][yy].kept_piece = pp;
	data[xx][yy].unhighlight_it = uh;
}
//Check And Unhighlight the Highlighted Steps
void check_and_unhighlight() {
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (data[i][j].unhighlight_it == 1) {
				gameSquares[i][j].unhighlightStep(i, j);
				data[i][j].unhighlight_it = 0;
			}
		}
	}
}
//To Check whether Game is ended or not
bool end_game_or_not() {
	int num = 0;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (gameSquares[i][j].which_piece == KING) {
				num++;
			}
		}
	}
	if (num == 2) {
		return 0;
	}
	else return 1;
}
//Tell About the Check
/*void tell_about_check (int xx, int yy) {
	if ( gameSquares[xx][yy].which_piece == KING && gameSquares[xx][yy].kill_him == 1 && gameSquares[xx][yy].is_highlight == 1) {
		gotoxy(5,15);
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
		cout<<"Check";
	}
}*/
//Highlight Piece Function_________________________________________
void CPiece::highlightPiece(int cx, int cy, int thisPiece) {
	//_____________________PAWN STEPS______________________//
	if (thisPiece == PAWN) {
		if (gameSquares[cx][cy].kill_him == 0) {	//If it is Player's PAWN
			if (cy == 2) {                  //If this is first action of pawn
				printPiece(cx, cy, 14, PAWN);
				for (int i = cy, j = 0; j < 2; i++, j++) {    //j<2 for 2 steps
					if (gameSquares[cx][i + 1].is_empty == 0 && gameSquares[cx][i + 1].kill_him == 0) { break; }
					else if (gameSquares[cx][i + 1].is_empty == 0 && gameSquares[cx][i + 1].kill_him == 1) { break; }
					else {
						pinkHighlightStep(cx, i, PAWN);
						gameSquares[cx][i + 1].setSquare(cx, i, 1, 1, BLANK, 0);
						set_data_highlight(cx, i + 1, BLANK, 1);
					}
				}
				if (gameSquares[cx + 1][cy + 1].is_empty == 0 && gameSquares[cx + 1][cy + 1].kill_him == 1) {
					pinkHighlightStep(cx + 1, cy, gameSquares[cx + 1][cy + 1].which_piece);
					gameSquares[cx + 1][cy + 1].setSquare(cx + 1, cy + 1, 0, 1, gameSquares[cx + 1][cy + 1].which_piece, 1);
					set_data_highlight(cx + 1, cy + 1, gameSquares[cx + 1][cy + 1].which_piece, 1);
					gameSquares[cx + 1][cy + 1].printPiece(cx + 1, cy + 1, 11, gameSquares[cx + 1][cy + 1].which_piece);
					//tell_about_check(cx+1,cy+1);
				}
				if (gameSquares[cx - 1][cy + 1].is_empty == 0 && gameSquares[cx - 1][cy + 1].kill_him == 1) {
					pinkHighlightStep(cx - 1, cy, gameSquares[cx - 1][cy + 1].which_piece);
					gameSquares[cx - 1][cy + 1].setSquare(cx - 1, cy + 1, 0, 1, gameSquares[cx - 1][cy + 1].which_piece, 1);
					set_data_highlight(cx - 1, cy + 1, gameSquares[cx - 1][cy + 1].which_piece, 1);
					gameSquares[cx - 1][cy + 1].printPiece(cx - 1, cy + 1, 11, gameSquares[cx - 1][cy + 1].which_piece);
					//tell_about_check(cx+1,cy+1);
				}
			}
			else {				//Not First Move
				printPiece(cx, cy, 14, PAWN);
				if (gameSquares[cx][cy + 1].is_empty == 0 && gameSquares[cx][cy + 1].kill_him == 0) {}
				else if (gameSquares[cx][cy + 1].is_empty == 0 && gameSquares[cx][cy + 1].kill_him == 1) {}
				else {
					pinkHighlightStep(cx, cy, BLANK);
					gameSquares[cx][cy + 1].setSquare(cx, cy + 1, 1, 1, BLANK, 0);
					set_data_highlight(cx, cy + 1, BLANK, 1);
				}
				if (gameSquares[cx + 1][cy + 1].is_empty == 0 && gameSquares[cx + 1][cy + 1].kill_him == 1) {
					pinkHighlightStep(cx + 1, cy, gameSquares[cx + 1][cy + 1].which_piece);
					gameSquares[cx + 1][cy + 1].setSquare(cx + 1, cy + 1, 0, 1, gameSquares[cx + 1][cy + 1].which_piece, 1);
					set_data_highlight(cx + 1, cy + 1, gameSquares[cx + 1][cy + 1].which_piece, 1);
					gameSquares[cx + 1][cy + 1].printPiece(cx + 1, cy + 1, 11, gameSquares[cx + 1][cy + 1].which_piece);
				}
				if (gameSquares[cx - 1][cy + 1].is_empty == 0 && gameSquares[cx - 1][cy + 1].kill_him == 1) {
					pinkHighlightStep(cx - 1, cy, gameSquares[cx - 1][cy + 1].which_piece);
					gameSquares[cx - 1][cy + 1].setSquare(cx - 1, cy + 1, 0, 1, gameSquares[cx - 1][cy + 1].which_piece, 1);
					set_data_highlight(cx - 1, cy + 1, gameSquares[cx - 1][cy + 1].which_piece, 1);
					gameSquares[cx - 1][cy + 1].printPiece(cx - 1, cy + 1, 11, gameSquares[cx - 1][cy + 1].which_piece);
				}
			}
		}

		else {	//If it is Computer's PAWN
			if (cy == 7) {                  //If this is first action of pawn
				printPiece(cx, cy, 14, PAWN);
				for (int i = cy - 1, j = 0; j < 2; i--, j++) {    //j<2 for 2 steps
					if (gameSquares[cx][i].is_empty == 0 && gameSquares[cx][i].kill_him == 0) { break; }
					else if (gameSquares[cx][i].is_empty == 0 && gameSquares[cx][i].kill_him == 1) { break; }
					else {
						pinkHighlightStep(cx, i - 1, PAWN);
						gameSquares[cx][i].setSquare(cx, i, 1, 1, BLANK, 0);
						set_data_highlight(cx, i, BLANK, 1);
					}
				}
				if (gameSquares[cx + 1][cy - 1].is_empty == 0 && gameSquares[cx + 1][cy - 1].kill_him == 0 && cx != 8) {
					pinkHighlightStep(cx + 1, cy - 2, gameSquares[cx + 1][cy - 1].which_piece);
					gameSquares[cx + 1][cy - 1].setSquare(cx + 1, cy - 1, 0, 1, gameSquares[cx + 1][cy - 1].which_piece, 0);
					set_data_highlight(cx + 1, cy - 1, gameSquares[cx + 1][cy - 1].which_piece, 1);
					gameSquares[cx + 1][cy - 1].printPiece(cx + 1, cy - 1, 11, gameSquares[cx + 1][cy - 1].which_piece);
				}
				if (gameSquares[cx - 1][cy - 1].is_empty == 0 && gameSquares[cx - 1][cy - 1].kill_him == 0 && cx != 1) {
					pinkHighlightStep(cx - 1, cy - 2, gameSquares[cx - 1][cy - 1].which_piece);
					gameSquares[cx - 1][cy - 1].setSquare(cx - 1, cy - 1, 0, 1, gameSquares[cx - 1][cy - 1].which_piece, 0);
					set_data_highlight(cx - 1, cy - 1, gameSquares[cx - 1][cy - 1].which_piece, 1);
					gameSquares[cx - 1][cy - 1].printPiece(cx - 1, cy - 1, 11, gameSquares[cx - 1][cy - 1].which_piece);
				}
			}
			else {
				printPiece(cx, cy, 14, PAWN);
				if (gameSquares[cx][cy - 1].is_empty == 0 && gameSquares[cx][cy - 1].kill_him == 1) {}
				if (gameSquares[cx][cy - 1].is_empty == 0 && gameSquares[cx][cy - 1].kill_him == 0) {}
				else {
					pinkHighlightStep(cx, cy - 2, PAWN);
					gameSquares[cx][cy - 1].setSquare(cx, cy - 1, 1, 1, BLANK, 0);
					set_data_highlight(cx, cy - 1, BLANK, 1);
				}
				if (gameSquares[cx + 1][cy - 1].is_empty == 0 && gameSquares[cx + 1][cy - 1].kill_him == 0 && cx != 8) {
					pinkHighlightStep(cx + 1, cy - 2, gameSquares[cx + 1][cy - 1].which_piece);
					gameSquares[cx + 1][cy - 1].setSquare(cx + 1, cy - 1, 0, 1, gameSquares[cx + 1][cy - 1].which_piece, gameSquares[cx + 1][cy - 1].kill_him);
					set_data_highlight(cx + 1, cy - 1, gameSquares[cx + 1][cy - 1].which_piece, 1);
					gameSquares[cx + 1][cy - 1].printPiece(cx + 1, cy - 1, 11, gameSquares[cx + 1][cy - 1].which_piece);
				}
				if (gameSquares[cx - 1][cy - 1].is_empty == 0 && gameSquares[cx - 1][cy - 1].kill_him == 0 && cx != 1) {
					pinkHighlightStep(cx - 1, cy - 2, gameSquares[cx - 1][cy - 1].which_piece);
					gameSquares[cx - 1][cy - 1].setSquare(cx - 1, cy - 1, 0, 1, gameSquares[cx - 1][cy - 1].which_piece, gameSquares[cx + 1][cy - 1].kill_him);
					set_data_highlight(cx - 1, cy - 1, gameSquares[cx - 1][cy - 1].which_piece, 1);
					gameSquares[cx - 1][cy - 1].printPiece(cx - 1, cy - 1, 11, gameSquares[cx - 1][cy - 1].which_piece);
				}
			}
		}
	}
	//_____________________KNIGHT STEPS______________________//
	else if (thisPiece == KNIGHT) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx, cy, 14, KNIGHT);
			int temp_x; int temp_y;
			//First Step (X-1,Y+2)
			temp_x = cx - 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Second Step (X-1,Y-2)
			temp_x = cx - 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Third Step (X+1,Y+2)
			temp_x = cx + 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Fourth Step (X+1,Y-2)
			temp_x = cx + 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Fifth Step (X-2,Y-1)
			temp_x = cx - 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Sixth Step (X-2,Y+1)
			temp_x = cx - 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Seventh Step (X+2,Y-1)
			temp_x = cx + 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Eighth Step (X+2,Y+1)
			temp_x = cx + 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
		}
		else {
			printPiece(cx, cy, 14, KNIGHT);
			int temp_x; int temp_y;
			//First Step (X-1,Y+2)
			temp_x = cx - 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Second Step (X-1,Y-2)
			temp_x = cx - 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Third Step (X+1,Y+2)
			temp_x = cx + 1;
			temp_y = cy + 1;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Fourth Step (X+1,Y-2)
			temp_x = cx + 1;
			temp_y = cy - 3;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Fifth Step (X-2,Y-1)
			temp_x = cx - 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Sixth Step (X-2,Y+1)
			temp_x = cx - 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Seventh Step (X+2,Y-1)
			temp_x = cx + 2;
			temp_y = cy - 2;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Eighth Step (X+2,Y+1)
			temp_x = cx + 2;
			temp_y = cy + 0;
			if (temp_x < 1 || temp_x > 8 || temp_y < 0 || temp_y >= 8) {}
			else {
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
		}
	}
	//_____________________BISHOP STEPS______________________//
	else if (thisPiece == BISHOP) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx, cy, 14, BISHOP);
			int temp_x, temp_y;
			//1st Quadrant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				for (int i = cx + 1, j = cy; /*<No Condition>*/; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//2nd Quadrant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) {}
			else {
				for (int i = cx - 1, j = cy; /*<No Condition>*/; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//3rd Quadrant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) {}
			else {
				for (int i = cx - 1, j = cy - 2; /*<No Condition>*/; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//4th Quadrant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) {}
			else {
				for (int i = cx + 1, j = cy - 2; /*<No Condition>*/; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
		}
		else {					//COMPUTER STEPS
			printPiece(cx, cy, 14, BISHOP);
			int temp_x, temp_y;
			//1st Quadrant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				for (int i = cx + 1, j = cy; /*<No Condition>*/; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//2nd Quadrant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) {}
			else {
				for (int i = cx - 1, j = cy; /*<No Condition>*/; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//3rd Quadrant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) {}
			else {
				for (int i = cx - 1, j = cy - 2; /*<No Condition>*/; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//4th Quadrant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) {}
			else {
				for (int i = cx + 1, j = cy - 2; /*<No Condition>*/; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
		}
	}
	//_____________________ROOK STEPS______________________//
	else if (thisPiece == ROOK)
	{
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx, cy, 14, ROOK);
			int temp_x, temp_y;
			//1st loop Increasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x >= 8) {}
			else {
				for (int i = cx + 1; /*<No Condition>*/; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//2nd loop Decreasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x < 1) {}
			else {
				for (int i = cx - 1; /*<No Condition>*/; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//3rd loop Constant x, Increasing y
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				for (int i = cy; /*<No Condition>*/; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
			//4th loop Constant x, Decreasing y
			temp_x = cx; temp_y = cy;
			if (temp_y < 0) {}
			else {
				for (int i = cy - 2; /*<No Condition>*/; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
		}
		else {					//COMPUTER STEPS
			printPiece(cx, cy, 14, ROOK);
			int temp_x, temp_y;
			//1st loop Increasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x >= 8) {}
			else {
				for (int i = cx + 1; /*<No Condition>*/; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//2nd loop Decreasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x < 1) {}
			else {
				for (int i = cx - 1; /*<No Condition>*/; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//3rd loop Constant x, Increasing y
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				for (int i = cy; /*<No Condition>*/; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
			//4th loop Constant x, Decreasing y
			temp_x = cx; temp_y = cy;
			if (temp_y < 0) {}
			else {
				for (int i = cy - 2; /*<No Condition>*/; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
		}
	}
	//___________________QUEEN STEPS______________________//
	else if (thisPiece == QUEEN) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx, cy, 14, QUEEN);
			int temp_x, temp_y;
			//1st Quadrant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				for (int i = cx + 1, j = cy; /*<No Condition>*/; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//2nd Quadrant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) {}
			else {
				for (int i = cx - 1, j = cy; /*<No Condition>*/; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//3rd Quadrant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) {}
			else {
				for (int i = cx - 1, j = cy - 2; /*<No Condition>*/; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//4th Quadrant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) {}
			else {
				for (int i = cx + 1, j = cy - 2; /*<No Condition>*/; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			////////////////////////////////////////
			//1st loop Increasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x >= 8) {}
			else {
				for (int i = cx + 1; /*<No Condition>*/; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//2nd loop Decreasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x < 1) {}
			else {
				for (int i = cx - 1; /*<No Condition>*/; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//3rd loop Constant x, Increasing y
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				for (int i = cy; /*<No Condition>*/; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
			//4th loop Constant x, Decreasing y
			temp_x = cx; temp_y = cy;
			if (temp_y < 0) {}
			else {
				for (int i = cy - 2; /*<No Condition>*/; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
		}
		else {				//COMPUTER STEPS
			printPiece(cx, cy, 14, QUEEN);
			int temp_x, temp_y;
			//1st Quadrant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				for (int i = cx + 1, j = cy; /*<No Condition>*/; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//2nd Quadrant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) {}
			else {
				for (int i = cx - 1, j = cy; /*<No Condition>*/; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//3rd Quadrant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) {}
			else {
				for (int i = cx - 1, j = cy - 2; /*<No Condition>*/; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			//4th Quadrant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) {}
			else {
				for (int i = cx + 1, j = cy - 2; /*<No Condition>*/; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) {
						pinkHighlightStep(i, j, gameSquares[i][j + 1].which_piece);
						gameSquares[i][j + 1].setSquare(i, j + 1, 0, 1, gameSquares[i][j + 1].which_piece, gameSquares[i][j + 1].kill_him);
						set_data_highlight(i, j + 1, gameSquares[i][j + 1].which_piece, 1);
						gameSquares[i][j + 1].printPiece(i, j + 1, 11, gameSquares[i][j + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, j, BLANK);
					gameSquares[i][j + 1].setSquare(i, j + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, j + 1, BLANK, 1);
				}
			}
			////////////////////////////////////////
			//1st loop Increasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x >= 8) {}
			else {
				for (int i = cx + 1; /*<No Condition>*/; i++) {
					if (i > 8) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//2nd loop Decreasing x, Constanat y
			temp_x = cx; temp_y = cy - 1;
			if (temp_x < 1) {}
			else {
				for (int i = cx - 1; /*<No Condition>*/; i--) {
					if (i < 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 1) { break; }
					if (gameSquares[i][temp_y + 1].is_empty == 0 && gameSquares[i][temp_y + 1].kill_him == 0) {
						pinkHighlightStep(i, temp_y, gameSquares[i][temp_y + 1].which_piece);
						gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 0, 1, gameSquares[i][temp_y + 1].which_piece, gameSquares[i][temp_y + 1].kill_him);
						set_data_highlight(i, temp_y + 1, gameSquares[i][temp_y + 1].which_piece, 1);
						gameSquares[i][temp_y + 1].printPiece(i, temp_y + 1, 11, gameSquares[i][temp_y + 1].which_piece);
						break;
					}
					pinkHighlightStep(i, temp_y, BLANK);
					gameSquares[i][temp_y + 1].setSquare(i, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(i, temp_y + 1, BLANK, 1);
				}
			}
			//3rd loop Constant x, Increasing y
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				for (int i = cy; /*<No Condition>*/; i++) {
					if (i >= 8) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
			//4th loop Constant x, Decreasing y
			temp_x = cx; temp_y = cy;
			if (temp_y < 0) {}
			else {
				for (int i = cy - 2; /*<No Condition>*/; i--) {
					if (i < 0) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 1) { break; }
					if (gameSquares[temp_x][i + 1].is_empty == 0 && gameSquares[temp_x][i + 1].kill_him == 0) {
						pinkHighlightStep(temp_x, i, gameSquares[temp_x][i + 1].which_piece);
						gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 0, 1, gameSquares[temp_x][i + 1].which_piece, gameSquares[temp_x][i + 1].kill_him);
						set_data_highlight(temp_x, i + 1, gameSquares[temp_x][i + 1].which_piece, 1);
						gameSquares[temp_x][i + 1].printPiece(temp_x, i + 1, 11, gameSquares[temp_x][i + 1].which_piece);
						break;
					}
					pinkHighlightStep(temp_x, i, BLANK);
					gameSquares[temp_x][i + 1].setSquare(temp_x, i + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, i + 1, BLANK, 1);
				}
			}
		}
	}
	//_____________________KING STEPS______________________//
	else if (thisPiece == KING) {
		if (gameSquares[cx][cy].kill_him == 0) {
			printPiece(cx, cy, 14, KING);
			int temp_x, temp_y;
			//Right-Upper Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				temp_x = cx + 1; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left-Upper Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y >= 8) {}
			else {
				temp_x = cx - 1; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Right-Lower Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y <= 1) {}
			else {
				temp_x = cx + 1; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left-Lower Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y <= 1) {}
			else {
				temp_x = cx - 1; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Right Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8) {}
			else {
				temp_x = cx + 1; temp_y = cy - 1;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1) {}
			else {
				temp_x = cx - 1; temp_y = cy - 1;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Up Step
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				temp_x = cx; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Down Step
			temp_x = cx; temp_y = cy;
			if (temp_y <= 1) {}
			else {
				temp_x = cx; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
		}
		else if (gameSquares[cx][cy].kill_him == 1) {
			printPiece(cx, cy, 14, KING);
			int temp_x, temp_y;
			//Right-Upper Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				temp_x = cx + 1; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left-Upper Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y >= 8) {}
			else {
				temp_x = cx - 1; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Right-Lower Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y <= 1) {}
			else {
				temp_x = cx + 1; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left-Lower Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1 || temp_y <= 1) {}
			else {
				temp_x = cx - 1; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Right Step
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8) {}
			else {
				temp_x = cx + 1; temp_y = cy - 1;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Left Step
			temp_x = cx; temp_y = cy;
			if (temp_x <= 1) {}
			else {
				temp_x = cx - 1; temp_y = cy - 1;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Up Step
			temp_x = cx; temp_y = cy;
			if (temp_y >= 8) {}
			else {
				temp_x = cx; temp_y = cy;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
			//Down Step
			temp_x = cx; temp_y = cy;
			if (temp_y <= 1) {}
			else {
				temp_x = cx; temp_y = cy - 2;
				if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 1) {}
				else if (gameSquares[temp_x][temp_y + 1].is_empty == 0 && gameSquares[temp_x][temp_y + 1].kill_him == 0) {
					pinkHighlightStep(temp_x, temp_y, gameSquares[temp_x][temp_y + 1].which_piece);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 0, 1, gameSquares[temp_x][temp_y + 1].which_piece, gameSquares[temp_x][temp_y + 1].kill_him);
					set_data_highlight(temp_x, temp_y + 1, gameSquares[temp_x][temp_y + 1].which_piece, 1);
					gameSquares[temp_x][temp_y + 1].printPiece(temp_x, temp_y + 1, 11, gameSquares[temp_x][temp_y + 1].which_piece);
				}
				else {
					pinkHighlightStep(temp_x, temp_y, BLANK);
					gameSquares[temp_x][temp_y + 1].setSquare(temp_x, temp_y + 1, 1, 1, BLANK, 0);
					set_data_highlight(temp_x, temp_y + 1, BLANK, 1);
				}
			}
		}
	}
}
//Tell About the Check of King
void tell_about_check(int cx, int cy) {
	//For Pawn
	if (gameSquares[cx][cy].which_piece == PAWN) {
		if (gameSquares[cx][cy].kill_him == 0) {	//If it is Player's PAWN
			if (gameSquares[cx + 1][cy + 1].kill_him == 1 && gameSquares[cx + 1][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			if (gameSquares[cx - 1][cy + 1].kill_him == 1 && gameSquares[cx - 1][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
		}
		else {
			if (gameSquares[cx + 1][cy - 1].kill_him == 0 && gameSquares[cx + 1][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			if (gameSquares[cx - 1][cy - 1].kill_him == 0 && gameSquares[cx + 1][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
		}
	}
	//For Knight
	if (gameSquares[cx][cy].which_piece == KNIGHT) {
		if (gameSquares[cx][cy].kill_him == 0) {
			//(x+1,y+2)
			if (gameSquares[cx + 1][cy + 2].kill_him == 1 && gameSquares[cx + 1][cy + 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+1,y-2)
			else if (gameSquares[cx + 1][cy - 2].kill_him == 1 && gameSquares[cx + 1][cy - 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-1,y+2)
			else if (gameSquares[cx - 1][cy + 2].kill_him == 1 && gameSquares[cx - 1][cy + 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-1,y-2)
			else if (gameSquares[cx - 1][cy - 2].kill_him == 1 && gameSquares[cx - 1][cy - 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+2,y+1)
			else if (gameSquares[cx + 2][cy + 1].kill_him == 1 && gameSquares[cx + 2][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+2,y-1)
			else if (gameSquares[cx + 2][cy - 1].kill_him == 1 && gameSquares[cx + 2][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-2,y+1)
			else if (gameSquares[cx - 2][cy + 1].kill_him == 1 && gameSquares[cx - 2][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-2,y-1)
			else if (gameSquares[cx - 2][cy - 1].kill_him == 1 && gameSquares[cx - 2][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
		}
		else {
			//(x+1,y+2)
			if (gameSquares[cx + 1][cy + 2].kill_him == 0 && gameSquares[cx + 1][cy + 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+1,y-2)
			else if (gameSquares[cx + 1][cy - 2].kill_him == 0 && gameSquares[cx + 1][cy - 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-1,y+2)
			else if (gameSquares[cx - 1][cy + 2].kill_him == 0 && gameSquares[cx - 1][cy + 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-1,y-2)
			else if (gameSquares[cx - 1][cy - 2].kill_him == 0 && gameSquares[cx - 1][cy - 2].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+2,y+1)
			else if (gameSquares[cx + 2][cy + 1].kill_him == 0 && gameSquares[cx + 2][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x+2,y-1)
			else if (gameSquares[cx + 2][cy - 1].kill_him == 0 && gameSquares[cx + 2][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-2,y+1)
			else if (gameSquares[cx - 2][cy + 1].kill_him == 0 && gameSquares[cx - 2][cy + 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
			//(x-2,y-1)
			else if (gameSquares[cx - 2][cy - 1].kill_him == 0 && gameSquares[cx - 2][cy - 1].which_piece == KING) {
				gotoxy(5, 15);
				HANDLE hConsole;
				hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
				cout << "Check";
			}
		}
	}
	//For Bishop
	if (gameSquares[cx][cy].which_piece == BISHOP) {
		if (gameSquares[cx][cy].kill_him == 0) {
			int temp_x, temp_y;
			//1st Quadrant (+ve x , +ve y)
			temp_x = cx; temp_y = cy;
			if (temp_x >= 8 || temp_y >= 8) {}
			else {
				for (int i = cx + 1, j = cy; /*<No Condition>*/; i++, j++) {
					if (i > 8 || j >= 8) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == KING && gameSquares[i][j + 1].kill_him == 1) {
						gotoxy(5, 15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
						cout << "Check";
						break;
					}
				}
			}
			//2nd Quadrant (x -ve , y +ve)
			if (temp_x < 1 || temp_y >= 8) {}
			else {
				for (int i = cx - 1, j = cy; /*<No Condition>*/; i--, j++) {
					if (i < 1 || j > 7) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == KING && gameSquares[i][j + 1].kill_him == 1) {
						gotoxy(5, 15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
						cout << "Check";
						break;
					}
				}
			}
			//3rd Quadrant (x -ve , y -ve)
			if (temp_x < 1 || temp_y < 1) {}
			else {
				for (int i = cx - 1, j = cy - 2; /*<No Condition>*/; i--, j--) {
					if (i <= 0 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == KING && gameSquares[i][j + 1].kill_him == 1) {
						gotoxy(5, 15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
						cout << "Check";
						break;
					}
				}
			}
			//4th Quadrant (x +ve , y -ve)
			if (temp_x >= 8 || temp_y < 1) {}
			else {
				for (int i = cx + 1, j = cy - 2; /*<No Condition>*/; i++, j--) {
					if (i > 8 || j < 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 0) { break; }
					if (gameSquares[i][j + 1].is_empty == 0 && gameSquares[i][j + 1].kill_him == 1) { break; }
					if (gameSquares[i][j + 1].is_empty == KING && gameSquares[i][j + 1].kill_him == 1) {
						gotoxy(5, 15);
						HANDLE hConsole;
						hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 207);          //RED Colour Code = 207
						cout << "Check";
						break;
					}
				}
			}
		}
	}
}

//Unhighlighted Pink Step_______________________
void CPiece::unhighlightStep(int cx, int cy) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (cx % 2 == 0 && cy % 2 == 0) {            //If x is even, y is evem
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 8);          //Gray Colour Code = 8 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		X = X - 2;
		Y = Y - 1;
		gotoxy(X, Y);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			Y++;
			gotoxy(X, Y);
		}
	}
	else if (cx % 2 != 0 && cy % 2 != 0) {       //If x is odd, y is odd
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 8);          //Gray Colour Code = 8 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		X = X - 2;
		Y = Y - 1;
		gotoxy(X, Y);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			Y++;
			gotoxy(X, Y);
		}
	}
	else if (cx % 2 != 0 && cy % 2 == 0) {       //If x is odd, y is even
		HANDLE hConsole;                  //Print Green Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);          //Greem Colour Code = 2 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		X = X - 2;
		Y = Y - 1;
		gotoxy(X, Y);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xB0";
			}
			Y++;
			gotoxy(X, Y);
		}
	}
	else if (cx % 2 == 0 && cy % 2 != 0) {       //If x is even, y is odd
		HANDLE hConsole;                  //Print Green Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 2);          //Green Colour Code = 2 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		X = X - 2;
		Y = Y - 1;
		gotoxy(X, Y);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xB0";
			}
			Y++;
			gotoxy(X, Y);
		}
	}
	//////////////////////////////

	if (gameSquares[cx][cy].is_empty == 1) {
		gameSquares[cx][cy].setSquare(cx, cy, 1, 0, 0, 0);
	}
	else {
		if (gameSquares[cx][cy].kill_him == 1) {
			gameSquares[cx][cy].setSquare(cx, cy, 0, 0, gameSquares[cx][cy].which_piece, gameSquares[cx][cy].kill_him);
			gameSquares[cx][cy].printPiece(cx, cy, 15, gameSquares[cx][cy].which_piece);
		}
		else {
			gameSquares[cx][cy].setSquare(cx, cy, 0, 0, gameSquares[cx][cy].which_piece, gameSquares[cx][cy].kill_him);
			gameSquares[cx][cy].printPiece(cx, cy, 10, gameSquares[cx][cy].which_piece);
		}
	}
}
//Pink Highlight Step_______________________
void CPiece::pinkHighlightStep(int cx, int cy, int pieceNum) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (cx % 2 == 0 && cy % 2 == 0) {            //If x is even, y is evem
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 5);          //Dark Pink Colour Code = 5 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		int tempX = X - 2;
		int tempY = Y - 4;
		gotoxy(tempX, tempY);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			tempY++;
			gotoxy(tempX, tempY);
		}
	}
	else if (cx % 2 != 0 && cy % 2 != 0) {       //If x is odd, y is odd
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 5);          //Dark Pink Colour Code = 5 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		int tempX = X - 2;
		int tempY = Y - 4;
		gotoxy(tempX, tempY);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			tempY++;
			gotoxy(tempX, tempY);
		}
	}
	else if (cx % 2 != 0 && cy % 2 == 0) {       //If x is odd, y is even
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);          //Light Pink Colour Code = 13 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		int tempX = X - 2;
		int tempY = Y - 4;
		gotoxy(tempX, tempY);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			tempY++;
			gotoxy(tempX, tempY);
		}
	}
	else if (cx % 2 == 0 && cy % 2 != 0) {       //If x is even, y is odd
		HANDLE hConsole;                  //Print Gray Step
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);          //Light Pink Colour Code = 13 
		int X = (cx * 5) + 16 - 3;
		int Y = 24 - (cy * 3) + 1;
		int tempX = X - 2;
		int tempY = Y - 4;
		gotoxy(tempX, tempY);
		for (int i = 0; i < 3; i++) {
			for (int i = 0; i < 5; i++) {
				cout << "\xDB";
			}
			tempY++;
			gotoxy(tempX, tempY);
		}
	}
}