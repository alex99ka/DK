#define NOMINMAX

#include<windows.h> // sleep and other stuff
#include<iostream>
#include <algorithm>
#include <conio.h> // For _kbhit() and _getch and go to 
#include "ColorPoint.h"
#include "utils.h"
#include "File.h"
#include <cctype>
#include "Game.h"
#include <set>
using namespace std;



void CGame::Start()
{
	char board[BORDER_HIGHT - 2][BORDER_WIDTH - 2] = {};
	while (true) {
		PrintMenu();
		CGame::MenuDecision decision = GetMenuDecision(board);
		if (decision== GAME_END)
		{
			PrintGoodbye();
			return;
		}
		clrscr();
		StartGame(board);
		PlayLoop();
	}
}

void CGame::PrintMenu()
{
	clrscr();

	CColoredPrint::prl("Hello, guy!\n");
	CColoredPrint::prl("Welcome to Donkey Kong game\n", CColorPoint::c_color::BLUE, CColorPoint::c_decoration::BOLD);
	CColoredPrint::prl("Please select one of the follwing options : ", CColorPoint::c_color::CYAN, CColorPoint::c_decoration::BOLD);
	// add print for choose level on 3
	CColoredPrint::prl("1 - Start a new game", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	if (m_IsColored)
		CColoredPrint::prl("2 - Turn off color", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	else
		CColoredPrint::prl("2 - Turn on color", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	CColoredPrint::prl("3 - choose desired level", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	CColoredPrint::prl("8 - Present instructions and keys", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
	CColoredPrint::prl("9 - exit", CColorPoint::c_color::GREEN, CColorPoint::c_decoration::ITALIC);
}

CGame::MenuDecision CGame::GetMenuDecision(char board[][BORDER_WIDTH - 2])
{
	char choice;


	while (true)
	{
		if (_kbhit())
		{
		 choice = _getch();
		 switch (choice)
		 {
		 case '1':
			 if (!DecipherScreen(board))
			 {
				// m_board = {}; // clear board;
				 cout << "The file: " << m_FileName << "contains an illegal char inside, make sure it's correct" <<" or a file wan't loaded" << endl;
				 break;
			 }
			 return GAME_START;
		 case '2':
			 m_IsColored = !m_IsColored;// toggle 
			 PrintMenu();
			 break;
		 case '3':
			 ChooseLevel(board);
			 break;
		 case '8':
			 PrintInstructions(MAIN_MENU);
			 break;
		 case '9':
			 return CGame::GAME_END;
	
			default:
				cout << "your choice is not legal input"<< endl;
		 }
		}
	}
	return GAME_END;
}

void CGame::PrintInstructions(ScreenType type)
{
	clrscr();
	CColoredPrint::prl("\nGame instructions and keys\n", m_IsColored ? CColoredPrint::c_color::YELLOW : CColoredPrint::c_color::WHITE);
	CColoredPrint::prl("When the game starts, Mario(the hero) is positioned at his start position without any movement.");
	CColoredPrint::prl("Once you selects move direction(using the keys, as listed below)");
	CColoredPrint::prl("Mario will continue to move in this direction even if the user does not press any key");
	CColoredPrint::prl("as long as game board boundaries are not reached and the STAY key is not pressed.");
	CColoredPrint::prl("KEYS :", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, m_IsColored ? CColoredPrint::c_decoration::BLINK : CColoredPrint::c_decoration::NORMAL);
	CColoredPrint::pr("LEFT :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("a or A", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("RIGHT :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("d or D", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("UP / JUMP :		", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("w or W", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("DOWN :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("x or X", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::pr("STAY :			", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	CColoredPrint::prl("s or S", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::ITALIC);
	CColoredPrint::prl("\nPausing a game:", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);
	CColoredPrint::prl("Pressing the ESC key during a game pauses the game.");
	CColoredPrint::prl("When the game is at pause state, pressing ESC again would continue the game");
	CColoredPrint::prl("\nExit a game:", m_IsColored ? CColoredPrint::c_color::GREEN : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);
	CColoredPrint::prl("You can exit the game via the Pause menu");
	CColoredPrint::prl("\nYou need to defeat Donkey Kong in order to save the Princess", m_IsColored ? CColoredPrint::c_color::BLUE : CColoredPrint::c_color::WHITE, CColoredPrint::c_decoration::UNDERLINE);

	while (true)
	{
		if (_kbhit())
		{
			char clean = _getch(); // trash input to clean the buffer 
			if (type == PAUSE_MENU) // ASCII code for ESC key
			{
				clrscr();
				PrintPauseMenu();
				return;
			}
			else
			{
				clrscr();
				PrintMenu();
				return;
			}
		}
	}
}

void CGame::PrintGoodbye()
{
	clrscr();
	CColoredPrint::prl("Goodbye, friend!\n", CColoredPrint::c_color::CYAN);
	Sleep(100);
}

void CGame::StartGame(char board[][BORDER_WIDTH - 2])
{
	Init(board);
	m_board.Draw();
}

void CGame::Init(char board[][BORDER_WIDTH - 2])
{
	m_board.Init(m_IsColored, board); // should get board.
	ResetMovingItems();
	m_mario.SetLives(MARIO_LIVES);
//	m_DonkeyIsDead = false;
	m_nBarrels = MAX_NUM_BARRELS;
	m_barrels.clear();
}


void CGame::ChooseLevel(char board[][BORDER_WIDTH - 2])
{
	vector<string> screen;
	CFile fileManager;
	char input;
	int instance = 0, Amount_of_Files_on_screen = 9;
	int option;
	vector<string> FileNames  = ReadDirectory();
	int len = (int)FileNames.size();
	int Pages = (len / Amount_of_Files_on_screen) + 1;
	clrscr();
	hideCursor();
	sort(FileNames.begin(), FileNames.end()); // stl sort
	if (!FileNames.empty())
	{
		PrintChooseLevel(FileNames, instance, len, Amount_of_Files_on_screen); //color
		while (true)
		{
			if (_kbhit())
			{
				input = _getch();
				option = LegalButton(input, instance, len, Amount_of_Files_on_screen);
				if (!option)
					continue;
				else
				{
					switch (input)
					{
					case PAGE_RIGHT: // right
						(Pages >= instance + 1) ? instance++ : instance = 0;
						break;
					case PAGE_LEFT:
						if (instance > 0)
							instance--;
						break;
					default:
						m_FileName = FileNames[option + instance*Amount_of_Files_on_screen - 1];
						if (OpenFile(fileManager))
							return;
						break;
					}
				}
			}

		}
	}
}
void CGame::PrintChooseLevel(vector<string> FileNames, int instance, int len, int Amount_of_Files_on_screen)
{
	int startIndex = instance * Amount_of_Files_on_screen;
	int filesToShow = min(Amount_of_Files_on_screen, len - startIndex); //to prevent overflow
	hideCursor();
	for (int i = 0; i < filesToShow; i++)
	{
		CColoredPrint::prl(FileNames[startIndex + i],
			m_IsColored ? CColoredPrint::c_color::CYAN : CColoredPrint::c_color::WHITE,
			CColoredPrint::c_decoration::BOLD);
	}
}

// checks if the file is correct and of not prints to correct error
bool CGame::OpenFile(CFile& fileManager)
{
	if (!fileManager.OpenFile(m_FileName, m_screen)) {
		cout << "Failed to load file: " << fileManager.GetLastError() << endl;
		return false;
	}
	clrscr();
	PrintMenu();
	return true;
}

int CGame::LegalButton(char input, int instance, int len, int Amount_of_Files_on_screen)
{
	int num;
	int filesInCurrentInstance;
	if (instance == len / Amount_of_Files_on_screen) 
		filesInCurrentInstance = len % Amount_of_Files_on_screen;
	else
		filesInCurrentInstance = Amount_of_Files_on_screen;

	if (isdigit(input))
	{
		num = input - '0';
		if (num > 0 && num <= filesInCurrentInstance)
			return num;
	}
	if (isalpha(input))
	{
		input = tolower(input);
		num = input - 'a' + 1;
		return(num);
	}
	if (input == '>')
		return PAGE_RIGHT;
	if (input == '<')
		return PAGE_LEFT;

	return 0;  // Invalid input
}

// need to be changes
bool CGame::DecipherScreen(char board[][BORDER_WIDTH - 2])
{
	m_ghosts.clear();  // Clear existing ghosts
	char const UpperHammer = 'P';
	int hammer_counter{};
	/*for (string line : m_screen)
		cout << line << endl;*/
		// Parse screen with bounds checking
	for (int i = 0; i < min(static_cast<int>(m_screen.size()), BORDER_HIGHT - 2); ++i) {
		for (int j = 0; j < min(static_cast<int>(m_screen[i].size()), BORDER_WIDTH - 2); ++j) {
			char symbol = m_screen[i][j];
			if (isalpha(symbol)) // exept the screen to be decipherd in lower and upper
				symbol = toupper(symbol);

			switch (symbol) {
			case AVATAR_MARIO:
				m_mario = CMovingItem(j, i, AVATAR_MARIO, // the + 1 is for the offset cause by rpint board
					m_IsColored ? CColorPoint::GREEN : CColorPoint::WHITE);
				board[i][j] = SPACE_SYMB;
				break;

			case HAMMER_SYMB:
			case UpperHammer:
				if (hammer_counter != 0)
					return false;
				hammer_counter++;
				m_hammer = CItem(j, i, HAMMER_SYMB,
					m_IsColored ? CColorPoint::GREEN : CColorPoint::WHITE);
				m_IsHammer = true; //  indicate that the hammer should be printed 
				board[i][j] = SPACE_SYMB;
				break;

			case AVATAR_PRINCESS:
				m_princess = CItem(j, i, AVATAR_PRINCESS,
					m_IsColored ? CColorPoint::MAGENTA : CColorPoint::WHITE);
				board[i][j] = SPACE_SYMB;
				break;

			case AVATAR_DONKEYKONG:
				m_donkeykong = CItem(j, i, AVATAR_DONKEYKONG,
					m_IsColored ? CColorPoint::CYAN : CColorPoint::WHITE);
				board[i][j] = SPACE_SYMB;
				break;

			case AVATAR_GHOST:
				m_ghosts.push_back(CMovingItem(j, i, AVATAR_GHOST,
					 CColorPoint::WHITE, BORDER_HIGHT + 1)); //  max fall is BORDER_HIGHT just in case they spawn in the air and need to fall. ghost are dead already therfore they can't die again from fall
				board[i][j] = SPACE_SYMB;
				break;

			case LEGENS_SYMB:
				m_Legend = CPoint(j, i);
				board[i][j] = SPACE_SYMB;
				break;

			case LADDER_SYMB:
			case BOARDER_SYMB:
			case FLOOR_SYMB:
			case MOVE_LEFT_SYMB:
			case MOVE_RIGHT_SYMB:
				board[i][j] = symbol;
				break;

			case SPACE_SYMB:
				board[i][j] = SPACE_SYMB;
				break;

			default:
				return false; // Found an invalid symbol
			}
		}
	}

	// Set initial direction for ghosts
	for (auto& ghost : m_ghosts) {
		ghost.SetDirection(CMovingItem::RIGHT); //arbitrary 

	}

	return NecessaryItemExicst(); // Everything was processed successfully
			
}

vector<string> CGame::ReadDirectory()
{
	vector<string> Names;
	regex pattern("dkong_[a-zA-Z0-9]+\\.screen");  // Only letters and numbers between dkong_ and .screen

	try {
		for (const auto& entry : fs::directory_iterator(fs::current_path()))
		{
			string filenameStr = entry.path().filename().string();

			// Check if filename matches our pattern
			if (regex_match(filenameStr, pattern))
				Names.push_back(filenameStr);
		}
	}
	catch (const fs::filesystem_error& e) {
		cout << "Filesystem error: " << e.what() << endl;
	}
	return Names;
}

bool CGame::NecessaryItemExicst()
{
	// First check if items exist
	if (m_mario == CMovingItem())
	{
		cout << "mario was missing" << endl;
		return false;
	}
	if (m_donkeykong == CItem())
	{
		cout << "Donkey Kong was missing" << endl;
		return false;
	}
	if (m_princess == CItem())
	{
		cout << "Pauline was missing" << endl;
		return false;
	}
	if (m_Legend == CPoint())
	{
		cout << "The Legend was missing" << endl;
		return false;
	}

	// Then check if they're not on borders
	// Check mario
	if (m_mario.GetX() <= 0 || m_mario.GetX() >= BORDER_WIDTH - 1 ||
		m_mario.GetY() <= 0 || m_mario.GetY() >= BORDER_HIGHT - 1)
		return false;

	// Check donkey kong
	if (m_donkeykong.GetX() <= 0 || m_donkeykong.GetX() >= BORDER_WIDTH - 1 ||
		m_donkeykong.GetY() <= 0 || m_donkeykong.GetY() >= BORDER_HIGHT - 1)
		return false;

	// Check princess
	if (m_princess.GetX() <= 0 || m_princess.GetX() >= BORDER_WIDTH - 1 ||
		m_princess.GetY() <= 0 || m_princess.GetY() >= BORDER_HIGHT - 1)
		return false;

	// Check legend
	if (m_Legend.GetX() <= 0 || m_Legend.GetX() >= BORDER_WIDTH - 1 ||
		m_Legend.GetY() <= 0 || m_Legend.GetY() >= BORDER_HIGHT - 1)
		return false;

	return true;
}
// called upon after a death, returns mario to spawn point
void CGame::ResetPlayer()
{
	EraseCharacter(m_mario);
		m_mario.SetX(m_mario.GetXSpawn());
	m_mario.SetY(m_mario.GetYSpawn());
	m_mario.Respawn(AVATAR_MARIO);
	m_mario.ReduceLife();
	m_mario.ResetFalls();
	m_mario.SetDirection(CMovingItem::STOP);
}

void CGame::ChangeAllEntitysColor()
{
	CColorPoint::c_color GhostColor;
	CColorPoint::c_color BarrelColor;
	if (m_IsHammerActive)
	{
		GhostColor = CColorPoint::BLUE;
		BarrelColor = CColorPoint::BLUE;
	}
	else
	{
		GhostColor = CColorPoint::WHITE;
		BarrelColor = CColorPoint::RED;
	}

	for (auto ghost : m_ghosts)
		ghost.ChangeColor(GhostColor);
	for (auto barrel : m_barrels)
		barrel.ChangeColor(BarrelColor);
}

void CGame::ResetMovingItems()
{
	ResetPlayer();
	clrscr();
	for (auto ghost : m_ghosts)
	{
		ghost.SetX(ghost.GetXSpawn());
		ghost.SetY(ghost.GetYSpawn());
	}
	m_barrels.clear();
	
}

void CGame::PlayLoop()
{
	bool Mario(true), Italian(true);
	bool OnLadder(false);
	char input;	
	int cnt = 0;

	hideCursor();
	m_mario.Draw();
	DrawGhost();

	while (Mario = Italian)
	{
		cnt++;
		if (_kbhit())
		{
			input = _getch();
			{
				switch (input)
				{
				case 'a':
				case 'A':
					m_mario.SetDirection(CMovingItem::LEFT);
					break;
				case 'd':
				case 'D':
					m_mario.SetDirection(CMovingItem::RIGHT);
					break;
				case 'w':
				case 'W':
					m_mario.SetDirection(CMovingItem::UP);
					break;
				case 'x':
				case 'X':
					m_mario.SetDirection(CMovingItem::DOWN);
					break;
				case 's':
				case 'S':
					m_mario.SetDirection(CMovingItem::STOP);
					break;
				case ESC_KEY:
				{
					if (Paused() == GAME_END)
						return;
					break;
				}
				default:
					// ignore illegal input
					break;
				}
			}
		}
		if (cnt % BARREL_FREQUENCY_BIRTH == 0) {
			if (AddBarrel() == DEAD) {
				if (GameOver() == false) // game finished
					return;
			}
		}

		if (BarrelsMoving() == DEAD) {
			if (GameOver() == false) // game finished
				return;
		}

		if (GhostsMoving() == DEAD)
		{
			if (GameOver() == false) // game finished
				return;
		}

		switch(PlayerCheckNextCell(m_mario))
		{
		case DEAD:
			if (GameOver() == false) // game finished
				return;
			break;
		case WON:
			PrintCongratulation();
			return;
		case ALIVE:
			break;
		} 
		if (m_IsHammer)
			m_hammer.Draw();
		m_donkeykong.Draw();
		m_princess.Draw();
		DrawHearts();
		std::cout.flush(); 
		Sleep(SLEEP_TIME);
	}
}
void CGame::ResetScreen()
{
	clrscr();
	m_board.Draw();
	m_donkeykong.Draw();
	DrawHearts();
	if (m_DonkeyIsDead)
		m_princess.Draw();
	m_mario.Draw();
	for (CMovingItem& barrel : m_barrels) {
		barrel.SetColor(m_IsColored ? CColorPoint::c_color::MAGENTA : CColorPoint::c_color::WHITE);
		barrel.Draw();
	}
}
// triggerd by the esc button
CGame::MenuDecision CGame::Paused()
{
	char choice, prevchioce= '\0';

	clrscr();
	PrintPauseMenu();

	while (true)
	{
		if (_kbhit())
		{
			choice = _getch();
			if (prevchioce != choice)
			{
				switch (choice)
				{
					case ESC_KEY:
					{
						ResetScreen();
						return GAME_START; // just continue the game
					}
					case '1':
					{
						clrscr();
						PrintInstructions(PAUSE_MENU);
						break;
					}
					case '2':
					{
						PrintGoodbye();
						return GAME_END;
					}
				}
			}
		}
	}
	return GAME_START;
}

void CGame::PrintPauseMenu() 
{
	const char* PauseMenu[] = {
		"********************************************************************************",
		"*                                                                              *",
		"*                               GAME PAUSED                                    *",
		"*                                                                              *",
		"********************************************************************************",
		"*                                                                              *",
		"*                            [ESC] Resume Game                                 *",
		"*                                                                              *",
		"*                            [1] Instructions                                  *",
		"*                                                                              *",
		"*                            [2] Quit Game                                     *",
		"*                                                                              *",
		"********************************************************************************",
		"*                                                                              *",
		"*                   Use the indicated keys to make your selection              *",
		"*                                                                              *",
		"********************************************************************************"
	};

	for (const char* line : PauseMenu) {
		std::cout << line << std::endl;
	}
}

CGame::LiveStatus CGame::ExplosionBarrel(CMovingItem& barrel)
{
	CGame::LiveStatus status = ALIVE;
	CPoint explPos;
	int minX = std::max(barrel.GetX() , 1);
	int minY = std::max(barrel.GetY() , 1);
	int maxX = std::min(barrel.GetX() + 1, m_board.GetBorderWidth() - 1);
    int maxY = std::min(barrel.GetY() + 1, m_board.GetBorderHight() - 1);


	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++)
		{
			explPos.SetCoord( x, y);
			if (m_mario == explPos)
				status = DEAD;
			GoToXY(x, y);
			CColoredPrint::pr(EXPL_SYMB, m_IsColored ? CColorPoint::c_color::RED : CColorPoint::c_color::WHITE, m_IsColored ? CColoredPrint::c_decoration::BLINK : CColoredPrint::c_decoration::NORMAL);
		}
	}
	Sleep(500);
	if (status != DEAD)
	{
		char symbol;
		CColorPoint::c_color color;

		for (int y = minY; y <= maxY; y++) {
			for (int x = minX; x <= maxX; x++)
			{
				explPos.SetCoord(x, y);
				GoToXY(x, y);
				m_board.GetBoardSymbol(explPos, &symbol, &color);
				CColoredPrint::pr(symbol, color, CColoredPrint::c_decoration::BOLD);
			}
		}
	}
	ResetBarrel(barrel);

	return status;
}

bool CGame::IsHitPlayer(CPoint& Entity)
{
	return (Entity == m_mario);
}

CGame::LiveStatus CGame::GhostsMoving()
{
	CGame::LiveStatus status;

	for (CMovingItem& ghost : m_ghosts) {
	 status = GhostMoving(ghost);
		if (status == DEAD) // Marios dead
			return status;
	}
	return ALIVE;
}

void CGame::GhostCollision(CMovingItem& ghost)
{

	for (auto& t_ghost : m_ghosts)
	{
		// Skip if it's the same object 
		if (&ghost == &t_ghost)
			continue;
		if (ghost == t_ghost)
		{
			SwitchGhostDirection(ghost);
			return;
		}
	}
}

CGame::LiveStatus CGame::GhostMoving(CMovingItem& ghost)
{
	if (IsHitPlayer(ghost))
		return DEAD;	


	CBoard::Board_Place place = m_board.GetBoardPlace(ghost);// where the ghost is now
	CMovingItem::Directions direction = ghost.GetDirection();
	CPoint newPos = CPoint(ghost.GetX() + ghost.GetXDirection(), ghost.GetY()); // next render location
	CBoard::Board_Place nextPlace = m_board.GetBoardPlace(newPos);
	  // uncharted water
	switch (nextPlace)
	{
	case CBoard::Board_Place::FLOOR:
	case CBoard::Board_Place::BOARDER:
		SwitchGhostDirection(ghost);
		return ALIVE;
	case CBoard::Board_Place::LADDER:
	case CBoard::Board_Place::FREE:
		CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
		if (m_board.GetBoardPlace(downPos) == CBoard::Board_Place::FREE)
			SwitchGhostDirection(ghost);
		break;
	}

	EraseCharacter(ghost);
	ghost.SetCoord(newPos.GetX(), newPos.GetY());
	ghost.Draw(); 
	return ALIVE;
	
	/*switch (nextPlace) {
	case CBoard::Board_Place::FLOOR:
	case CBoard::Board_Place::BOARDER:
		SwitchGhostDirection(ghost);
		return ALIVE;
		if (BarrelFlowCollision(ghost, ghost.GetPrevDirection(), newPos))
			return CGame::ExplosionBarrel(ghost);
		break;
	case CBoard::Board_Place::FREE:
	{
		CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
		enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
		if (direction == CMovingItem::RIGHT || direction == CMovingItem::LEFT) {
			ghost.SetPrevDirection(ghost.GetDirection());
			if (downPlace == CBoard::Board_Place::ARROW_LEFT) {
				ghost.SetDirection(CMovingItem::LEFT);
				newPos.SetCoord(ghost.GetX() + ghost.GetXDirection(), ghost.GetY());
			}
			else if (downPlace == CBoard::Board_Place::ARROW_RIGHT) {
				ghost.SetDirection(CMovingItem::RIGHT);
				newPos.SetCoord(ghost.GetX() + ghost.GetXDirection(), ghost.GetY());
			}
			else if (downPlace == CBoard::Board_Place::LADDER)
				ghost.SetDirection(CMovingItem::DOWN);
		}
		if (downPlace == CBoard::Board_Place::FREE)
			FallCharacter(ghost);
	}
	break;
		break;
	}

	*/

}

CGame::LiveStatus CGame::SwitchGhostDirection(CMovingItem& ghost)
{
	enum CMovingItem::Directions dir;
	dir = ghost.GetDirection(); 
	if (dir == CMovingItem::Directions::LEFT)
		ghost.SetDirection(CMovingItem::Directions::RIGHT);
	else
		ghost.SetDirection(CMovingItem::Directions::LEFT);
	CPoint newPos = CPoint(ghost.GetX() + ghost.GetXDirection(), ghost.GetY());
	if (IsHitPlayer(newPos)) // checking if mario was behind the ghost before the switch
		return DEAD;

	return ALIVE;
}

void CGame::ResetBarrel(CMovingItem& barrel)
{
	EraseCharacter(barrel);
	auto it = std::find(m_barrels.begin(), m_barrels.end(), barrel);
	m_barrels.erase(it);
	m_nBarrels++;
}

bool CGame::BarrelFlowCollision(CMovingItem& barrel, CMovingItem::Directions direction, CPoint& newPos)
{
	if (barrel.GetFallCounter() >= barrel.GetMaxFall()) 
		return true;
	barrel.ResetFalls();
	barrel.SetDirection(direction);
	newPos.SetCoord(barrel.GetX() + barrel.GetXDirection(), barrel.GetY());

	return false;
}

CGame::LiveStatus  CGame::BarrelMoving(CMovingItem& barrel)
{
	if (IsHitPlayer(barrel)) {
		ResetBarrel(barrel);
		return DEAD;
	}
		
	CPoint newPos = CPoint(barrel.GetX() + barrel.GetXDirection(), barrel.GetY() + barrel.GetYDirection());

	enum CBoard::Board_Place place = m_board.GetBoardPlace(barrel);
	enum CBoard::Board_Place nextPlace = m_board.GetBoardPlace(newPos);
	CMovingItem::Directions direction = barrel.GetDirection();
	
	switch (nextPlace) {
	case CBoard::Board_Place::BOARDER:
		ResetBarrel(barrel);
		return ALIVE;
	case CBoard::Board_Place::ARROW_LEFT:
		if (BarrelFlowCollision(barrel, CMovingItem::LEFT, newPos))
			return CGame::ExplosionBarrel(barrel);
		break;
	case CBoard::Board_Place::ARROW_RIGHT:
		if (BarrelFlowCollision(barrel, CMovingItem::RIGHT, newPos))
			return CGame::ExplosionBarrel(barrel);
		break;
	case CBoard::Board_Place::FLOOR:
		if (BarrelFlowCollision(barrel, barrel.GetPrevDirection(), newPos))
			return CGame::ExplosionBarrel(barrel);
		break;
	case CBoard::Board_Place::FREE:
	{
		CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
		enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
		if (direction == CMovingItem::RIGHT || direction == CMovingItem::LEFT) {
			barrel.SetPrevDirection(barrel.GetDirection());
			if (downPlace == CBoard::Board_Place::ARROW_LEFT) {
				barrel.SetDirection(CMovingItem::LEFT);
				newPos.SetCoord(barrel.GetX() + barrel.GetXDirection(), barrel.GetY());
			}
			else if (downPlace == CBoard::Board_Place::ARROW_RIGHT) {
				barrel.SetDirection(CMovingItem::RIGHT);
				newPos.SetCoord(barrel.GetX() + barrel.GetXDirection(), barrel.GetY());
			} /*else if (downPlace == CBoard::Board_Place::LADDER)
				barrel.SetDirection(CMovingItem::DOWN);*/
		}
		if (downPlace == CBoard::Board_Place::FREE)
			FallCharacter(barrel);
	}
	break;
	case CBoard::Board_Place::LADDER:
		break;
	}
	
	EraseCharacter(barrel);
	barrel.SetCoord(newPos.GetX(), newPos.GetY());
	barrel.Draw();
	return ALIVE;
}

CGame::LiveStatus CGame::BarrelsMoving() {

	CGame::LiveStatus status;

	for (CMovingItem& barrel : m_barrels) {
		status = BarrelMoving(barrel);
		if (status == DEAD) // Marios dead
			return status;
	}

	return ALIVE;
}

CGame::LiveStatus CGame::AddBarrel()
{
	if (m_nBarrels == 0)
		return ALIVE;
	CMovingItem::Directions direction;
	CMovingItem::Directions prevDirection;
	static bool flag = false;
	int x;

	if (flag) {
		x = getRandomInt(1, m_donkeykong.GetX() - 1);
		prevDirection = CMovingItem::RIGHT;
		direction = CMovingItem::LEFT;
	}
	else {
		x = getRandomInt(m_donkeykong.GetX() + 1, m_board.GetBorderWidth() - 2);
		prevDirection = CMovingItem::LEFT;
		direction = CMovingItem::RIGHT;
	}

	CMovingItem barrel = CMovingItem (x, m_donkeykong.GetY(), AVATAR_BARREL, m_IsColored ? CColorPoint::c_color::MAGENTA : CColorPoint::c_color::WHITE, MAX_FALL_BARREL);
	barrel.SetPrevDirection(prevDirection);

	CPoint downPos(barrel.GetX(), barrel.GetY() + 1);
	enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
	if (downPlace == CBoard::Board_Place::FREE)
		FallCharacter(barrel);
	else 
		barrel.SetDirection(direction);

	barrel.Draw();

	m_barrels.push_back(barrel);
	m_nBarrels--;
	flag = !flag;
	return ALIVE;
}

void CGame::EraseCharacter(CItem& character)
{
	char symbol;
	CColorPoint::c_color color;

	m_board.GetBoardSymbol(character, &symbol, &color); /// print board
	character.SetRestoreSymbol(symbol, color);
	character.Erase();
}

bool CGame::IsInBounds(int i, int j) const
{
		return i >= 0 && i < BORDER_HIGHT &&
			j >= 0 && j < BORDER_WIDTH;
}

CGame::NeighboorType CGame::WhoSomeoneNextToMe(CPoint& point)
{
	for (CMovingItem& barrel : m_barrels) {
		if (barrel.Compare(point))
			return BARREL;
	}
	for (CMovingItem& ghost : m_ghosts) {
		if (ghost.Compare(point))
			return GHOST;
	}
	if (m_princess.Compare(point))
		return PRINCESS;
	if (m_donkeykong.Compare(point))
	return DONKEYKONG;
	if (m_IsHammer && m_hammer.Compare(point))
		return HAMMER;

	return NONE;
}

CGame::LiveStatus CGame::MovePlayer(CMovingItem& character, CPoint& newPos)
{
	CGame::NeighboorType neigboorType , thisneighboor;

	neigboorType = WhoSomeoneNextToMe(newPos);
	thisneighboor = WhoSomeoneNextToMe(character);
	if (thisneighboor == BARREL || thisneighboor == GHOST)
		return DEAD;
	

	switch (neigboorType)
	{
	case NONE:
		if (character.IsStop() == false) {
			EraseCharacter(character);
		}
		break;
	case GHOST:
	case BARREL:
		return DEAD;
	case DONKEYKONG:
		if (m_DonkeyIsDead == false) {
			m_donkeykong.ChangeColor(m_IsColored ? CColorPoint::RED : CColorPoint::BLACK);
		}
		EraseCharacter(character);
		break;
	case PRINCESS:
		return WON;
	case HAMMER:
		m_IsHammerActive = true;
		EraseCharacter(m_hammer);
		character.HammerActivated(AVATAR_MARIO_WITH_HAMMER);
		ChangeAllEntitysColor();
		EraseCharacter(character);
	}

	character.SetCoord(newPos.GetX() , newPos.GetY());
	character.Draw();
	m_donkeykong.Draw();

	return ALIVE;
}

void CGame::FallCharacter(CMovingItem& character)
{
	character.SetDirection(CMovingItem::DOWN); //fall
	character.Falling();
}
// checks what in cell next to the direction of the player
CGame::LiveStatus CGame::PlayerCheckNextCell(CMovingItem& character)
{
	enum CBoard::Board_Place place = m_board.GetBoardPlace(character);
	CMovingItem::Directions direction = character.GetDirection();
	CPoint newPos;

	if (place == CBoard::Board_Place::LADDER && direction == CMovingItem::UP)
		newPos.SetCoord(character.GetX(), character.GetY() - 1);
	else 
		newPos.SetCoord(character.GetX() + character.GetXDirection(), character.GetY() + character.GetYDirection());

	enum CBoard::Board_Place nextPlace  = m_board.GetBoardPlace(newPos);
	
	int nFalls = character.GetFallCounter();
	switch (nextPlace) {
	case CBoard::Board_Place::BOARDER:
	case CBoard::Board_Place::FLOOR:
	case CBoard::Board_Place::ARROW_LEFT:
	case CBoard::Board_Place::ARROW_RIGHT:
		if (direction == CMovingItem::UP) {
			newPos.SetCoord(character.GetX(), character.GetY() - 1);
			nextPlace = m_board.GetBoardPlace(newPos);
			if (nextPlace == CBoard::Board_Place::FREE) {
				FallCharacter(character);
				return MovePlayer(character, newPos);
			}
		}
		if (direction == CMovingItem::DOWN)
		{
			character.ResetFalls();
			if (nFalls > character.GetMaxFall())
			{
				return DEAD;
			}
			character.SetDirection(CMovingItem::STOP);
		}
		break;
	case CBoard::Board_Place::LADDER:
			return MovePlayer(character, newPos);
		break;
	case CBoard::Board_Place::FREE:
	{
		if (place == CBoard::Board_Place::LADDER) {
			if(direction == CMovingItem::LEFT || direction == CMovingItem::RIGHT) 
			{
				CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
				enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
				if (downPlace == CBoard::Board_Place::FREE)
					character.SetDirection(CMovingItem::STOP);
				else 
					return MovePlayer(character, newPos);
			}
			else if (direction == CMovingItem::UP) {
				MovePlayer(character, newPos);
				character.SetDirection(CMovingItem::STOP);
				break;
			} 
			else
				return MovePlayer(character, newPos);
		} // current place is FREE
		else if (direction == CMovingItem::LEFT || direction == CMovingItem::RIGHT) {
			CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
			enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
			if (downPlace == CBoard::Board_Place::FREE) {
				FallCharacter(character);
			}
			return MovePlayer(character, newPos);
		}
		else 
		{
			if (direction == CMovingItem::DOWN) 
			{
				if (nFalls > 0) {
					character.Falling();
					return MovePlayer(character, newPos);
				}
			}
			else if (direction == CMovingItem::UP) { //   JUMPING
				// we should check directions cell
				CPoint UpPos(character.GetX(), character.GetY() - 1);
				CPoint UpUpPos(character.GetX(), character.GetY() - 2);
				enum CBoard::Board_Place UpPlace = m_board.GetBoardPlace(UpPos);
				enum CBoard::Board_Place UpUpPlace = m_board.GetBoardPlace(UpUpPos);
				if (UpPlace == CBoard::Board_Place::FREE && UpUpPlace == CBoard::Board_Place::FREE) {
					if (newPos.Compare(UpUpPos)) { // Jump UP only
						FallCharacter(character);
					}
					else {
						CPoint downPos(newPos.GetX(), newPos.GetY() + 1);
						enum CBoard::Board_Place downPlace = m_board.GetBoardPlace(downPos);
						if (downPlace == CBoard::Board_Place::FREE) {
							FallCharacter(character);
						}
						else {
							int xDir = character.GetXDirection();
							if (xDir == 1) character.SetDirection(CMovingItem::RIGHT);
							if (xDir == -1) character.SetDirection(CMovingItem::LEFT);
						}
					}
					return MovePlayer(character, newPos);
				}
			}
			character.SetDirection(CMovingItem::STOP);		
		}
			
		break;
	}
	default:
		break;

	}
	return ALIVE;
}

void CGame::PrintCongratulation()
{
	clrscr();

	CColoredPrint::prl("         _                                  _                       ");
	CColoredPrint::prl("__      _(_)_ __  _ __   ___ _ __  __      _(_)_ __  _ __   ___ _ __ ");
	CColoredPrint::prl("\\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__| \\ \\ /\\ / / | '_ \\| '_ \\ / _ \\ '__|");
	CColoredPrint::prl(" \\ V  V /| | | | | | | |  __/ |     \\ V  V /| | | | | | | |  __/ |   ");
	CColoredPrint::prl("  \\_/\\_/ |_|_| |_|_|_|_|\\___|_|      \\_/\\_/_|_|_| |_|_| |_|\\___|_|   ");
	CColoredPrint::prl("   ___| |__ (_) ___| | _____ _ __     __| (_)_ __  _ __   ___ _ __   ");
	CColoredPrint::prl("  / __| '_ \\| |/ __| |/ / _ \\ '_ \\   / _` | | '_ \\| '_ \\ / _ \\ '__|  ");
	CColoredPrint::prl(" | (__| | | | | (__|   <  __/ | | | | (_| | | | | | | | |  __/ |     ");
	CColoredPrint::prl("  \\___|_| |_|_|\\___|_|\\_\\___|_| |_|  \\__,_|_|_| |_|_| |_\\___|_|     ");
	CColoredPrint::prl("                                                                      ");
	Sleep(1500);
	CColoredPrint::prl("\n\n\n PRESS ANY KEY TO RETURN");

	while (true)
	{
		if (_kbhit())
			return;
	}
}

bool CGame::GameOver()
{
	CharacterDeathAnimation(m_mario);
	ResetMovingItems();
	m_IsHammer = false; // a hammer is avaliable only on the first try
	m_IsHammerActive = false;
	
	if (m_mario.GetLives() == 0) {
    	GameOverScreen();
		return false;
	}
	ResetScreen();
	
	return true;
}

void CGame::GameOverScreen()
{
	// Clear the screen
	clrscr();

	// ASCII art for a gravestone with Mario's name
	const char* art[] = {
		"         _______",
		"      .-'       `-.",
		"     /             \\",
		"    /               \\",
		"   |    RIP MARIO    |",
		"   |                 |",
		"   |    1981-2024    |",
		"   |                 |",
		"    \\               /",
		"     \\_____________/",
		"         ||     ||",
		"         ||     ||",
		"      ###############",
		"      #             #",
		"      ###############",
		"",
		"        GAME OVER!",
		"",
		" PRESS ANY KEY TO RETURN"
	};

	Beep(1200, 300);

	// Print the gravestone
	if (m_IsColored) {
		// Print in color
		int cntLine = 0;
		for (const char* line : art) {
			if (cntLine == 16)
				CColoredPrint::prl(line, CColoredPrint::c_color::RED, CColoredPrint::c_decoration::BOLD); // Game Over
			else if (cntLine == 18)
				CColoredPrint::prl(line, CColoredPrint::c_color::YELLOW, CColoredPrint::c_decoration::ITALIC); // Press any key
			else
				CColoredPrint::prl(line, CColoredPrint::c_color::WHITE); // Base
			cntLine++;
		}
	}
	else {
		// Print in black and white
		for (const char* line : art) {
			CColoredPrint::prl(line); // Default black and white
		}
	}

	while (true)
	{
		if (_kbhit())
			return;
	}
}

void CGame::DrawHearts()
{
	int i, lives;
	lives = m_mario.GetLives();
	GoToXY(3, 2);
	for (i = 0; i < lives; i++)
		CColoredPrint::pr("<3", m_IsColored ? CColoredPrint::c_color::RED : CColorPoint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
}
//// triggerd after donkey was deafeated

// should be deleted 
void CGame::CreatePrincess()
{
	int princessY = 3, princessX = 67;
	int PlatforSize = 3;
	m_princess = CItem(princessX, princessY, AVATAR_PRINCESS, m_IsColored ? CColorPoint::c_color::MAGENTA : CColorPoint::c_color::WHITE);
	for (int i = -1; i < PlatforSize - 1; i++)
	{
		m_board.UpdateworkBoard(princessX + i, princessY + 1, FLOOR_SYMB);
		GoToXY(princessX + i, princessY + 1);
		CColoredPrint::pr(FLOOR_SYMB, m_IsColored ? CColorPoint::c_color::YELLOW : CColorPoint::c_color::WHITE, CColoredPrint::c_decoration::BOLD);
	}
	m_princess.Draw();
}

void CGame::DrawGhost()
{
	for (auto ghost : m_ghosts)
		ghost.Draw();
}

// animation inspired by old games for when mario dies
void CGame::CharacterDeathAnimation(CMovingItem& character)
{
	int i, up = 2;
	int x = character.GetX();
	int y = character.GetY();
	int BoarderHight = m_board.GetBorderHight();
	Sleep(200);
	for (i = 0; i < up; i++)
	{
		EraseCharacter(character);
		y--;
		character.SetY(y);
		GoToXY(x, y);
		if (m_IsColored)
		{
			if (i % 2 == 0)
				character.ChangeColor(CColorPoint::RED);
			else
				character.ChangeColor(CColorPoint::GREEN);
		}

		character.Draw();
		Sleep(100);
	}
	for (; y < BoarderHight; y++)
	{
		EraseCharacter(character);
		character.SetY(y);
		GoToXY(x, y);
		if (m_IsColored)
		{
			if (y % 2 == 0)
				character.ChangeColor(CColorPoint::RED);
			else
				character.ChangeColor(CColorPoint::GREEN);
		}
		character.Draw();
		Sleep(150);
	}

}