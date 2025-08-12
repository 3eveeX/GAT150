#include "Font.h"


namespace whermst {
	/// <summary>
	/// Destructor for the Font class.
	/// </summary>
	Font::~Font()
	{
		if (_ttfFont != nullptr) {
			TTF_CloseFont(_ttfFont);
		}
	}

	/// <summary>
	/// Loads a font from a file.
	/// </summary>
	/// <param name="name">The name of the font file.</param>
	/// <param name="fontSize">The size of the font.</param>
	/// <returns>True if the font was loaded successfully, false otherwise.</returns>
	bool Font::Load(const std::string& name, float fontSize)
	{
		_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (_ttfFont == nullptr) {
			Logger::Error("Could not load font: {}", name);
			return false;
		}

		return true;
	}
}