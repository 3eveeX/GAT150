#include "TextureAnimation.h"

namespace whermst {
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		whermst::json::document_t document;
		if (!whermst::json::Load(filename, document)) {
			Logger::Error("Could not load TextureAnimation json {}", filename);
			return false;
		}

		std::string textureName;
		JSON_READ(document, textureName);

		_texture = Resources().Get<Texture>(textureName, renderer);
		if (!_texture) {
		Logger::Error("Could not load texture in TextureAnimation {}", textureName);
		return false;
		}

		JSON_READ_NAME(document, "columns", _columns);
		JSON_READ_NAME(document, "rows", _rows);
		JSON_READ_NAME(document, "startFrame", _startFrame);
		JSON_READ_NAME(document, "totalFrames", _totalFrames);
		JSON_READ_NAME(document, "framesPerSecond", _framesPerSecond);
		JSON_READ_NAME(document, "loop", _loop);

		return true;
	}

	vec2 TextureAnimation::GetSize() const {
		vec2 size = _texture->GetSize();

		return vec2(size.x / _columns, size.y / _rows);
	}

	rect TextureAnimation::GetFrameRect(int frame) const
	{
		if (!IsValidFrame(frame)) {
			Logger::Warning("Frame is outside Bounds {}/{}", frame, _totalFrames);
			frame = 0;
		}

		rect frameRect;
		vec2 size = GetSize();

		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((_startFrame + frame) % _columns) * frameRect.w;
		frameRect.y = ((_startFrame + frame) / _columns) * frameRect.h;

		return frameRect;
	}

}