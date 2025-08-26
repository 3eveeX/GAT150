#pragma once
#include <string>
#include <sstream>

namespace whermst {
	inline std::string tolower(const std::string& str){
		std::string result = str;

		//convert to lowercase
		for (char& c : result) {
			c = std::tolower(c);
		}

		return result;
	}
	inline std::string toupper(const std::string& str) {
		std::string result = str;
		//convert to uppercase
		for (char& c : result) {
			c = std::toupper(c);
		}
		return result;
	}
    class StringBuilder {
    public:
        StringBuilder& append(const std::string& str) {
            buffer << str;
            return *this;
        }

        StringBuilder& append(const char* str) {
            buffer << str;
            return *this;
        }

        template<typename T>
        StringBuilder& append(const T& value) {
            buffer << value;
            return *this;
        }

        std::string toString() const {
            return buffer.str();
        }

        void clear() {
            buffer.str("");
            buffer.clear();
        }

    private:
        std::ostringstream buffer;
    };
    inline bool equalsIgnoreCase(const std::string& a, const std::string& b) {
        if (a.length() != b.length()) return false;
        return std::equal(a.begin(), a.end(), b.begin(), [](char ac, char bc) {
            return std::tolower(ac) == std::tolower(bc);
	});
	}
}
