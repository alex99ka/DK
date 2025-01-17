#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>
#include "Board.h"
#include "Item.h"
#include "string.h"(
#include "File.h"


class CGame
{
public:
	void Start();
private:
	enum NeighboorType {
		NONE, BARREL, DONKEYKONG, PRINCESS, GHOST, HAMMER};
	enum MenuDecision { GAME_START, GAME_END };
	enum LiveStatus { DEAD, ALIVE, WON };
    enum ScreenType { MAIN_MENU, PAUSE_MENU };
	
	static constexpr int ESC_KEY = 27;
	static constexpr int MARIO_LIVES = 3;
	static constexpr int AMOUNT_OF_FILES = 4;
	static constexpr int PAGE_RIGHT = -1;
	static constexpr int PAGE_LEFT = -2;
	static constexpr char AVATAR_MARIO = '@';
	static constexpr char AVATAR_MARIO_WITH_HAMMER = 'M';
	static constexpr char AVATAR_BARREL = 'O';
	static constexpr char AVATAR_DONKEYKONG = '&';
	static constexpr char AVATAR_PRINCESS = '$';
	static constexpr char AVATAR_GHOST = 'X';
	static constexpr char LEGENS_SYMB = 'L';
	static constexpr char HAMMER_SYMB= 'p';
	static constexpr char FLOOR_SYMB = '=';
	static constexpr char EXPL_SYMB = '*';
	static constexpr char BOARDER_SYMB = 'Q';
	static constexpr char MOVE_RIGHT_SYMB = '>';
	static constexpr char MOVE_LEFT_SYMB = '<';
	static constexpr char LADDER_SYMB = 'H';
	static constexpr char SPACE_SYMB = ' ';
	static constexpr int NUM_OF_BARRELS = 7;
	static constexpr int SLEEP_TIME = 100;
	static constexpr int MAX_NUM_BARRELS = 10;
	static constexpr int BARREL_FREQUENCY_BIRTH = 25;
	static constexpr int MAX_FALL_BARREL = 8;

	vector<string> ReadDirectory();
	MenuDecision Paused();
	void StartGame(char board[][BORDER_WIDTH - 2]);
	void Init(char board[][BORDER_WIDTH - 2]);
	void PlayLoop();
	void ResetScreen();
	void ChooseLevel(char board[][BORDER_WIDTH - 2]);
	void PrintChooseLevel(vector<string> FileNames, int instance, int len, int Amount_of_Files_on_screen);
	bool OpenFile(CFile& fileManager);
	int LegalButton(char input, int instance, int len, int Amount_of_Files_on_screen);
	//bool ValidateChars();
	bool DecipherScreen(char board[][BORDER_WIDTH - 2]);
	bool NecessaryItemExicst();

	MenuDecision GetMenuDecision(char board[][BORDER_WIDTH - 2]);
	void PrintMenu();
	void PrintInstructions(ScreenType type);
	void PrintGoodbye();
	void PrintCongratulation();
	void PrintPauseMenu();
	bool GameOver();
	void GameOverScreen();
	void CharacterDeathAnimation(CMovingItem& character);
	void DrawHearts();
	void CreatePrincess();
	void DrawGhost();
	
	LiveStatus AddBarrel();
	LiveStatus BarrelMoving(CMovingItem& barrel);
	LiveStatus BarrelsMoving();
	LiveStatus ExplosionBarrel(CMovingItem& barrel);
	LiveStatus GhostsMoving();
	LiveStatus GhostMoving(CMovingItem& ghost);
	LiveStatus SwitchGhostDirection(CMovingItem& ghost);
	void ResetBarrel(CMovingItem& barrel);
	bool IsHitPlayer(CPoint& barrel);
	bool BarrelFlowCollision(CMovingItem& barrel, CMovingItem::Directions direction, CPoint& newPos);
	void GhostCollision(CMovingItem& ghost);


	LiveStatus PlayerCheckNextCell(CMovingItem& character);
	CGame::LiveStatus MovePlayer(CMovingItem& character, CPoint& newPos);
	NeighboorType WhoSomeoneNextToMe(CPoint& point);
	void FallCharacter(CMovingItem& character);
	void ResetPlayer();
	void ChangeAllEntitysColor();
	void ResetMovingItems();
	void EraseCharacter(CItem& character);
	bool IsInBounds(int i, int j) const;

	string m_FileNames[AMOUNT_OF_FILES];
	string m_FileName = " "; // player must choose a screen from the options
	vector<string> m_screen = {}; // default empty
	vector<CMovingItem> m_ghosts;  // ghost vector
	bool m_DonkeyIsDead = false;
	int m_nBarrels = MAX_NUM_BARRELS;
	bool m_IsColored = true;
	bool m_IsHammer = false;
	bool m_IsHammerActive = false;
	CFile m_file;
	CMovingItem m_mario;
	CItem m_donkeykong;
	CItem m_princess;
	CItem m_hammer;
	vector<CMovingItem> m_barrels;
	CBoard m_board;
	ScreenData m_data;
	CPoint m_Legend;
};






