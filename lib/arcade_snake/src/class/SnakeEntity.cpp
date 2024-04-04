/*
** EPITECH PROJECT, 2024
** project
** File description:
** SnakeEntity
*/

#include "GameSnake.hpp"

AEntity::AEntity()
{
    entityType = UNDEFINED;
    position.x = 0;
    position.y = 0;
    visibility = false;
}

AEntity::~AEntity()
{
}

EntityType AEntity::getEntityType() const
{
    return entityType;
}

void AEntity::setEntityType(EntityType type)
{
    entityType = type;
}

Vector2D AEntity::getPosition() const
{
    return position;
}

void AEntity::setPosition(Vector2D pos)
{
    position = pos;    
}

bool AEntity::getVisibility() const
{
    return visibility;
}

void AEntity::setVisibility(bool vis)
{
    visibility = vis;
}
