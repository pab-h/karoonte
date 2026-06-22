#include "queue.hpp"

namespace app::globals::queue {

    static QueueHandle_t answer_queue; 

    void init() {

        answer_queue  = xQueueCreate(
            1, 
            sizeof(char)
        );
        
    }

    QueueHandle_t get_answer_queue() {
        return answer_queue;
    }

}

