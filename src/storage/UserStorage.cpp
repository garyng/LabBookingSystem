#include "UserStorage.h"

std::vector<User> UserStorage::LoadDefault()
{
	return std::vector<User>{
		{"0001", "admin", "8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918", UserRole::Adminstrator},
		{"0002", "garyng", "0d55f6fa2c80f790d39ef65eca13258aa6edaccf1b8563424a9e7e70c5245df5", UserRole::Normal},
		{"0003", "dambrozewicz2", "618db554ddf082d345ff51c1398c981e178cfb1799e4bf12d7591f1ec7e2b204", UserRole::Normal},
		{"0004", "hbrozek3", "305669aadd86c6fbdebd8fb8205f81353653aa9b479c647314dcfbb130f50aa2", UserRole::Normal},
		{"0005", "dinchbald4", "1cd2c3f8571636b9770a1f0bd83e26fcbb4361aad067f3a2bc0214aa7c509f91", UserRole::Normal},
		{"0006", "tskokoe5", "dc92f99807191c42f44fa7b258bb5fa90341e987242ff10c7576ddf79b56bc1e", UserRole::Normal},
		{"0007", "ssodeau6", "dcb03948fb3a48df7505e285a9b73de6f63e96e69fd5edf907023f947c9a3172", UserRole::Normal},
		{"0008", "dolivie7", "b9c367d018b8f64c2981ea14eb798b9e40916a5947d5ad530ea73b499f447da2", UserRole::Normal},
		{"0009", "ddaltrey8", "caa609b60ca5cc6618ee94869d5642ab47cb8a10fff7f51581fa02a05358746d", UserRole::Normal},
		{"0010", "jivens9", "24ed6188d6377fbb932d886308c0f95bf8d04311f0e4ee93520a3ea856cc13d7", UserRole::Normal},
		{"0011", "tcashleya", "9706502520433c6c38481885f9c0de8b8a1a3e43e7bdffb987b64915478e5a2f", UserRole::Normal},
		{"0012", "ewhisbyb", "990c2d0251d29b7462cffa4186b4f6cc75945c553a5c7f2bbd641a4f85580e4e", UserRole::Normal},
		{"0013", "djanskyc", "9cd66ecec60c85bc723bcc576cc4d1e3ae6a71235fd99ad2325c388d89c02dc7", UserRole::Normal},
		{"0014", "jlenzd", "18f323e83495b2319129371919da5bd9fa0e848a9e024950a467ce26aee1ba69", UserRole::Normal},
		{"0015", "spoore", "066820a42d2428eb02111e9cb7027e4e91f698772582c6accf1d97f788c4fdb8", UserRole::Normal},
		{"0016", "alossmanf", "ad059207d40cf90e97244de30e97c0403c3f11841cde41b3554bef5816da6a11", UserRole::Normal},
		{"0017", "jmulmurayg", "69e93f83a6773733d12008da0394337400515c9ec20c50240dac6a5b17fcbebb", UserRole::Normal},
		{"0018", "ccordeyh", "7289c9fb53c4e2a930110fc21c91c42eb6f3262a01403b27429c6111569bfe27", UserRole::Normal},
		{"0019", "lbabei", "8c037669f7f73a1cae2c7220730cfb42c0335f104c9a91fd36cfd91e84f71246", UserRole::Normal},
		{"0020", "sfrushardj", "79ab47772feffa381f949153218cfa83bf1a82c44fa1ee7f06b56bee93e5e7df", UserRole::Normal}
	};
}

std::string UserStorage::GetDataFilename()
{
	return "users.json";
}
