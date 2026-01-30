#include "impact_handler.h"
#include "sound_happy.h"
#include "sound_angry.h"

using namespace m5avatar;

// 定数（二乗値で比較するため、しきい値も二乗で定義）
const float IMPACT_THRESHOLD_HAPPY_SQ = 0.25f; // 0.5^2
const float IMPACT_THRESHOLD_ANGRY_SQ = 121.00f; // 11.0^2
const uint32_t IMPACT_COOLDOWN = 300; // 2度反応するのを防ぐためおクールダウン時間（ミリ秒）
const uint32_t EXPRESSION_DURATION = 1500; // 表情の持続時間（ミリ秒）
const uint8_t SPEAKER_VOLUME = 64; // スピーカーのボリューム

// IMU有効性キャッシュ（setup時に一度だけチェック）
static bool imu_enabled = false;

// 音声再生処理
inline void playSound(const uint8_t* sound_data, size_t sound_size) {
  M5.Speaker.end();
  M5.Mic.end();
  M5.Speaker.begin();
  M5.Speaker.setVolume(SPEAKER_VOLUME);
  M5.Speaker.playRaw(sound_data, sound_size, 16000, false, 1, 0, true);
}

// パレットの初期化
void initializeEmotionPalettes(ColorPalette** cps) {
  // 喜び用パレット
  cps[PALETTE_HAPPY]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[PALETTE_HAPPY]->set(COLOR_BACKGROUND, TFT_PINK);
  
  // 怒り用パレット
  cps[PALETTE_ANGRY]->set(COLOR_PRIMARY, TFT_BLACK);
  cps[PALETTE_ANGRY]->set(COLOR_BACKGROUND, (uint16_t)0xFCE0);
}

void handleImpactDetection(Avatar& avatar, ColorPalette** cps) {
  // IMUキャッシュチェック（初回のみ）
  if (!imu_enabled) {
    imu_enabled = M5.Imu.isEnabled();
    if (!imu_enabled) return;
  }
  
  // 衝撃検知処理（加速度の変化量を使用）
  M5.Imu.update();
  auto imu_data = M5.Imu.getImuData();
  
  // 加速度ベクトルの二乗を計算（sqrt()を削除して高速化）
  float accel_sq = 
    imu_data.accel.x * imu_data.accel.x +
    imu_data.accel.y * imu_data.accel.y +
    imu_data.accel.z * imu_data.accel.z;
  
  // 前回からの変化量の二乗を計算
  float delta = accel_sq - prev_accel_sq;
  float accel_delta_sq = delta * delta;
  
  // クールダウン時間チェック（2度反応するのを防ぐ）
  uint32_t current_time = lgfx::v1::millis();
  if ((current_time - last_impact_detect_time) > IMPACT_COOLDOWN) {
    // 衝撃判定
    if (accel_delta_sq >= IMPACT_THRESHOLD_ANGRY_SQ) {
      // 強い変化 -> 怒り
      palette_index = PALETTE_ANGRY;
      avatar.setColorPalette(*cps[PALETTE_ANGRY]);
      avatar.setExpression(Expression::Angry);
      avatar.setMouthOpenRatio(1.0f);
      impact_detected_time = current_time;
      last_impact_detect_time = current_time;
      is_playing_sound = true;
      playSound(sound_angry, sizeof(sound_angry));
      M5_LOGI("Angry! Delta²: %.3f", accel_delta_sq);
    } else if (accel_delta_sq >= IMPACT_THRESHOLD_HAPPY_SQ) {
      // 弱い変化 -> 喜び
      palette_index = PALETTE_HAPPY;
      avatar.setColorPalette(*cps[PALETTE_HAPPY]);
      avatar.setExpression(Expression::Happy);
      avatar.setMouthOpenRatio(0.8f);
      impact_detected_time = current_time;
      last_impact_detect_time = current_time;
      is_playing_sound = true;
      playSound(sound_happy, sizeof(sound_happy));
      M5_LOGI("Happy! Delta²: %.3f", accel_delta_sq);
    }
  }
  
  // 現在の値を次回用に保存
  prev_accel_sq = accel_sq;
}

void handleExpressionDuration(Avatar& avatar, ColorPalette** cps) {
  // 表情の持続時間管理
  if ((lgfx::v1::millis() - impact_detected_time) > EXPRESSION_DURATION) {
    // 元のパレットに戻す
    palette_index = PALETTE_NEUTRAL;
    avatar.setColorPalette(*cps[PALETTE_NEUTRAL]);
    avatar.setExpression(Expression::Neutral);
    
    M5.Speaker.end();
    M5.Mic.begin();
    
    is_playing_sound = false;
  }
}
