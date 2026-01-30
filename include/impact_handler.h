#ifndef IMPACT_HANDLER_H
#define IMPACT_HANDLER_H

#include <M5Unified.h>
#include <Avatar.h>

// パレットインデックス定数
const uint8_t PALETTE_NEUTRAL = 4; // 通常
const uint8_t PALETTE_HAPPY = 0; // 喜び
const uint8_t PALETTE_ANGRY = 1; // 怒り

// 外部変数宣言
extern uint32_t impact_detected_time; // 衝撃を検知した時間
extern uint32_t last_impact_detect_time; // 前回の衝撃を検知した時間
extern bool is_playing_sound; // 音声を再生中か否か
extern float prev_accel_sq; // 加速度の二乗値を保存（最適化）
extern uint8_t palette_index;

// パレットの初期化
void initializeEmotionPalettes(m5avatar::ColorPalette** cps);

// 衝撃検知と音声再生を処理する関数
void handleImpactDetection(m5avatar::Avatar& avatar, m5avatar::ColorPalette** cps);

// 表情の持続時間管理と復帰処理を行う関数
void handleExpressionDuration(m5avatar::Avatar& avatar, m5avatar::ColorPalette** cps);

#endif // IMPACT_HANDLER_H
