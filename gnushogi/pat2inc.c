/*
 * FILE: pat2inc.c
 *
 *     Convert GNU Shogi pattern textfile to an include file.
 *
 * ----------------------------------------------------------------------
 *
 * Copyright (c) 2012 Free Software Foundation
 *
 * GNU SHOGI is based on GNU CHESS
 *
 * This file is part of GNU SHOGI.
 *
 * GNU Shogi is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * GNU Shogi is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with GNU Shogi; see the file COPYING. If not, see
 * <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------
 *
 */

#include "version.h"
#include "gnushogi.h"
#include "pattern.h"


extern void ReadOpeningSequences(short *pindex);
extern void WriteOpeningSequences(short pindex);

/*

small_short PieceCnt[2];
small_short PieceList[2][NO_SQUARES];
small_short PieceIndex[NO_SQUARES];

small_short board[NO_SQUARES];
small_short color[NO_SQUARES];

*/

void
test_distance()
{
    short side, piece, f, t, d;

    for (side = 0; side <= 1; side++)
    {
        printf("SIDE = %d\n", side);

        for (piece = pawn; piece <= king; piece++)
        {
            printf("PIECE = %d\n", piece);

            for (f = 0; f < NO_SQUARES; f++)
            {
                printf("FROM %d TO ", f);

                for (t = 0; t < NO_SQUARES; t++)
                {
                    d = piece_distance(side, piece, f, t);

                    if (d != CANNOT_REACH)
                        printf("%d:%d ", t, d);
                }

                printf("\n");
            }
        }
    }

}



int
main(int argc, char **argv)

{

    short sq, side, max_pattern_data;

#if defined(EXTLANGFILE)
    char *Lang = NULL;
#endif

#ifdef TEST_DISTANCE
    short d;
    char  s[80];
#endif

    display_type = DISPLAY_RAW;

#if defined(EXTLANGFILE)
    InitConst(Lang);
#endif

    Initialize_data();

    for (sq = 0; sq < NO_SQUARES; sq++)
    {
        board[sq] = no_piece;
        color[sq] = neutral;
    }

    ClearCaptured();

    for (side = 0; side <= 1; side++)
        PieceCnt[side] = -1;

#ifdef TEST_DISTANCE
    strcpy(s, "g6i k5i g4i p9g p8g r* s3h p7g b8h B* S5f");

    if (string_to_board_color(s))
    {
        printf("ERROR IN string_to_board_color");
        exit(1);
    }
    else
    {
        UpdateDisplay(0, 0, 1, 0);
    }

    d = pattern_distance(black, &pattern);

    printf("distance = %d\n", d);

#endif

    ReadOpeningSequences(&max_pattern_data);
    WriteOpeningSequences(max_pattern_data);

    return 0;
}

