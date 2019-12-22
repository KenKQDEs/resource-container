
#include <iostream>
#include <map>
#include <assert.h>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/System.hpp>
namespace textures
{
    enum ID
    {
        airplane, rocket, landscape
    };
}
namespace fonts
{
    enum ID
    {
        arial,times
    };
}
template <typename resource, typename identifier>
class ResourceContainer
{
public:
  
    
    resource& get(identifier id)
    {
        auto found = mResourceMap.find(id);
        assert(found != mResourceMap.end());
        return *found->second;
    }
    const resource& get(identifier id) const
    {
        auto found = mResourceMap.find(id);
        assert(found != mResourceMap.end());
        return *found->second;
    }
    
    void load(identifier id, const std::string& filename)
    {
        std::unique_ptr <resource> resources(new resource());
        if (!resources->loadFromFile(filename))
            throw std::runtime_error("Multiple attempts to render same resource \0" + filename);
        std::pair<std::map<identifier, std::unique_ptr<resource>>::iterator, bool> inserted = mResourceMap.insert(std::make_pair(id, std::move (resources)));
        assert(inserted.second);
    }
    template <typename parameter>
    void load(identifier id, const std::string& filename, const parameter& secondParameter)
    {
        std::unique_ptr <resource> resources(new resource());
        if (!resources->loadFromFile(filename,secondParameter))
            throw std::runtime_error("Multiple attempts to render same resource \0" + filename);
        std::pair<std::map<identifier, std::unique_ptr<resource>>::iterator, bool> inserted = mResourceMap.insert(std::make_pair(id, std::move(resources)));
        assert(inserted.second);
    }
private:  
    std::map < textures::ID, std::unique_ptr < sf::Texture>> mResourceMap;
};
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "text", sf::Style::Default);
    ResourceContainer<sf::Texture, textures::ID> tcontainer;
    try
    {
        tcontainer.load(textures::airplane, "rocket.png");
        tcontainer.load(textures::landscape, "desert.png");
    }
    catch (std::runtime_error & e)
    {
        std::cout << "Exceptie: " << e.what() << std::endl;
        return 1;
    }
 
    sf::Sprite airplane(tcontainer.get(textures::airplane)), 
               landscape(tcontainer.get(textures::landscape));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return 0;
        }
        window.clear();
        window.draw(landscape);
        window.draw(airplane);
        window.display();
    }


}
