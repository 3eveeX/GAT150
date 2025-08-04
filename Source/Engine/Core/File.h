#pragma once
#include <string>
#include <vector>

namespace whermst::file {
    std::string GetCurrentDirectory();
    bool SetCurrentDirectory(const std::string& path);
    std::string GetExtension(const std::string& path);
    std::string GetFilename(const std::string& path);
    bool Exists(const std::string& path);
    int GetLineCountInFile(const std::string& path);
    void SortFileByScore(const std::string& path, const std::string& derivative, int offset = 0, int lineAmount = 100);
    std::string ReadFileByLine(const std::string& path);
    std::vector<std::string> GetFilesInDirectory(const std::string& path);
    std::vector<std::string> GetDirectoriesIn(const std::string& path);

    bool ReadTextFile(const std::string& path, std::string& content);
    bool WriteTextFile(const std::string& path, const std::string& content, bool append = false);
	bool ClearFile(const std::string& path);
}
