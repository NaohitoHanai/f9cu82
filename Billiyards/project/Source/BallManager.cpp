#include "BallManager.h"
#include "Ball.h"
void BallManager::Update()
{
	std::list<Ball*> balls = FindGameObjects<Ball>();
	for (Ball* b1 : balls) {
		for (Ball* b2 : balls) {
			if (b1 == b2)
				continue;
			// b1‚©‚çb2‚Ö‚Ì“–‚½‚è”»’è
			b1->HitOtherBall(b2);
		}
	}
}
