#include "game.h"
#include "field.h"
#include <stdbool.h>
#include <nmmintrin.h>
#include <omp.h>
#include <stdio.h>

bool *RequestBuffer(void) {
  // Returns a pointer to a new static buffer
  // flip-flops between returning buffer1 and buffer2

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

static inline bool GetCell(bool *buffer, int index) {
  return index >= 0 && index <= BUFF_SIZE && buffer[index];
}

static int AdjCells(bool *buffer, int index) {
  // First 3 bits are top 3 adj cell from left to right
  // Next 2 bits are left and right adj cells respectfully
  // Last 3 bits are bottom 3 adj cells from left to right

  int result = GetCell(buffer, index - BUFF_WIDTH - 1);

  int neighbours[7] = {index - BUFF_WIDTH, index - BUFF_WIDTH + 1,
		    index - 1, index + 1, index + BUFF_WIDTH - 1, index + BUFF_WIDTH,
		    index + BUFF_WIDTH + 1};

  for (int i = 0; i < 7; i++) {
    result <<= 1;
    result |= GetCell(buffer, neighbours[i]);
  }

  return result;
}

// Define cell states

typedef enum {
  Unknown = 0,
  Dead,
  Alive
} CellState;

bool UpdateCell(int adjcells, bool current_state) {
  // Create two static caches
 
  static CellState cell_enabled_cache[256];
  static CellState cell_disabled_cache[256];

  // Select the correct cache for the cells state
  
  CellState *cache = (CellState*)cell_enabled_cache;
  
  if (!current_state)
    cache = cell_disabled_cache;

  // Retrieve cached cell state
  
  CellState new_state = cache[adjcells];
  
  if (new_state != Unknown)
    // Dead = 1, Alive = 2
    // sub 1 to get state
    return new_state - 1; 

  // Count number of active adjacent cells
  int n_adj = _mm_popcnt_u32(adjcells);

  // Perform cell rules and cache result
  
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

  omp_set_dynamic(0);
  omp_set_num_threads(5);
  
  // Iterate through each cell and generate a new state
#pragma omp parallel
  {
 
#pragma omp for
  for (int i = 0; i < BUFF_SIZE; i++) {
    nextbuf[i] = UpdateCell(AdjCells(buffer, i), buffer[i]);
    
    printf("%d\n", omp_get_thread_num());
  }

  
  }
    
  return nextbuf;
}


