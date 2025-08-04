#include "Model.h"
#include "Renderer.h"

namespace whermst{
	void Model::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {
		renderer.SetColourf(_colour.r, _colour.g, _colour.b);
		for (int i = 0; i < _points.size(); ++i) {
			const vec2& p1 = (_points[i].rotate(math::degToRad(rotation)) * scale) + position;
			const vec2& p2 = ((_points[(i + 1) % _points.size()].rotate(math::degToRad(rotation)) * scale) + position);
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Calculates and updates the model's radius based on the farthest point from the origin.
	/// </summary>
	void Model::CalculateRadius()
	{
		_radius = 0.0f;
		for (auto& point : _points) {
		float length = point.Length();
			if (length > _radius) {
				_radius = length;
			}
		}
	}

}