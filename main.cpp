#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

const int SCREEN_WIDHT=910;
const int SCREEN_HEIGHT=750;
const std::string WINDOW_NAME="Sorting Visualizer";

std::vector<sf::RectangleShape> createRectangles() {
    int rec_width = SCREEN_WIDHT/10;
    std::vector<sf::RectangleShape> rectangles;
    for (int i = 0; i < 10; i++) {
        int rec_height = rand() % SCREEN_HEIGHT;
        sf::RectangleShape rectangle(sf::Vector2f(rec_width, rec_height));
        rectangle.setFillColor(sf::Color(150, 50, 250));
        rectangles.push_back(rectangle);
        rectangle.setPosition(0, SCREEN_HEIGHT-50);
    }
    return rectangles;
}

std::vector<int> createHeightsVector(int size) {
    std::vector<int> heights;
    int base = SCREEN_HEIGHT/size;
    for (int i = 0; i < size; i++) {
        int h = (i+1)*base;
        heights.push_back(h);
    } 
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(heights.begin(), heights.end(), std::default_random_engine(seed));
    return heights;
}

void drawRectangles(std::vector<int> heights, sf::RenderWindow &window, int first, int second) {
    float rec_width = (float)SCREEN_WIDHT/heights.size();
    window.clear(sf::Color::Black);
    for (int i = 0; i < heights.size(); i++) {
        sf::RectangleShape rectangle(sf::Vector2f(rec_width, heights[i]));
        if(i == first) {
            rectangle.setFillColor(sf::Color(21, 141, 2));
        } else if (i == second){
            rectangle.setFillColor(sf::Color(212, 0, 0));
        } else {
            rectangle.setFillColor(sf::Color(200, 200, 200));
        }
        rectangle.setPosition(i*rec_width, SCREEN_HEIGHT-heights[i]);
        window.draw(rectangle);
    } 
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void drawSorted(std::vector<int> heights, sf::RenderWindow &window) {
    float rec_width = (float)SCREEN_WIDHT/heights.size();
    for (int i = 0; i < heights.size(); i++) {
        sf::RectangleShape rectangle(sf::Vector2f(rec_width, heights[i]));
        rectangle.setFillColor(sf::Color(21, 141, 2));
        rectangle.setPosition(i*rec_width, SCREEN_HEIGHT-heights[i]);
        window.draw(rectangle);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    } 
}

void bubbleSort(std::vector<int> array, unsigned int length, sf::RenderWindow &window) {
    
    bool changed;

    length -= 1;

    for (int i = 0; i < length; i++) { 

        changed = false; 

        for (int j = 0; j < length - i; j++) { 

            if (array[j] > array[j + 1]) {
 
                drawRectangles(array, window, j, j+1);
                std::swap(array[j], array[j+1]);
                drawRectangles(array, window, j+1, j);
                changed = true; 
            } 
        } 
        if (changed == false) {
            drawSorted(array, window);
            return;
        }
    }     
}

int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDHT, SCREEN_HEIGHT), WINDOW_NAME);
    std::vector<int> heights = createHeightsVector(20);
    for (int i = 0; i < heights.size(); i++) {
        std::cout<<heights[i]<<std::endl;
    }
    drawRectangles(heights, window, -1, -1);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            bubbleSort(heights, heights.size(), window);
        }
        
    }
    return 0;
}
