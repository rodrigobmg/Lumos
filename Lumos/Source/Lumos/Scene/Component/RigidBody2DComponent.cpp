#include "Precompiled.h"
#include "RigidBody2DComponent.h"

#include <box2d/box2d.h>
#include <imgui/imgui.h>

namespace Lumos
{
    RigidBody2DComponent::RigidBody2DComponent()
    {
        m_RigidBody = CreateSharedPtr<RigidBody2D>();
    }

    RigidBody2DComponent::RigidBody2DComponent(const RigidBodyParameters& params)
    {
        m_RigidBody = CreateSharedPtr<RigidBody2D>(params);
    }

    RigidBody2DComponent::RigidBody2DComponent(SharedPtr<RigidBody2D>& physics)
        : m_RigidBody(physics)
    {
    }

    void RigidBody2DComponent::Update()
    {
    }

    void RigidBody2DComponent::OnImGui()
    {
        auto pos      = m_RigidBody->GetPosition();
        auto angle    = m_RigidBody->GetAngle();
        auto friction = m_RigidBody->GetFriction();
        auto isStatic = m_RigidBody->GetIsStatic();
        auto isRest   = m_RigidBody->GetIsAtRest();

        auto elasticity = m_RigidBody->GetElasticity();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
        ImGui::Columns(2);
        ImGui::Separator();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Position");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat2("##Position", &pos.x))
            m_RigidBody->SetPosition(pos);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Orientation");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Orientation", &angle))
            m_RigidBody->SetOrientation(angle);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Friction");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Friction", &friction))
            m_RigidBody->SetFriction(friction);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Elasticity");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Elasticity", &elasticity))
            m_RigidBody->SetElasticity(elasticity);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("Static");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::Checkbox("##Static", &isStatic))
            m_RigidBody->SetIsStatic(isStatic);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted("At Rest");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::Checkbox("##At Rest", &isRest))
            m_RigidBody->SetIsAtRest(isRest);

        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
    }
}
