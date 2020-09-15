#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define SPRITE_SCALE 2.f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Inputs* inputs = {new Inputs()};

    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Sprite* sprite1{new sf::Sprite(*tilesTexture1, *(new sf::IntRect(16 * 0, 16 * 11, 16, 16)))};
    sprite1->setScale(*(new sf::Vector2f(SPRITE_SCALE, SPRITE_SCALE)));
    //sprite1->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);

    /*sf::RectangleShape* boxShape{new sf::RectangleShape(*(new sf::Vector2f(100, 100)))};
    boxShape->setPosition((WINDOW_WIDTH / 2), WINDOW_HEIGHT / 2);
    boxShape->setFillColor(sf::Color::Transparent);
    boxShape->setOutlineColor(sf::Color::Green);
    boxShape->setOutlineThickness(2.f);

    sf::CircleShape* pointShape{new sf::CircleShape(2.f)};
    pointShape->setPosition(boxShape->getPosition());
    pointShape->setFillColor(sf::Color::White);*/

    //TAREA:

	// Activa la sincronización vertical (60 fps)
	window->setVerticalSyncEnabled(true);

	// Creamos una textura
	sf::Texture textura;

	// Cargamos la textura desde un archivo
	if(!textura.loadFromFile("data/Mustang.png"))
	{
		// Si hay un error salimos
		std::cout << "No se pudo cargar la textura" << std::endl;
	}

	// Creamos un sprite
	sf::Sprite sprite;
	// Asignamos la textura al sprite
	sprite.setTexture(textura);
	// Seleccionamos solo un rectangulo de la textura
	sprite.setTextureRect(sf::IntRect(120, 120, 128, 128));
	// Movemos el sprite
	sprite.move(100, 100);
	// Cambiamos el origen al centro del sprite
	sf::Vector2f centro;
	centro.x = sprite.getTextureRect().width / 2.f;
	centro.y = sprite.getTextureRect().height / 2.f;
	sprite.setOrigin(centro);
	// Rotamos el sprite 360 grados
	sprite.rotate(360);


	// Creamos otro sprite con la MISMA textura
	sf::Sprite Mustang(textura);
	Mustang.setPosition(200, 150);
	Mustang.setTextureRect(sf::IntRect(0, 0, 364, 364));

    //LO VISTO EN CLASE:

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {
        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};
        //std::cout << "keyboard axis x: " << keyboardAxis->x << " keyboard axis y: " << keyboardAxis->y << std::endl;
        //std::cout << "joystic axis x: " << joystickAxis->x << " joystic axis y: " << joystickAxis->y << std::endl;

        if(sf::Joystick::isConnected(0))
        {
            sprite1->move(joystickAxis->x, joystickAxis->y);
        }
        else
        {
            sprite1->move(keyboardAxis->x, keyboardAxis->y);
        }

        window->clear(sf::Color::Black);//lipiar la pantalla
        //window->draw(*boxShape); //agregar la caja a las cosas que se van a dibujar
        //window->draw(*pointShape);
        window->draw(*sprite1);
        window->display(); //mostrar en pantalla lo que se va dibujar

        //Tmb de la Tarea
        /*window->clear(sf::Color::Black);
        window->draw(sprite);
        window->draw(Mustang);   
        window->display();*/

        //inputs->GetJoystickAxis();
        delete keyboardAxis;
        delete joystickAxis;

    }

    /*std::cout << &window << std::endl;
    std::cout << &textura << std::endl;
    std::cout << &Mustang << std::endl;
    std::cout << &sprite << std::endl;
    std::cin.get();*/
    
    return 0;
}