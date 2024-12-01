#include "Collision.h"

Collision::Collision(sf::Vector2u tileSize) : mTileSize(tileSize)
{
}

void Collision::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier de collision " << filename << std::endl;
        return;
    }

    std::string line;
    int row = 0;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        int col = 0;
        int value;
        while (ss >> value)
        {
            if (value == 1) // Si c'est un mur
            {
                mCollisions.push_back(sf::FloatRect(col * mTileSize.x, row * mTileSize.y, mTileSize.x, mTileSize.y));
            }
            col++;
        }
        row++;
    }
}


bool Collision::checkCollision(const sf::FloatRect& playerBounds)
{
    for (const auto& coll : mCollisions)
    {
        if (playerBounds.intersects(coll))
        {
            return true;
        }
    }
    return false;
}

void Collision::draw(sf::RenderWindow& window)
{
    for (const auto& coll : mCollisions)
    {
        sf::RectangleShape rect(sf::Vector2f(coll.width, coll.height));
        rect.setPosition(coll.left, coll.top);
        rect.setFillColor(sf::Color(255, 0, 0, 255));
        window.draw(rect);
    }
}
