#include <stdlib.h>
#include <cstdlib>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "ProgS4"}};
    ctx.maximize_window();

    float x = 0.0f;
    float y = 0.0f;

    std::vector<glm::vec2> rectangles(100);
    std::vector<int>       directions(100);

    // initialisation des positions de rectangle
    for (auto& rectangle : rectangles)
    {
        x = p6::random::number(-2, 2);
        y = p6::random::number(-1, 1);

        rectangle = glm::vec2(x, y);
    }

    for (auto& direction : directions)
    {
        direction = p6::random::number(0, 3);
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // Clear the background with a fading effect
        ctx.use_stroke = false;
        ctx.fill       = {0.2f, 0.1f, 0.3f, 0.1f};
        ctx.rectangle(p6::FullScreen{});

        ctx.fill = {1.f, 0.7f, 0.2f};

        for (int i = 0; i < 100; i++)
        {
            if (directions[i] == 0)
            {
                rectangles[i].y += 0.01;
            }
            else if (directions[i] == 1)
            {
                rectangles[i].x += 0.01;
            }
            else if (directions[i] == 2)
            {
                rectangles[i].y -= 0.01;
            }
            else
            {
                rectangles[i].x -= 0.01;
            }

            ctx.square(
                p6::Center{rectangles[i].x, rectangles[i].y},
                p6::Radius{0.1f}
            );
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}