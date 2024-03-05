#include "tema1.h"
#include "mesh_manager.h"

#include <vector>
#include <iostream>
#include <queue>
#include <random>
#include <utility>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"



namespace tema {

	Tema1::Tema1() : r(1000){

	}

	Tema1::~Tema1() {

	} 

	void Tema1::Init() {
		glm::ivec2 resolution = window->GetResolution();
		auto camera = GetSceneCamera();
		camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
		camera->SetPosition(glm::vec3(0, 0, 50));
		camera->SetRotation(glm::vec3(0, 0, 0));
		camera->Update();
		GetCameraInput()->SetActive(false);

		Mesh* m1 = MeshManager::initSquareMesh(glm::vec3(1, 1, 1), "white_square");
		AddMeshToList(m1);
		m1 = MeshManager::initStarMesh(glm::vec3(1, 1, 0), "yellow_star");
		AddMeshToList(m1);
		m1 = MeshManager::initStarMesh(glm::vec3(0, 1, 0), "green_star");
		AddMeshToList(m1);
		m1 = MeshManager::initSquareMesh(glm::vec3(1, 0, 0), "red_square");
		AddMeshToList(m1);
		m1 = MeshManager::initSquareContourMesh(glm::vec3(1, 1, 1), "square_contour");
		AddMeshToList(m1);

		m1 = MeshManager::initStarMesh(glm::vec3(0, 1, 1), "star1");
		AddMeshToList(m1);
		star_meshes.emplace_back(m1);
		m1 = MeshManager::initStarMesh(glm::vec3(0.33f, 0.38f, 0.96f), "star2");
		AddMeshToList(m1);
		star_meshes.emplace_back(m1);
		m1 = MeshManager::initStarMesh(glm::vec3(0.8f, 0.59f, 0.98f), "star3");
		AddMeshToList(m1);
		star_meshes.emplace_back(m1);
		m1 = MeshManager::initStarMesh(glm::vec3(0.79f, 0.8f, 0.22f), "star4");
		AddMeshToList(m1);
		star_meshes.emplace_back(m1);

		m1 = MeshManager::initRombMesh(glm::vec3(0, 1, 1), glm::vec3(1, 0, 0), "low_value_romb");
		AddMeshToList(m1);
		romb_meshes.emplace_back(m1);
		m1 = MeshManager::initRombMesh(glm::vec3(0.33f, 0.38f, 0.96f), glm::vec3(1, 0, 0), "med_value_romb1");
		AddMeshToList(m1);
		romb_meshes.emplace_back(m1);
		m1 = MeshManager::initRombMesh(glm::vec3(0.8f, 0.59f, 0.98f), glm::vec3(1, 0, 0), "med_value_romb2");
		AddMeshToList(m1);
		romb_meshes.emplace_back(m1);
		m1 = MeshManager::initRombMesh(glm::vec3(0.79f, 0.8f, 0.22f), glm::vec3(1, 0, 0), "high_value_romb");
		AddMeshToList(m1);
		romb_meshes.emplace_back(m1);

		m1 = MeshManager::initHexagonMesh(glm::vec3(0, 1, 1), glm::vec3(1, 1, 0), "hexagon_r_y");
		AddMeshToList(m1);
		enemy_meshes.emplace_back(m1);
		m1 = MeshManager::initHexagonMesh(glm::vec3(0.33f, 0.38f, 0.96f), glm::vec3(1, 1, 0), "hexagon_b_y");
		AddMeshToList(m1);
		enemy_meshes.emplace_back(m1);
		m1 = MeshManager::initHexagonMesh(glm::vec3(0.8f, 0.59f, 0.98f), glm::vec3(1, 1, 0), "hexagon");
		AddMeshToList(m1);
		enemy_meshes.emplace_back(m1);
		m1 = MeshManager::initHexagonMesh(glm::vec3(0.79f, 0.8f, 0.22f), glm::vec3(1, 1, 0), "hexagon3");
		AddMeshToList(m1);
		enemy_meshes.emplace_back(m1);

		selected_romb.scaleBy(50);
		selected_romb.mesh = nullptr;

		last_star_appearance = std::chrono::high_resolution_clock::now();

		root.addChildContainer(&top_screen);
		top_screen.addChildContainer(&shop);
		top_screen.addChildContainer(&star_counter);
		top_screen.addChildContainer(&lives_counter);
		root.addChildContainer(&play_area);
		play_area.moveTo(glm::vec3(0, 60, 0));

		star_count = 10;

		glm::vec3 corner = glm::vec3(0, 0, 0);
		float squareSide = 100;
		Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
		AddMeshToList(square1);
		initPlayArea();
		initTopDisplayArea();
	}
	void Tema1::FrameStart() {
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::ivec2 resolution = window->GetResolution();
		glViewport(0, 0, resolution.x, resolution.y);
	}
	void Tema1::FrameEnd() {
		
	}
	std::vector<std::pair<Hexagon*, Shape*>> Tema1::getCollisions() {
		std::vector<std::pair<Hexagon*, Shape*>> s;
		RefPointContainer* r = &play_area;
		std::queue<RefPointContainer*> q;
		q.push(r);
		std::vector<Shape*> other_shapes;
		std::vector<Hexagon*> hexagons;

		while (!q.empty()) {
			RefPointContainer* rt = q.front();
			q.pop();
			for (auto& s : rt->shapes) {
				if (s == nullptr) {
					continue;
				}
				Hexagon* h = dynamic_cast<Hexagon*>(s);
				if (h == nullptr && s != nullptr && s->can_collide == true) {
					other_shapes.emplace_back(s);
					continue;
				}
				if (h != nullptr) {
					hexagons.emplace_back(h);
				}
			}
			for (auto& s : rt->children) {
				q.push(s);
			}
		}
		for (auto& hexagon : hexagons) {
			for (auto& shape : other_shapes) {
				if (hexagon->collidesWith(shape)) {
					s.emplace_back(std::make_pair(hexagon, shape));
				}
			}
		}
		return s;
	}
	void Tema1::checkCollision(std::pair<Hexagon*, Shape*> collision) {
		Star* star_ptr = dynamic_cast<Star*>(collision.second);
		if (star_ptr != nullptr) {
			collision.first->nr_of_lives--;
			star_ptr->should_render = false;
			return;
		}
		Romb* romb_ptr = dynamic_cast<Romb*>(collision.second);
		if (romb_ptr != nullptr) {
			collision.first->dying = true;
			romb_ptr->dying = true;
			//romb_ptr->parent->shapes.erase(std::find(romb_ptr->parent->shapes.begin(), romb_ptr->parent->shapes.end(), romb_ptr));
			return;
		}
		lives_count--;
		//if (lives_counter.shapes.size() > 0) {
		//	lives_counter.shapes.erase(lives_counter.shapes.end() - 1);
		//}
		collision.first->dying = true;

	}
	void Tema1::displayLives() {
		glm::vec3 pos = lives_counter.shapes[0]->getAbsolutePosition();
		if (lives_count == 0) {
			exit(0);
		}
		for (int i = 0; i < lives_count; i++) {
			glm::mat4 m = glm::mat4(1);
			m = glm::translate(m, pos);
			m = glm::scale(m, glm::vec3(40, 40, 0));
			RenderMesh(meshes["red_square"], shaders["VertexColor"], m);
			pos.x += 120;
		}
	}
	void Tema1::displayStars() {
		glm::vec3 pos = star_counter.shapes[0]->getAbsolutePosition();
		for (int i = 0; i < star_count; i++) {
			glm::mat4 m = glm::mat4(1);
			m = glm::translate(m, pos);
			m = glm::scale(m, glm::vec3(10, 10, 0));
			RenderMesh(meshes["yellow_star"], shaders["VertexColor"], m);
			pos.x += 25;
		}
	}
	void Tema1::Update(float deltaTimeSeconds) {
		glLineWidth(3);
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);

