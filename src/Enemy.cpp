#include <fstream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "entity/Enemy.h"
#include "Widget.h"
#include "StateManager.h"
#include "State.h"
#include "GameState.h"
#include "utility/Direction.h"

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Entity::draw(target, states);
  target.draw(damage_bar_, states);
  target.draw(health_bar_, states);
  if (is_mouse_in_) {
    const sf::Font& font = State::GetFontResourceManager().GetOrLoadResource(
        "assets/font/default.ttf");
    sf::Text name_of_enemy(name_, font, 10);
    name_of_enemy.setFillColor(sf::Color::Red);
    name_of_enemy.setPosition(x_, y_ - 20);
    target.draw(name_of_enemy, states);
  }
}

void Enemy::Save(std::ostream& out) {
  out << id_ << std::endl;
  out << source_ << std::endl;
  out << position_ << std::endl;
  out << current_sprite_rect_.left << " " << current_sprite_rect_.top << std::endl;
  out << current_sprite_rect_.width << " " << current_sprite_rect_.height << std::endl;
  out << delay_for_sprite_change_ << std::endl;
  current_tile_.Save(out);
  out << static_cast<int>(direction_of_move_) << " " << destination_point_ << std::endl;
  out << health_ << std::endl;
  poison_booster_.Save(out);
  freeze_booster_.Save(out);
}

void Enemy::DoMove() {
  std::vector<std::pair<Point, Direction>> possible_moves =
      GetAvailableMoves(static_cast<int>(position_.x), static_cast<int>(position_.y));
  if (position_ == destination_point_) {
    if (possible_moves.empty()) {
      if (state_.GetStateManager().game_ptr_->GetMap()->
          GetTile(static_cast<int>(position_.x / 60), static_cast<int>(y_ / 60)).GetNumber() == 1) {
        std::shared_ptr<Base> base_ptr = state_.GetStateManager().game_ptr_->GetBase();
        DoDamage(base_ptr);
        return;
      }
    } else {
      std::mt19937 generator(
          static_cast<unsigned int>(std::chrono::steady_clock::now()
              .time_since_epoch().count()));

      std::uniform_int_distribution<int> distribution_of_index(
          0, static_cast<int>(possible_moves.size() - 1));

      Point new_destination;
      Direction direction;
      std::tie(new_destination, direction) =
          possible_moves[distribution_of_index(generator)];
      destination_point_ = new_destination;
      direction_of_move_ = direction;
    }
  }
  DoMove(direction_of_move_);
}

void Enemy::DoMove(const Direction& direction) {
  direction_of_move_ = direction;
  switch (direction) {
    case Direction::North:position_.y = std::max(destination_point_.y, position_.y - speed_);
      y_ = static_cast<int>(position_.y - sprite_.getGlobalBounds().height);
      break;
    case Direction::East:position_.x = std::min(destination_point_.x, position_.x + speed_);
      x_ = static_cast<int>(position_.x - sprite_.getGlobalBounds().width);
      break;
    case Direction::West:position_.x = std::max(destination_point_.x, position_.x - speed_);
      x_ = static_cast<int>(position_.x - sprite_.getGlobalBounds().width);
      break;
    case Direction::South:position_.y = std::min(destination_point_.y, position_.y + speed_);
      y_ = static_cast<int>(position_.y - sprite_.getGlobalBounds().height);
      break;
    default:break;
  }

  CheckAndChangeCoordinates();
  state_.GetStateManager().game_ptr_->ChangeEnemyPriority(
      id_, DrawPriority(static_cast<int>(position_.y + 100), this));
  health_bar_.setPosition(x_, y_);
  damage_bar_.setPosition(x_, y_);
  sprite_.setPosition(static_cast<float>(x_), static_cast<float>(y_));
  ChangeCurrentSpriteRect();
  Tile tile_after_move = state_.GetStateManager().game_ptr_->
      GetMap()->GetTile(static_cast<int>(position_.x) / 60, static_cast<int>(position_.y) / 60);
  ChangeDirectionTile(tile_after_move);
  previous_direction_ = direction;
}

