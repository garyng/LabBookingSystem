#pragma once
#include <memory>
#include "storage/LabStorage.h"
#include "SelectTimeViewModel.h"
#include "query/GetAllLabsQuery.h"

class SelectLabViewModel
	: public ViewModelBase
{
private:
	std::vector<Lab> _labs;
	std::shared_ptr<LabStorage> _labStorage;
	std::string _userName;

	int _selectedIndex;

public:
	std::vector<Lab> Labs() const { return _labs; }
	void Labs(std::vector<Lab> value) { _labs = value; }

	int SelectedIndex() const { return _selectedIndex; }
	void SelectedIndex(int value) { _selectedIndex = value; }

	std::string UserName() const { return _userName; }
	void UserName(std::string value) { _userName = value; }

	explicit SelectLabViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<LabStorage>& labStorage);

	void LoadAllLabsCommand();
	void SelectTimeCommand();

	void Reset() override;
	void GoBackCommand() const override;

	std::string Name() override { return "SelectLabViewModel"; }
};
