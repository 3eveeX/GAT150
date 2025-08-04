#include "File.h"
#include "StringHelper.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace whermst::file
{


    std::string GetCurrentDirectory()
    {
        std::error_code ec;
		auto path = std::filesystem::current_path();
        return ec ? std::string{} : path.string();
    }

    bool SetCurrentDirectory(const std::string& path)
    {
        std::error_code ec;
		std::filesystem::current_path(path, ec);
        return !ec;
    }

    std::string GetExtension(const std::string& path)
    {
        std::filesystem::path p(path);
		return p.extension().string();
    }

    std::string GetFilename(const std::string& path)
    {
        std::filesystem::path p(path);
		return p.filename().string();
    }

    bool Exists(const std::string& path)
    {
        std::error_code ec;
        bool result = std::filesystem::exists(path, ec);

        return !ec && result;
    }

    int GetLineCountInFile(const std::string& path)
    {
		std::ifstream file(path);
        if (!file.is_open()) {
            return -1; // error opening file
        }
        int lineCount = 0;
        std::string line;
        while (std::getline(file, line)) {
            ++lineCount;
        }
        file.close();
        return lineCount;
	}

    void SortFileByScore(const std::string& path, const std::string& derivative, int offset, int lineAmount)
    {
        if (offset == 0) {
			offset = derivative.length(); 
        }
		std::vector<std::string> playerNames;
		std::vector<int> scores;
        std::ifstream score_fileRead(path);
        std::string scoreString;
        while (std::getline(score_fileRead, scoreString)) {
            if (scoreString.find(derivative) == std::string::npos) {
                continue; // skip lines that do not contain the derivative
			}
			playerNames.push_back(scoreString);
			// Extract the score after the derivative
            scores.push_back(std::stoi(scoreString.substr(scoreString.find(derivative) + offset)));
        }
        std::cout << "Before Sort" << std::endl;
        score_fileRead.close();

        std::sort(scores.begin(), scores.end(), std::greater<int>());

		std::cout << "After Sort, before write" << std::endl;
        scores.erase(std::unique(scores.begin(), scores.end()), scores.end());

        while (scores.size() > lineAmount) {
            scores.pop_back();
        }

		// Clear the file before writing sorted scores
		ClearFile(path);
		// Write the sorted scores back to the file
        for (const auto& score : scores) {
            std::string scoreStr = std::to_string(score);

            for (const auto& name : playerNames) {
                // Check if the score is in the player's name
                if (name.find(scoreStr) == std::string::npos) {
                    continue; // Skip if not found
                }

                // Find position of ':' in the name
                size_t colonPos = name.find(':');
                std::string playerName = (colonPos != std::string::npos)
                    ? name.substr(0, colonPos)
                    : name; // fallback if no ':'

                // Build the output line
                std::string outputLine = playerName + derivative + scoreStr + "\n";

                // Write to file
                WriteTextFile(path, outputLine, true);

                // Debug output
                std::cout << "writing" << std::endl;
            }
        }
		std::cout << "After Write" << std::endl;
    }

    std::string ReadFileByLine(const std::string& path)
    {
		std::string content;
		StringBuilder sb;
		std::ifstream file(path);
        if (!file.is_open()) {
            return std::string(); // return empty string on error
		}
        while (std::getline(file, content)) {
            sb.append(content + "\n");
        }
        return sb.toString();
    }
    

    

    std::vector<std::string> GetFilesInDirectory(const std::string& path)
    {
        std::vector<std::string> files;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return files; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_regular_file(ec) && !ec) {
                files.push_back(entry.path().string());
            }
        }

        return files;
    }

    std::vector<std::string> GetDirectoriesIn(const std::string& path)
    {
        std::vector<std::string> directories;
        std::error_code ec;

        auto iter = std::filesystem::directory_iterator(path, ec);
        if (ec) return directories; // return empty vector on error

        for (const auto& entry : iter) {
            if (entry.is_directory(ec) && !ec) {
                directories.push_back(entry.path().string());
            }
        }

        return directories;
    }

    bool ReadTextFile(const std::string& path, std::string& content)
    {
        std::ifstream file(path);
        if (!file.is_open()) {
            return false;
        }

        // read entire file into string
        std::stringstream buffer;
		buffer << file.rdbuf();
        content = buffer.str();
        file.close();
		return true;
    }

    bool WriteTextFile(const std::string& path, const std::string& content, bool append)
    {
        std::ios::openmode mode = append ? std::ios::app : std::ios::out;
        std::ofstream file(path, mode);
        if (!file.is_open()) {
            return false;
        }


		file << content;
		file.close();
		return true;
    }
    bool ClearFile(const std::string& path)
    {                 
        std::ofstream file(path, std::ios::trunc);
        if (!file.is_open()) {
            return false;
        }
        file.close();
        return true;
    }
}