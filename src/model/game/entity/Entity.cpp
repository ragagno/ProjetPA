#include <dirent.h>
#include <iostream>
#include <vector>
#include <fstream>
#include "Entity.h"
#include "../../../ProximaCentauri.h"

uint_fast32_t Entity::entityNumber;
Entity *Entity::entities;

Entity::Entity()
{
    x = 0;
    y = 0;
    speed = 0;
    hp = 0;
    damageHit = 0;
    damageFire = 0;
    spriteNumber = 0;
    attackFrequency = 0;
    damageType = PLASMA_BALL;

    lastShoot = 0;
}

Entity::Entity(const Entity &initial)
{
    speed = initial.speed;
    y = ENTITY_Y_SPAWN;
    hp = initial.hp;
    damageHit = initial.damageHit;
    damageFire = initial.damageFire;
    spriteNumber = initial.spriteNumber;
    attackFrequency = initial.attackFrequency;
    damageType = initial.damageType;
    lastShoot = 0;
}

Entity::~Entity()
{

}

void Entity::setX(uint_fast32_t x)
{
    this->x = x * (WINDOW_WIDTH / 16);
}

Entity Entity::getEntity(char c)
{
    return entities[static_cast<uint_fast32_t >(c) - static_cast<uint_fast32_t>('a')];
}

int_fast32_t Entity::getX() const
{
    return static_cast<uint_fast32_t>(x);
}

int_fast32_t Entity::getY() const
{
    return static_cast<uint_fast32_t>(y);
}

uint_fast32_t Entity::getSprite() const
{
    return spriteNumber;
}

uint_fast32_t Entity::getDamageHit() const
{
    return damageHit;
}

void Entity::move(long double lag)
{
    y += speed * lag;
}

void Entity::shoot(long double lag)
{
    lastShoot += lag;
    if (lastShoot > attackFrequency)
    {
        lastShoot = 0;
        switch (damageType)
        {
            case LASER_BEAM:
                std::cout << "LASER" << std::endl;
                // TODO: create laser
                break;
            case PLASMA_BALL:
                std::cout << "PLASMA" << std::endl;
                // TODO: create plasma ball
                break;
            default:
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]unexpected damage type " << damageType << "\n";
                exit(EXIT_FAILURE);
        }
    }
}

void Entity::init()
{
    entityNumber = 0;
    entities = nullptr;
    struct dirent *ep;
    std::vector<std::string> temp;
    DIR *dp;

    dp = opendir("enemies/");

    if (dp != nullptr)
    {
        while ((ep = readdir(dp)))
        {
            if (ep->d_name[0] == '.')
            {
                continue;
            }
            entityNumber++;
            temp.push_back(static_cast<std::string>(ep->d_name));
        }
        closedir(dp);
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not count enemies.\n";
        exit(EXIT_FAILURE);
    }

    if (entityNumber == 0)
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]No enemy to be loaded.\n";
        exit(EXIT_FAILURE);
    }

    entities = new Entity[entityNumber]{};

    for (uint_fast32_t i = 0; i < entityNumber; i++)
    {
        entities[i].loadEntity(temp[i]);
    }
}

bool Entity::exists(char c)
{
    return static_cast<uint_fast32_t>(c) - static_cast<uint_fast32_t>('a') < entityNumber;
}

void Entity::loadEntity(const std::string &filename)
{
    std::ifstream fin("enemies/" + filename);

    if (fin.is_open())
    {
        try
        {
            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::string line;

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid speed.\n";
                exit(EXIT_FAILURE);
            }
            speed = std::stold(line);

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid hp.\n";
                exit(EXIT_FAILURE);
            }
            hp = static_cast<uint_fast32_t>(std::stoi(line));

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid damage hit.\n";
                exit(EXIT_FAILURE);
            }
            damageHit = static_cast<uint_fast32_t>(std::stoi(line));

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid damage fire.\n";
                exit(EXIT_FAILURE);
            }
            damageFire = static_cast<uint_fast32_t>(std::stoi(line));

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid sprite number.\n";
                exit(EXIT_FAILURE);
            }
            spriteNumber = static_cast<uint_fast32_t>(std::stoi(line));

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid attack frequency.\n";
                exit(EXIT_FAILURE);
            }
            attackFrequency = static_cast<uint_fast32_t>(std::stoi(line));

            if (fin.eof())
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
                exit(EXIT_FAILURE);
            }

            std::getline(fin, line);
            if (line.length() == 0)
            {
                std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Could not load enemy " << filename << " invalid attack type.\n";
                exit(EXIT_FAILURE);
            }
            switch (std::stoi(line))
            {
                case 0:
                    damageType = LASER_BEAM;
                    break;
                case 1:
                    damageType = PLASMA_BALL;
                    break;
                default:
                    std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Unexpected attack type " << std::stoi(line) << "\n";
                    exit(EXIT_FAILURE);
            }
        }
        catch (std::invalid_argument const &e)
        {
            std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " is invalid.\n";
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "[ERROR][" << __FILE__ << ":" << __LINE__ << "]Enemy " << filename << " could not be loaded.\n";
        exit(EXIT_FAILURE);
    }

    fin.close();
}