#include "stdafx.h"
#include "SpriteFontLoader.h"

SpriteFont* SpriteFontLoader::LoadContent(const ContentLoadInfo& loadInfo)
{
	const auto pReader = new BinaryReader();
	pReader->Open(loadInfo.assetFullPath);

	if (!pReader->Exists())
	{
		Logger::LogError(L"Failed to read the assetFile!\nPath: \'{}\'", loadInfo.assetSubPath);
		return nullptr;
	}

	//TODO_W5(L"Implement SpriteFontLoader >> Parse .fnt file")
	//See BMFont Documentation for Binary Layout

	//Parse the Identification bytes (B,M,F)
	//If Identification bytes doesn't match B|M|F,
	//Log Error (SpriteFontLoader::LoadContent > Not a valid .fnt font) &
	//return nullptr
	if (pReader->Read<char>() != 'B' || pReader->Read<char>() != 'M' || pReader->Read<char>() != 'F')
	{
		Logger::LogError(L"not a valid .fnt font");
		return nullptr;
	}

	//Parse the version (version 3 required)
	//If version is < 3,
	//Log Error (SpriteFontLoader::LoadContent > Only .fnt version 3 is supported)
	//return nullptr
	if (pReader->Read<uint8_t>() != 3)
	{
		Logger::LogError(L"only. fnt version 3 is supported");
		return nullptr;
	}

	//Valid .fnt file >> Start Parsing!
	//use this SpriteFontDesc to store all relevant information (used to initialize a SpriteFont object)
	SpriteFontDesc fontDesc{};

	//**********
	// BLOCK 0 *
	//**********
	//Retrieve the blockId and blockSize
	//Retrieve the FontSize [fontDesc.fontSize]
	//Move the binreader to the start of the FontName [BinaryReader::MoveBufferPosition(...) or you can set its position using BinaryReader::SetBufferPosition(...))
	//Retrieve the FontName [fontDesc.fontName]
	uint8_t blockId = pReader->Read<uint8_t>();
	int blockSize = pReader->Read<int>();

	fontDesc.fontSize = pReader->Read<uint16_t>();

	pReader->MoveBufferPosition(12);
	fontDesc.fontName = pReader->ReadNullString();

	//**********
	// BLOCK 1 *
	//**********
	//Retrieve the blockId and blockSize
	//Retrieve Texture Width & Height [fontDesc.textureWidth/textureHeight]
	//Retrieve PageCount
	//> if pagecount > 1
	//	> Log Error (Only one texture per font is allowed!)
	//Advance to Block2 (Move Reader)
	blockId = pReader->Read<uint8_t>();
	blockSize = pReader->Read<int>();

	pReader->MoveBufferPosition(4);
	fontDesc.textureWidth = pReader->Read<uint16_t>();
	fontDesc.textureHeight = pReader->Read<uint16_t>();

	if (pReader->Read<uint16_t>() > 1)
	{
		Logger::LogError(L"Only one texture per font is allowed");
		return nullptr;
	}

	pReader->MoveBufferPosition(blockSize - 10);


	//**********
	// BLOCK 2 *
	//**********
	//Retrieve the blockId and blockSize
	blockId = pReader->Read<uint8_t>();
	blockSize = pReader->Read<int>();
	//Retrieve the PageName (BinaryReader::ReadNullString)
	auto pageName = pReader->ReadNullString();
	//Construct the full path to the page texture file
	//	>> page texture should be stored next to the .fnt file, pageName contains the name of the texture file
	//	>> full texture path = asset parent_path of .fnt file (see loadInfo.assetFullPath > get parent_path) + pageName (filesystem::path::append)
	//	>> Load the texture (ContentManager::Load<TextureData>) & Store [fontDesc.pTexture]
	fontDesc.pTexture = ContentManager::Load<TextureData>(loadInfo.assetFullPath.parent_path().append(pageName));

	//**********
	// BLOCK 3 *
	//**********
	//Retrieve the blockId and blockSize
	blockId = pReader->Read<uint8_t>();
	blockSize = pReader->Read<int>();

	//Retrieve Character Count (see documentation)
	size_t wordCount = blockSize / sizeof(FontMetric);
	//pReader->MoveBufferPosition(20);
	//Create loop for Character Count, and:
	for (size_t i = 0; i <= wordCount; i++)
	{
		//> Retrieve CharacterId (store Local) and cast to a 'wchar_t'
		wchar_t characterId =static_cast<wchar_t>(pReader->Read<uint32_t>());

		//> Create instance of FontMetric (struct)
		FontMetric fontMetric{};

		//	> Set Character (CharacterId) [FontMetric::character]
		fontMetric.character = characterId;

		//	> Retrieve Xposition (store Local)
		uint16_t x = pReader->Read<uint16_t>();
		//	> Retrieve Yposition (store Local)
		uint16_t y = pReader->Read<uint16_t>();

		//	> Retrieve & Set Width [FontMetric::width]
		fontMetric.width = pReader->Read<uint16_t>();
		//	> Retrieve & Set Height [FontMetric::height]
		fontMetric.height = pReader->Read<uint16_t>();
		//	> Retrieve & Set OffsetX [FontMetric::offsetX
		fontMetric.offsetX = pReader->Read<uint16_t>();
		//	> Retrieve & Set OffsetY [FontMetric::offsetY]
		fontMetric.offsetY = pReader->Read<uint16_t>();
		//	> Retrieve & Set AdvanceX [FontMetric::advanceX]
		fontMetric.advanceX = pReader->Read<uint16_t>();
		//	> Retrieve & Set Page [FontMetric::page]
		fontMetric.page = pReader->Read<char>();
		//	> Retrieve Channel (BITFIELD!!!) 
		//		> See documentation for BitField meaning [FontMetrix::channel]
		fontMetric.channel = pReader->Read<char>();
		fontMetric.channel -= 1;
		if (fontMetric.channel == 2)
			fontMetric.channel = 0;
		else if (fontMetric.channel == 0)
			fontMetric.channel = 2;
		else if (fontMetric.channel == 3)
			fontMetric.channel = 0;

		//fontMetric.channel -= 1;
		//	> Calculate Texture Coordinates using Xposition, Yposition, fontDesc.TextureWidth & fontDesc.TextureHeight [FontMetric::texCoord]
		fontMetric.texCoord = XMFLOAT2{ 
			(static_cast<float>(x) /  fontDesc.textureWidth) ,  (static_cast<float>(y) /  fontDesc.textureHeight)
		};

		//> Insert new FontMetric to the metrics [font.metrics] map
		//	> key = (wchar_t) charId
		//	> value = new FontMetric

		fontDesc.metrics[characterId] = fontMetric;
	}
	//(loop restarts till all metrics are parsed)

	//Done!
	delete pReader;
	return new SpriteFont(fontDesc);
}

void SpriteFontLoader::Destroy(SpriteFont* objToDestroy)
{
	SafeDelete(objToDestroy);
}