Enemy::Enemy(std::string path, double x, double y,
             const Tile& current_tile, const Direction& direction,
             State& state)
    : Entity(state, DrawPriority(static_cast<int>(y + 100), this)),
      source_(std::move(path)),
      name_(),
      frames_up_(1),
      frames_down_(1),
      frames_left_(1),
      frames_right_(1),
      frames_(frames_right_),
      current_sprite_rect_(),
      max_delay_for_sprite_change_(10),
      delay_for_sprite_change_(max_delay_for_sprite_change_),
      current_tile_(current_tile),
      direction_of_move_(direction),
      destination_point_(),
      max_health_(0),
      health_(0),
      health_bar_(),
      damage_bar_(),
      default_speed_(0),
      speed_(0),
      power_(0),
      drop_(0),
      position_(),
      is_alive_(true),
      poison_booster_(state, 50),
      freeze_booster_(state, 0),
      moving_up_sprite_(),
      moving_down_sprite_(),
      moving_right_sprite_(),
      moving_left_sprite_(),
      previous_direction_() {
  position_ = Point(x, y);
  Init();
}

Enemy::Enemy(State& state, std::istream& in) :
    Entity(state, DrawPriority(static_cast<int>(100), this)),
    source_(),
    name_(),
    frames_up_(1),
    frames_down_(1),
    frames_left_(1),
    frames_right_(1),
    frames_(frames_right_),
    current_sprite_rect_(),
    max_delay_for_sprite_change_(10),
    delay_for_sprite_change_(max_delay_for_sprite_change_),
    current_tile_(),
    direction_of_move_(),
    destination_point_(),
    max_health_(0),
    health_(0),
    health_bar_(),
    damage_bar_(),
    default_speed_(0),
    speed_(0),
    power_(0),
    drop_(0),
    position_(),
    is_alive_(true),
    poison_booster_(state, 50),
    freeze_booster_(state, 0),
    moving_up_sprite_(),
    moving_down_sprite_(),
    moving_right_sprite_(),
    moving_left_sprite_(),
    previous_direction_() {
  in >> id_;
  in >> source_;
  in >> position_;

  Init();

  int left(0), top(0), width(0), height(0);
  in >> left >> top;
  in >> width >> height;
  current_sprite_rect_ = sf::IntRect(left, top, width, height);
  sprite_.setTextureRect(current_sprite_rect_);
  in >> delay_for_sprite_change_;
  current_tile_ = Tile(in);
  int move_id(0);
  in >> move_id >> destination_point_;
  direction_of_move_ = static_cast<Direction>(move_id);
  in >> health_;
  poison_booster_.LoadSave(in);
  freeze_booster_.LoadSave(in);
}

void Enemy::Init() {
  LoadSpritesForMoving(source_);
  sound_of_entity_.setBuffer(State::GetSoundResourceManager()
                                 .GetOrLoadResource("assets/sounds/enemy.wav"));
  std::ifstream reader(source_ + "/config.txt");
  getline(reader, name_);
  reader >> frames_up_ >> frames_down_ >> frames_left_ >> frames_right_;
  frames_ = frames_up_;
  reader >> drop_;
  reader >> health_ >> speed_ >> power_;
  default_speed_ = speed_;
  icon_sprite_.setPosition(650, 230);
  sprite_.setTextureRect(sf::IntRect(0, 0, sprite_.getTexture()->getSize().x,
                                     sprite_.getTexture()->getSize().y / frames_up_));

  destination_point_ = position_;
  x_ = static_cast<int>(position_.x - sprite_.getGlobalBounds().width);
  y_ = static_cast<int>(position_.y - sprite_.getGlobalBounds().height);
  sprite_.setPosition(static_cast<float>(x_), static_cast<float>(y_));
  max_health_ = health_;
  health_bar_.setFillColor(sf::Color(0, 255, 0));
  health_bar_.setPosition(x_, y_);
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getGlobalBounds().width, 3));
  damage_bar_.setFillColor(sf::Color(255, 0, 0));
  damage_bar_.setPosition(x_, y_);
  damage_bar_.setSize(sf::Vector2f(sprite_.getGlobalBounds().width, 3));
}

EnemyCreator::EnemyCreator(State& state) :
    state_(state),
    spawn_points_(),
    enemy_types_(),
    current_cooldown_(0),
    cooldown_(0),
    delta_(0) {}

void EnemyCreator::Load(const std::string& level_path) {
  LoadSpawnPointsAndDirections(level_path + "/spawn_points.txt");

  std::ifstream fin(level_path + "/enemies.txt");
  int amount_of_waves;
  fin >> amount_of_waves;
  int amount_of_enemies_per_wave;
  fin >> amount_of_enemies_per_wave;
  fin >> cooldown_;
  fin >> delta_;
  current_cooldown_ = cooldown_;
  state_.GetStateManager().game_ptr_->SetAmountOfEnemiesPerWave(amount_of_enemies_per_wave);
  state_.GetStateManager().game_ptr_->SetAmountOfWaves(amount_of_waves);
  int count_of_types;
  fin >> count_of_types;
  enemy_types_.resize(static_cast<unsigned long long int>(count_of_types));
  for (auto& enemy_type : enemy_types_) {
    fin >> enemy_type;
  }
}

