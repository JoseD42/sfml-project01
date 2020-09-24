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
#define PLAYER_MOVESPEED 0.2f

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

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};

    sf::Sprite* tileWall_1_1{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 1, 16, 16)))};
    tileWall_1_1->setScale(SPRITE_SCALE, SPRITE_SCALE);

    sf::Sprite* tileWall_1_2{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 2, 16, 16)))};
    tileWall_1_2->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileWall_1_2->move(tileBaseWidth * 1, tileWall_1_2->getPosition().y);
    
    sf::Sprite* tileWall_1_3{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 3, 16, 16)))};
    tileWall_1_3->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileWall_1_3->move(tileBaseWidth * 2, tileWall_1_3->getPosition().y);

    sf::Sprite* tileGround_1_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 4, 16, 16)))};
    tileGround_1_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_4->move(tileWall_1_3->getPosition().y, tileBaseHeight);

    sf::Sprite* tileGround_2_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 4, 16, 16)))};
    tileGround_2_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_4->move(tileBaseWidth * 1, tileBaseHeight);

    sf::Sprite* tileGround_3_4{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 4, 16, 16)))};
    tileGround_3_4->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_4->move(tileBaseWidth * 2, tileBaseHeight);

    sf::Sprite* tileGround_1_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 5, 16, 16)))};
    tileGround_1_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_5->move(tileGround_1_5->getPosition().x, tileBaseHeight * 2);

    sf::Sprite* tileGround_2_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 5, 16, 16)))};
    tileGround_2_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_5->move(tileBaseWidth * 1, tileBaseHeight * 2);

    sf::Sprite* tileGround_3_5{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 5, 16, 16)))};
    tileGround_3_5->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_5->move(tileBaseWidth * 2, tileBaseHeight * 2);

    sf::Sprite* tileGround_1_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 1, 16 * 6, 16, 16)))};
    tileGround_1_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_1_6->move(tileGround_1_6->getPosition().x, tileBaseHeight * 3);

    sf::Sprite* tileGround_2_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 2, 16 * 6, 16, 16)))};
    tileGround_2_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_2_6->move(tileBaseWidth * 1, tileBaseHeight * 3);

    sf::Sprite* tileGround_3_6{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 3, 16 * 6, 16, 16)))};
    tileGround_3_6->setScale(SPRITE_SCALE, SPRITE_SCALE);
    //tileGround_3_6->move(tileBaseWidth * 2, tileBaseHeight * 3);

    //w = tileWall_1_1  q = tileWall_1_2    e =  tileWall_1_3   

    //g = tileGround_1_4    f = tileGround_2_4  d = tileGround_3_4

    char** tiles 
    {
        new char*[2]
        {
            new char[12]{'w', 'q', 'e', 'w', 'q', 'e', 'w', 'q', 'e', 'w', 'q', 'e'},
            new char[12]{'g', 'f', 'd', 'g', 'f', 'd', 'g', 'f', 'd', 'g', 'f', 'd'}
        }
    };

    std::vector<sf::Sprite> maze;

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            char& tile = *(*(tiles + i) + j);

            switch (tile)
            {
                case 'w':
                    maze.push_back(*tileWall_1_1);
                    //maze.back().move(tileBaseWidth * j, tileBaseHeight * i);
                    //tileWall_1_1->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;
                case 'q':
                    maze.push_back(*tileWall_1_2);
                    //tileWall_1_2->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;
                case 'e':
                    maze.push_back(*tileWall_1_3);
                    //tileWall_1_3->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;
                case 'g':
                    maze.push_back(*tileGround_1_4);
                    //tileGround_1_4->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;
                case 'f':
                    maze.push_back(*tileGround_2_4);
                    //tileGround_2_4->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;
                case 'd':
                    maze.push_back(*tileGround_3_4);
                    //tileGround_3_4->move(tileBaseWidth * j, tileBaseHeight * i);
                    break;                
                default:
                    break;
            }
            maze.back().move(tileBaseWidth * j, tileBaseHeight * i);
        }
    }

    //Main player
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

        window->clear(*(new sf::Color(150, 100, 0, 255)));//lipiar la pantalla

        /*window->draw(*tileWall_1_1);
        window->draw(*tileWall_1_2);
        window->draw(*tileWall_1_3);

        window->draw(*tileGround_1_4);
        window->draw(*tileGround_2_4);
        window->draw(*tileGround_3_4);

        window->draw(*tileGround_1_5);
        window->draw(*tileGround_2_5);
        window->draw(*tileGround_3_5);

        window->draw(*tileGround_1_6);
        window->draw(*tileGround_2_6);
        window->draw(*tileGround_3_6);*/

        for(auto& mazeTile : maze)
        {
            window->draw(mazeTile);
        }
        
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