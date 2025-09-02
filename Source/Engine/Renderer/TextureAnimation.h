#pragma once

namespace whermst {
	class Texture;

	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;
		~TextureAnimation() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize() const;

		rect GetFrameRect(int frame) const;
		int GetTotalFrames() const { return _totalFrames; }
		float GetFPS() const { return _framesPerSecond; }
		bool IsValidFrame(int frame) const { return frame >= 0 && frame < _totalFrames; }
		bool IsLooping() const { return _loop; }

		res_t<Texture> GetTexture() { return _texture; }
	private:
		int _columns = 0;
		int _rows = 0;
		int _startFrame = 0;
		int _totalFrames = 0;
		float _framesPerSecond = 0;
		bool _loop = true;

		res_t<Texture> _texture;

	};
}
