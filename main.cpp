
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
  
    template <typename parameter>
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
    void load(identifier id, const std::string& filename,const parameter& secondParameter)
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
    ResourceContainer<sf::Texture,textures::ID> a;
    sf::Sprite playerPlane;
    a.load(textures::airplane, "rocket.png");
    a.load(textures::airplane, "rocket.png");
    a.load(textures::rocket, "rocket.jpg");
    a.load(textures::landscape, "desert.png");
    playerPlane.setTexture(a.get(textures::airplane));

}
