/*
 * Log.hpp
 *
 *  Created on: Jun 15, 2022
 *      Author: lieuwe
 */

#ifndef INCLUDE_DD_LOG_HPP_
#define INCLUDE_DD_LOG_HPP_

#include <iostream>

namespace dd {

	class _Log {
	public:
		bool verbose;  //  0: silent
		               //  1: loud

		_Log(unsigned int _verbose)
			: verbose(_verbose) {
		}


		template <class T>
		_Log& operator<<(const T& val) {
			if (verbose) {
				std::cout << val;
			}
			return *this;
		}

		void flush() const {
			if (verbose) {
				std::cout.flush();
			}
		}
	};

	std::ostream& operator<<(std::ostream& out, [[maybe_unused]] const _Log& log) {
		return out;
	}

	class Log {
	public:
		static inline _Log log = _Log(1);
		static inline char endl = '\n';
	};

//	Log Log::log(1);
//	char Log::endl = '\n';
}



#endif /* INCLUDE_DD_LOG_HPP_ */
