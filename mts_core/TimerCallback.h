#pragma once

namespace mts{
    class TimerCallback{
        public:
            virtual ~TimerCallback(){}
                virtual void onTimeout(int timerId) = 0;
    };
}