void EnemyCreator::LoadSpawnPointsAndDirections(const std::string& path_to_file) {
  spawn_points_.clear();
  std::ifstream reader(path_to_file);
  int x, y;
  Direction direction;
  while (reader >> x >> y) {
    reader >> direction;
    spawn_points_.emplace_back(std::make_pair(x, y), direction);
  }
  reader.close();
}

void EnemyCreator::CreateSomeEnemies(int64_t count) {
  current_cooldown_--;
  if (current_cooldown_ == 0) {
    int cnt = state_.GetStateManager().game_ptr_->GetAmountOfEnemiesPerWave();
    state_.GetStateManager().game_ptr_->SetAmountOfEnemiesPerWave(cnt + delta_);
    current_cooldown_ = cooldown_;
  }
  std::mt19937 generator(
      static_cast<unsigned int>(std::chrono::steady_clock::now().
          time_since_epoch().count()));
  std::uniform_int_distribution<int64_t>
      distribution_of_points(0, spawn_points_.size() - 1);

  std::uniform_int_distribution<int> distribution_of_type(
      0, static_cast<int>(enemy_types_.size() - 1));

  for (int64_t i = 0; i < count; ++i) {
    int type = distribution_of_type(generator);
    std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();
    auto point_of_spawn_with_direction = spawn_points_[distribution_of_points(generator)];
    const Tile& spawn_tile = map->GetTile(
        point_of_spawn_with_direction.first.first,
        point_of_spawn_with_direction.first.second);
    state_.GetStateManager().
        game_ptr_->AddNewEnemy("assets/enemies/" + enemy_types_[type],
                               spawn_tile.RandomX(),
                               spawn_tile.RandomY(),
                               point_of_spawn_with_direction.second);
  }
}

int EnemyCreator::GetHealthFromType(const EnemyType& type) {
  switch (type) {
    case EnemyType::VeryHigh:return 1000;
    case EnemyType::High:return 500;
    case EnemyType::Middle:return 250;
    case EnemyType::Low:return 100;
    default:return 0;
  }
}

double EnemyCreator::GetSpeedByType(const EnemyType& type) {
  switch (type) {
    case EnemyType::VeryHigh:return 0.2;
    case EnemyType::High:return 0.4;
    case EnemyType::Middle:return 0.8;
    case EnemyType::Low:return 1;
    default:return 0;
  }
}

void EnemyCreator::LoadSave(std::istream& in) {
  in >> current_cooldown_;
}

void EnemyCreator::Save(std::ostream& out) {
  out << current_cooldown_ << std::endl;
}

void Enemy::DoDamage(const std::shared_ptr<Entity>& other_entity) {
  other_entity->DecreaseHealth(power_);
}

std::vector<std::pair<Point, Direction>> Enemy::GetAvailableMoves(int x, int y) const {
  std::vector<std::pair<Point, Direction>> available_moves;

  std::shared_ptr<Map> map = state_.GetStateManager().game_ptr_->GetMap();

  if (map->IsMoveAvailable(Direction::North, x, y)) {
    available_moves.emplace_back(Point(position_.x, map->GetTile(x / 60, y / 60 - 1).RandomY()), Direction::North);
  }

  if (map->IsMoveAvailable(Direction::West, x, y)) {
    available_moves.emplace_back(Point(map->GetTile(x / 60 - 1, y / 60).RandomX(), position_.y), Direction::West);
  }

  if (map->IsMoveAvailable(Direction::East, x, y)) {
    available_moves.emplace_back(Point(map->GetTile(x / 60 + 1, y / 60).RandomX(), position_.y), Direction::East);
  }

  if (map->IsMoveAvailable(Direction::South, x, y)) {
    available_moves.emplace_back(Point(position_.x, map->GetTile(x / 60, y / 60 + 1).RandomY()), Direction::South);
  }

  return available_moves;
}

void Enemy::ChangeDirectionTile(const Tile& new_tile) {
  current_tile_ = new_tile;
}

