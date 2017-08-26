#include "UserStorage.h"

std::vector<User> UserStorage::LoadDefault()
{
	return std::vector<User>{
		{"0001", "admin", "21232f297a57a5a743894a0e4a801fc3", UserRole::Adminstrator},
		{"0002", "garyng", "e10adc3949ba59abbe56e057f20f883e", UserRole::Normal},
		{"0003", "dambrozewicz2", "e091f9e70d76bf77716e48660913a859", UserRole::Normal},
		{"0004", "hbrozek3", "9d61173bb509f2e10940492dde1e81d3", UserRole::Normal},
		{"0005", "dinchbald4", "cd5d453e45c584e243a48298364ed01e", UserRole::Normal},
		{"0006", "tskokoe5", "6982dab3b0838b01b098ccdd00451421", UserRole::Normal},
		{"0007", "ssodeau6", "5c4852551f44309b876f743a4fb873ab", UserRole::Normal},
		{"0008", "dolivie7", "5640c42213f396f9670b85247787a572", UserRole::Normal},
		{"0009", "ddaltrey8", "cffa496c770644f2d0059146cca3a512", UserRole::Normal},
		{"0010", "jivens9", "ed731c7461cfa486e1124d83f3ebc0ba", UserRole::Normal},
		{"0011", "tcashleya", "aed013afcc57e808dde1e6a3c8687e5b", UserRole::Normal},
		{"0012", "ewhisbyb", "72c5f5ed0374633fbca0dcb8fec11113", UserRole::Normal},
		{"0013", "djanskyc", "cf9a80979b2a9fb22a18019284544a32", UserRole::Normal},
		{"0014", "jlenzd", "137ad5b557e902d06d4ccfb6f7c2fdce", UserRole::Normal},
		{"0015", "spoore", "e04e183b1df4fe5d7fd11c733d82f6dc", UserRole::Normal},
		{"0016", "alossmanf", "bb2deff531c81b672140aa09c2852699", UserRole::Normal},
		{"0017", "jmulmurayg", "7f9df2f127ebd30b47c9816db4557886", UserRole::Normal},
		{"0018", "ccordeyh", "28d3d603f1b222b3150d079474f551e7", UserRole::Normal},
		{"0019", "lbabei", "bd0065ebc3ffc720fdc75ba1ccad7ffd", UserRole::Normal},
		{"0020", "sfrushardj", "42e26d2e890c496a977d68cf7b4fa237", UserRole::Normal}
	};
}

std::string UserStorage::GetDataFilename()
{
	return "users.json";
}
