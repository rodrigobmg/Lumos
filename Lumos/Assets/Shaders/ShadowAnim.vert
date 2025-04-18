#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable
#include "Buffers.glslh"

layout(push_constant) uniform PushConsts
{
	mat4 transform;
	uint cascadeIndex;
    float p0;
    float p1;
    float p2;
} pushConsts;

out gl_PerVertex
{
    vec4 gl_Position;
};

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;
layout(location = 4) in vec3 inTangent;
layout(location = 5) in vec3 inBitangent;
layout(location = 6) in ivec4 inBoneIndices;
layout(location = 7) in vec4 inBoneWeights;

layout(location = 0) out vec2 uv;

void main()
{
    vec3 position = inPosition;
	vec4 colour = inColor;
	uv = inTexCoord;
	vec3 normal = inNormal;
	vec3 tangent = inTangent;
	vec3 bitangent = inBitangent;
	ivec4 boneIn = inBoneIndices;
    vec4 boneWe = inBoneWeights;

	mat4 boneTransform = u_BoneTransforms.BoneTransforms[int(boneIn[0])] * boneWe[0];
    boneTransform += u_BoneTransforms.BoneTransforms[int(boneIn[1])] * boneWe[1];
    boneTransform += u_BoneTransforms.BoneTransforms[int(boneIn[2])] * boneWe[2];
    boneTransform += u_BoneTransforms.BoneTransforms[int(boneIn[3])] * boneWe[3];

    mat4 proj;
    switch(pushConsts.cascadeIndex)
    {
        case 0 :
            proj = u_DirShadow.DirLightMatrices[0];
            break;
        case 1 :
            proj = u_DirShadow.DirLightMatrices[1];
            break;
        case 2 :
            proj = u_DirShadow.DirLightMatrices[2];
            break;
        default :
            proj = u_DirShadow.DirLightMatrices[3];
            break;
    }

    gl_Position = pushConsts.transform * boneTransform  * vec4(position, 1.0); // proj *

    float test6 = pushConsts.p0;
    float test7 = pushConsts.p1;
    float test8 = pushConsts.p2;
}
