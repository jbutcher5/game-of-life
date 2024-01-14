#include "game.h"
#include "field.h"
#include <stdbool.h>
#include <nmmintrin.h>

bool *RequestBuffer(void) {
  static bool buffer1[BUFF_SIZE];
  static bool buffer2[BUFF_SIZE]; 
  static bool i = 0;

  if (!i) {
    i++;
    return (bool *)buffer1;
  }

  i--;
  return (bool *)buffer2;
}

static bool GetCell(bool *buffer, int index) {
  if (index < 0 || index > BUFF_SIZE)
    return 0;

  return buffer[index];
}

static int AdjCells(bool *buffer, int index) {
  // First 3 bits are top 3 adj cell from left to right
  // Next 2 bits are left and right adj cells respectfully
  // Last 3 bits are bottom 3 adj cells from left to right

  int result = GetCell(buffer, index - BUFF_WIDTH - 1);

  int neighbors[7] = {index - BUFF_WIDTH, index - BUFF_WIDTH + 1,
		    index - 1, index + 1, index + BUFF_WIDTH - 1, index + BUFF_WIDTH,
		    index + BUFF_WIDTH + 1};

  for (int i = 0; i < 7; i++) {
    result <<= 1;
    result |= GetCell(buffer, neighbors[i]);
  }

  return result;
}

typedef enum {
  Unknown = 0,
  Dead,
  Alive
} CellState;

bool UpdateCell(int adjcells, bool current_state) {
  static CellState cell_enabled_cache[256];
  static CellState cell_disabled_cache[256];

  CellState *cache = (CellState*)cell_enabled_cache;
  
  if (!current_state)
    cache = cell_disabled_cache;

  CellState new_state = cache[adjcells];
  
  if (new_state != Unknown)
    return new_state - 1;

  int n_adj = _mm_popcnt_u32(adjcells);

  if (!current_state && n_adj == 3) {
    cache[adjcells] = Alive;
    return 1;
  }

  if (current_state && (n_adj < 2 || n_adj > 3)) {
    cache[adjcells] = Dead;
    return 0;
  }

  if (current_state && (n_adj == 2 || n_adj == 3)) {
    cache[adjcells] = Alive;
    return 1;
  }

  cache[adjcells] = Dead;
  return 0;
}

bool *UpdateCells(bool *buffer) {
  bool *nextbuf = RequestBuffer();

  for (int i = 0; i < BUFF_SIZE; i++)
    nextbuf[i] = UpdateCell(AdjCells(buffer, i), buffer[i]);

  return nextbuf;
}


