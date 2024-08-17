#pragma once

namespace mts{
    class DateCallback{
        public:
            virtual ~DateCallback(){}
                virtual void onBusinessDateChanged(int businessDate) = 0;
    };
}