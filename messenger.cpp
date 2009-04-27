#include "messenger.h"

Messenger::Messenger (int max_time) {
    timeline = new Queue[max_time];
}

void Messenger::send (char msg, int site) {
    int time = compute_delivery_time();
    timeline[time].enqueue(
}
