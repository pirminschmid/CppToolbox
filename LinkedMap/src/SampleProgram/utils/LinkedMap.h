//
// Created by Pirmin Schmid on 12.04.17.
//

#ifndef TOOLBOX_UTILS_LINKED_MAP_H_
#define TOOLBOX_UTILS_LINKED_MAP_H_

#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <unordered_map>
#include <vector>

namespace toolbox {

	/**
	 * This is an implementation of a std::unordered_map, with the additional feature of keeping
	 * insertion/refresh order, to easily traverse from least recently used (LRU) to
	 * most recently used (MRU) item using the findFirstWithPredicate method,
	 * leading to an optionally modified removal instead of FIFO.
	 *
	 * This implementation does not (yet) fulfill the entire interface of std::unordered_map.
	 * Thus, the class is not named linked_map.
	 *
	 * Use add() until capacity is full and then use replace() with an id found before using one of
	 * these functins: findFirstWithPredicate(), find(), getLruId(), getMruId().
	 * This replacement is a 2-step process on purpose, to allow using a cascade of different
	 * predicates, if one should be unsuccessful. This allows building more sophisticated
	 * map management schemes on top.
	 *
	 * The predicate is user defined; see predicate_type type. Additionally, a range close to
	 * MRU can be declared to be reserved and is not tested in this traversal. Also, the
	 * actual LRU can be excluded from testing. The returned Id can be used for the replace() method.
	 *
	 * A kNone value indicates that no suitable id could be found.
	 *
	 * Note: capacity is not enforced. It is increased if more elements are added. However,
	 * there is some cost with copying of the internal buffers of the used containers.
	 *
	 * It also allows a refresh() of an entry by key, i.e. lookup by key and then move to MRU position,
	 * without the need to remove and reinsert the element. While there is a clear() method,
	 * no erase() method is defined on purpose.
	 *
	 * The implementation keeps the values stored without movements. The list is also kept as
	 * vector to keep index values as close as possible.
	 *
	 * Debug output can be activated with a flag at the moment. If more performance is needed
	 * without debug output, the associated debug conditionals can be removed from code
	 * by commenting the LM_DEBUG_MODE_ALLOWED preprocessor macro.
	 *
	 * For additional performance gain, checks can be deactivated by commenting LM_APPLY_CHECKS.
	 *
	 * Hint: use std::unique_ptr<T> for non-trivial value types T. The map store will
	 * handle memory management automatically without copying lots of data.
	 *
	 * v1.3 2017-04-12 / 2017-05-03 Pirmin Schmid
	 *
	 * @tparam K key type
	 * @tparam V value type
	 */

#define LM_DEBUG_MODE_ALLOWED

#define LM_APPLY_CHECKS

	template<typename K, typename V>
	class LinkedMap {
	public:
		typedef int32_t ID_type;  // must be a signed integer type large enough to hold capacity

		typedef std::function<bool(const V &)> predicate_type;

		static constexpr ID_type kMaxCapacity = std::numeric_limits<ID_type>::max();

		static constexpr ID_type kNone = -1;

		LinkedMap(const ID_type capacity, bool debug_mode = false): capacity_(capacity), debug_mode_(debug_mode) {
			store_.reserve(capacity);
			list_.reserve(capacity);

#ifdef LM_DEBUG_MODE_ALLOWED
			if (debug_mode_) {
				std::cout << "LinkedMap initialized with capacity " << capacity_ << std::endl;
			}
#endif
		}


		void setDebugMode(bool debug_mode) {
			debug_mode_ = debug_mode;
		}


		void clear() {
			store_.clear();
			list_.clear();
			map_.clear();

			next_id_ = 0;
			first_ = kNone;
			last_ = kNone;
		}


		void add(const K &key, V value) {
			if (next_id_ == kMaxCapacity) {
				std::cerr << "Error in LinkedMap::add(): add not possible. Max. capacity " << kMaxCapacity
						  << " of current ID_type is reached." << std::endl;
				return;
			}

			ID_type id = next_id_++;
			store_.push_back(std::move(value));
			ListInfo info = {key, kNone, kNone};
			list_.push_back(info);
			addAsMru(id);
			map_[key] = id;

			if (capacity_ < next_id_) {
				capacity_ = next_id_;
			}

#ifdef LM_DEBUG_MODE_ALLOWED
			if (debug_mode_) {
				std::cout << "LinkedMap: add key " << key << " @ ID " << id
						  << ", size " << next_id_
						  << ", capacity " << capacity_
						  << std::endl;
			}
#endif
		}


		void replace(ID_type id, const K &key, V value) {
#ifdef LM_APPLY_CHECKS
			if (id < 0) {
				std::cerr << "ERROR in LinkedMap::replace(): id must be >= 0" << std::endl;
				return;
			}
			if (next_id_ <= id) {
				std::cerr << "ERROR in LinkedMap::replace(): id must be < map size " << next_id_ << std::endl;
				return;
			}
#endif

#ifdef LM_DEBUG_MODE_ALLOWED
			if (debug_mode_) {
				std::cout << "LinkedMap: replace entry " << list_[id].key << " @ id pos " << id << " with key " << key << std::endl;
			}
#endif

			map_.erase(list_[id].key);
			store_[id] = std::move(value);
			list_[id].key = key;
			moveToMru(id);
			map_[key] = id;
		}


