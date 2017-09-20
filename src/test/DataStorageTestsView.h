#pragma once

class DataStorageTestsView
	: public IView
{
private:

public:
	DataStorageTestsView(std::vector<std::shared_ptr<IStorage>> storages): _storages(storages)
	{
	}

	void Render() override
	{
		ImGui::Begin("Debug: Storages");

		for (auto& storage : _storages)
		{
			std::string name(typeid(*storage).name());
			std::string text(ICON_MD_SETTINGS_BACKUP_RESTORE " Reset " + name);

			if (ImGui::Button(text.c_str()))
			{
				storage->Restore();
			};
		}

		ImGui::End();
	}

	std::string virtual Name() override { return "DataStorageTestsView"; }
	std::vector<std::shared_ptr<IStorage>> _storages;
};
