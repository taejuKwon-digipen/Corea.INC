#pragma once
#include "../Header/Engine.h"
#include "../Header/GameObject.h"
#include "../Header/Rect.h"
#include "../Header/Collision.h"

GLApp::GLModel model;

void RectCollision::Draw(math::TransformMatrix cameraMatrix) {
    /*doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    math::rect2 displayRect = GetWorldCoorRect();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix);
    doodle::draw_rectangle(displayRect.Left(), displayRect.Bottom(), displayRect.Size().x, displayRect.Size().y);
    doodle::pop_settings();*/

    glLineWidth(3.f);
    glVertexAttrib3f(1, 1.f, 1.f, 1.f);
    math::rect2 displayRect = GetWorldCoorRect();
    std::array<glm::vec2, 4> pos_vtx{
        glm::vec2(displayRect.Left(), displayRect.Bottom()), glm::vec2(display)
    	displayRect.Size().x, displayRect.Size().y
    };
    std::array<glm::vec2, 4> idx_vtx{
        glm::vec2(0.f, 0.f), glm::vec2(0.f, 1.f),
    glm::vec2(1.f, 1.f), glm::vec2(1.f, 0.f)
    };
	
    glDrawElements(GL_LINE, 4, GL_UNSIGNED_INT, NULL);
}

void CircleCollision::Draw(math::TransformMatrix cameraMatrix) {
    /*doodle::no_fill();
    doodle::set_outline_width(2);
    doodle::set_outline_color(doodle::HexColor(0xFFFFFFFF));
    doodle::push_settings();
    doodle::apply_matrix(cameraMatrix[0][0], cameraMatrix[1][0], cameraMatrix[0][1], cameraMatrix[1][1], cameraMatrix[0][2], cameraMatrix[1][2]);
    doodle::draw_ellipse(objectPtr->GetPosition().x, objectPtr->GetPosition().y, GetRadius() * 2);
    doodle::pop_settings();*/

    glLineWidth(3.f);

}


math::rect2 RectCollision::GetWorldCoorRect() {
    return { objectPtr->GetMatrix() * static_cast<glm::vec2>(rect.point1),
                objectPtr->GetMatrix() * static_cast<glm::vec2>(rect.point2) };
}

bool RectCollision::DoesCollideWith(GameObject* objectB) {
    Collision* collideAgainst = objectB->GetGOComponent<Collision>();
    if (collideAgainst == nullptr) {
        Engine::GetLogger().LogError(Part::Entire,"testAgainstObject collision is null");
        return false;
    }
    if (collideAgainst->GetCollideType() != CollideType::Rect_Collide) {
        Engine::GetLogger().LogError(Part::Entire,"Rect vs unsupported type");
        return false;
    }

    math::rect2 rectA = GetWorldCoorRect();
    math::rect2 rectB = dynamic_cast<RectCollision*>(collideAgainst)->GetWorldCoorRect();

    if (rectA.Right() > rectB.Left() && rectA.Left() < rectB.Right() &&
        rectA.Bottom() < rectB.Top() && rectA.Top() > rectB.Bottom()) {
        return true;
    }
    return false;
}

bool RectCollision::DoesCollideWith(glm::vec2 point) {
    math::rect2 worldRect = GetWorldCoorRect();
    return point.x >= worldRect.Left() && point.x <= worldRect.Right() && point.y <= worldRect.Top() && point.y >= worldRect.Bottom();
}

double CircleCollision::GetRadius() {
    return (glScaled(objectPtr->GetScale()) * glm::vec2{ radius, 0 }).x;
}

bool CircleCollision::DoesCollideWith(GameObject* objectB) {
    Collision* collideAgainst = objectB->GetGOComponent<Collision>();
    if (collideAgainst == nullptr) {
        Engine::GetLogger().LogError(Part::Entire,"testAgainstObject collision is null");
        return false;
    }
    if (collideAgainst->GetCollideType() != CollideType::Circle_Collide) {
        Engine::GetLogger().LogError(Part::Entire, "Circle vs unsupported type");
        return false;
    }

    glm::vec2 dist = objectPtr->GetPosition() - objectB->GetPosition();
    double radiusA = GetRadius();
    double radiusB = dynamic_cast<CircleCollision*>(collideAgainst)->GetRadius();
    double distSquare = dist.x * dist.x + dist.y * dist.y;
    double collideDistSquare = (radiusA + radiusB) * (radiusA + radiusB);

    return distSquare < collideDistSquare;
}

bool CircleCollision::DoesCollideWith(glm::vec2 point) {

    glm::vec2 dist = objectPtr->GetPosition() - point;
    double distSquare = dist.x * dist.x + dist.y * dist.y;
    double radiusA = GetRadius();
    double collideDistSquare = radiusA * radiusA;

    return distSquare < collideDistSquare;
}