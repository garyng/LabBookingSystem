// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include <functional>
#include <stack>
#include <filesystem>
#include <fstream>
#include <optional>
#include <initializer_list>
#include <iostream>

#include <imgui.h>
#include <imgui_internal.h>
#include <IconsMaterialDesign.h>
#include <picosha2.h>
#include <coveo/linq.h>
#include <enum.h>
#include <json.hpp>
#include <date.h>

#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeParser.h>
#include <Poco/Data/Time.h>
#include <Poco/Data/Date.h>

#include "IView.h"
#include "ViewBase.h"
#include "IViewModel.h"
#include "ViewModelBase.h"
#include "AppColors.h"
#include "AppFontIndex.h"
#include "services/NavigationService.h"
#include "storage/IStorage.h"
#include "storage/JsonStorage.h"
#include "logger/ILogger.h"
#include "logger/Logger.h"
