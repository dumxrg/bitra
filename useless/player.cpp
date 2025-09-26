// player.cpp
#include "player.h"
#include "raymath.h"
#include <algorithm>
#include <raylib.h>

// Smoothly interpolate between two angles (handles wrapping)
static float LerpAngle(float current, float target, float amount) {
    float diff = target - current;
    if (diff > PI) diff -= 2.0f * PI;
    else if (diff < -PI) diff += 2.0f * PI;
    return current + diff * amount;
}

// Easing: smoothstep (0 to 1 with ease-in-out)
static float SmoothStep(float edge0, float edge1, float x) {
    x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

Player::Player(int windowWidth, int windowHeight) {
    position = {windowWidth / 3.0f, windowHeight / 2.0f};
    size = 20.0f;
    currentRotation = 0.0f;
    targetRotation = 0.0f;
    rotationLerpTimer = 0.0f;
    rotationLerpTime = 0.05f;
    squeezeFactor = 0;

    isDashing = false;
    dashTimer = 0.0f;
    isOnCooldown = false;
    cooldownTimer = 0.0f;

    shouldSpawnRing = false;
    queuedDash = false;
}

void Player::Update(float deltaTime, Vector2 inputDir, bool dashPressed, bool dashReleased) {
     hitbox  = (Rectangle){position.x-size/2, position.y-size/2, size/1.5f, size/1.5f};
    float inputLength = Vector2Length(inputDir);
    Vector2 normalizedInputDir = (inputLength > 0.01f)
                               ? Vector2Scale(inputDir, 1.0f / inputLength)
                               : Vector2Zero();

    // Dash trigger
    bool canDash = !isOnCooldown && inputLength > 0.01f;

    if (dashPressed) {
        if (canDash) {
            isDashing = true;
            isOnCooldown = true;
            dashTimer = 0.0f;
            cooldownTimer = 0.0f;
            dashStartPos = position;
            shouldSpawnRing = true;
            queuedDash = false;
        } else {
            queuedDash = true;
        }
    }

    if (dashReleased) {
        isDashing = false;
        dashTimer = 0.0f;
    }

    squeezeFactor = isDashing ? inputLength * 2.0f : inputLength * 3.0f;

    // Update timers
    dashTimer += isDashing ? deltaTime : 0.0f;
    cooldownTimer += isOnCooldown ? deltaTime : 0.0f;

    isDashing = isDashing && (dashTimer < DASH_DURATION);
    isOnCooldown = isOnCooldown && (cooldownTimer < DASH_COOLDOWN);

    if (queuedDash && !isOnCooldown && inputLength > 0.01f) {
        dashStartPos = position;
        isDashing = true;
        isOnCooldown = true;
        dashTimer = 0.0f;
        cooldownTimer = 0.0f;
        shouldSpawnRing = true;
        queuedDash = false;
    }

    // Update position
    float currentSpeed = isDashing ? DASH_SPEED : WALK_SPEED;
    position.x += normalizedInputDir.x * currentSpeed * deltaTime;
    position.y += normalizedInputDir.y * currentSpeed * deltaTime;

    // Clamp to screen
    float halfSize = size * 0.5f;
    position.x = std::max(halfSize, std::min(position.x, (float)GetScreenWidth() - halfSize));
    position.y = std::max(halfSize, std::min(position.y, (float)GetScreenHeight() - halfSize));

    // Update rotation
    if (inputLength > 0.01f) {
        targetRotation = atan2f(normalizedInputDir.y, normalizedInputDir.x);
        rotationLerpTimer = 0.0f;
    }

    if (rotationLerpTimer < rotationLerpTime) {
        float t = deltaTime / rotationLerpTime;
        currentRotation = LerpAngle(currentRotation, targetRotation, t);
        rotationLerpTimer += deltaTime;
    }

    // Update visuals
    size = isDashing ? 15.0f : 20.0f;
    rotationLerpTime = isDashing ? 0.001f : 0.05f;
}

void Player::Draw() {
    DrawRectanglePro(
        (Rectangle){position.x, position.y, size + squeezeFactor, size},
        (Vector2){size * 0.5f, size * 0.5f},
        currentRotation * RAD2DEG,
        (Color){0, 255, 244, 255}
    );
    
     DrawCircleLinesV((Vector2){position.x, position.y}, 10, RED);
}