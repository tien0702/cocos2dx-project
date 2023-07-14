#include "Setting.h"
#include "json/rapidjson.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/document.h"


float Setting::_BGM_Volume;
float Setting::_SFX_Volume;
float Setting::_Effect_Volume;
bool Setting::_fixedJoystick;
char* Setting::_fileName = "config.txt";

bool Setting::loadSettings()
{
	std::string path = Setting::getPath();

	if (cocos2d::FileUtils::getInstance()->isFileExist(path)) {
		Setting::readConfigFile();
	}
	else {
		Setting::initConfigFile();
	}
	return true;
}

void Setting::save()
{
	std::string path = Setting::getPath();

	rapidjson::Document document;
	document.SetObject();
	document.AddMember("BGM", Setting::_BGM_Volume, document.GetAllocator());
	document.AddMember("SFX", Setting::_SFX_Volume, document.GetAllocator());
	document.AddMember("Effect", Setting::_BGM_Volume, document.GetAllocator());
	document.AddMember("FixedJoystick", Setting::_fixedJoystick, document.GetAllocator());

	// writer
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	// save
	FILE* file = fopen(path.c_str(), "wb");
	if (file) {
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}

void Setting::reset()
{
	_BGM_Volume = 0.5f;
	_SFX_Volume = 0.5f;
	_Effect_Volume = 0.5f;
	_fixedJoystick = false;
}

std::string Setting::getPath()
{
	std::string path = FileUtils::getInstance()->getWritablePath();
	path += Setting::_fileName;
	return path;
}

bool Setting::readConfigFile()
{
	std::string path = Setting::getPath();

	rapidjson::Document document;
	std::string fileData = FileUtils::getInstance()->getStringFromFile(path);
	document.Parse(fileData.c_str());
	if (document.HasParseError()) {
		log("Parse error");
	}
	else {
		Setting::_BGM_Volume = document["BGM"].GetFloat();
		Setting::_SFX_Volume = document["SFX"].GetFloat();
		Setting::_Effect_Volume = document["Effect"].GetFloat();
		Setting::_fixedJoystick = document["FixedJoystick"].GetBool();
	}
	return true;
}

bool Setting::initConfigFile()
{
	_BGM_Volume = 0.5f;
	_SFX_Volume = 0.5f;
	_Effect_Volume = 0.5f;
	_fixedJoystick = false;
	Setting::save();
	return true;
}
