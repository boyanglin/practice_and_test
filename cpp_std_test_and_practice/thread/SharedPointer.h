#ifndef SHARED_POINTER_H_
#define SHARED_POINTER_H_

#include <memory>

namespace SharedPointer {
	template<class T>
	bool ifTwoSharedPtrTheSame(const std::shared_ptr<T>& target1, const std::shared_ptr<T>& target2) {
		if (target1 == nullptr || target2 == nullptr)
			return false;
		T* pTarget1 = target1.get();
		T* pTarget2 = target2.get();
		return pTarget1 == pTarget2;
	}
}

#endif