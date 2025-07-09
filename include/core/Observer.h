//
// Created by 39347 on 09/07/2025.
//

#pragma once
#include "Activity.h"

class ActivityObserver {
public:
    virtual ~ActivityObserver() = default;
    virtual void onActivityAdded(const Activity& activity) = 0;
    virtual void onActivityRemoved(int id) = 0;
    virtual void onActivityUpdated(const Activity& activity) = 0;
};

