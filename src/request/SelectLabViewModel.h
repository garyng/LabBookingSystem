#pragma once
#include <memory>
#include "storage/LabStorage.h"

class GetAllLabsQuery
{
private:
	std::shared_ptr<LabStorage> _labStorage;

public :
	explicit GetAllLabsQuery(const std::shared_ptr<LabStorage>& labStorage)
		: _labStorage(labStorage)
	{
	}


	std::vector<Lab> Execute()
	{
		return _labStorage->Data();
	}
};


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

	explicit SelectLabViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<LabStorage>& labStorage)
		: ViewModelBase(navigation), _labStorage(labStorage),  _selectedIndex(0)
	{
	}

	void LoadAllLabsCommand()
	{
		GetAllLabsQuery query(_labStorage);
		std::vector<Lab> labs = query.Execute();

		Labs(labs);
	}

	void Reset() override
	{
		_selectedIndex = 0;
	}
	std::string Name() override { return "SelectLabViewModel"; }
};
