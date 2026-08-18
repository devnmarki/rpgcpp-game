#ifndef ASSET_HPP
#define ASSET_HPP

class Texture;
class TextureConfig;
class Sprite;
class SpriteConfig;
class SpriteSheet;
class SpriteSheetConfig;
class AnimationGroup;
class AnimationGroupConfig;
class Tilemap;
class TilemapConfig;

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

template<>
struct AssetTraits<SpriteSheet> {
	using ConfigType = SpriteSheetConfig;
};

template<>
struct AssetTraits<AnimationGroup> {
	using ConfigType = AnimationGroupConfig;
};

template<>
struct AssetTraits<Tilemap> {
	using ConfigType = TilemapConfig;
};

#endif