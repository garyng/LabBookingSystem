#include "stdafx.h"
#include "SelectLabViewModel.h"

SelectLabViewModel::SelectLabViewModel(const std::shared_ptr<NavigationService>& navigation, const std::shared_ptr<LabStorage>& labStorage): ViewModelBase(navigation), _labStorage(labStorage), _selectedIndex(0)
{
}

void SelectLabViewModel::LoadAllLabsCommand()
{
	GetAllLabsQuery query(_labStorage);
	std::vector<Lab> labs = query.Execute();

	Labs(labs);
}

void SelectLabViewModel::SelectTimeCommand()
{
	std::string labId = _labs[_selectedIndex].Id();
	_navigation->GoTo<SelectTimeViewModel>([&](std::shared_ptr<SelectTimeViewModel> vm)
                                       {
	                                       vm->LabId(labId);
	                                       vm->UserName(_userName);
	                                       vm->LoadRequestsCommand();
	                                       vm->RefreshTimeListCommand();
                                       }, true);
}

void SelectLabViewModel::Reset()
{
	_selectedIndex = 0;
}

void SelectLabViewModel::GoBackCommand() const
{
	_navigation->GoBack<RequestViewModel>([](std::shared_ptr<RequestViewModel> vm) { vm->LoadUserRequestCommand(); });
}
