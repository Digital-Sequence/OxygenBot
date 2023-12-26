#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <mysql/mysql.h>

class Connection_pool {
	std::condition_variable	condition;
	std::queue<MYSQL*>		connection_pool;
	std::mutex				mx;
	bool					locked;
	public:
		void push(MYSQL* con) {
			std::unique_lock<std::mutex> lock(mx);
			locked = true;
			connection_pool.push(con);
			locked = false;
			condition.notify_one();
		};
		MYSQL* pop() {
			std::unique_lock<std::mutex> lock(mx);
			locked = true;
			MYSQL* element = connection_pool.front();
			connection_pool.pop();
			locked = false;
			condition.notify_one();
			return element;
		};
		bool empty() {
			return connection_pool.empty();
		};
		int size() {
			return connection_pool.size();
		}
		std::queue<MYSQL*>& data() {
			return connection_pool;
		}
};

extern Connection_pool connections;