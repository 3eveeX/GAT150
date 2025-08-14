#include "Mesh.h"
#include "Renderer.h"

namespace whermst{
	/// <summary>
	/// Attempts to load mesh data from the specified file.
	/// </summary>
	/// <param name="fileName">The name of the file containing mesh data to load.</param>
	/// <returns>True if the mesh was loaded successfully; otherwise, false.</returns>
	bool Mesh::Load(const std::string& fileName){
		std::string buffer;
		if (!file::ReadTextFile(fileName, buffer)) {
			Logger::Error("could not read file: {}", fileName);
			return false;
		}

		std::stringstream stream(buffer);

		stream >> _colour;
		vec2 point;
		while (stream >> point) {
			_points.push_back(point);
		}

		if (!stream.eof()) {
			Logger::Error("could not parse");
			return false;
		}

		return true;
	}
	void Mesh::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {
		renderer.SetColourf(_colour.r, _colour.g, _colour.b);
		for (int i = 0; i < _points.size(); ++i) {
			const vec2& p1 = (_points[i].rotate(math::degToRad(rotation)) * scale) + position;
			const vec2& p2 = ((_points[(i + 1) % _points.size()].rotate(math::degToRad(rotation)) * scale) + position);
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}

	void Mesh::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	/// <summary>
	/// Calculates and updates the model's radius based on the farthest point from the origin.
	/// </summary>
	void Mesh::CalculateRadius()
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