		void refreshWithKey(const K &key) {
			auto ref = map_.find(key);
			if (ref == map_.end()) {
				std::cerr << "ERROR in LinkedMap::refreshWithKey(): key " << key << " not found.";
				return;
			}

#ifdef LM_DEBUG_MODE_ALLOWED
			if (debug_mode_) {
				std::cout << "LinkedMap: refresh entry " << key << " @ id pos " << ref->second << std::endl;
			}
#endif

			// just list adjustment
			moveToMru(ref->second);
		}


		void refreshWithId(ID_type id) {
#ifdef LM_APPLY_CHECKS
			if (id < 0) {
				std::cerr << "ERROR in LinkedMap::refreshWithId(): id must be >= 0" << std::endl;
				return;
			}
			if (next_id_ <= id) {
				std::cerr << "ERROR in LinkedMap::refreshWithId(): id must be < map size " << next_id_ << std::endl;
				return;
			}
#endif

#ifdef LM_DEBUG_MODE_ALLOWED
			if (debug_mode_) {
				std::cout << "LinkedMap: refresh entry @ id pos " << id << std::endl;
			}
#endif

			// just list adjustment
			moveToMru(id);
		}


		V *get(ID_type id) {
#ifdef LM_APPLY_CHECKS
			if (id < 0) {
				std::cerr << "ERROR in LinkedMap::get(): id must be >= 0" << std::endl;
				return nullptr;
			}
			if (next_id_ <= id) {
				std::cerr << "ERROR in LinkedMap::get(): id must be < map size " << next_id_ << std::endl;
				return nullptr;
			}
#endif

			// not const since client may/will change value
			return &(store_[id]);
		}


		/**
		 * Lookup by given key.
		 * @param key
		 * @return id or kNone if not found
		 */
		ID_type find(const K &key) const {
			auto ref = map_.find(key);
			if (ref == map_.end()) {
				return kNone;
			}

			return ref->second;
		}


		/**
		 * Lookup by traversal of the linked list in LRU -> MRU direction. The first id is returned that
		 * matches the provided predicate. Actual LRU and/or an amount of elements starting at MRU can be
		 * excluded from search.
		 * @param predicate
		 * @param exclude_lru
		 * @param reserved_mru_count (>= 0)
		 * @return id or kNone if not found
		 */
		ID_type findFirstWithPredicate(predicate_type predicate, bool exclude_lru, ID_type reserved_mru_count) const {
			if (reserved_mru_count < 0) {
				reserved_mru_count = 0;
			}

			ID_type max = next_id_ - reserved_mru_count;
			ID_type count = 0;
			ID_type current = first_;

			if (exclude_lru) {
				if (max < 2) {
					return kNone;
				}

				current = list_[current].next;
				++count;
			}

			while (count < max) {
				if (predicate(store_[current])) {
					return current;
				}
				current = list_[current].next;
				++count;
			}

			// default
			return kNone;
		}


		ID_type capacity() const {
			return capacity_;
		}

		ID_type size() const {
			return next_id_;
		}

		ID_type getLruId() const {
			return first_;
		}

		ID_type getMruId() const {
			return last_;
		}

		void printList(std::ostream *out) const {
			ID_type max = next_id_; // all, without exclusion of reserved MRU
			ID_type count = 0;
			ID_type current = first_;
			*out << std::endl << "LinkedMap, size " << max << ", LRU ID: " << getLruId() << ", MRU ID: " << getMruId() << std::endl;
			if (0 < max) {
				*out << "list of stored elements, order: from LRU to MRU" << std::endl;
			}
			while (count < max) {
				*out << count << ": ID " << current << ", key " << list_[current].key << std::endl;
				current = list_[current].next;
				++count;
			}
		}

	private:
		struct ListInfo {
			K key;
			ID_type prev;
			ID_type next;
		};

		ID_type capacity_;
		ID_type next_id_ = 0;
		ID_type first_ = kNone;
		ID_type last_ = kNone;

		std::vector<V> store_;               // id -> to actual data
		std::vector<ListInfo> list_;         // id -> associated list info
		std::unordered_map<K, ID_type> map_; // key -> id

		bool debug_mode_;

		// internal list handling
		inline void moveToMru(ID_type id)  {
			// move to end of list -> becomes MRU
			ID_type prev = list_[id].prev;
			ID_type next = list_[id].next;

			if (0 <= prev) {
				list_[prev].next = next;
			} else {
				first_ = next;
			}

			if (0 <= next) {
				list_[next].prev = prev;
			} else {
				last_ = prev;
			}

			addAsMru(id);
		}

		inline void addAsMru(ID_type id) {
			if (0 <= last_) {
				list_[last_].next = id;
			}

			list_[id].prev = last_;
			list_[id].next = kNone;
			last_ = id;

			if (first_ < 0) {
				first_ = id;
			}
		}

	};

}

#endif //TOOLBOX_UTILS_LINKED_MAP_H_
