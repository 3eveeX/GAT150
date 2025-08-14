#pragma once
#include <vector>

namespace whermst{
	class Mesh : public Resource {
	public:
		Mesh() = default;

		Mesh(const std::vector<vec2>& points, const vec3& colour = {1.0f, 1.0f, 1.0f}) 
			: _points(points)
			, _colour(colour) 
		{
			CalculateRadius();
		}

		bool Load(const std::string& fileName);

		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale = 1.0f);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return _radius; }

		void SetColour(const vec3& colour) { _colour = colour; }

		
	private:
		void CalculateRadius();
	private:
		std::vector<vec2> _points;
		vec3 _colour{1.0f, 1.0f, 1.0f};
		float _radius{ 0.0f };	
	};

}