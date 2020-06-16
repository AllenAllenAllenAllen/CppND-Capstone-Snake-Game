#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      dis(5.0, 2.0),
      random_num(1, 3) {
  GenerateFood();
  for (auto &food : foods) {
    PlaceFood(food);
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, foods);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::GenerateFood() {
  int num_foods = random_num(engine);
  if (num_foods <= foods.size()) {
    return;
  }
  int curr_size = foods.size();
  for (int i = 0; i < num_foods - curr_size; i++) {
    double number = dis(gen);
    if (number < 4) {
      // green candy (same score but no speed addition)
      foods.emplace_back(Food(0x00, 0x80, 0x00, 1, false));
    } else if (number > 6) {
      // orange candy (same as before)
      foods.emplace_back(Food(0x80, 0x00, 0x00, 2, true));
    } else {
      // red candy (double score with speed addition)
      foods.emplace_back(Food(0xFF, 0xCC, 0x00, 1, true));
    }
  }
}

void Game::PlaceFood(Food &food) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    bool is_occupied_by_food = false;
    for (auto &f : foods) {
      if (x == f.position.x && y == f.position.y) {
        is_occupied_by_food = true;
        break;
      }
    }
    if (is_occupied_by_food) {
      continue;
    }

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.position.x = x;
      food.position.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  for (int i = 0; i < foods.size(); i++) {
    Food food = foods[i];
    if (food.position.x != new_x || food.position.y != new_y) {
      continue;
    }
    if (food.inc_speed) {
      snake.speed += 0.02;
    }
    score += food.points;
    foods.erase(foods.begin() + i);
    snake.GrowBody();
    GenerateFood();
    for (auto &f : foods) {
      PlaceFood(f);
    }
    return;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }