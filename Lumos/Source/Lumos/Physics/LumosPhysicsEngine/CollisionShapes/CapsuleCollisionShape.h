#pragma once

#include "CollisionShape.h"

namespace Lumos
{

    class LUMOS_EXPORT CapsuleCollisionShape : public CollisionShape
    {
    public:
        CapsuleCollisionShape(float radius = 1.0f, float height = 1.0f);
        ~CapsuleCollisionShape();

        // Collision Shape Functionality
        virtual Mat3 BuildInverseInertia(float invMass) const override;

        virtual TDArray<Vec3>& GetCollisionAxes(const RigidBody3D* currentObject) override;
        virtual TDArray<CollisionEdge>& GetEdges(const RigidBody3D* currentObject) override;

        virtual void GetMinMaxVertexOnAxis(const RigidBody3D* currentObject, const Vec3& axis, Vec3* out_min, Vec3* out_max) const override;
        virtual void GetIncidentReferencePolygon(const RigidBody3D* currentObject, const Vec3& axis, ReferencePolygon& refPolygon) const override;

        virtual void DebugDraw(const RigidBody3D* currentObject) const override;

        // Get/Set Sphere Radius
        void SetRadius(float radius)
        {
            m_Radius         = radius;
            m_LocalTransform = Mat4(1.0); // Mat4::Scale(Vec3(m_Radius, m_Height, m_Radius));
        }

        float GetRadius() const
        {
            return m_Radius;
        }

        float GetSize() const override
        {
            return m_Radius;
        }

        float GetHeight() const
        {
            return m_Height;
        }

        void SetHeight(float height)
        {
            m_Height         = height;
            m_LocalTransform = Mat4(1.0); // Mat4::Scale(Vec3(m_Radius, m_Height, m_Radius));
        }

        template <typename Archive>
        void save(Archive& archive) const
        {
            archive(m_Radius, m_Height);
        }

        template <typename Archive>
        void load(Archive& archive)
        {
            archive(m_Radius, m_Height);
            m_LocalTransform = Mat4(1.0); // Mat4::Scale(Vec3(m_Radius * 2.0f));
            m_Type           = CollisionShapeType::CollisionCapsule;
        }

    protected:
        float m_Radius;
        float m_Height;
    };
}
