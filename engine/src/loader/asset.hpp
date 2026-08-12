#ifndef ASSET_HPP
#define ASSET_HPP

class Texture;
class TextureConfig;
class Sprite;
class SpriteConfig;

struct Asset {
	virtual ~Asset() = default;
};

template<typename T>
struct AssetTraits {};

template<>
struct AssetTraits<Texture> {
	using ConfigType = TextureConfig;
};

template<>
struct AssetTraits<Sprite> {
	using ConfigType = SpriteConfig;
};

#endif