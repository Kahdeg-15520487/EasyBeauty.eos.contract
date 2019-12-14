#include <eosio/eosio.hpp>

using namespace std;
using namespace eosio;

class [[eosio::contract("store.data")]] eva_store : public contract {
  public:
    using contract::contract;

    ACTION transact(name user, string transactionId, string from, string to, string hash);
    ACTION updatecoin(name user, string userId, uint64_t coin, int key);
    ACTION addreview(name user, string reviewId, string transactionId, string hash);
    ACTION adddiscount(name user, string transactionId,string userId,int percent);

  private:
    TABLE transactions {
      uint64_t  key;
      string transactionId;
      string  from;
      string  to;
      string  hash;
      uint64_t  primary_key() const { return key; }
    };
    typedef multi_index<name("transactions"), transactions> transactions_table;

    TABLE coins{
      uint64_t key;
      string userId;
      uint64_t coin;
      uint64_t  primary_key() const { return key; }
    };
    typedef multi_index<name("coins"), coins> coins_table;

    TABLE reviews{
      uint64_t key;
      string transactionId;
      string reviewId;
      string hash;
      uint64_t  primary_key() const { return key; }
    };
    typedef multi_index<name("reviews"), reviews> reviews_table;

    TABLE discounts{
      uint64_t key;
      string transactionId;
      string userId;
      uint64_t percent;
      uint64_t  primary_key() const { return key; }
    };
    typedef multi_index<name("discounts"), discounts> discounts_table;
};