void Enemy::ChangeCurrentSpriteRect() {
  if (previous_direction_ != direction_of_move_) {
    auto sprite_and_amount_of_frames = ChooseSpriteFromDirection();
    auto position_of_sprite = sprite_.getPosition();
    sprite_ = sprite_and_amount_of_frames.first;
    sprite_.setPosition(position_of_sprite);
    frames_ = sprite_and_amount_of_frames.second;
    current_sprite_rect_.left = 0;
    current_sprite_rect_.top = 0;
    int width = sprite_.getTexture()->getSize().x;
    int height = sprite_.getTexture()->getSize().y / frames_;

    current_sprite_rect_ = sf::IntRect(current_sprite_rect_.left,
                                       (current_sprite_rect_.top + height) % (height * frames_), width, height);
    sprite_.setTextureRect(current_sprite_rect_);
    icon_sprite_.setTextureRect(current_sprite_rect_);
    delay_for_sprite_change_ = max_delay_for_sprite_change_;
  }
  if (delay_for_sprite_change_ == 0) {
    int width = sprite_.getTexture()->getSize().x;
    int height = sprite_.getTexture()->getSize().y / frames_;

    current_sprite_rect_ = sf::IntRect(current_sprite_rect_.left,
                                       (current_sprite_rect_.top + height) % (height * frames_), width, height);
    sprite_.setTextureRect(current_sprite_rect_);
    icon_sprite_.setTextureRect(current_sprite_rect_);
    delay_for_sprite_change_ = max_delay_for_sprite_change_;
  } else {
    --delay_for_sprite_change_;
  }
}

void Enemy::CheckAndChangeCoordinates() {
  if (x_ >= 600) {
    x_ = 599;
  }

  if (y_ >= 600) {
    y_ = 599;
  }
}

void Enemy::Click(int x, int y) {
  Entity::Click(x, y);
  state_.GetStateManager().game_ptr_->InfoMenuForEnemy(id_);
}

std::vector<sf::Text> Enemy::GetInfo() const {
  sf::Text name_text;
  sf::Text health_text;
  sf::Text damage_text;
  InitText(name_text, 650, 200, 15, sf::Color::Red);
  InitText(health_text, 620, 300, 15);
  InitText(damage_text, 620, 320, 15);
  name_text.setString(name_);
  health_text.setString("Health: " + std::to_string(health_) + " / " + std::to_string(max_health_));
  damage_text.setString("Damage: " + std::to_string(power_));

  return std::vector<sf::Text>{name_text, health_text, damage_text};
}

bool Enemy::IsAlive() const {
  return is_alive_;
}

Tile Enemy::GetTile() const {
  return current_tile_;
}

void Enemy::DecreaseHealth(int delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }
  if (health_ == 0) {
    is_alive_ = false;
    state_.GetStateManager().game_ptr_->ChangeBalance(drop_);
    state_.GetStateManager().game_ptr_->RemoveEnemyById(GetID());
    return;
  }
  health_bar_.setSize(sf::Vector2f(
      static_cast<float>(health_) / max_health_ * sprite_.getGlobalBounds().width, 3));
}

void Enemy::AddPoison(int poison, int poison_cnt) {
  poison_booster_.AddBooster(poison, poison_cnt * poison_booster_.GetCooldown());
}

void Enemy::AddFreeze(int freeze, int freeze_time) {
  freeze_booster_.AddBooster(freeze, freeze_time);
}

void Enemy::Tick() {
  if (poison_booster_.Boost()) {
    DecreaseHealth(poison_booster_.GetMax());
  }
  if (freeze_booster_.Boost()) {
    speed_ = default_speed_ / freeze_booster_.GetMax();
  } else {
    speed_ = default_speed_;
  }

}

std::pair<sf::Sprite, int> Enemy::ChooseSpriteFromDirection() {
  switch (direction_of_move_) {
    case Direction::North:return std::make_pair(moving_up_sprite_, frames_up_);
    case Direction::South:return std::make_pair(moving_down_sprite_, frames_down_);
    case Direction::East:return std::make_pair(moving_right_sprite_, frames_right_);
    case Direction::West:return std::make_pair(moving_left_sprite_, frames_left_);
    default:return std::make_pair(sprite_, frames_);
  }
}

void Enemy::LoadSpritesForMoving(const std::string& file_name) {
  sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_up.png"), true);
  icon_sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_right.png"));

  moving_up_sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_up.png"), true);

  moving_down_sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_down.png"), true);

  moving_left_sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_left.png"), true);

  moving_right_sprite_.setTexture(
      State::GetTextureResourceManager()
          .GetOrLoadResource(file_name + "/sprite_right.png"), true);
}


