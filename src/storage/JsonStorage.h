#pragma once
#include <filesystem>
#include <json.hpp>
#include <vector>
#include <fstream>
#include "../logger/Logger.h"
#include "IStorage.h"

namespace fs = std::experimental::filesystem;
using json = nlohmann::json;

template <class TData>
class JsonStorage
	: public IStorage
{
private:
	fs::path ResolvePath(std::string filename)
	{
		fs::path dataDirectory("data");
		if (!exists(dataDirectory))
		{
			create_directory(dataDirectory);
		}
		fs::path dataFilePath = dataDirectory / GetDataFilename();

		return dataFilePath;
	}

protected:
	std::vector<TData> _data;
	std::shared_ptr<ILogger> Log = Logger::Instance();

	std::vector<TData> virtual LoadDefault() = 0;
	std::string virtual GetDataFilename() = 0;

public:
	void Load() override
	{
		fs::path dataFilePath = ResolvePath(GetDataFilename());

		if (!exists(dataFilePath))
		{
			Log->Warn("\"" + dataFilePath.string() + "\" not found! Default data loaded.");
			_data = LoadDefault();
			return;
		}

		std::ifstream reader(dataFilePath);

		if (!reader.is_open())
		{
			Log->Error("Unable to open \"" + dataFilePath.string() + "\"");
			return;
		}

		json json;

		reader >> json;
		reader.close();

		_data = json.get<std::vector<TData>>();

		Log->Debug("Data loaded from \"" + dataFilePath.string() + "\"");
	}

	void Save() override
	{
		fs::path dataFilePath = ResolvePath(GetDataFilename());
		json json = _data;

		std::ofstream writer(dataFilePath);
		if (!writer.is_open())
		{
			Log->Error("Unable to open \"" + dataFilePath.string() + "\"");
			return;
		}

		writer << json;
		writer.close();
		Log->Debug("Data saved to \"" + dataFilePath.string() + "\"");
	}

	void Restore() override
	{
		_data = LoadDefault();
		Save();
		Log->Info("Restored data to original state");
	}

	std::vector<TData>& Data()
	{
		return _data;
	}

	virtual ~JsonStorage() = default;
};
