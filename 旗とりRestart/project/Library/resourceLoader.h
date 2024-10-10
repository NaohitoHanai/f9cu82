#pragma once
#include <string>

namespace ResourceLoader {
	void Init();
	int LoadGraph(std::string filename);
	void DeleteGraph(int handle);
	int MV1LoadModel(std::string filename);
	void MV1DeleteModel(int handle);
	int LoadSoundMem(std::string filename);
	void DeleteSoundMem(int handle);
	void LoadFolderFile(std::string folder, bool loadSubFolder=false);

	/// <summary>
	/// 非同期読み込みをするかを設定する
	/// </summary>
	/// <param name="async">非同期読み込みする場合true</param>
	void SetAsync(bool async);

	/// <summary>
	/// 非同期でファイルを読んでいるか
	/// </summary>
	/// <returns>ファイルを読んでいる途中はtrue</returns>
	bool IsLoading();

	/// <summary>
	/// 読んだファイルを全部消す
	/// </summary>
	void ReleaseAllFile();
};