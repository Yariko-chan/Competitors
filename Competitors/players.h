#pragma once

void add_player(void);
void view_players_list(void);
void delete_player(void);
void edit_player(void);

void filter_players(const Player* p_list, const int count); 
void search(const Player* p_list, const int count);
void sort_players_list(Player* p_list, const int p_count);