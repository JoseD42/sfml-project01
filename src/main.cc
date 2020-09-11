#include<iostream>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"

int main()
{
    //esto es la ventana de tu grafico
    sf::Window* window = new sf::Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;
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
        //la clase Keyboard trae la inputs del teclado
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            std::cout << "left" << std::endl;
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            std::cout << "right" << std::endl;
        }
         if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            std::cout << "up" << std::endl;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            std::cout << "down" << std::endl;
        }

        //Hay un joystick conetado ?
        if(sf::Joystick::isConnected(0)) //literalmente le digo, ve y busca el joystick numero 0 en la lista de controles conectados. 
        {
            //cachamos el valor del axis X y Y, lo dividimos entre 100 porque el valor min de los axis es -100 y el maximo 100
            //osea lo pusimos en escala de 1
            float x{sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) /100};
            float y{sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) /100};

             // ? = si es verdadero; y : = si es falso

             //el joystick por si solo nunca deja de enviar valores, osea aunque no lo estes tocando, envia datos
            //por eso debemos hacer un filtro de las entradas de este.
            //en este caso el espectro de menor a -0.2 y mayor a 0.2 es el valor 1 osea que si vale.
            x = x > 0.2f ? 1 : x < -0.2f ? -1 : 0;
            y = -(y > 0.2f ? 1 : y < -0.2f ? -1 : 0);

            std::cout << "X: " << x << " Y: " << y << std::endl;
        }
    }
    
    return 0;
}