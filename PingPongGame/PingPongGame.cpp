#include <SFML/Graphics.hpp>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Pong!");

    // ======== POLICE & SCORE ========
    sf::Font font("Roboto_Condensed-MediumItalic.ttf");

    int scoreLeft = 0;
    int scoreRight = 0;

    sf::Text scoreText(font, "0    0", 50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 345.f, 20.f });

    // Ligne du milieu (décorative)
    sf::RectangleShape middleLine({ 5.f, 600.f });
    middleLine.setFillColor(sf::Color(255, 255, 255, 100)); // blanc transparent
    middleLine.setPosition({ 397.f, 0.f });

    // ======== LA BALLE ========
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition({ 400.f, 300.f });
    sf::Vector2f velocity(200.f, 200.f);

    // ======== LES RAQUETTES ========
    sf::RectangleShape paddleLeft({ 15.f, 100.f });
    paddleLeft.setFillColor(sf::Color::White);
    paddleLeft.setPosition({ 20.f, 250.f });

    sf::RectangleShape paddleRight({ 15.f, 100.f });
    paddleRight.setFillColor(sf::Color::White);
    paddleRight.setPosition({ 765.f, 250.f });

    float paddleSpeed = 400.f;
    sf::Clock clock;

    while (window.isOpen())
    {
        // ======== ÉVÉNEMENTS ========
        while (const std::optional event = window.pollEvent())
            if (event->is<sf::Event::Closed>())
                window.close();

        float dt = clock.restart().asSeconds();

        // ======== MOUVEMENT RAQUETTES ========
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            paddleLeft.move({ 0.f, -paddleSpeed * dt });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            paddleLeft.move({ 0.f, paddleSpeed * dt });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            paddleRight.move({ 0.f, -paddleSpeed * dt });
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            paddleRight.move({ 0.f, paddleSpeed * dt });

        // Limites raquettes
        if (paddleLeft.getPosition().y < 0)
            paddleLeft.setPosition({ 20.f, 0.f });
        if (paddleLeft.getPosition().y > 500)
            paddleLeft.setPosition({ 20.f, 500.f });
        if (paddleRight.getPosition().y < 0)
            paddleRight.setPosition({ 765.f, 0.f });
        if (paddleRight.getPosition().y > 500)
            paddleRight.setPosition({ 765.f, 500.f });

        // ======== MOUVEMENT BALLE ========
        ball.move(velocity * dt);

        // Rebondir haut/bas
        if (ball.getPosition().y <= 0 || ball.getPosition().y >= 590)
            velocity.y = -velocity.y;

        // ======== COLLISIONS ========
        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect leftBounds = paddleLeft.getGlobalBounds();
        sf::FloatRect rightBounds = paddleRight.getGlobalBounds();

        if (ballBounds.findIntersection(leftBounds))
        {
            velocity.x = std::abs(velocity.x)*1.05;
            float hitPos = (ball.getPosition().y - paddleLeft.getPosition().y) / 100.f;
            velocity.y = (hitPos - 0.5f) * 400.f;
        }

        if (ballBounds.findIntersection(rightBounds))
        {
            velocity.x = -std::abs(velocity.x)*1.05;
            float hitPos = (ball.getPosition().y - paddleRight.getPosition().y) / 100.f;
            velocity.y = (hitPos - 0.5f) * 400.f;
        }

        // ======== SCORE ========
        // Balle sort à droite → point pour le joueur GAUCHE
        if (ball.getPosition().x > 800)
        {
            scoreLeft++;
            ball.setPosition({ 400.f, 300.f });
            velocity = { 200.f, 200.f };
        }

        // Balle sort à gauche → point pour le joueur DROITE
        if (ball.getPosition().x < 0)
        {
            scoreRight++;
            ball.setPosition({ 400.f, 300.f });
            velocity = { -200.f, 200.f };
        }

        // Mettre à jour le texte du score
        scoreText.setString(std::to_string(scoreLeft) + "     " + std::to_string(scoreRight));

        // ======== GAME OVER à 5 points ========
        if (scoreLeft == 5 || scoreRight == 5)
        {
            // Afficher le gagnant
            sf::Text winText(font, "", 60);
            winText.setFillColor(sf::Color::Yellow);

            if (scoreLeft == 5)
                winText.setString("Joueur 1 gagne !");
            else
                winText.setString("Joueur 2 gagne !");

            winText.setPosition({ 150.f, 250.f });

            window.clear(sf::Color::Black);
            window.draw(winText);
            window.display();

            // Attendre 3 secondes puis fermer
            sf::sleep(sf::seconds(3));
            window.close();
        }

        // ======== DESSIN ========
        window.clear(sf::Color::Black);
        window.draw(middleLine);
        window.draw(ball);
        window.draw(paddleLeft);
        window.draw(paddleRight);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}