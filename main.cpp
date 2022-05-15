#include <SFML/Graphics.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>   

using namespace std;
int main()
{
    double PI = 22.0/7.0;
    double speed = .1;
    double xSpeed,ySpeed;
    double angle = (rand()%60+25)*PI/180.0;
    int s = 0;
    bool bob = false;

    xSpeed = speed * cos(angle);
    ySpeed = speed * sin(angle);

   //create the main window
   sf::RenderWindow app(sf::VideoMode(800,600), "SFML window");

    int num=0;

    // brick array
    sf::RectangleShape brickArray[50];
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<10; j++)
        {
            brickArray[num].setSize(sf::Vector2f(75, 15));
            brickArray[num].setOrigin(75/2,15/2);
            brickArray[num].setPosition(j*80 + 40, i*20 +10);

            if (i==0){
                brickArray[num].setFillColor(sf::Color::Red);
            }
            else if (i == 1){
                brickArray[num].setFillColor(sf::Color::Yellow);
            }
            else if (i == 2){
                brickArray[num].setFillColor(sf::Color::Green);
            }
            else if (i == 3){
                brickArray[num].setFillColor(sf::Color::Blue);
            }
            else if (i == 4){
                brickArray[num].setFillColor(sf::Color::Magenta);
            }


            num++;



        }
    }

    //load a circles
    sf::CircleShape ball(10);
    ball.setOrigin(10,10);
    ball.setFillColor(sf::Color(0, 255, 0));
    ball.setPosition(400, 525);

    //load a rectangle
    sf::RectangleShape paddle(sf::Vector2f(150, 10));
    paddle.setOrigin(75,0);
    paddle.setFillColor(sf::Color(225, 0, 0));
    paddle.setPosition(400, 555);

    sf::RectangleShape r(sf::Vector2f(800, 600));
    r.setFillColor(sf::Color(0, 0, 0));
    r.setPosition(0, 0);

    //Text
    sf::Font myfont;
    myfont.loadFromFile("arial.ttf");

    sf:: Text score;
    score.setFont(myfont);
    score.setPosition(750,120);
    score.setFillColor(sf::Color(255,255,255));
    score.setString(std::to_string(s));

    sf:: Text win;
    win.setFont(myfont);
    win.setPosition(330,200);
    win.setFillColor(sf::Color(255,255,255));
    win.setString("You win!");

    sf:: Text start;
    start.setFont(myfont);
    start.setPosition(240,250);
    start.setFillColor(sf::Color(255,255,255));
    start.setString("Press Spacebar to start!");
    
  

    //Game loop
    while (app.isOpen())
    {
        //Process events
        sf::Event event;
        while (app.pollEvent(event))
        {   
            //Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { 
            
            bob = true;
        }

        if (bob == true){
        
            if (s != 150) {

                //game loop
                ball.move(xSpeed, ySpeed);
                
                if (ball.getPosition().x >800 || ball.getPosition().x<0){
                    xSpeed *= -1;
                }
                if (ball.getPosition().y >600 || ball.getPosition().y<0){
                    ySpeed *= -1;
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 75)
                {
                    paddle.move(-.2,0);
                }   
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x<725)
                {
                    paddle.move(.2,0);
                }


                // if ball hits array
                for (int i =0; i<50;i++) {
                    if (brickArray[i].getGlobalBounds().intersects(ball.getGlobalBounds())) {

                        xSpeed = (ball.getPosition().x - brickArray[i].getPosition().x)/70 * speed;

                        if(ySpeed < 0){
                            ySpeed = (sqrt(speed*speed - xSpeed*xSpeed));
                        } else{
                            ySpeed = -1* (sqrt(speed*speed - xSpeed*xSpeed));
                        }
                        
                        brickArray[i].move(0,-600);


                        if (i > 39) {
                            s++;
                        } 
                        else if (i > 29 && i <= 39){
                            s = s + 2;
                        }
                        else if (i > 19 && i <= 29) {
                            s = s + 3;
                        }
                        else if (i > 9 && i <= 19){
                            s = s + 4;
                        }
                        else if (i <=9){
                            s = s + 5;
                        }
                        
                        score.setString(std::to_string(s));
                        break;
                    }
                }


                //if ball hits paddle


                if(paddle.getGlobalBounds().intersects(ball.getGlobalBounds())){
                    xSpeed = (ball.getPosition().x - paddle.getPosition().x)/90 * speed;
                    ySpeed = (-(sqrt(speed*speed - xSpeed*xSpeed)));
                }
            
                //clear screen
                app.clear();

                app.draw(ball);
                //draw the sprite
                for(int i=0; i<50;i++){
                    app.draw(brickArray[i]);
                }
                app.draw(paddle);
                app.draw(score);
            }
        }

        if (bob != true){
            app.draw(r);
            app.draw(start);
        }

        if (s == 150) {
            app.draw(r);
            app.draw(win);
            // "red wins";
        }

        app.display();

    }

    return 0;
}