#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
    waiting.clear();
}

EnemyManager::~EnemyManager()
{
}

bool EnemyManager::RequestAttack(Enemy* e)
{
    waiting.push_back(e); // ’Ç‰Á‚ğ‚·‚é
    if (*(waiting.begin()) == e) { // æ“ª‚ª©•ª
        return true;
    }
    return false;
}

void EnemyManager::CancelAttack(Enemy* e)
{
    for (auto it = waiting.begin(); it != waiting.end(); ) {
        if (*it == e) {
            it = waiting.erase(it);
        } else {
            it++;
        }
    }
}
