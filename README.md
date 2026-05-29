# Langton's Ant — Multi-Agent Grid Simulator

A generalised implementation of **Langton's Ant** in C++, supporting multiple simultaneous ants on a configurable binary grid with toroidal (wrap-around) boundary conditions.

---

## Background

Langton's Ant is a two-dimensional cellular automaton with deceptively simple rules:

- On a **white cell**: turn 90° right, flip the cell to black, move forward
- On a **black cell**: turn 90° left, flip the cell to white, move forward

Despite this simplicity, the system produces complex emergent behaviour — initially chaotic, eventually resolving into a structured repeating "highway" pattern after ~10,000 steps on a standard grid.

This implementation extends the classic model to support **multiple ants** operating concurrently on the same grid, with configurable grid dimensions and step counts.

---

## Features

- **Multi-agent simulation** — arbitrary number of ants, each with independent position and direction state
- **Toroidal boundary** — ants that walk off one edge reappear on the opposite side, creating a seamless infinite-plane approximation
- **Conflict handling** — duplicate starting positions and out-of-bounds placements are silently filtered at initialisation
- **Step-by-step grid output** — prints the full grid state after every simulation step
- **Binary grid representation** — cells are `0` (white) or `1` (black), printed as a compact integer matrix

---

## Input Format

Input is read from stdin in the following order:

```
<steps> <num_ants>
<grid_rows> <grid_cols>
<ant1_row> <ant1_col>
<ant2_row> <ant2_col>
...
```

| Field | Description |
|-------|-------------|
| `steps` | Number of simulation steps to run |
| `num_ants` | Number of ants to place |
| `grid_rows`, `grid_cols` | Grid dimensions |
| `ant_row`, `ant_col` | Starting position of each ant (0-indexed) |

All ants start facing **North**. Out-of-bounds positions and duplicate placements are ignored.

---

## Output Format

The initial grid state is printed first, followed by the full grid after each step, separated by blank lines.

Each grid row is printed as a compact string of `0`s and `1`s (no spaces).

### Example

**Input:**
```
3 1
5 5
2 2
```

**Output:**
```
00000
00000
00000
00000
00000

00000
00000
00100
00000
00000

00000
00000
00110
00000
00000

00000
00000
00110
00010
00000
```

---

## Algorithm

### Initialisation
1. Read grid dimensions and allocate an `R × C` matrix of zeros
2. Read ant positions, filtering out-of-bounds and duplicate entries using a `set<pair<int,int>>`
3. Assign each valid ant a starting direction of `N` (North)

### Simulation Loop (per step, per ant)
1. Apply toroidal wrap to the ant's current position
2. Read the cell value at that position
3. Apply the turn rule:
   - **White (0):** turn right (`N→E→S→W→N`), flip cell to 1, move forward
   - **Black (1):** turn left (`N→W→S→E→N`), flip cell to 0, move forward
4. Update the ant's stored position and direction
5. After all ants have moved, print the full grid

### Direction Maps

```
White cell (turn right):   N→E, E→S, S→W, W→N
Black cell (turn left):    N→W, W→S, S→E, E→N
```

Movement is always one step in the **new** direction after turning.

---

## Boundary Conditions

The grid wraps toroidally. An ant at row `0` moving North reappears at row `R-1`, and vice versa. The same applies to columns. Wrap detection is applied at the start of each ant's turn, before the cell is read.

---

## Building

Requires a C++11-compatible compiler.

```bash
g++ -O2 -o langtons_ant langtons_ant.cpp
```

---

## Usage

```bash
./langtons_ant < input.txt
```

Or interactively:

```bash
./langtons_ant
3 1
5 5
2 2
```

---

## File Structure

```
langtons-ant/
├── langtons_ant.cpp    # Full simulator implementation
└── README.md
```

---

## Implementation Notes

- **Direction state** is stored as a `char` (`N`, `S`, `E`, `W`) per ant, looked up via `std::map` for clean rule expression
- **Collision behaviour** — when two ants occupy the same cell simultaneously, each applies the turn rule independently to whatever cell state it reads; no inter-ant collision logic is applied
- **Grid storage** — `vector<vector<int>>` sized at runtime from parsed input; no fixed limits on grid dimensions beyond available memory

---

## Author

**Ailton Ilidio Eugenio Novele**  
BSc Computer Science & Computational Applications — University of the Witwatersrand  
ailtonnovele24@gmail.com
