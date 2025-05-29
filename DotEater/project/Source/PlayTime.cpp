#include "PlayTime.h"

PlayTime::PlayTime()
{
    timer = 10.0f;
}

PlayTime::~PlayTime()
{
}

void PlayTime::Update()
{
    timer -= Time::DeltaTime();
}

void PlayTime::Draw()
{
}

bool PlayTime::TimeUp()
{
    return timer <= 0.0f;
}
