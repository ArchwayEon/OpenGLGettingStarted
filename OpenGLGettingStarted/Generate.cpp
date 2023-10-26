#include "Generate.h"

std::unique_ptr<Mesh> Generate::LineArrow(float length, RGB color)
{
	//auto lineArrow = std::make_shared<GraphicsObject>();

	float oneTenthLength = length / 10;
	float nineTenthLength = length - oneTenthLength;

	Position p0 = { 0.0f, 0.0f, 0.0f };
	Position p1 = { length, 0.0f,  0.0f };
	Position p2 = { nineTenthLength, oneTenthLength,  0 };
	Position p3 = { nineTenthLength, -oneTenthLength,  0 };


	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	mesh->AddVertex(p0, color);
	mesh->AddVertex(p1, color);
	mesh->AddVertex(p2, color);
	mesh->AddVertex(p3, color);
	mesh->AddIndexData(6, 0, 1, 1, 2, 1, 3);
	mesh->material.ambientIntensity = 1.0f;

	//lineArrow->mesh = std::move(mesh);

	return mesh;
}

std::unique_ptr<Mesh> Generate::FlatSurface(float width, float depth, RGB color)
{
	//auto flatSurface = std::make_shared<GraphicsObject>();

	float halfWidth = width / 2;
	float halfDepth = depth / 2;

	Position p0 = { -halfWidth, 0.0f, -halfDepth };
	Position p1 = { -halfWidth, 0.0f,  halfDepth };
	Position p2 = { halfWidth, 0.0f,  halfDepth };
	Position p3 = { halfWidth, 0.0f, -halfDepth };

	Direction normal = { 0.0f, 1.0f, 0.0f };

	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	mesh->AddVertex(p0, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p2, color, normal);
	mesh->AddVertex(p3, color, normal);
	mesh->AddTriangleIndices(0, 1, 2);
	mesh->AddTriangleIndices(2, 3, 0);

	//flatSurface->mesh = std::move(mesh);

	return mesh;
}

std::unique_ptr<Mesh> Generate::Cuboid(float width, float height, float depth, RGB color)
{
	//auto cuboid = std::make_shared<GraphicsObject>();

	float halfWidth = width / 2;
	float halfDepth = depth / 2;
	float halfHeight = height / 2;

	Position p0 = { -halfWidth,  halfHeight, halfDepth };
	Position p1 = { -halfWidth, -halfHeight, halfDepth };
	Position p2 = { halfWidth, -halfHeight, halfDepth };
	Position p3 = { halfWidth,  halfHeight, halfDepth };

	Position p4 = { -halfWidth,  halfHeight, -halfDepth };
	Position p5 = { -halfWidth, -halfHeight, -halfDepth };
	Position p6 = { halfWidth, -halfHeight, -halfDepth };
	Position p7 = { halfWidth,  halfHeight, -halfDepth };

	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	// Front face
	Direction normal = { 0, 0, -1 };
	mesh->AddVertex(p0, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p2, color, normal);
	mesh->AddVertex(p2, color, normal);
	mesh->AddVertex(p3, color, normal);
	mesh->AddVertex(p0, color, normal);
	// Right face
	normal = { 1, 0, 0 };
	mesh->AddVertex(p3, color, normal);
	mesh->AddVertex(p2, color, normal);
	mesh->AddVertex(p6, color, normal);
	mesh->AddVertex(p6, color, normal);
	mesh->AddVertex(p7, color, normal);
	mesh->AddVertex(p3, color, normal);
	// Back face
	normal = { 0, 0, 1 };
	mesh->AddVertex(p7, color, normal);
	mesh->AddVertex(p6, color, normal);
	mesh->AddVertex(p5, color, normal);
	mesh->AddVertex(p5, color, normal);
	mesh->AddVertex(p4, color, normal);
	mesh->AddVertex(p7, color, normal);
	// Left face
	normal = { -1, 0, 0 };
	mesh->AddVertex(p4, color, normal);
	mesh->AddVertex(p5, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p0, color, normal);
	mesh->AddVertex(p4, color, normal);
	// Top face
	normal = { 0, 1, 0 };
	mesh->AddVertex(p4, color, normal);
	mesh->AddVertex(p0, color, normal);
	mesh->AddVertex(p3, color, normal);
	mesh->AddVertex(p3, color, normal);
	mesh->AddVertex(p7, color, normal);
	mesh->AddVertex(p4, color, normal);
	// Bottom face
	normal = { 0, -1, 0 };
	mesh->AddVertex(p6, color, normal);
	mesh->AddVertex(p2, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p1, color, normal);
	mesh->AddVertex(p5, color, normal);
	mesh->AddVertex(p6, color, normal);

	//cuboid->mesh = std::move(mesh);

	return mesh;
}

