#pragma once

#pragma once

#include "components/simple_scene.h"
#include "shape.h"
#include "square.h"
#include "romb.h"
#include "hexagon.h"
#include "star.h"
#include "lane.h"
#include "random_number_generator.h"

namespace tema {
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void initPlayArea();
        void initTopDisplayArea();
        void initShop();
        void initShopItem(RefPointContainer* r, int i);
        
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        std::vector<Shape*> getElementsAtPoint(RefPointContainer* container, int mouseX, int mouseY);
        std::vector<std::pair<Hexagon*, Shape*>> getCollisions();
        void checkCollision(std::pair<Hexagon*, Shape*> collision);
        void displayLives();
        void displayStars();
    protected:
        std::vector<tema::Shape*> shapes;
        //tema::Square* end_line;
        //tema::Square* top_display;
        RandomNumberGenerator r;
        std::vector<tema::Shape> romb_contours;
        std::vector<Mesh*> enemy_meshes;
        std::vector<Mesh*> romb_meshes;
        std::vector<Mesh*> star_meshes;
        std::chrono::high_resolution_clock::time_point last_star_appearance;
        const int right_margin = 100;
        const int bottom_margin = 100;
        int animation_counter = 0;
        int next_star_in = 10000;
        int star_count = 10;
        int lives_count = 3;
        int lane_count = 3;

        RefPointContainer root;
        RefPointContainer star_counter;
        RefPointContainer lives_counter;
        RefPointContainer top_screen;
        RefPointContainer shop;
        RefPointContainer play_area;
        std::vector<Lane*> lanes;
        //Hexagon h;
        Romb selected_romb;
    };
}

