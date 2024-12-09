/**
 *
 * @file observer.h
 * @brief Defines an interface for observing changes in observable objects.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once

class Observer {
public:

    virtual void update() = 0; 
};