std::unique_ptr<Mesh> Generate::Cylinder(float radius, float height, int slices, int stacks, RGB color, ShadingType shadingType)
{
	//auto cylinder = std::make_shared<GraphicsObject>();
	float sliceStep = 360.0f / slices;
	float halfHeight = height / 2;
	float tHeight = 1.0f / stacks;
	float tWidth = 1.0f / slices;

	std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
	Position p1, p2, p3;
	Direction n1, n2, n3;
	float theta, thetaRad, sinTheta, cosTheta;
	for (theta = 0; theta < 360.0f; theta += sliceStep) {
		p1 = { 0.0f, halfHeight, 0.0f };
		n1 = { 0, 1, 0 };

		thetaRad = glm::radians(theta);
		sinTheta = sinf(thetaRad);
		cosTheta = cosf(thetaRad);
		p2 = { radius * sinTheta, halfHeight, radius * cosTheta };
		n2 = { 0, 1, 0 };

		thetaRad = glm::radians(theta + sliceStep);
		sinTheta = sinf(thetaRad);
		cosTheta = cosf(thetaRad);
		p3 = { radius * sinTheta, halfHeight, radius * cosTheta };
		n3 = { 0, 1, 0 };

		mesh->AddVertex(p1, color, n1);
		mesh->AddVertex(p2, color, n2);
		mesh->AddVertex(p3, color, n3);
	}

	// The middle facets have 4 vertices
	// V1--V4
	// |\  |
	// | \ |
	// |  \|
	// V2--V3
	// Generate the middle
	PCNVertex V1{}, V2{}, V3{}, V4{};
	glm::vec3 VA, VB, VC, VD;
	float y = halfHeight;
	float stackHeight = height / stacks;
	for (int stack = 0; stack < stacks; stack++) {
		for (theta = 0; theta < 360.0f; theta += sliceStep) {
			// V1
			thetaRad = glm::radians(theta);
			sinTheta = sinf(thetaRad);
			cosTheta = cos(thetaRad);
			V1.position = { radius * sinTheta, y, radius * cosTheta };
			VA = glm::vec3(V1.position.x, V1.position.y, V1.position.z);
			V1.color = color;
			// V2
			V2.position = { radius * sinTheta, y - stackHeight, radius * cosTheta };
			VB = glm::vec3(V2.position.x, V2.position.y, V2.position.z);
			V2.color = color;
			// V3
			thetaRad = glm::radians(theta + sliceStep);
			sinTheta = sinf(thetaRad);
			cosTheta = cos(thetaRad);
			V3.position = { radius * sinTheta, y - stackHeight, radius * cosTheta };
			VC = glm::vec3(V3.position.x, V3.position.y, V3.position.z);
			V3.color = color;
			// V4
			V4.position = { radius * sinTheta, y, radius * cosTheta };
			VD = glm::vec3(V4.position.x, V4.position.y, V4.position.z);
			V4.color = color;

			if (shadingType == ShadingType::Flat_Shading) {
				glm::vec3 AB = glm::normalize(VB - VA);
				glm::vec3 AC = glm::normalize(VC - VA);
				glm::vec3 NA = glm::cross(AB, AC);
				V1.normal = { NA.x, NA.y, NA.z };

				glm::vec3 BC = glm::normalize(VC - VB);
				glm::vec3 BA = glm::normalize(VA - VB);
				glm::vec3 NB = glm::cross(BC, BA);
				V2.normal = { NB.x, NB.y, NB.z };

				glm::vec3 CA = glm::normalize(VA - VC);
				glm::vec3 CB = glm::normalize(VB - VC);
				glm::vec3 NC = glm::cross(CA, CB);
				V3.normal = { NC.x, NC.y, NC.z };

				glm::vec3 AD = glm::normalize(VD - VA);
				glm::vec3 ND = glm::cross(AC, AD);
				V4.normal = { ND.x, ND.y, ND.z };
			}
			else { // Use the normalized position vectors as the normal
				VA.y = 0;
				glm::vec3 NA = glm::normalize(VA);
				V1.normal = { NA.x, NA.y, NA.z };

				VB.y = 0;
				glm::vec3 NB = glm::normalize(VB);
				V2.normal = { NB.x, NB.y, NB.z };

				VC.y = 0;
				glm::vec3 NC = glm::normalize(VC);
				V3.normal = { NC.x, NC.y, NC.z };

				VD.y = 0;
				glm::vec3 ND = glm::normalize(VD);
				V4.normal = { ND.x, ND.y, ND.z };
			}
			mesh->AddVertex(V1.position, V1.color, V1.normal);
			mesh->AddVertex(V2.position, V2.color, V2.normal);
			mesh->AddVertex(V3.position, V3.color, V3.normal);

			mesh->AddVertex(V3.position, V3.color, V3.normal);
			mesh->AddVertex(V4.position, V4.color, V4.normal);
			mesh->AddVertex(V1.position, V1.color, V1.normal);
		} // for theta
		y -= stackHeight;
	} // for each stack

	y = -halfHeight;
	// The bottom
	//  V1---V3
	//   \   /
	//    \ /
	//     V2
	for (theta = 0; theta < 360.0f; theta += sliceStep) {
		// V1
		thetaRad = glm::radians(theta);
		sinTheta = sinf(thetaRad);
		cosTheta = cosf(thetaRad);
		V1.position = { radius * sinTheta, y, radius * cosTheta };
		V1.color = color;
		V1.normal = { 0, -1, 0 };
		// V2
		V2.position = { 0, y, 0 };
		V2.color = color;
		V2.normal = { 0, -1, 0 };
		// V3
		thetaRad = glm::radians(theta + sliceStep);
		sinTheta = sinf(thetaRad);
		cosTheta = cos(thetaRad);
		V3.position = { radius * sinTheta, y, radius * cosTheta };
		V3.color = color;
		V3.normal = { 0, -1, 0 };

		mesh->AddVertex(V1.position, V1.color, V1.normal);
		mesh->AddVertex(V2.position, V2.color, V2.normal);
		mesh->AddVertex(V3.position, V3.color, V3.normal);
	}


	//cylinder->mesh = std::move(mesh);
	return mesh;
}
