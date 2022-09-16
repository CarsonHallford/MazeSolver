// Carson Hallford
// I debugged in Visual Studio 19'
// I got examples of flood fill algorithm from stack overflow and techiedelight
// Link: https://stackoverflow.com/questions/9191428/maze-solving-algorithm-in-c
// Link: https://www.techiedelight.com/flood-fill-algorithm/
// Peer reviewed by: Kevin Fogle

#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// Make a print function for maze and drop it throughout program to see where it
// segfaults

struct Hash {
  size_t operator()(const std::pair<int, int>& p) { return p.first * p.second; }
};  // unordered_set<std::pair<int, int>, Hash> set();

static void solve() {
  int width, height;
  std::cin >> width >> height;  // O(1)

  // Fill the maze with INT_MAX.
  std::vector<std::vector<int>> maze;
  maze.resize(width, std::vector<int>(height, INT_MAX));  // O(n)

  // Read the maze, adding the walls as -1.
  std::cin.ignore();

  for (int i = 0; i < height; i++) {  // O (n^2)
    std::string n;
    std::getline(std::cin, n);
    for (int j = 0; j < width; j++) {
      if (n[j] == 'x') maze[j][i] = -1;
    }
  }

  // Read the target cell.
  int endX, endY;
  std::cin >> endX >> endY;  // O(1)

  // Start at the top-left, and do a BFS.
  std::queue<std::pair<int, int>> queue;
  queue.push({0, 0});  // O(1)
  maze[0][0] = 0;      // O(1)

  std::set<std::pair<int, int>> visited;
  std::pair<int, int> checks[] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  for (int dist = 0; !queue.empty(); dist++) {  //  O(4 * n * n ) ~ // O(n^2)
    // start at 0,0
    std::pair<int, int> current = queue.front();
    int currentX = current.first, currentY = current.second;

    queue.pop();  // O(1)

    if (!visited.count(current)) {  // O(1)
      if (currentX == endX && currentY == endY) {
        break;
      }
      visited.insert(current);  // O(1)

      for (auto check : checks) {  // O(4n) in this case, otherwise O(n)
        // add offset to current
        int checkX = currentX + check.first, checkY = currentY + check.second;

        // Check out of bounds
        if (checkX < 0 || checkY < 0 || checkX >= width || checkY >= height) {
          continue;
        }
        // If empty spot, set distance
        if (maze[checkX][checkY] == INT_MAX) {                  // O(1)
          queue.push({checkX, checkY});                         // O(1)
          maze[checkX][checkY] = maze[currentX][currentY] + 1;  // O(n)
        }
      }
    }
  }

  // Backtrack starting at the target.
  std::vector<std::string> path;
  std::stack<std::pair<int, int>> temp;
  path.resize(width, std::string(height, ' '));  // O(n)
  path[endX][endY] = 'o';                        // O(n)

  // Push  backtrack start on stack
  // Until we reach 0,0 keep going
  while (endX || endY) {                 // O(n^2)
    int nextVal = maze[endX][endY] - 1;  // O(1)
    // L, R, U, D
    for (auto check : checks) {  // O(4) worst case
      int checkX = endX + check.first, checkY = endY + check.second;

      if (checkX < 0 || checkY < 0 || checkX >= width ||
          checkY >= height)  // O(1)
      {
        continue;
      }
      if (maze[checkX][checkY] == nextVal) {  // O(1)
        endX = checkX;
        endY = checkY;

        break;
      }
    }
    path[endX][endY] = 'o';  // O(n)
  }

  for (int i = 0; i < height; i++)  // O(n^2)
  {
    for (int j = 0; j < width; j++) {
      std::cout << path[j][i];  // O(1)
    }
    std::cout << std::endl;  // O(1)
  }
}

int main() {
  solve();
  return 0;
}