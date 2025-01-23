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
#include "string.h"
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
	enum ScorePoints {GHOST_HIT = 50, BARREL_HIT = 50, DONKEY_KONG_HIT = 150, LIVES_BONUS = 75};
	
	static constexpr int ESC_KEY = 27;
	static constexpr int MARIO_LIVES = 3;
	static constexpr char PAGE_RIGHT = '>';
	static constexpr char PAGE_LEFT = '<';
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
	static constexpr int EXPLOSION_TIME = 200;
	static constexpr int MAX_NUM_BARRELS = 10;
	static constexpr int BARREL_FREQUENCY_BIRTH = 25;
	static constexpr int MAX_FALL_BARREL = 8;

	void ReadDirectory();
	MenuDecision Paused();
	void LevelSelector(int& ind, char board[][BORDER_WIDTH - 2]);
	void StartGame(char board[][BORDER_WIDTH - 2], int );
	void Init(char board[][BORDER_WIDTH - 2]);
	MenuDecision PlayLoop();
	MenuDecision GetMenuDecision(char board[][BORDER_WIDTH - 2], int &ind);
	void ResetScreen();
	void ChooseLevel(char board[][BORDER_WIDTH - 2], int &ind);
	void PrintChooseLevel(int instance, int len, int Amount_of_Files_on_screen) const;
	bool OpenFile(CFile& fileManager);
	bool LegalButton(char& input, int instance, int len, int Amount_of_Files_on_screen) const;
	bool DecipherScreen(char board[][BORDER_WIDTH - 2]);
	bool NecessaryItemExicst() const;
	void TurnOffColor();

	void PrintMenu() const;
	void PrintInstructions(ScreenType type) const;
	void PrintGoodbye() const;
	void PrintCongratulation() const;
	void PrintPauseMenu() const;
	void GameOverScreen() const;
	void CharacterDeathAnimation(CMovingItem& character);
	void DrawHearts() const;
	void DrawGhost() const;
	bool GameOver();
	
	LiveStatus AddBarrel();
	LiveStatus BarrelMoving(CMovingItem& barrel);
	LiveStatus BarrelsMoving();
	LiveStatus ExplosionBarrel(CMovingItem& barrel);
	LiveStatus GhostsMoving();
	LiveStatus GhostMoving(CMovingItem& ghost);
	LiveStatus SwitchGhostDirection(CMovingItem& ghost);
	void ResetBarrel(CMovingItem& barrel);
	bool IsHitPlayer(CPoint& Entity) const {return (Entity == m_mario);};
	bool BarrelFlowCollision(CMovingItem& barrel, CMovingItem::Directions direction, CPoint& newPos);
	void GhostCollision(CMovingItem& ghost);
	void UseHammer();
	void DisplayLegend() const;

	LiveStatus PlayerCheckNextCell(CMovingItem& character);
	LiveStatus MovePlayer(CMovingItem& character, CPoint& newPos);
	NeighboorType WhoSomeoneNextToMe(CPoint& point) const;
	void FallCharacter(CMovingItem& character);
	void ResetPlayer();
	void ChangeAllEntitysColor();
	void ResetMovingItems();
	void EraseCharacter(CItem& character);
	bool IsInBounds(int i, int j) const;


	vector<string> m_FileNames;
	string m_FileName = " "; // player must choose a screen from the options
	vector<string> m_screen = {}; // default empty
	vector<CMovingItem> m_ghosts;  // ghost vector
	bool m_DonkeyIsDead = false;
	int m_nBarrels = MAX_NUM_BARRELS;
	int m_score{};
	bool m_IsColored = true;
	bool m_IsHammer = false;
	bool m_IsHammerActive = false;
	bool m_LevelWasChoosen = false;
	CColorPoint::c_color m_HammerEntityColor = CColorPoint::BLUE;
	CFile m_file;
	CMovingItem m_mario;
	CItem m_donkeykong;
	CItem m_princess;
	CItem m_hammer;
	vector<CMovingItem> m_barrels;
	CBoard m_board;
	CPoint m_Legend;

};






