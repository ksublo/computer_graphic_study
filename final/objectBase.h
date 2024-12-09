/**
 *
 * @file objectBase.h
 * @brief Defines the base class for all objects.
 *
 * @author Kseniia Blokhina
 * @login BLO0021
 *
 */
#pragma once
class ObjectBase {
public:

    virtual void bind() = 0;
    virtual void draw() = 0;

};