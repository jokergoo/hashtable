#ifndef __HASH_ENV__
#define __HASH_ENV__

#include <Rcpp.h>

template <typename TRcppVector>
TRcppVector internal_hash_env_values(Environment env, CharacterVector keys) {
	int n = keys.size();
	TRcppVector res(n);

	for(int i = 0; i < n; i ++) {
		std::string key = Rcpp::as<std::string>(keys[i]);
		if(env.exists(key)) {
			RObject x = env.get(key);
			TRcppVector v = as<TRcppVector>(x);
			res[i] = v[0];
		} else {
			Rcpp::stop("key: " + key + " not found.");
		}
	}
	return res;
}


template <typename TRcppVector, typename RType>
Environment internal_hash_env_set_values(Environment env, CharacterVector keys, TRcppVector values) {
	int n = keys.size();
	for(int i = 0; i < n; i ++) {
		std::string key = Rcpp::as<std::string>(keys[i]);
		RType v = values[i];
		env.assign(key, v);
	}

	return env;
}



#endif
