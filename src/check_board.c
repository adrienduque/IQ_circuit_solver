/**
 * @file check_board.c
 *
 * File where we will have a succession checking methods to determine if the current state of a board is worthy to be continued on
 * Or if we know that this state doesn't have any change of leading to a complete board
 */

/**
 * @todo new check idea in addition to those in python project :
 * if the double missing connection still exist after its corresponding piece has been played
 * we know for a fact that no other piece can fill it and thus, the board is discarded
 */

/**
 * @warning remember using this funciton in checks : extract_normal_tile_at_pos
 */

#include <local/check_board.h>