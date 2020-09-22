#include<iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"
#include "Character.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 0.3f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);
    //Game inputs
    Inputs* inputs{new Inputs()};
    //Textures
    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);
    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);
    sf::Texture* tilesTexture3{new sf::Texture()};
    tilesTexture3->loadFromFile(TILES3);

    sf::Sprite* tileGround1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 3, 16, 16)))};
    tileGround1->setScale(SPRITE_SCALE, SPRITE_SCALE);


    //Main Player
    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, SPRITE_SCALE, SPRITE_SCALE)};
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );

    character1->GetSprite()->setPosition(400, 300);

    //TAREA:

	// Activa la sincronización vertical (60 fps)
	/*window->setVerticalSyncEnabled(true);

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
	Mustang.setTextureRect(sf::IntRect(0, 0, 364, 364));*/

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
            character1->GetSprite()->move(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(joystickAxis->x);
            
            if(std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }
        else
        {
            character1->GetSprite()->move(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(keyboardAxis->x);

            if(std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y) > 0)
            {
                //run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                //idle
                character1->GetAnimation(0)->Play(deltaTime);
            }
        }

        //character1->GetAnimation(0)->Play(deltaTime);


        window->clear(*(new sf::Color(150, 100, 0, 255)));//lipiar la pantalla
        window->draw(*tileGround1);
        window->draw(*character1->GetSprite());
        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        clock->restart();

        //std::cout << "delta time: " << deltaTime << std::endl;

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