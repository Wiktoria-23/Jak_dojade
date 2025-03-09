# Jak dojadę
<p align="justify">
The purpose of this program is to determine shortest path between two cities on a given map. First line of input is map size, followed by the whole map. After that, amount of flights and flights details are given. Finally, number of queries and queries themselves are given. Queries have two types: type 0 returns distance between cities and type 1 returns distance and path between cities. An example input looks like this:
  <pre>
  20 20
  .........GDANSK.....
  ........*...........
  ........#...........
  ........#...........
  *##################.
  #SZCZECIN.........#.
  #.................#.
  ##................#.
  .############*#####.
  .#...WARSZAWA.......
  .#..................
  .#############......
  .#...........#......
  .#..WROCLAW.##......
  .#..*.......*.......
  .####.......#KIELCE.
  ......*##.#########.
  .OPOLE..#.*.......#.
  ........#.KRAKOW..#.
  ........###########.
  0
  3
  KIELCE KRAKOW 0
  KRAKOW GDANSK 0
  KRAKOW GDANSK 1
  </pre>
  The program parses provided map and saves result as a graph representation. Then,  
  it processes queries and returns results. Example result looks like this:
  <pre>
  5
  40
  40 KIELCE SZCZECIN
  </pre>
</p>

## Implementation
Paths between cities are searched using BFS algorithm and shortest path between cities is calculated using Dijkstra's algorithm. Efficiency of program is improved by implementing a priority queue and a linked list.