		auto collisions = getCollisions();

		auto now = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> elapsed_seconds = now - last_star_appearance;
		std::chrono::milliseconds secs = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds);

		if (secs.count() > next_star_in) {
			Star* st = new Star(meshes["green_star"]);
			st->scaleBy(50);
			st->moveTo(glm::vec3(r.getRandomNumber(50, window->GetResolution().x), r.getRandomNumber(50, window->GetResolution().y), 5));
			root.addShape(st);
			next_star_in = r.getRandomNumber(3000, 6000);
			last_star_appearance = std::chrono::high_resolution_clock::now();
		}

		for (auto& collision : collisions) {
			checkCollision(collision);
		}

		if (selected_romb.mesh != nullptr) {
			selected_romb.update();
			RenderMesh(selected_romb.mesh, shaders["VertexColor"], selected_romb.transformMatrix);
		}

		displayLives();
		displayStars();

		RefPointContainer* r = &root;
		std::queue<RefPointContainer*> q;
		q.push(r);
		
		while (!q.empty()) {
			RefPointContainer* rt = q.front();
			q.pop();
			for (int i = 0; i < rt->shapes.size();i++) {
				Shape* s = rt->shapes[i];
				if (!s->should_render) {
					auto iter = std::find(s->parent->shapes.begin(), s->parent->shapes.end(), s);
					if (iter == s->parent->shapes.end()) {
						continue;
					}
					s->parent->shapes.erase(iter);
					delete s;
					continue;
				}
			}

			for (int i = 0; i < rt->shapes.size();i++) {
				auto s = rt->shapes[i];
				if (s == nullptr) {
					continue;
				}
				s->animate(deltaTimeSeconds);
				s->update();
				if (s->mesh != nullptr) {
					RenderMesh(s->mesh, shaders["VertexColor"], s->transformMatrix);
				}
			}
			for (auto& s : rt->children) {
				s->onUpdate(deltaTimeSeconds);
				q.push(s);
			}
		}
		animation_counter++;
	}
	void Tema1::initPlayArea() {
		Square* s = new Square(meshes["red_square"], true);
		s->moveTo(glm::vec3(0, 120, 0));
		s->scaleBy(50, OX);
		s->scaleBy(170, OY);
		play_area.addShape(s);

		for (int i = 0; i < lane_count; i++) {
			Lane* l = new Lane(enemy_meshes, glm::vec3(100, i * 120, 0), glm::vec3(1, 1, 0), 2000, glm::vec3(window->GetResolution().x + 50, 0, 0));
			l->generate_in = r.getRandomNumber(1000, 3000);
			for (int j = 0; j < 3; j++) {
				Square* s = new Square(meshes["white_square"], false);
				s->moveTo(glm::vec3(50 + j * 120, 0, 0));
				s->scaleBy(50);
				l->addShape(s);
			}
			lanes.push_back(l);
			play_area.addChildContainer(l);
		}
	}
	void Tema1::initTopDisplayArea() {

		top_screen.moveTo(glm::vec3(0, window->GetResolution().y - 240, 0));
		lives_counter.moveTo(glm::vec3(window->GetResolution().x - 400, 160, 0));
		star_counter.moveTo(glm::vec3(window->GetResolution().x - 400, 100, 0));
		Shape* s = new Shape(meshes["yellow_star"]);
		s->transformMatrix = glm::mat4(0);
		s->position = glm::vec3(0,0,0);
		star_counter.addShape(s);
		s = new Shape(meshes["yellow_star"]);
		s->transformMatrix = glm::mat4(0);
		s->position = glm::vec3(0,0,0);
		lives_counter.addShape(s);

		initShop();
	}

	void Tema1::initShop() {

		shop.moveTo(glm::vec3(50, 100, 0));

		for (int i = 0; i < 4; i++) {
			RefPointContainer* rc = new RefPointContainer();
			rc->moveTo(glm::vec3(i * 150 + 100, 0, 0));
			initShopItem(rc, i + 1);
			shop.addChildContainer(rc);
		}
	}

	void Tema1::initShopItem(RefPointContainer* r, int index) {
		int type = index - 1;
		if (index > 2) {
			index--;
		}
		Shape* sqr = new Shape(meshes["square_contour"]);
		r->addShape(sqr);
		sqr->moveTo(glm::vec3(0, 60, 0));
		sqr->scaleBy(50);
		sqr->update();
		Romb* romb = new Romb(romb_meshes[type], index, type);
		romb->projectile_mesh = star_meshes[type];
		r->addShape(romb);
		romb->moveTo(glm::vec3(0, 60, 0));
		romb->scaleBy(50);
		romb->update();
		for (int i = 0; i < index; i++) {
			Star* star = new Star(meshes["yellow_star"], false, -1);
			star->moveTo(glm::vec3(i * 20 - 40, 0, 0));
			star->scaleBy(10);
			star->update();
			r->addShape(star);
		}

	}

	void Tema1::OnInputUpdate(float deltaTime, int mods) {
	}
	void Tema1::OnKeyPress(int key, int mods) {
	}
	void Tema1::OnKeyRelease(int key, int mods) {
	}
	void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
		if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
			if (selected_romb.mesh != nullptr && selected_romb.should_move == true) {
				//std::cerr << "a";
				mouseY = window->GetResolution().y - mouseY;
				selected_romb.moveTo(glm::vec3(mouseX, mouseY, 1.0f));
			}
		}
	}
	void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
		mouseY = window->GetResolution().y - mouseY;
		std::vector<Shape*> under_cursor = getElementsAtPoint(&root, mouseX, mouseY);
		if (button == GLFW_MOUSE_BUTTON_3) {
			for (Shape* shape : under_cursor) {
				Romb* romb = dynamic_cast<Romb*>(shape);
				if (romb == nullptr) {
					continue;
				}
				if (dynamic_cast<Lane*>(romb->parent) == nullptr) {
					continue;
				}
				romb->should_render = false;
				star_count++;
			}
			return;
		}
		if (button == GLFW_MOUSE_BUTTON_2) {
			//std::cerr << mouseX << " " << mouseY << "\n";
			for (Shape* shape : under_cursor) {
				Star* star = dynamic_cast<Star*>(shape);
				if (star != nullptr) {
					if (star->parent != &root) {
						continue;
					}
					star->should_render = false;
					if (this->star_count < 16) {
						this->star_count++;
					}
					continue;
				}
				Romb* romb = dynamic_cast<Romb*>(shape);
				if (romb == nullptr) {
					continue;
				}
				if (dynamic_cast<Lane*>(romb->parent)) {
					continue;
				}
				if (romb->price > star_count) {
					return;
				}
				selected_romb.should_render = true;
				selected_romb.should_move = true;
				selected_romb.moveTo(glm::vec3(mouseX, mouseY, 1.0f));
				selected_romb.mesh = romb->mesh;
				selected_romb.projectile_mesh = romb->projectile_mesh;
				selected_romb.price = romb->price;
				selected_romb.type = romb->type;
			}
		}
	}
	void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
		if (selected_romb.mesh == nullptr) {
			return;
		}
		Mesh* prev_mesh = selected_romb.mesh;
		selected_romb.mesh = nullptr;
		mouseY = window->GetResolution().y - mouseY;
		selected_romb.should_move = false;
		std::vector<Shape*> under_cursor = getElementsAtPoint(&play_area, mouseX, mouseY);
		if (under_cursor.empty()) {
			return;
		}
		Shape* ptr = nullptr;
		Square* sqr_ptr = nullptr;
		Romb* romb_ptr = nullptr;
		for (auto& shape : under_cursor) {
			romb_ptr = dynamic_cast<Romb*>(shape);
			if (romb_ptr != nullptr) {
				return;
			}
			ptr = dynamic_cast<Square*>(shape);
			if (ptr != nullptr) {
				sqr_ptr = dynamic_cast<Square*>(shape);
			}
		}
		if (sqr_ptr == nullptr) {
			return;
		}
		star_count -= selected_romb.price;
		Romb* new_romb = new Romb(prev_mesh, 0, selected_romb.type);
		new_romb->can_collide = true;
		new_romb->moveTo(sqr_ptr->position + glm::vec3(0,0,1));
		new_romb->scaleBy(50);
		new_romb->update();
		new_romb->projectile_mesh = selected_romb.projectile_mesh;
		sqr_ptr->parent->addShape(new_romb);
		new_romb->startFiring();
	}
	void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
	}
	void Tema1::OnWindowResize(int width, int height) {
	}
	std::vector<Shape*> Tema1::getElementsAtPoint(RefPointContainer* container, int mouseX, int mouseY) {
		std::vector<Shape*> v;
		
		RefPointContainer* r = container;
		std::queue<RefPointContainer*> q;
		q.push(r);

		while (!q.empty()) {
			RefPointContainer* rt = q.front();
			q.pop();
			for (auto& s : rt->shapes) {
				if (dynamic_cast<Star*>(s) == nullptr && dynamic_cast<Romb*>(s) == nullptr && dynamic_cast<Square*>(s) == nullptr) {
					continue;
				}
				if (s->hasPointInside(mouseX, mouseY)) {
					v.emplace_back(s);
				}
			}
			for (auto& s : rt->children) {
				q.push(s);
			}
		}
		return v;
	}
}