#include "function_priority.hpp"
#include <limits>

cuttle::function_priority_t cuttle::push(
	cuttle::function_priorities_t &priors, cuttle::function_priority_t prior, std::string func_name, int direction = 1
) {
	using namespace cuttle;
	if (priors.prior_to_func.find(prior) != priors.prior_to_func.end()) {
		if (push(priors, prior + direction, priors.prior_to_func[prior])
			== FUNCTION_PRIORITY_UNKNOWN
		) {
			if (push(priors, prior + direction, priors.prior_to_func[prior])
				== FUNCTION_PRIORITY_UNKNOWN
			) {
				throw std::runtime_error("not enough space for this function priority");
			}
		}
	}
	if (priors.func_to_prior.find(func_name) != priors.func_to_prior.end()) {
		priors.prior_to_func.erase(priors.func_to_prior[func_name]);
	}
	priors.prior_to_func[prior] = func_name;
	priors.func_to_prior[func_name] = prior;
}

cuttle::function_priority_t push(
	const cuttle::function_priorities_t &priors,
	const std::string& func_name, const std::string& func_name_before, const std::string& func_name_after
) {
	using namespace cuttle;
	if (push(priors,
		(priors.func_to_prior[func_name_before] + priors.func_to_prior[func_name_after]) / 2,
		func_name) == FUNCTION_PRIORITY_UNKNOWN
	) {
		throw std::runtime_error("not enough space for this function priority");
	}
}

cuttle::function_priority_t compare(const cuttle::function_priorities_t &priors, const std::string& func_name1, const std::string& func_name2)
{
	using namespace cuttle;
}