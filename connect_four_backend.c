#define _CRT_SECURE_NO_WARNINGS
#define fseeko _fseeki64
#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mongoose.h"
#include <winsock2.h>
#include <windows.h>
#include <malloc.h>

// Your original structures
struct user
{
    char name[20];
    char colour[6];
};

struct scoreboard
{
    int player1;
    int player2;
    int tie;
};

struct Board
{
    int board[7][9];
    int topindex[9];
};

// Game state to maintain between requests
struct GameState
{
    struct Board currboard;
    struct user *listofusers;
    struct scoreboard score;
    int currentRound;
    int totalRounds;
    int currentTurn;
    int gameActive;
};

// Your original game logic functions (unchanged)
int checkifgameisover(struct Board *b, int coln)
{
    int c = 0;
    for (int i = 0; i < 9; i++)
    {
        if (b->topindex[i] < 0)
        {
            c++;
        }
    }
    return (c == 9) ? 0 : 1;
}

int checkleft(struct user u, struct Board b, int row, int coln, int count)
{
    // Your original checkleft implementation
    int countl = 0;
    for (int i = coln - 1; i > coln - 4; i--)
    {
        if (i > -1)
        {
            if (!strcmp(u.colour, "red"))
            {
                if (b.board[row][i] == 1)
                {
                    countl++;
                }
                else
                {
                    break;
                }
            }
            else if (!strcmp(u.colour, "blue"))
            {
                if (b.board[row][i] == 2)
                {
                    countl++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    return countl;
}
int checkright(struct user u, struct Board b, int row, int coln, int count)
{
    int countr = 0;
    for (int i = coln + 1; i < coln + 4; i++)
    {
        if (i < 9)
        {
            if (!strcmp(u.colour, "red"))
            {
                if (b.board[row][i] == 1)
                {
                    countr++;
                }
                else
                {
                    break;
                }
            }
            else if (!strcmp(u.colour, "blue"))
            {
                if (b.board[row][i] == 2)
                {
                    countr++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    count = countr;
    if (count < 3)
    {
        count = count + checkleft(u, b, row, coln, count);
    }
    if (count == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int checktop(struct user u, struct Board b, int row, int coln, int count)
{
    int countt = 0;
    for (int i = row - 1; i > row - 4; i--)
    {
        if (i > -1)
        {
            if (!strcmp(u.colour, "red"))
            {
                if (b.board[i][coln] == 1)
                {
                    countt++;
                }
                else
                {
                    break;
                }
            }
            else if (!strcmp(u.colour, "blue"))
            {
                if (b.board[i][coln] == 2)
                {
                    countt++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    count = count + countt;
    return count;
}

int checkdown(struct user u, struct Board b, int row, int coln, int count)
{
    int countd = 0;
    for (int i = row + 1; i < row + 4; i++)
    {
        if (i < 7)
        {
            if (!strcmp(u.colour, "red"))
            {
                if (b.board[i][coln] == 1)
                {
                    countd++;
                }
                else
                {
                    break;
                }
            }
            else if (!strcmp(u.colour, "blue"))
            {
                if (b.board[i][coln] == 2)
                {
                    countd++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }
    count = countd;
    if (count < 3)
    {
        count = count + checktop(u, b, row, coln, count);
    }
    if (count == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int checkdiagonal1(struct user u, struct Board b, int row, int coln, int count)
{
    int countbr = 0;
    int i = row + 1;
    int j = coln + 1;
    int c = 0;
    while (i < 7 && j < 7 && c < 3)
    {
        if (!strcmp(u.colour, "red"))
        {
            if (b.board[i][j] == 1)
            {
                ++countbr;
            }
        }
        else if (!strcmp(u.colour, "blue"))
        {
            if (b.board[i][j] == 2)
            {
                ++countbr;
            }
        }
        ++i;
        ++j;
        ++c;
    }
    return countbr;
}
int checkdiagonal(struct user u, struct Board b, int row, int coln, int count)
{
    int counttl = 0;
    int i = row - 1;
    int j = coln - 1;
    int c = 0;
    while (i > -1 && j > -1 && c < 3)
    {
        if (!strcmp(u.colour, "red"))
        {
            if (b.board[i][j] == 1)
            {
                ++counttl;
            }
        }
        else if (!strcmp(u.colour, "blue"))
        {
            if (b.board[i][j] == 2)
            {
                ++counttl;
            }
        }
        --i;
        --j;
        ++c;
    }
    count = counttl;
    if (count < 3)
    {
        count = count + checkdiagonal1(u, b, row, coln, count);
    }
    if (count == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int checkdiagonal3(struct user u, struct Board b, int row, int coln, int count)
{
    int countbl = 0;
    int i = row + 1;
    int j = coln - 1;
    int c = 0;

    while (i > -1 && j > -1 && c < 3)
    {
        if (!strcmp(u.colour, "red"))
        {
            if (b.board[i][j] == 1)
            {
                ++countbl;
            }
        }
        else if (!strcmp(u.colour, "blue"))
        {
            if (b.board[i][j] == 2)
            {
                ++countbl;
            }
        }
        ++i;
        --j;
        ++c;
    }
    return countbl;
}
int checkdiagonal2(struct user u, struct Board b, int row, int coln, int count)
{
    int counttr = 0;
    int i = row - 1;
    int j = coln + 1;
    int c = 0;

    while (i > -1 && j > -1 && c < 3)
    {
        if (!strcmp(u.colour, "red"))
        {
            if (b.board[i][j] == 1)
            {
                ++counttr;
            }
        }
        else if (!strcmp(u.colour, "blue"))
        {
            if (b.board[i][j] == 2)
            {
                ++counttr;
            }
        }
        --i;
        ++j;
        ++c;
    }
    count = counttr;
    if (count < 3)
    {
        count = count + checkdiagonal3(u, b, row, coln, count);
    }
    if (count == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Modified play function for API use
int play(int coln, struct user u, struct Board *b)
{
    if (coln > 8 || coln < 0)
    {
        return -1; // Invalid column
    }

    if (b->topindex[coln - 1] < 0)
    {
        int flag = checkifgameisover(b, coln);
        if (flag == 0)
        {
            return -2; // Game over (tie)
        }
        return -3; // Column full
    }

    if (!strcmp(u.colour, "red"))
    {
        b->board[b->topindex[coln - 1]][coln - 1] = 1;
        b->topindex[coln - 1] = b->topindex[coln - 1] - 1;
        return 1;
    }
    if (!strcmp(u.colour, "blue"))
    {
        b->board[b->topindex[coln - 1]][coln - 1] = 2;
        b->topindex[coln - 1] = b->topindex[coln - 1] - 1;
        return 1;
    }
    return 0;
}
int checkforwinner(struct user u, struct Board b, int coln)
{
    int count = 0;
    int row = b.topindex[coln - 1] + 1;
    coln = coln - 1;
    int flag = 0;
    flag = checkright(u, b, row, coln, count);
    if (flag == 1)
    {
        return 1;
    }
    count = 0;
    flag = checkdown(u, b, row, coln, count);
    if (flag == 1)
    {

        return 1;
    }
    count = 0;
    flag = checkdiagonal(u, b, row, coln, count);
    if (flag == 1)
    {

        return 1;
    }
    count = 0;
    flag = checkdiagonal2(u, b, row, coln, count);
    if (flag == 1)
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

// Initialize game state
struct GameState *init_game_state(const char *player1_name, const char *player2_name, int rounds)
{
    struct GameState *state = malloc(sizeof(struct GameState));
    state->listofusers = (struct user *)calloc(2, sizeof(struct user));

    // Initialize players
    strncpy(state->listofusers[0].name, player1_name, 19);
    strncpy(state->listofusers[0].colour, "red", 5);
    strncpy(state->listofusers[1].name, player2_name, 19);
    strncpy(state->listofusers[1].colour, "blue", 5);

    // Initialize score
    state->score.player1 = 0;
    state->score.player2 = 0;
    state->score.tie = 0;

    // Initialize game parameters
    state->currentRound = 1;
    state->totalRounds = rounds;
    state->currentTurn = 1;
    state->gameActive = 1;

    // Initialize board
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            state->currboard.board[i][j] = 0;
        }
    }
    for (int j = 0; j < 9; j++)
    {
        state->currboard.topindex[j] = 6;
    }

    return state;
}

// API response helpers
void send_error(struct mg_connection *c, int code, const char *message)
{
    char response[200];
    snprintf(response, sizeof(response),
             "{\"success\": false, \"error\": \"%s\"}", message);
    mg_http_reply(c, code,
                  "Content-Type: application/json\r\n"
                  "Access-Control-Allow-Origin: *\r\n",
                  "%s", response);
}

void send_board_state(struct mg_connection *c, struct GameState *state)
{
    char *response = malloc(2000); // Ensure enough space for the full board
    char *ptr = response;

    ptr += sprintf(ptr, "{\"success\": true, \"board\": [");

    // Add board state
    for (int i = 0; i < 7; i++)
    {
        ptr += sprintf(ptr, "[");
        for (int j = 0; j < 9; j++)
        {
            ptr += sprintf(ptr, "%d%s",
                           state->currboard.board[i][j],
                           j < 8 ? "," : "");
        }
        ptr += sprintf(ptr, "]%s", i < 6 ? "," : "");
    }

    ptr += sprintf(ptr, "],");
    ptr += sprintf(ptr, "\"currentTurn\": %d,", state->currentTurn);
    ptr += sprintf(ptr, "\"currentRound\": %d,", state->currentRound);
    ptr += sprintf(ptr, "\"score\": {\"player1\": %d, \"player2\": %d, \"tie\": %d}",
                   state->score.player1, state->score.player2, state->score.tie);
    ptr += sprintf(ptr, "}");

    mg_http_reply(c, 200,
                  "Content-Type: application/json\r\n"
                  "Access-Control-Allow-Origin: *\r\n",
                  "%s", response);

    free(response);
}

// API endpoint handlers
static void handle_start_game(struct mg_connection *c, struct mg_http_message *hm)
{
    // Parse request
    char player1[20] = {0}, player2[20] = {0};
    int rounds = 0;

    // Fixed JSON parsing
    char *p1 = mg_json_get_str(hm->body, "$.player1");
    char *p2 = mg_json_get_str(hm->body, "$.player2");
    double rounds_d = 0;
    mg_json_get_num(hm->body, "$.rounds", &rounds_d);
    rounds = (int)rounds_d;

    if (p1)
        strncpy(player1, p1, sizeof(player1) - 1);
    if (p2)
        strncpy(player2, p2, sizeof(player2) - 1);
    free(p1);
    free(p2);

    if (strlen(player1) == 0 || strlen(player2) == 0 || rounds <= 0)
    {
        send_error(c, 400, "Invalid parameters");
        return;
    }

    struct GameState *state = init_game_state(player1, player2, rounds);
    c->fn_data = state;

    send_board_state(c, state);
}

static void handle_make_move(struct mg_connection *c, struct mg_http_message *hm)
{
    struct GameState *state = (struct GameState *)c->fn_data;
    if (!state)
    {
        send_error(c, 400, "Game not initialized");
        return;
    }

    // Parse move with fixed JSON parsing
    double column_d = 0;
    mg_json_get_num(hm->body, "$.column", &column_d);
    int column = (int)column_d;

    // Make move
    int result = play(column, state->listofusers[state->currentTurn - 1], &state->currboard);

    if (result < 0)
    {
        switch (result)
        {
        case -1:
            send_error(c, 400, "Invalid column");
            return;
        case -2:
            send_error(c, 400, "Game is a tie");
            return;
        case -3:
            send_error(c, 400, "Column is full");
            return;
        }
    }

    // Check for winner
    if (checkforwinner(state->listofusers[state->currentTurn - 1],
                       state->currboard, column))
    {
        if (state->currentTurn == 1)
        {
            state->score.player1++;
        }
        else
        {
            state->score.player2++;
        }
        state->currentRound++;
        if (state->currentRound > state->totalRounds)
        {
            state->gameActive = 0;
        }
    }

    // Update turn
    state->currentTurn = (state->currentTurn == 1) ? 2 : 1;

    send_board_state(c, state);
}

// Main event handler
static void fn(struct mg_connection *c, int ev, void *ev_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *hm = (struct mg_http_message *)ev_data;

        // Handle CORS preflight
        if (mg_match(hm->uri, mg_str("/api/*"), NULL))
        {
            if (mg_strcmp(hm->method, mg_str("OPTIONS")) == 0)
            {
                mg_http_reply(c, 200,
                              "Allow: POST, GET, OPTIONS\r\n"
                              "Access-Control-Allow-Origin: *\r\n"
                              "Access-Control-Allow-Methods: POST, GET, OPTIONS\r\n"
                              "Access-Control-Allow-Headers: Content-Type\r\n",
                              "");
                return;
            }
        }

        // Route API requests
        if (mg_match(hm->uri, mg_str("/api/start"), NULL))
        {
            handle_start_game(c, hm);
        }
        else if (mg_match(hm->uri, mg_str("/api/move"), NULL))
        {
            handle_make_move(c, hm);
        }
        else
        {
            send_error(c, 404, "Not found");
        }
    }
}

int main()
{
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);

    // Start server
    mg_http_listen(&mgr, "http://localhost:8000", fn, NULL);
    printf("Starting Connect Four server on port 8000\n");

    // Event loop
    for (;;)
        mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
    return 0;
}